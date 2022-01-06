#include <iostream>

/*
Simple Implementation of a Binary Tree in C++

Author: James Donlan
Last Modified: 5 / 1 / 2022

methods:
    insert
    remove
    find
    print:
        inorder
        postorder
        preorder

*/

struct Node
{
    int data;
    Node *left;
    Node *right;
};

class Tree
{
public:
    Node *head;
    Tree(int data)
    {
        head = new_node(data);
    }

    void insert(int data)
    {
        if (head == NULL)
        {
            head = new_node(data);
            return;
        }
        insert(head, data);
    }

    void remove(int data)
    {
        if (head == NULL)
            return;
        remove(head, data);
    }

    Node *find(int data)
    {
        Node *p = head;
        while (head != NULL)
        {
            if (p->data == data)
                return p;
            if (data < p->data)
                p = p->left;
            else
                p = p->right;
        }
        return NULL;
    }

    Node *minimum()
    {
        Node *p = head;

        if (p == NULL)
            return NULL;
        while (p->left != NULL)
            p = p->left;
        return p;
    }

    Node *maximum()
    {
        Node *p = head;

        if (p == NULL)
            return NULL;
        while (p->right != NULL)
            p = p->right;
        return p;
    }

    void print_inorder()
    {
        print_inorder(head);
        std::cout << std::endl;
    }

    void print_postorder()
    {
        print_postorder(head);
        std::cout << std::endl;
    }

    void print_preorder()
    {
        print_preorder(head);
        std::cout << std::endl;
    }

private:
    static Node *remove(Node *in, int data)
    {
        Node *p = in;
        Node *temp = NULL;

        if (p == NULL)
            return NULL;

        if (data < p->data)
            p->left = remove(p->left, data);
        else if (data > p->data)
            p->right = remove(p->right, data);

        // this is the node to delete
        else
        {
            if (p->left == NULL && p->right == NULL)
            {
                free(p);
                return NULL;
            }
            if (p->left == NULL)
            {
                temp = p->right;
                free(p);
                return temp;
            }
            if (p->right == NULL)
            {
                temp = p->left;
                free(p);
                return temp;
            }
            temp = minValueNode(p->right);
            p->data = temp->data;
            p->right = remove(p->right, p->data);
        }
        return p;
    }
    static Node *minValueNode(Node *in)
    {
        Node *p = in;
        while (p && p->left != NULL)
            p = p->left;
        return p;
    }
    static void print_inorder(Node *p)
    {
        if (!p)
            return;
        print_inorder(p->left);
        std::cout << p->data << " ";
        print_inorder(p->right);
    }
    static void print_postorder(Node *p)
    {
        if (!p)
            return;
        print_inorder(p->left);
        print_inorder(p->right);
        std::cout << p->data << " ";
    }
    static void print_preorder(Node *p)
    {
        if (!p)
            return;
        std::cout << p->data << " ";
        print_inorder(p->left);
        print_inorder(p->right);
    }

    static void insert(Node *p, int data)
    {
        if (data == p->data)
            return;
        if (data < p->data)
        {
            if (p->left == NULL)
            {
                p->left = new_node(data);
                return;
            }
            insert(p->left, data);
        }
        if (data > p->data)
        {
            if (p->right == NULL)
            {
                p->right = new_node(data);
                return;
            }
            insert(p->right, data);
        }
    }
    static Node *new_node(int data)
    {
        Node *node = new Node;
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
};

int main(void)
{
    std::cout << "standard BST" << std::endl;
    Tree tree = Tree(10);
    tree.insert(32);
    tree.insert(-2);
    tree.insert(42);
    tree.insert(2);
    tree.insert(7);
    tree.insert(9);
    tree.insert(1);
    tree.remove(-2);
    tree.remove(-4);
    tree.find(10);
    tree.print_inorder();
    tree.print_postorder();
    tree.print_preorder();
}
