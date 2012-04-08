#ifndef MYNODE_H
#define MYNODE_H

template<typename T>
struct node
{
    T data;
    int count;
    node<T>* next;

    node();
    node(const node<T> &other);
    node(const T &d,int qty = 1);
    ~node();

    node<T>& operator=(const node<T> &other);
};

template<typename T>
node<T>::node()
{
    next = NULL;
    count = 0;
}

template<typename T>
node<T>::node(const node<T> &other)
{
    data = other.data;
    count = other.count;
    next = other.next;
}

template<typename T>
node<T>::node(const T &d,int qty)
{
    data = d;
    count = qty;
    next = NULL;;
}

template<typename T>
node<T>::~node()
{
    next = NULL;
    count = 0;
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        data = other.data;
        count = other.count;
        next = NULL;
    }
    return *this;
}

#endif // MYNODE_H
