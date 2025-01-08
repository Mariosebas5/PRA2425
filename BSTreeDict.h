#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
		tree = new BSTree<TableEntry<V>>();
	}
	~BSTreeDict(){
		delete tree;
	}
	void insert(std::string key, V value) override{
		TableEntry<V> *aux = new TableEntry<V>(key, value);
		tree->insert(*aux);
		delete aux;
	}
	V search(std::string key) override{
		return (tree->search(key)).value;
	}
	V remove(std::string key) override{
		V valor = search(key);
	       	tree->remove(key);
		return valor;
	}
	int entries() override{
		return tree->size();
	}
	friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
                out << *(bs.tree);
                return out;
        }
        V operator[](std::string key){
                return search(key);
        }
};


#endif
