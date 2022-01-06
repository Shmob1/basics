#include <iostream>
#include <vector>
#include <map>
#include <list>

struct Node
{
    int data;
    Node *next;
};

class List
{
public:
    bool empty = true;
    Node *head = NULL;

    List()
    {
        empty = true;
        head = NULL;
    }

    List(int data)
    {
        head = new_node(data);
        empty = false;
    }
    Node *find(int data)
    {
        if (empty == true)
            return NULL;

        Node *p = head;
        while (p != NULL)
        {
            if (p->data == data)
                return p;
            p = p->next;
        }
        return NULL;
    }
    void insert(int data)
    {
        if (empty)
        {
            head = new_node(data);
            empty = false;
            return;
        }
        Node *newnode = new_node(data);
        Node *temp = head;
        head = newnode;
        newnode->next = temp;
        return;
    }
    // only inserts if the desired value is not in the list already
    int insert_atmoic(int data)
    {
        Node *test = find(data);
        if (test != nullptr)
            return 1;
        insert(data);

        return 0;
    }

    void remove(int data)
    {
        if (empty)
            return;
        Node *predicessor = find_pred(data);

        // if the head is being deleted
        if (predicessor == NULL)
        {
            Node *p = head;
            head = head->next;
            free(p);
            empty = true;
            return;
        }
        // item is not in list
        if (predicessor->next == NULL)
            return;
        // otherwise, delete the item
        Node *to_delete = predicessor->next;
        predicessor->next = predicessor->next->next;
        free(to_delete);
        return;
    }
    void print()
    {
        Node *p = head;
        while (p != NULL)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

private:
    Node *find_pred(int data)
    {
        if (data == head->data)
            return NULL;
        Node *p = head;
        while (p->next != NULL)
        {
            if (p->next->data == data)
                return p;
            p = p->next;
        }
        return p;
    }

    static Node *new_node(int data)
    {
        Node *node = new Node;
        node->data = data;
        node->next = NULL;
        return node;
    }
};

class Graph
{
public:
    std::map<int, bool> visited;
    std::map<int, List *> lists;
    int size;

    Graph(int size)
    {
        this->size = size;

        for (int i = 0; i < size; i++)
            this->lists[i] = new List();
    }

    void addEdge(int src, int dest, bool directed)
    {
        this->lists.at(src)->insert_atmoic(dest);
        if (directed == false)
            this->lists.at(dest)->insert_atmoic(src);
    }

    void DFS(int start)
    {
        for (int i = 0; i < size; i++)
            visited[i] = false;
        std::cout << "DFS: ";
        DFS_helper(start);
        std::cout << std::endl;
    }

    void BFS(int start)
    {
        for (int i = 0; i < size; i++)
            visited[i] = false;
        std::cout << "BFS: ";
        BFS_helper(start);
        std::cout << std::endl;
    }

    void print()
    {
        for (int i = 0; i < this->lists.size(); i++)
        {
            std::cout << "Node " << i << " : ";
            this->lists.at(i)->print();
        }
    }

private:
    void DFS_helper(int start)
    {

        visited[start] = true;
        std::cout << start << " ";

        for (Node *node = lists[start]->head; node != nullptr; node = node->next)
        {
            if (!visited[node->data])
            {
                DFS_helper(node->data);
            }
        }
    }

    void BFS_helper(int start)
    {
        std::list<int> queue;

        visited[start] = true;
        queue.push_back(start);

        while (!queue.empty())
        {
            start = queue.front();
            std::cout << start << " ";
            queue.pop_front();

            for (Node *node = lists[start]->head; node != nullptr; node = node->next)
            {
                if (!visited[node->data])
                {
                    visited[node->data] = true;
                    queue.push_back(node->data);
                }
            }
        }
    }
};

int main()
{
    // create the graph given in above fugure
    int size = 5;
    struct Graph *graph = new Graph(size);
    graph->addEdge(0, 3, false);
    graph->addEdge(0, 2, false);
    graph->addEdge(1, 2, false);
    graph->addEdge(2, 0, false);
    graph->addEdge(2, 4, false);
    graph->addEdge(2, 2, false);
    graph->addEdge(0, 4, false);

    graph->print();
    graph->DFS(0);
    graph->BFS(0);

    return 0;
}