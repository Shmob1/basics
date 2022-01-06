#include <iostream>

/*
Simple Implementation of the Singally linked List in C++

Author: James Donlan
Last Modified: 5 / 1 / 2022

methods:
    Node<auto>* find(auto data)
    void insert(auto data)
    void remove(auto data)
    void print(void)
    void push(auto data) #alias for insert
    Node<auto>* pop()

*/

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
class List
{
public:
    Node<T> *head;

    List(T data)
    {
        head = new_node(data);
    }
    Node<T> *find(int data)
    {
        Node<T> *p = head;
        while (p != NULL)
        {
            if (p->data == data)
                return p;
            p = p->next;
        }
        return NULL;
    }
    void insert(T data)
    {
        Node<T> *newnode = new_node(data);
        Node<T> *temp = head;
        head = newnode;
        newnode->next = temp;
        return;
    }
    void remove(T data)
    {
        Node<T> *predicessor = find_pred(data);

        // if the head is being deleted
        if (predicessor == NULL)
        {
            Node<T> *p = head;
            head = head->next;
            free(p);
            return;
        }
        // item is not in list
        if (predicessor->next == NULL)
            return;
        // otherwise, delete the item
        Node<T> *to_delete = predicessor->next;
        predicessor->next = predicessor->next->next;
        free(to_delete);
        return;
    }
    void print()
    {
        Node<T> *p = head;
        while (p != NULL)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

    void push(T data)
    {
        insert(T data);
    }
    Node<T> *pop()
    {
        Node<T> *temp = head;
        head = head->next;
        return temp;
    }

private:
    Node<T> *find_pred(T data)
    {
        if (data == head->data)
            return NULL;
        Node<T> *p = head;
        while (p->next != NULL)
        {
            if (p->next->data == data)
                return p;
            p = p->next;
        }
        return p;
    }

    static Node<T> *new_node(T data)
    {
        Node<T> *node = new Node<T>;
        node->data = data;
        node->next = NULL;
        return node;
    }
};

int main(void)
{
    std::cout << "standard LL" << std::endl;
    List list = List(10);
    list.print();
    list.insert(32);
    list.print();
    list.insert(-2);
    list.print();
    list.remove(-2);
    list.print();
    list.remove(-4);
    list.print();
    list.find(10);
    list.print();
}