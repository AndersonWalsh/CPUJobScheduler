// File: heap.h
// Purpose: An implementation of a heap using a vector-based binary tree

#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<algorithm>

template<class E>
class Heap{
public:
	//return true if the heap is empty
	bool isEmpty() const{
		return _tree.size() == 0;
	}
	//return the size of the container
	int size() const{
		return _tree.size();
	}
	//get root of tree, set root of tree
	//purpose: tree doesnt need to be reorganized if root 
	//needs to be accessed, changed, and then put back
	void setRoot(const E& item){
		_tree[0] = item;
		//_tree.push_back(item);
	}
	E getRoot(){
		return _tree[0];
	}
	//return true if the heap condition is met beteen 2 elements
	virtual bool isHeap(const E& root, const E& child)=0;
	//return the direction of the most extreme element, 0 - left, 1 - right
	virtual int extreme(const E& left, const E& right)=0;
	//add something to the heap
	void add(const E& item){
		//add the item to the end of the tree
		_tree.push_back(item);
		//get the index and parent of the item
		int i = _tree.size()-1;
		int p = (i-1)/2;
		
		//bubble until the heap is satisfied 
		while(i != 0 && !isHeap(_tree[p], _tree[i])){
			std::swap(_tree[p], _tree[i]);
			i = p;
			p = (i-1)/2;
		}
	}
	//remove top element from the heap
	E remove(){
		E result = _tree[0];
		//swap the last item to the root of the tree
		_tree[0] = _tree[_tree.size()-1];
		_tree.pop_back();
		//start the root and bubble down
		int i = 0;
		bool valid = false;
		
		while(!valid){
			//compute children
			int l = 2*i+1;
			int r = 2*i+2;
			//if we are a leaf node, we are automatically valid
			if(l >= _tree.size()){
				valid = true;
				continue;
			}
			//get the bubble direction
			int direction = 0;
			if(r < _tree.size()){
				direction = extreme(_tree[l], _tree[r]);
			}
			//bubble in that direction
			if(direction == 0 && !isHeap(_tree[i], _tree[l])){
				std::swap(_tree[i], _tree[l]);
				i = l;
			}
			else if(!isHeap(_tree[i], _tree[r])){
				std::swap(_tree[i], _tree[r]);
				i = r;
			}
			else{
				valid = true;
			}
		}
		return result;
	}
private:
	std::vector<E> _tree;
};

template<class E>
class Min_Heap : public Heap<E>{
	
	//return true if the heap condition is met beteen 2 elements
	virtual bool isHeap(const E& root, const E& child){
		return root < child;
	}
	//return the direction of the most extreme element, 0 - left, 1 - right
	virtual int extreme(const E& left, const E& right){
		if(left < right) return 0;
		else return 1;
	};
};

template<class E>
class Max_Heap : public Heap<E>{
	
	//return true if the heap condition is met beteen 2 elements
	virtual bool isHeap(const E& root, const E& child){
		return child < root;
	}
	//return the direction of the most extreme element, 0 - left, 1 - right
	virtual int extreme(const E& left, const E& right){
		if(right < left) return 0;
		else return 1;
	};
};






#endif
