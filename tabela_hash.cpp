#include <iostream>
#include <vector>
#include <list>
#include <string>

using std:: string;
using std:: vector;
using std:: list;
using std:: endl;
class Node {
public:
    Node(string& key, int value) : key(key), value(value) {}  //cada nó tem uma chave e um valor
    string key;
    int value;
};

class hash_duplo_encadeamento {
public:                             // tabela hash com 2 níveis de endereçamento, passando o tamamho de cada uma
    Double HashTable(int firstLevelSize, int secondLevelSize)
        : firstLevelSize(firstLevelSize), secondLevelSize(secondLevelSize) {
        firstLevel = vector<list<vector<Node>>>(firstLevelSize);
    }

    int hash_primeiro_nivel(const string& key) {
        hash<string> hasher;
        size_t hash = hasher(key);
        return hash % firstLevelSize;
    }

    int hash_segundo_nivel(const std::string& key) {
        hash<string> hasher;
        size_t hash = hasher(key);
        return hash % (secondLevelSize / firstLevelSize);
    }

    void insert(const std::string& key, int value) {    //insere valor-chave na tabela
        int firstLevelIndex = hash_primeiro_nivel(key);
        int secondLevelIndex = hash_segundo_nivel(key);

        vector<Node>& secondLevelTable = firstLevel[firstLevelIndex][secondLevelIndex];

        for (Node& node : secondLevelTable) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        secondLevelTable.emplace_back(key, value);
    }

    int get(const std::string& key) {
        int firstLevelIndex = hash_primeiro_nivel(key);  //recupera um valor com base um valor conforme a chave fornecida
        int secondLevelIndex = hash_segundo_nivel(key);

        const vector<Node>& secondLevelTable = firstLevel[firstLevelIndex][secondLevelIndex];

        for (const Node& node : secondLevelTable) {
            if (node.key == key) {
                return node.value;
            }
        }

        return -1; // Chave não encontrada
    }

    void remove(const string& key) {  //exclui um elemento com base na chave fornecida. 
        int firstLevelIndex = hash_primeiro_nivel(key);
        int secondLevelIndex = hash_segundo_nivel(key);

        vector<Node>& secondLevelTable = firstLevel[firstLevelIndex][secondLevelIndex];

        for (auto it = secondLevelTable.begin(); it != secondLevelTable.end(); ++it) {
            if (it->key == key) {
                secondLevelTable.erase(it);
                return;
            }
        }
    }

private:
    int firstLevelSize;
    int secondLevelSize;
    vector<list<vector<Node>>> firstLevel;
};

