#include <iostream>
#include <exception>
#include <string>

//Node class 
class Node{
    public:
        Node* next;
        int data;

        Node();   
};

//Linked List class
class LinkedList{
    public:
        Node* head;
        Node* tail;

        LinkedList();
};

//Disjoint Sets class for the MST
class Disjoint_sets{
    public:
        int t_nodes;
        LinkedList** head_array;

        Disjoint_sets(int nodes);
        ~Disjoint_sets();
        void makeSet(int u);
        void makeUnion(int u, int v);
        LinkedList* findSet(int u);
};

//Graph class
class Graph{
    public:
        int m;
        int edges;
        double** graph;
        int* degree_array;
        Disjoint_sets* disjoint_obj;

        Graph();                                        //Constructor
        ~Graph();                                       //Destructor
        void create_graph(int nodes);                       
        void insert_edge(int u, int v, double w);       //Insert function
        void delete_edge(int u, int v);                 //Delete function
        int degree(int u);                              //Returns the degree of vertex u
        int total_edges();                              //Returns total # of edges in the graph
        void clear();                                   //Removes all the edges in the graph
        void mst();                                     //Calculates the minimum spanning tree and returns the total weight
};