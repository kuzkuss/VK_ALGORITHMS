/*
Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K
добавляется в правое поддерево root;иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

2_1. Выведите элементы в порядке in-order (слева направо).
*/

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
	void TraverseDfsInOrder(void (*visit)(const T& key));

private:
	struct Node {
		Node* Left;
		Node* Right;
		T Key;
		Node(const T& key) : Left(nullptr), Right(nullptr), Key(key) {}
	};
	Node* root;
	Compare cmp;
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
void BinaryTree<T, Compare>::TraverseDfsInOrder(void (*visit)(const T& key)) {
	std::stack<Node *> Stack;
    Node *cur = root;

    while (cur != nullptr || !Stack.empty()) {
        while (cur != nullptr) {
            Stack.push(cur);
            cur = cur->Left;
        }

        cur = Stack.top();
        Stack.pop();

        visit(cur->Key);
        cur = cur->Right;
    }
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    size_t size = 0;
    assert(inputStream >> size);
    assert(size > 0);

	BinaryTree<int> tree;
    for (size_t i = 0; i < size; ++i) {
        int num = 0;
        assert(inputStream >> num);
        tree.Add(num);
    }

	tree.TraverseDfsInOrder([](const int& key) { std::cout << key << " "; });
}

int main() {
    run(std::cin, std::cout);
	return 0;
}

