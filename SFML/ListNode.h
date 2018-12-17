#pragma once
#include "Header.h"
#include "Bullet.h"


template <typename T>
class ListNode {

public:
	ListNode(T & bullet);
	T object;
	ListNode* next;
	
};

template <typename T>
class myList {
public:
	myList();
	~myList();
	ListNode<T> * pHead;
	int length;
	void insertAtFront(T bullet);
	void deleteLastNode();
	void deleteNode(ListNode<T> * node);
	ListNode<T> * getEndOfList();
};

template <typename T>
myList<T>::myList() {
	this->pHead = NULL;
	this->length = 0;
}

template <typename T>
void myList<T>::insertAtFront(T bullet) {// takes a bullet object and inserts it into the front of the list
	this->length += 1;
	ListNode<T> * temp = new ListNode<T>(bullet);
	ListNode<T> * tempCount = this->pHead;
	if (this->pHead == NULL) {
		this->pHead = temp;
		temp->next = NULL;
		
	}
	else {
		temp->next = this->pHead;
		this->pHead = temp;
	}
}


template <typename T>
void myList<T>::deleteLastNode() {// deletes last node in the list

	ListNode<T> * temp = this->pHead;
	int listLength = this->length;
	if (listLength == 1) {
		this->pHead = NULL;
		delete temp;
	}
	else if (listLength == 2) {
		ListNode<T> * temp2 = this->pHead;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp2->next = NULL;

		
		delete temp;
	}
	else {
		while (temp->next->next != NULL) {
			temp = temp->next;
		}
		ListNode<T> * temp3 = temp->next;
		temp->next = NULL;
		delete temp3;
	}
	this->length -= 1;
}

template <typename T>
void myList<T>::deleteNode(ListNode<T> * node) {// deletes a specific node from the list
	ListNode<T> * temp = this->pHead;
	if (this->length == 1) {// if list is only one long then just set the head to null
		this->pHead = NULL;
		delete node;
	}
	else if (node == temp) {// if node to be deleted is the head, then make the head the next node, assuming the list is more than one node long
		this->pHead = temp->next;
		delete node;
	}
	else if (node->next == NULL) {// if node to be deleted is the last node then set the previous nodes next pointer to null
		ListNode<T> * temp2 = this->pHead;
		while (temp2->next != node) {
			temp2 = temp2->next;
		}
		temp2->next = NULL;
		delete node;
	}
	else {// otherwise go to the node before the node to be deleted and set that nodes pointer to the node after the node to be deleted
		while (temp->next != node) {
			temp = temp->next;
		}
		temp->next = temp->next->next;
		delete node;
	}
	this->length -= 1;// decrease length of list
}

template <typename T>
ListNode<T>::ListNode(T & object) {
	this->object = object;
	this->next = NULL;
}


template <typename T>
myList<T>::~myList() {
	ListNode * current = this->pHead;
	while (current != 0) {
		ListNode * next = current->next;
		delete current;
		current = next;
	}
}

template <typename T>
ListNode<T> * myList<T>::getEndOfList() {// returns the last node in the list
	ListNode<T>* temp = this->pHead;
	int counter = 0;

	while (temp->next != NULL) {
		temp = temp->next;
	}
	return temp;
}