#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {

    private:
        int nelem;
	BSNode<T>* root;	
	BSNode<T>* search(BSNode<T>* n, T e) const{
	       if(n == nullptr)
		       throw std::runtime_error("Elemento no encontrado!");
	       else if(n->elem < e)
		       return search(n->right, e);
	       else if(n->elem > e)
		       return search(n->left, e);
	       else
		       return n;
	}
	
	BSNode<T>* insert(BSNode<T>* n, T e){
	       if(n == nullptr)
	       	       n = new BSNode(e);
	       else if(n->elem == e)
		       throw std::runtime_error("Elemento duplicado!");
	       else if(n->elem < e)
		       n->right = insert(n->right, e);
	       else
		       n->left = insert(n->left, e);
	       return n;	
	}
	
	void print_inorder(std::ostream &out, BSNode<T>* n) const{
	  
	       
	       if(n->right != nullptr)
		       print_inorder(out, n->right);
	       if(n->left != nullptr)
		       print_inorder(out, n->left);
	       out << n->elem << " ";
	}
	
	BSNode<T>* remove(BSNode<T>* n, T e){
	       if(n == nullptr)
		       throw std::runtime_error("Elemento no encontrado!");
	       else if(n->elem < e)
		       n->right = remove(n->right, e);
	       else if(n->elem > e)
		       n->left = remove(n->left, e);
	       else{
		       if(n->right != nullptr && n->left != nullptr){
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			}
			else{
				if(n->left != nullptr)
					n = n->left;
				else
					n = n->right;
			}
		}
	return n;
	}
	
	T max(BSNode<T>* n)const{
		if(n == nullptr)
			throw std::runtime_error("");
		else if(n->right != nullptr)
			return max(n->right);
		else
			return n->elem;
			
	}
	
	T min(BSNode<T>* n) const {
        if (n == nullptr)
            throw std::runtime_error("Árbol vacío!");
        else if (n->left != nullptr)
            return min(n->left);  
        else
            return n->elem;       
    }

	BSNode<T>* remove_max(BSNode<T>* n){
		if(n->right == nullptr)
			return n->left;
		else{
			n->right = remove_max(n->right);
			return n;
		}
	}
	
	void delete_cascade(BSNode<T>* n){
		if(n == nullptr)
			return;
		delete_cascade(n->left);
		delete_cascade(n->right);
		delete n;
	}
	
	void sumTree(BSNode<T>* node, BSTree<T>& result) const {
        	if (node == nullptr) return;
        	try {
           	T current = result.search(node->elem);
            	result.remove(node->elem);
            	result.insert(current + node->elem);
        } catch (std::runtime_error&) {
            result.insert(node->elem);
        }
        sumTree(node->left, result);
        sumTree(node->right, result);
    	}
	



    public:	
        BSTree(){
		nelem = 0;
		root = nullptr;
	}
	
	~BSTree(){
		delete_cascade(root);
	}
	
	int size() const{
		return nelem;
	}

	
	
	void prune(){
		if (root == nullptr) {
    			return; 
		}
		T minValue = min(root); 
		T maxValue = max(root);
	
		remove(minValue);
		remove(maxValue);
	
	}

	
	
	T search(T e) const{
		BSNode<T>* aux = search(root, e);
		return aux->elem;
	}
	
	T operator[](T e) const{
		return search(e);
	}
	
	void insert(T e){
		root = insert(root, e);
		nelem++;
	}
	
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		if(bst.root != nullptr)
			bst.print_inorder(out, bst.root); 
		return out;
	}
	
	void remove(T e){
		remove(root, e);
		nelem--;
	}
	
		
	
	BSTree<T> sum(const BSTree<T>& other) const {
    		BSTree<T> result;
    		sumTree(this->root, result);
    		sumTree(other.root, result);
    		return result;
	}
	};
	

#endif

