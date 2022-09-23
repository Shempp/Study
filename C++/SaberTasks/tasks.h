#pragma once

#include <string>
#include <cstdio>

namespace tasks {
    struct ListNode {
        ListNode* prev;
        ListNode* next;
        ListNode* rand; // a pointer to an arbitrary element of the given list, or NULL
        std::string data;
    };

    /*
    * The implementation of the List container (except for the Serialize and Deserialize methods)
    * was added only for testing within the original task and does not claim to be complete implementation
    */
    class List {
    public:
        List();
        ~List();

        List(const List&) = delete;
        List(List&&) = delete;

        List& operator=(const List&) = delete;
        List& operator=(List&&) = delete;

        bool Empty() const;
        int Size() const;

        std::string Front() const;
        void PushFront(std::string val);
        void PopFront();

        std::string Back() const;
        void PushBack(std::string val);
        void PopBack();

        void SetRandomLink(int pos, int randPos);

        void Serialize(FILE* file); // save to file (file opened with fopen(path, "wb"))
        void Deserialize(FILE* file); // loading from file (file opened with fopen(path, "rb"))
    private:
        ListNode* head;
        ListNode* tail;
        int count;
    };

    void PrintBinary(long long number);
    void RemoveDups(char* str);
}
