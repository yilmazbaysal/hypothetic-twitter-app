#include "LinkedList.h"
#include "User.h"
#include "Post.h"

using namespace std;

template <typename T> LinkedList<T>::LinkedList() {
    head = NULL; // NULL will represent the end of the list
    numberOfItems = 0;
}

//Returns the number of items which are stored in this list
template <typename T> int LinkedList<T>::getNumberOfItems() {
    return numberOfItems;
}

//Deletes an item with the given id number
template <typename T> void LinkedList<T>::deleteItem(string id) {
    Node *currNode = head, *prevNode = NULL;

    while(currNode != NULL) {
        if (currNode->data->getId() == id) {
            if (currNode == head) { // If item is head->data (first item in the list)
                head = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }

            delete currNode;
            numberOfItems--;
            return;
        }

        prevNode = currNode;
        currNode = currNode->next;
    }
}

// Checks if an item with the given id exists or not
template <typename T> bool LinkedList<T>::isContain(string id) {

    if(get(id) != NULL) {
        return true;
    }

    return false;
}

// Calls the toString methods of the all stored items
template <typename T> string LinkedList<T>::toString() {
    Node* temp = head;
    string str;

    while(temp != NULL) {
        str += temp->data->toString() + "\n";

        temp = temp->next;
    }

    return str;
}

//Start point to recursive call of freeNode method
template <typename T> void LinkedList<T>::free() {
    freeData(head);
}

//Deallocates the memory of datas recursively (starts from the last Node)
template <typename T> void LinkedList<T>::freeData(Node* toDelete) {
    if(toDelete == NULL)
        return;
    else
        freeData(toDelete->next);

    delete toDelete->data;
}

//Deallocates the memory of nodes recursively (starts from the last Node)
template <typename T> void LinkedList<T>::freeNode(Node* toDelete) {
    if(toDelete == NULL)
        return;
    else
        freeNode(toDelete->next);

    delete toDelete;
}

template <typename T> LinkedList<T>::~LinkedList() {
    freeNode(head);
}

// Types that T can be
template class LinkedList<User>;
template class LinkedList<Post>;
