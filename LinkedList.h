#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <iostream>

using namespace std;

template <class T> class LinkedList {

public:
	LinkedList();
	virtual ~LinkedList();

	string toString();
	int getNumberOfItems();
	void deleteItem(string);
	bool isContain(string);
	void free();

	void add(T* item) {
		Node* toAdd = new Node;

		if(head == NULL) { //If the list is empty
			toAdd->next = NULL;
			head = toAdd;
		}
		else {
			toAdd->next = head;
			head = toAdd;
		}

		head->data = item;

		numberOfItems++;
	}
	
	// Returns a pointer to an item with the given id
	T* get(string id) {
		Node* temp = head;

		while(temp != NULL) {
			if(temp->data->getId() == id) {
				return temp->data;
			}

			temp = temp->next;
		}

		return NULL;
	}
	
	// Returns a pointer to an item in the given index;
	T* getByIndex(int index) {
		Node* temp = head;
		
		for(int i = 0; temp != NULL; i++) {
			if(i == index) {
				return temp->data;
			}
			
			temp = temp->next;
		}

		return NULL;
	}

private:
	struct Node {
		T* data;
		Node* next;
	};

	Node* head;

    int numberOfItems;
	void freeData(Node*);
	void freeNode(Node*);
};

#endif /* LINKEDLIST_H_ */
