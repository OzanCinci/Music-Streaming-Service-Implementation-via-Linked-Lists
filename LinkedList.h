#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse = false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template <class T>
LinkedList<T>::LinkedList()
{
    size = 0;
    head = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    if (!obj.head)
    {
        size = 0;
        head = NULL;
        return;
    }

    Node<T> *p_copy = obj.head;
    Node<T> *tail = NULL;
    size = obj.size;
    head = NULL;

    for (int index = 0; index < size; index++)
    {
        Node<T> *temp = new Node<T>(p_copy->data);

        if (index == 0)
        {
            head = temp;
            temp->next = temp;
            temp->prev = temp;
            tail = head;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            temp->next = head;
            head->prev = temp;
            tail = tail->next;
            temp = NULL;
        }
        p_copy = p_copy->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    if (!head)
        return;

    Node<T> *traverser, *temp;
    traverser = head;

    for (int index = 0; index < size; index++)
    {
        if (index == 0)
            traverser->prev->next = NULL;

        temp = traverser->next;

        traverser->next = NULL;
        traverser->prev = NULL;
        delete traverser;

        traverser = temp;
    }
    head = NULL;
    size = 0;
}

template <class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <class T>
bool LinkedList<T>::contains(Node<T> *node) const
{
    Node<T> *traverser;
    traverser = head;

    for (int index = 0; index < size; index++)
    {
        if (traverser == node)
            return true;
        traverser = traverser->next;
    }
    return false;
}

template <class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    return head;
}

template <class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (!head)
        return head;
    return head->prev;
}

template <class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T> *traverser;
    traverser = head;

    for (int index = 0; index < size; index++)
    {
        if (traverser->data == data)
            return traverser;
        traverser = traverser->next;
    }
    return NULL;
}

template <class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    if (size == 0)
        return NULL;
    if (index < 0)
        return NULL;
    if (index > size - 1)
        return NULL;

    Node<T> *traverser;
    traverser = head;

    for (int i = 0; i < index; i++)
        traverser = traverser->next;
    return traverser;
}

template <class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    if (size == 0)
    {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
        size = 1;
    }
    else
    {
        Node<T> *temp = new Node<T>(data);
        temp->prev = head->prev;
        head->prev->next = temp;
        temp->next = head;
        head->prev = temp;
        size++;
        head = temp;
        temp = NULL;
    }
}

template <class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    if (size == 0)
    {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
        size = 1;
    }
    else
    {
        Node<T> *temp = new Node<T>(data);
        temp->prev = head->prev;
        head->prev->next = temp;
        temp->next = head;
        head->prev = temp;
        size++;
        temp = NULL;
    }
}

template <class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (contains(node) == false)
        return;
    size += 1;

    Node<T> *temp = new Node<T>(data);
    temp->next = node->next;
    temp->prev = node;
    node->next->prev = temp;
    node->next = temp;
    temp = NULL;
}

template <class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k)
{
    Node<T> *traverser = head;
    int times, step;

    step = k - 1;
    times = size / step;

    for (int i = 0; i < times; i++)
    {
        for (int j = 0; j < step; j++)
        {
            traverser = traverser->next;
        }
        insertAfterNode(data, traverser->prev);
    }
}

template <class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if (contains(node) == false)
        return;

    if (size == 1)
    {
        head->next = NULL;
        head->prev = NULL;
        delete head;
        head = NULL;
        size = 0;
    }
    else
    {
        if (head == node)
        {
            Node<T> *temp = head->next;
            temp->prev = head->prev;
            head->prev->next = temp;
            head->next = NULL;
            head->prev = NULL;
            delete head;
            head = temp;
            temp = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->next = NULL;
            node->prev = NULL;
            delete node;
            node = NULL;
        }
        size--;
    }
}

template <class T>
void LinkedList<T>::removeNode(const T &data)
{
    Node<T> *node = head;
    Node<T> *temp;
    int HowManyElementsLeft = size;

    while (HowManyElementsLeft)
    {
        if (node->data == data)
        {
            temp = node->next;
            removeNode(node);
            node = temp;
        }
        else
        {
            node = node->next;
        }
        HowManyElementsLeft--;
    }
}

template <class T>
void LinkedList<T>::removeAllNodes()
{
    if (!head)
        return;

    Node<T> *traverser, *temp;
    traverser = head;

    for (int index = 0; index < size; index++)
    {
        if (index == 0)
            traverser->prev->next = NULL;

        temp = traverser->next;

        traverser->next = NULL;
        traverser->prev = NULL;
        delete traverser;

        traverser = temp;
    }
    head = NULL;
    size = 0;
}

template <class T>
void LinkedList<T>::removeEveryKthNode(int k)
{
    if (k < 2)
        return;

    Node<T> *temp;
    int step, times, temp_size;
    times = size / k;
    temp_size = size - times;
    step = k - 1;
    Node<T> *traverser = head;

    for (int i = 0; i < times; i++)
    {
        for (int j = 0; j < step; j++)
        {
            traverser = traverser->next;
        }
        temp = traverser->next;
        removeNode(traverser);
        traverser = temp;
    }
    size = temp_size;
}

template <class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2)
{
    if (!contains(node1) || !contains(node2))
        return;
    if (node1 == node2)
        return;

    Node<T> *temp_next1, *temp_prev1;

    if (node1->next == node2)
    {
        node1->prev->next = node2;
        node2->next->prev = node1;
        node2->prev = node1->prev;
        node1->prev = node2;
        node1->next = node2->next;
        node2->next = node1;
        if (head == node1)
            head = node2;
        else if (node2 == head)
            head = node1;
        return;
    }
    if (node2->next == node1)
    {
        node1->prev = node2->prev;
        node2->prev = node1;
        node2->next = node1->next;
        node1->next = node2;
        node1->prev->next = node1;
        node2->next->prev = node2;
        if (head == node2)
            head = node1;
        else if (node1 == head)
            head = node2;
        return;
    }

    node1->next->prev = node2;
    node1->prev->next = node2;
    node2->next->prev = node1;
    node2->prev->next = node1;

    temp_next1 = node1->next;
    temp_prev1 = node1->prev;

    node1->next = node2->next;
    node1->prev = node2->prev;
    node2->next = temp_next1;
    node2->prev = temp_prev1;

    temp_next1 = NULL;
    temp_prev1 = NULL;
    if (node1 == head)
        head = node2;
    else if (node2 == head)
        head = node1;
}

template <class T>
void LinkedList<T>::shuffle(int seed)
{
    int i;
    for (i = 0; i < size; i++)
        swap(getNodeAtIndex(i), getNodeAtIndex((i * i + seed) % size));
}

template <class T>
void LinkedList<T>::print(bool reverse) const
{
    if (this->isEmpty())
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse)
    {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do
        {
            std::cout << *node << std::endl;
            node = node->prev;
        } while (node != this->getLastNode());
    }
    else
    {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do
        {
            std::cout << *node << std::endl;
            node = node->next;
        } while (node != this->getFirstNode());
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if (this != &rhs)
    {
        Node<T> *traverser = rhs.head;

        removeAllNodes();
        size = 0;

        for (int i = 0; i < rhs.size; i++)
        {
            insertAtTheEnd(traverser->data);
            traverser = traverser->next;
        }
        size = rhs.size;
    }
    return *this;
}

#endif // LINKEDLIST_H
