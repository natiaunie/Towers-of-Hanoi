#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "mynode.h"

using namespace std;

template<typename T>
class queue
{
    public:
        queue();
        queue(const T &d);
        queue(const queue<T> &other);
        ~queue();
        queue<T>& operator=(const queue<T> &other);

        bool find(T data);
        bool empty();
        void clear(node<T>* &ptr);
        void push(T data);
        void pop();
        T top();

    private:
		node<T>* back;
		node<T>* front;
        int qty; // Number of nodes in linked list
        void copy(const queue<T> &other);
        node<T>* find(node<T>* ptr, T item);
};


template<typename T>
queue<T>::queue()
{
    back = NULL;
    qty = 0;
}

template<typename T>
queue<T>::queue(const T &d)
{
    back = new node<T>(d);
    if(qty == 0)
        front = back;
    qty++;
}

template<typename T>
queue<T>::queue(const queue<T> &other)
{
    copy(other);
}

template<typename T>
queue<T>::~queue()
{
    clear(back);
    qty=0;
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T> &other)
{
    if(this != &other)
    {
        clear(back);
        copy(other);
    }
    return *this;
}

template<typename T>
bool queue<T>::find(T data)
{
    node<T>  *tmp = new node<T> , *tmp2;
    tmp->next = back;
    tmp2 = find(tmp, data);
    delete tmp;
    return tmp2;
}

template<typename T>
bool queue<T>::empty()
{
    return !front;
}

template<typename T>
void queue<T>::clear(node<T>* &ptr)
{
	ptr ? clear(ptr->next) : delete ptr;
	qty=0;
}

template<typename T>
void queue<T>::push(T data)
{
    node<T> *newBack= new node<T>;
    newBack->next = back;
    node<T> *mover = newBack;
    mover->next = newBack->next;
    for(; mover->next && (mover->next->data >= data); mover=mover->next);
    node<T> *temp= new node<T>(data);
    temp->next = mover->next;
    mover->next = temp;
    qty++;
    if(!temp->next)
    {
        front = temp;
    }
    back = newBack->next;
    delete newBack;
}

template<typename T>
void queue<T>::pop()
{
    if(qty > 1)
    {
        node<T> *newBack= new node<T>;
        newBack->next = back;
        node<T> *goner = find(back,front->data);
        node<T> *deletethis = goner->next;
        goner->next = goner->next->next;
        delete deletethis;
        qty--;
        front = goner;
        back = newBack->next;
        delete newBack;
    }
    else
    {
        node<T> *deletethis = front;
        delete deletethis;
        front = NULL;
        back = NULL;
    }
}

template<typename T>
T queue<T>::top()
{
    return front->data;
}

template<typename T>
void queue<T>::copy(const queue<T> &other)
{
    node<T> *tmp = other.back;
    for(; tmp != NULL; tmp = tmp->next)
        push(tmp->data);
}

template<typename T>
node<T> * queue<T> ::find(node<T> * ptr, T item)
{
    for(; ptr != NULL; ptr = ptr->next)
        if(ptr->next->data == item)
            return ptr;
    return NULL;
}

#endif // MYQUEUE_H
