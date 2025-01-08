#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
	    std::string key;
	    V value;
	    TableEntry(std::string key, V value){
	   	this->key = key;
		this->value = value;
	    }
	    TableEntry(std::string key){
		this->key = key;
	    }
	    TableEntry(){
		key = "";
	    }
	    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
		    if(te1.key == te2.key)
			    return true;
		    else
			    return false;
	    }
	    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
  		    if(te1.key != te2.key)
                            return true;
                    else
                            return false;
	    }
	    friend std::ostream&operator<<(std::ostream &out, const TableEntry<V> &te){
		   out << "('" << te.key << "' => " << te.value << ")";
		   return out;	
	    }
	    friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){
		    if(te1.key < te2.key)
			return true;
	    	    else
			return false;
	    }
	    friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
		    if(te1.key > te2.key)
			    return true;
		    else
			    return false;
	    }
};

#endif
