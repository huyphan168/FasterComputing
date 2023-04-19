#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> Next;
};

int main() {
    Node *root = new Node;
    Node *current = root;
    for (int i = 0; i < 100000; ++i) {
        current->Next = std::make_unique<Node>();
        current = current->Next.get();
    }
    delete root;
    return 0;
}
