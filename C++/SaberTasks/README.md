# Task 1

Write a function that takes a signed integer as input and prints its binary representation without using library classes or functions.

# Task 2

Write a function to remove consecutively duplicate characters in a string:

```cpp
void RemoveDups(char* str);

// ...

char data[] = “AAA BBB AAA”;
RemoveDups(data);
printf(“%s\n”, data); // “A B A”
```

# Task 3

Implement functions to serialize and deserialize a doubly linked list in binary format to a file. The algorithmic complexity of the solution must be less than the quadratic one.

Note: Serialization means saving and restoring the complete structure of the list, including the relative relationship of its elements to each other.

```cpp
// ListNode structure cannot be modified
struct ListNode {
    ListNode * prev;
    ListNode * next;
    ListNode * rand; // a pointer to an arbitrary element of the given list, or NULL
std::string data;
};
class List {
public:
    void Serialize (FILE * file); // save to file (file opened with fopen(path, "wb"))
        void Deserialize (FILE * file); // load from file (file opened with fopen(path, "rb"))
private:
    ListNode * head;
```