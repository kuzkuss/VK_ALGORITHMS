/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми.
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.
1_2. Для разрешения коллизий используйте двойное хеширование.
*/

#include <vector>
#include <iostream>
#include <cassert>
using std::vector;
using std::string;

const int INIT_SIZE = 8;
const int HASH_CONSTANT = 137;

struct StringHasher {
	unsigned int operator()(const string& key) const {
		unsigned int hash = 0;
		for(unsigned int i = 0; i < key.length(); ++i)
			hash = hash * HASH_CONSTANT + key[i];
		return hash;
	}
};

struct StringHasherPos {
	unsigned int operator()(const string& key) const {
        unsigned int len = key.size();
        if (len % 2 == 0) {
            ++len;
        }
		return len;
	}
};

template<class T, class H = StringHasher, class HP = StringHasherPos>
class HashTable {
public:
	HashTable(int initSize, const H& _hasher = StringHasher(), const HP& _hasherPos = StringHasherPos());
	~HashTable() = default;

	bool Has(const T& key) const;
	bool Add(const T& key);
	bool Delete(const T& key);

private:
    typedef enum {Empty, Key, Deleted} state_t;
	struct HashTableCell {
		T KeyValue;
		state_t CellState;
		unsigned int Hash;
		unsigned int HashPos;

		HashTableCell() : KeyValue(T{}), CellState(Empty), Hash(0), HashPos(0) {}
		HashTableCell(const T& keyValue, state_t state, unsigned int hash, unsigned int hashPos) :
			KeyValue(keyValue), CellState(state), Hash(hash), HashPos(hashPos) {}
	};
	H hasher;
    HP hasherPos;
	vector<HashTableCell> table;
	unsigned int keysCount;

	void growTable();
};

template<class T, class H, class HP>
HashTable<T, H, HP>::HashTable(int initSize, const H& _hasher, const HP& _hasherPos) :
	hasher(_hasher),
    hasherPos(_hasherPos),
	table(initSize),
	keysCount(0)
{
}

template<class T, class H, class HP>
bool HashTable<T, H, HP>::Has(const T& key) const {
	unsigned int hash = hasher(key) % table.size();
    unsigned int pos = hasherPos(key) % table.size();
    for (unsigned int i = 0; table[hash].CellState != Empty && i < table.size(); hash = (hash + pos) % table.size(), ++i) {
        if (table[hash].CellState == Key && table[hash].KeyValue == key) {
            return true;
        }
    }

    return false;
}

template<class T, class H, class HP>
bool HashTable<T, H, HP>::Add(const T& key) {
	if (keysCount > 0.75 * table.size()) {
		growTable();
	}

	unsigned int absHash = hasher(key);
	unsigned int absHashPos = hasherPos(key);
	unsigned int hash = absHash % table.size();
	unsigned int pos = absHashPos % table.size();
	unsigned int deletedCell = 0;
	bool findDeleted = false;
	
	for (unsigned int i = 0; table[hash].CellState != Empty && i < table.size(); hash = (hash + pos) % table.size(), ++i) {
		if (table[hash].CellState == Key && key == table[hash].KeyValue) {
			return false;
		}
		if (table[hash].CellState == Deleted && !findDeleted) {
			deletedCell = hash;
			findDeleted = true;
		}
    }

	if (findDeleted) {
		table[deletedCell] = HashTableCell(key, Key, absHash, absHashPos);
	} else {
		table[hash] = HashTableCell(key, Key, absHash, absHashPos);
	}

	++keysCount;

	return true;
}

template<class T, class H, class HP>
bool HashTable<T, H, HP>::Delete(const T& key) {
	unsigned int hash = hasher(key) % table.size();
	unsigned int pos = hasherPos(key) % table.size();
    for (unsigned int i = 0; table[hash].CellState != Empty && i < table.size(); hash = (hash + pos) % table.size(), ++i) {
        if (table[hash].CellState == Key && table[hash].KeyValue == key) {
			table[hash].CellState = Deleted;
			--keysCount;
            return true;
        }
    }

	return false;
}

template<class T, class H, class HP>
void HashTable<T, H, HP>::growTable() {
	vector<HashTableCell> newTable(table.size() * 2);
	for(unsigned int i = 0; i < table.size(); ++i) {
		if (table[i].CellState == Key) {
			HashTableCell cell = table[i];
			unsigned int newHash = cell.Hash % newTable.size();
			unsigned int newPos = cell.HashPos % newTable.size();
			while (newTable[newHash].CellState != Empty) {
				newHash = (newHash + newPos) % newTable.size();
			}
			newTable[newHash] = cell;
		}
	}
	table = std::move(newTable);
}

void run(std::istream &inputStream, std::ostream &outputStream) {
	HashTable<string> table(INIT_SIZE);
	char operation;
	string word;
	while(inputStream >> operation >> word) {
		switch (operation) {
			case '+':
				outputStream << (table.Add(word) ? "OK" : "FAIL") << std::endl;
				break;
			case '?':
				outputStream << (table.Has(word) ? "OK" : "FAIL") << std::endl;
				break;
			case '-':
				outputStream << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
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
