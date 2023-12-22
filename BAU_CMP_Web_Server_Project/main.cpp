#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <queue>
#include <utility>

using namespace std;

class HashTable
{
private:
    int size_;
    vector<vector<pair<string, int>>> table_;

    int hash_function(const string &key)
    {
        int hash = 0;
        for (char c : key)
        {
            hash = (hash * 31 + c) % size_;
        }
        return hash;
    }

public:
    HashTable(int size) : size_(size), table_(size) {}

    void insert(const string &key, int value)
    {
        int index = hash_function(key);
        for (auto &p : table_[index])
        {
            if (p.first == key)
            {
                p.second = value;
                return;
            }
        }
        table_[index].emplace_back(key, value);
    }

    int get(const string &key)
    {
        int index = hash_function(key);
        for (auto &p : table_[index])
        {
            if (p.first == key)
            {
                return p.second;
            }
        }
        return 0; // Key not found
    }

    vector<vector<pair<string, int>>> get_all_elements()
    {
        return table_;
    }
};

// Function to read the log file and populate the hash table
void processLogFile(const string &filename, HashTable &table)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        size_t pos = line.find("GET");
        if (pos != string::npos)
        {
            string key = line.substr(pos + 4, line.find(" ", pos + 4) - (pos + 4));
            int currentCount = table.get(key);
            table.insert(key, currentCount + 1);
        }
    }

    file.close();
}

// Function to find the top 10 most visited pages using a max heap
void findTop10(HashTable &table, vector<pair<int, string>> &top10)
{
    auto all_elements = table.get_all_elements();
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    for (const auto &bucket : all_elements)
    {
        for (const auto &entry : bucket)
        {
            pq.push(make_pair(entry.second, entry.first));
            if (pq.size() > 10)
            {
                pq.pop();
            }
        }
    }

    while (!pq.empty())
    {
        top10.insert(top10.begin(), pq.top());
        pq.pop();
    }
}

int main()
{
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

    HashTable table(1000);

    processLogFile("/Users/ahmetemreparmaksiz/Desktop/BAU_CMP_Web_Server_Project/access_log", table);

    vector<pair<int, string>> top10;
    findTop10(table, top10);

    chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_time = chrono::duration_cast<chrono::duration<double>>(end - start);

    cout << "Top 10 most visited pages:" << endl;
    for (const auto &entry : top10)
    {
        cout << entry.second << " #" << entry.first << endl;
    }

    cout << "Total elapsed time: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}
