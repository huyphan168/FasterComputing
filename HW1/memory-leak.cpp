// memory_leak_example.cpp
#include <memory>

struct Node {
    int data;
    Node* Next;
};

int main() {
    Node *root = new Node; // Using raw pointer instead of unique_ptr
    Node *current = root;
    for (int i = 0; i < 1000; ++i) {
        current->Next = new Node; // Using raw pointer instead of unique_ptr
        current = current->Next;
    }
    delete root; // Only deleting the root, not the rest of the list
    return 0;
}
