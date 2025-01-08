#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

     private:
        int n;
	int max;
	ListLinked<TableEntry<V>>*table;
	int h(std::string key){
		int suma = 0;
		for(int i = 0; i < key.length(); i++){
			char c = key.at(i);
			int s = int(c);
			suma += s;
		}
		return suma % max;
	}
    public:
	HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n = 0;
		max = size;
	}
	~HashTable(){
		for(int i = 0; i < capacity(); i++){
       			 table[i].~ListLinked();
    	}
		delete[] table;
	}
	int capacity(){
		return max;
	}
	friend std::ostream&operator<<(std::ostream&out, const HashTable<V> &th){
		out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n" << "==============\n\n";
		for(int i = 0; i < th.max; i++){
			out << "== Cubeta " << i << " ==\n\n";
			out << th.table[i] << "\n\n";
		}
		out << "==============\n\n";
		return out;
	}
	V operator[](std::string key){
		V valor = search(key);
		return valor;
	}

	friend HashTable<V> operator+(HashTable<V>& ht1, HashTable<V>& ht2) {
   
    		int newMax = std::max(ht1.max, ht2.max);
    		HashTable<V> result(newMax);
    		for (int i = 0; i < ht1.max; i++) {
       			for (int j = 0; j < ht1.table[i].size(); j++) {
            			result.insert(ht1.table[i].get(j).key, ht1.table[i].get(j).value);
        		}
   		 }
    		for (int i = 0; i < ht2.max; i++) {
        		for (int j = 0; j < ht2.table[i].size(); j++) {
            		std::string key = ht2.table[i].get(j).key;
           	 try {
               		 result.search(key); 
           	 } catch (const std::runtime_error&) {
                
                result.insert(key, ht2.table[i].get(j).value);
            }
        }
    }

    return result;
}



	virtual void insert(std::string key, V value) {
    		int pos = h(key);
    		int poslink = table[pos].search(key);
    		if (poslink != -1) {
       		 try {
          		std::string msg = "Key '" + key + "' already exists!";
           		throw std::runtime_error(msg);
       			} catch (const std::runtime_error& e) {
       		}
  		} else {
        		TableEntry<V> newEntry(key, value);
        		table[pos].prepend(newEntry);
      			  n++;
    }
}

        virtual V search(std::string key){
		int pos = h(key);
       		int poslink = table[pos].search(key);
		if(poslink == -1){
			std::string msg = "Key '" + key + "' not found!";
			throw std::runtime_error(msg);
		}
		else
			return table[pos].get(poslink).value; 
        }
        virtual V remove(std::string key){
		int pos = h(key);
		int poslink = table[pos].search(key);
                if(poslink == -1){
			std::string msg = "Key '" + key + "' not found!";
                        throw std::runtime_error(msg);
		}
                else{
			n--;
			return table[pos].remove(poslink).value;
		}
        }
        virtual int entries(){
		int ent = 0;
		for(int i = 0; i < capacity(); i++){
			ent += table[i].size();
        	}
	return ent;
	}

};

#endif
