/*
Требование для всех вариантов Задачи 4
Решение должно поддерживать передачу функции сравнения снаружи.
4_2. Порядковые статистики. Дано число N и N строк.
Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики.
Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”.
Запрос на получение k-ой порядковой статистики задается числом k. 
Требования: скорость выполнения запроса - O(log n).
*/

#include <cassert>
#include <iostream>
#include <stack>

template <class T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) const 
    {
        if (l < r) return -1;
        if (l > r) return 1;
        return 0;
    }
};

template <class T, class Comparator = DefaultComparator<T>>
class AVLTree {
public:
    AVLTree(Comparator cmp_ = Comparator()) : root(nullptr), cmp(cmp_) {}
    
    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree& operator=(AVLTree&&) = delete;
    
    ~AVLTree();
    
    void insert(const T &key);
    
    void erase(const T &key);

    const T &findKStat(size_t k) const;
     
private:
    struct Node {
        Node* Left;
		Node* Right;
		T Key;

        size_t height;
        size_t numNodes;

		Node(const T& key) : Left(nullptr), Right(nullptr), Key(key), height(1), numNodes(1) {}
    };

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    void fixHeight(Node* node);
    void fixNumNodes(Node *node);
    size_t height(const Node* node) const;
    int bfactor(const Node* node) const;
    Node* balance(Node* node);
    Node* _insert(Node *node, const T &key);
    Node* _erase(Node *node, const T &key);
    Node* removeMin(Node* node, Node *& min);

    Node *root;
    Comparator cmp;
};

template<class T, class Comparator>
void AVLTree<T, Comparator>::insert(const T &key) {
    root = _insert(root, key);
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::erase(const T &key) {
    root = _erase(root, key);
}

template <class T, class Comparator>
AVLTree<T, Comparator>::~AVLTree() {
    if (!root){
        return;
    }

	Node *cur = root;
    std::stack<Node *> Stack;
    Stack.push(cur);
    while (!Stack.empty()){
        Node *node = Stack.top();
        Stack.pop();
        if (node->Right){
           Stack.push(node->Right);
        }
        if (node->Left){
           Stack.push(node->Left);
        }
        delete node;
    }
}

template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::rotateRight(Node* node) {
	Node* left(node->Left);
	node->Left = left->Right;
	left->Right = node;

	fixHeight(node);
    fixNumNodes(node);
	fixHeight(left);
    fixNumNodes(left);

	return left;
}

template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::rotateLeft(Node* node) {
	Node* right(node->Right);
	node->Right = right->Left;
	right->Left = node;

	fixHeight(node);
    fixNumNodes(node);
	fixHeight(right);
    fixNumNodes(right);

	return right;
}

template <class T, class Comparator>
void AVLTree<T, Comparator>::fixNumNodes(Node *node) {
    node->numNodes = 1;
    if (node->Right) {
        node->numNodes += node->Right->numNodes;
    }
    if (node->Left) {
        node->numNodes += node->Left->numNodes;
    }
}

template <class T, class Comparator>
void AVLTree<T, Comparator>::fixHeight(Node* node) {
	node->height = std::max(height(node->Left), height(node->Right)) + 1;
}

template <class T, class Comparator>
size_t AVLTree<T, Comparator>::height(const Node* node) const {
	return node ? node->height : 0;
}

template <class T, class Comparator>
int AVLTree<T, Comparator>::bfactor(const Node* node) const {
    return height(node->Right) - height(node->Left);
}

template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::balance(Node* node) {
	fixHeight(node);
    fixNumNodes(node);
    
	if (bfactor(node) == 2) {
		if(bfactor(node->Right) < 0)
			node->Right = rotateRight(node->Right);
		return rotateLeft(node);
	}

	if (bfactor(node) == -2) {
		if(bfactor(node->Left) > 0)
			node->Left = rotateLeft(node->Left);
		return rotateRight(node);
	}
	return node;
}

template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_insert(Node *node, const T &key) {
	if(!node) {
        return new Node(key);
    }

	if(cmp(key, node->Key) < 0)
		node->Left = _insert(node->Left, key);
	else
		node->Right = _insert(node->Right, key);
	return balance(node);
}

template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_erase(Node* node, const T &key) {
    if (!node) {
        return nullptr;
    }
    
    if (cmp(key, node->Key) < 0) {
        node->Left = _erase(node->Left, key);
    } else if (cmp(key, node->Key) > 0) {
        node->Right = _erase(node->Right, key);
    } else {
        Node* left = node->Left;
        Node* right = node->Right;
        
        delete node;
        
        if (!right) {
            return left;
        }
        
        Node* minNode = nullptr;
        Node* newRight = removeMin(right, minNode);
        minNode->Right = newRight;
        minNode->Left = left;
        
        return balance(minNode);
    }
    return balance(node);
}

template <class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::removeMin(Node* node, Node *& min) {
    if (!node->Left) {
        min = node;
        return node->Right;
    }

    node->Left = removeMin(node->Left, min);
    return balance(node);
}

template <class T, class Comparator>
const T &AVLTree<T, Comparator>::findKStat(size_t k) const {
    assert(root);
    assert(k < root->numNodes);

    Node *node = root;
    size_t leftSize = node->Left ? node->Left->numNodes : 0;
    while (k != leftSize) {
        if (!node->Left) {
            --k;
            node = node->Right;
            leftSize = node->Left ? node->Left->numNodes : 0;
        } else if (leftSize < k) {
            k -= leftSize + 1;
            node = node->Right;
            leftSize = node->Left ? node->Left->numNodes : 0;
        } else if (leftSize > k) {
            node = node->Left;
            leftSize = node->Left ? node->Left->numNodes : 0;
        } else {
            --k;
        }
    }

    return node->Key;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    size_t num = 0;
    assert(inputStream >> num);
    assert(num > 0);

	AVLTree<int> tree;
    for (size_t i = 0; i < num; ++i) {
        int val = 0;
        size_t k = 0;
        assert(inputStream >> val >> k);
        assert(val != 0);
        if (val > 0) {
            tree.insert(val);
        } else {
            tree.erase(-val);
        }

        std::cout << tree.findKStat(k) << std::endl;
    }
}

int main() {
    run(std::cin, std::cout);
    return 0;
}

