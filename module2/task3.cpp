/*
Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне 0..232 -1

Требования: 
B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
*/

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template<class T, class Compare = DefaultComparator<T>>
class BTree {
public:
	BTree(size_t _t, Compare _cmp = Compare()) : root(nullptr), t(_t), cmp(_cmp) {}
	~BTree() { delete root; }

	void Insert(const T& key);
    void TraverseLevelOrder(void (*visit)(const T &val, bool last));

private:
	struct Node {
		bool IsLeaf;
		std::vector<T> Keys;
		std::vector<Node*> Children;
		Node(bool isLeaf) : IsLeaf(isLeaf) {}
		~Node() { for(Node* child : Children) { delete child; } }
	};
	Node* root;
	size_t t;
    Compare cmp;

	bool isNodeFull(Node* node) const { return node->Keys.size() == 2 * t - 1; }
	void insertNonFull(Node* node, const T& key);
	void splitChild(Node* node, int pos);
};


template<class T, class Compare>
void BTree<T, Compare>::Insert(const T& key) {
	if(root == nullptr) {
		root = new Node(true);
	}
	if(isNodeFull(root)) {
		Node* newRoot = new Node(false);
		newRoot->Children.push_back(root);
		root = newRoot;
		splitChild(root, 0);
	}
	insertNonFull(root, key);
}

template<class T, class Compare>
void BTree<T, Compare>::insertNonFull(Node* node, const T& key) {
    int pos = node->Keys.size() - 1;
	if(node->IsLeaf) {
		node->Keys.resize(node->Keys.size() + 1);
		while(pos >= 0 && key < node->Keys[pos]) {
			node->Keys[pos + 1] = node->Keys[pos];
			--pos;
		}
        node->Keys[pos + 1] = key;
	} else {
		while(pos >= 0 && key < node->Keys[pos]) {
			--pos;
		}
		if(isNodeFull(node->Children[pos + 1])) {
			splitChild(node, pos + 1);
			if(key > node->Keys[pos + 1]) {
				++pos;
			}
		}
		insertNonFull(node->Children[pos + 1], key);
	}
}

template<class T, class Compare>
void BTree<T, Compare>::splitChild(Node* node, int pos) {
    Node *child = node->Children[pos];
    size_t childSize = child->Keys.size();

    int mid = childSize / 2 + childSize % 2 - 1;
    node->Keys.insert(node->Keys.begin() + pos, child->Keys[mid]);

    Node *rightNode = new Node(child->IsLeaf);
    rightNode->Keys.insert(rightNode->Keys.begin(), child->Keys.begin() + mid + 1, child->Keys.end());
    child->Keys.erase(child->Keys.begin() + mid, child->Keys.end());
    if (!rightNode->IsLeaf) {
        rightNode->Children.insert(rightNode->Children.begin(), child->Children.begin() + mid + 1, child->Children.end());
        child->Children.erase(child->Children.begin() + mid + 1, child->Children.end());
    }

    node->Children.insert(node->Children.begin() + pos + 1, rightNode);
}

template<class T, class Compare>
void BTree<T, Compare>::TraverseLevelOrder(void (*visit)(const T &val, bool last)) {
    if(!root) {
        return;
    }
    std::queue<Node*> Queue;
    Queue.push(root);
    while(!Queue.empty()) {
        Node* node = Queue.front();
        Queue.pop();
        for (auto key = node->Keys.begin(); key != node->Keys.end(); ++key) {
            Queue.empty() ? visit(*key, (key == node->Keys.end() - 1)) :
                    visit(*key, (key == node->Keys.end() - 1) && Queue.front()->Keys[0] < *key);
        }
        for (auto child = node->Children.begin(); child != node->Children.end(); ++child) {
            Queue.push(*child);
        }
    }
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    size_t t = 0;
    assert(inputStream >> t);
    assert(t >= 2);

	BTree<int> tree(t);
    int elem = 0;
    while(inputStream >> elem) {
        tree.Insert(elem);
    }

    tree.TraverseLevelOrder([](const int &val, bool last){ std::cout << val << (last ? "\n" : " "); });
}

int main() {
    run(std::cin, std::cout);
    return 0;
}

