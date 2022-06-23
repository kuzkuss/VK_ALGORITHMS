#include <cassert>
#include <iostream>
#include <stack>

struct IntCmp
{
	bool operator()(int l, int r) {return  l < r;}
};

template<class T, class Compare = IntCmp>
class BinaryTree {
public:
	BinaryTree(const Compare& _cmp = IntCmp()) : root(nullptr), cmp(_cmp) {}
	~BinaryTree();

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

	void Add(const T& key);
	int MinDistance();

private:
	struct Node {
		Node* Left;
		Node* Right;
		T Key;
		Node(const T& key) : Left(nullptr), Right(nullptr), Key(key) {}
	};
	Node* root;
	Compare cmp;

    int MinDistanceNode(Node *);
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
    if (!root){
        return;
    }
    
	Node *cur = root;
    std::stack<Node *> Stack;
    Stack.push(cur);
    while(!Stack.empty()){
        Node *node = Stack.top();
        Stack.pop();
        if(node->Right){
           Stack.push(node->Right);
        }
        if(node->Left){
           Stack.push(node->Left);
        }
        delete node;
    }
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T& key)
{
	if(root == nullptr) {
		root = new Node(key);
		return;
	}

    Node* node = root;
    Node *parent = nullptr;
	while(node != nullptr) {
        parent = node;
		if(cmp(key, node->Key)) {
			node = node->Left;
		}
		else {
			node = node->Right;
		}
	}
    node = new Node(key);
    if (parent->Key > key){
        parent->Left = node;
    } else {
        parent->Right = node;
    }
}

template<class T, class Compare>
int BinaryTree<T, Compare>::MinDistance() {
    return MinDistanceNode(root);
}

template<class T, class Compare>
int BinaryTree<T, Compare>::MinDistanceNode(Node *node) {
    if (!node) {
        return 0;
    }

    int sizeLeft = 0;
    int sizeRight = 0;
    if (node->Left) {
        sizeLeft = MinDistanceNode(node->Left);
    }
    if (node->Right) {
        sizeRight = MinDistanceNode(node->Right);
    }
    if (!node->Left && !node->Right) {
        return 1;
    }

    int result = 0;
    if (!sizeLeft || !sizeRight) {
        result = sizeLeft + sizeRight + 1;
    } else {
        result = std::min(sizeLeft, sizeRight) + 1;
    }

    return result;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
	BinaryTree<int> tree;
    int elem = 0;
    while(inputStream >> elem) {
        tree.Add(elem);
    }

	outputStream << tree.MinDistance();
}

int main() {
    run(std::cin, std::cout);
	return 0;
}

