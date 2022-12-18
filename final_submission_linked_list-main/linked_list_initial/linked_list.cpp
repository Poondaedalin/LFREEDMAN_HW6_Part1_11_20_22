
#include "linked_list.h"
#include <stdexcept>
//#include <iostream>

using namespace std;


template <typename T>
LinkedList<T>::~LinkedList() {
	delete(head);
}

template <typename T>
void LinkedList<T>::push_back(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;
	
	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	tail->next = n;
	n->prev = tail;
	tail = n;	
}


template <typename T>
void LinkedList<T>::push_front(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;

	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	head->prev = n;
	n->next = head;
	head = n;
}


template <typename T>
T LinkedList<T>::at(size_t idx){
	if(idx >= numItems){
		throw invalid_argument("List index out of range: " + to_string(idx));
	}

	Node<T> *n = get_node(idx);
	return n->data;
}


template <typename T>
Node<T> *LinkedList<T>::get_node(size_t idx){

	size_t i = 0;
	Node<T> *cur = head;
	while(i < idx){
		cur = cur->next;
		i++;
	}

	return cur;
}

template <typename T>
void LinkedList<T>::insert(size_t pos, T item) {
	// In every case, assume that we're inserting the item after, not before.
	if (pos > numItems || pos < 0) {
		throw invalid_argument("Insert index out of range: " + to_string(pos) + " > " + to_string(numItems));
	}
	if (pos == 0 && numItems == 0) {
		Node<T>* transplant = new Node<T>;
		transplant->data = item;
		head = transplant;
		numItems++;
		return;
	}
	Node<T>* curr = head;
	while (pos > 1) {
		curr = curr->next;
		pos--;
	}

	Node<T>* transplant = new Node<T>;
	transplant->data = item;

		Node<T>* temp;
		transplant->prev = curr;
		temp = curr->next;
		curr->next = transplant;
		transplant->next = temp;

		numItems++;
}



