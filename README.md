# CMP DATA STRUCTURES AND ALGORITHMS - GROUP PROJECT - 25/12/2023

C++ program reads a log file to identify and rank the most visited web pages, and measures the duration of the process for performance analysis.

# Contributors of The Group Project

- https://github.com/AEP20 (Ahmet Emre Parmaksız)
- https://github.com/Midzer00 (Ömer Dursun)
- https://github.com/denizozmen/denizozmen (Deniz Özmen)
- https://github.com/baris04 (Barış Korkmaz)

# How Does It Work?

The function aims to find the top 10 key-value pairs with the highest values in the given hash table and to store these pairs in an ordered way in the top10 vector. The use of a priority queue provides efficient selection and ordering of the pairs with the highest values. When the loops completed, the top10 vector will contain the 10 pairs having the highest values.

# Function Descriptions

- HashTable(int size):
  Constructor of the class, creates hash table in given sizes

- Hash_function ( const string &key):
  This function takes a key and returns an index indicating that the hash table should be placed in the section

- insert (const string &key, int value):
  This function adds the given key-value pair to the hash table.
  Updates the value if it already exists in the key table.

- get(const string &key):
  This function returns the value of the key (returns 0 if key is not available).

- get*all_elements*():
  This function returns all the pairs in the table

# Parameters

- HashTable &table:
  The hash table to be searched.

- vector<pair<int, string>> &top10:
  The vector that will store top 10 highest values.

# Collusion Resolution

The insert function, when a added key and its value into hash table, finds the correct section using the hash_function. If same key exists in that section, it updates the value. This prevents overwriting. If same key is not written, it writes the new pair<string, int> to end of the 'section'. This makes easy to "chaining" of different keys that have the same hash value with same section.

# Total Elapsed Time

The total elapsed time is calculated by taking the difference between the start and end times of the process. Given log file is 52.3 MB.

- with hashTable: 4.1392 seconds
- with unordered Map: 3.8291 seconds

# The Reason of the Difference Between Elapsed Times

Hash table is a broad concept, unordered_map is a special application in C++. While unordered_map provides standardized, predictable performance and features as part of C++'s Library, hash tables can be implemented in a variety of ways, which can lead to different behaviors and efficiencies.
