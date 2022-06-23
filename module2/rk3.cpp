#include <iostream>
#include <cassert>
#include <string>
#include <unordered_set>

const int HASH_CONSTANT = 137;

struct Node {
    std::string product_name;
    int color;
    int size;
};

namespace std {
  template<> struct hash<Node>
  {
    unsigned int operator()(const Node& key) const {
		unsigned int hash = 0;
		for(unsigned int i = 0; i < key.product_name.length(); ++i)
			hash = hash * HASH_CONSTANT + key.product_name[i];
		return hash;
	}
  };
}

bool operator==(const Node firstNode, const Node secondNode) {
    return firstNode.product_name == secondNode.product_name && firstNode.color == secondNode.color && firstNode.size == secondNode.size;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
	std::unordered_set<Node> table;
	char operation;
    Node node;
	while(inputStream >> operation >> node.product_name >> node.color >> node.size) {
		switch (operation) {
			case '+':
				outputStream << (table.insert(node).second ? "OK" : "FAIL") << std::endl;
				break;
			case '?':
				outputStream << (table.find(node) != table.end() ? "OK" : "FAIL") << std::endl;
				break;
			case '-':
				outputStream << (table.erase(node) ? "OK" : "FAIL") << std::endl;
				break;
			default:
				assert(false);
		}
	}
}

int main() {
    run(std::cin, std::cout);
	return 0;
}
