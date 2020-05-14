#include <iostream>
#include <string>
#include <exception>
#include "header.h"
#include <vector>
#include <algorithm>

//My exception class which handles exceptions when failures are detected for certain graph operations 
class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "failure\n";
  }
} illegal_argument;

//Node class constructor
Node::Node(){
    next = NULL;
    data = 0;
    //parent = NULL;
}

//Linked List class constructor
LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
}

Disjoint_sets::Disjoint_sets(int nodes){
    t_nodes = nodes;

    head_array = new LinkedList* [nodes];

    for (int i = 0; i < nodes; i++){
        head_array[i] = NULL;
    }
}

//Disjoint set destructor
Disjoint_sets::~Disjoint_sets(){
    Node* temp;
    Node* temp1;

    for (int i = 0; i < t_nodes; i++){
        temp = head_array[i]->head;
        while (temp != NULL){
            temp1 = temp;
            temp = temp->next;
            delete temp1;
        }
        head_array[i]->head = NULL;
    }

    delete [] head_array;
}

//Makeset function
void Disjoint_sets::makeSet(int u){
    Node* temp = new Node;
    temp->data = u;

    LinkedList* ll = new LinkedList;
    ll->head = temp;
    ll->tail = temp;

    //temp->parent = ll;

    head_array[u] = ll;
}

//Findset function
LinkedList* Disjoint_sets::findSet(int u){
    if (head_array[u] != NULL){
        return head_array[u];
    }
    return NULL;
}

void Disjoint_sets::makeUnion(int u, int v){
    LinkedList* temp = head_array[u];
    LinkedList* temp1 = head_array[v];
    temp->tail->next = temp1->head;
    temp->tail = temp1->tail;

    for (int i = 0; i < t_nodes; i++){
        if (head_array[i] == head_array[v] && (i != v)){
            head_array[i] = head_array[u];
        }
    }
    temp1->head = NULL;
    head_array[v] = head_array[u];
}

//Minimum Spanning Tree - Kruskal's Algorithm
void Graph::mst(){
    disjoint_obj = new Disjoint_sets(m);
    std::vector <std::pair<double, std::pair<int, int>>> edge;
    double sum_weight = 0;
    int edge_count = 0;

    for (int i = 0; i < m; i++){
        disjoint_obj->makeSet(i);
    }

    //Sorting the edges in ascending order (by weight)
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            if ((i < j) && (graph[i][j] != __DBL_MAX__)){
                edge.push_back(std::make_pair(graph[i][j], std::make_pair(i, j)));
            }
        }
    }

    std::sort(edge.begin(), edge.end());
    for (auto x = edge.begin(); x != edge.end(); x++){
        if (disjoint_obj->findSet(x->second.first) != disjoint_obj->findSet(x->second.second)){
            disjoint_obj->makeUnion(x->second.first, x->second.second);
            sum_weight += x->first;
            edge_count++;
        }
    }
    if (edge_count == m - 1){
        std::cout << "mst " << sum_weight << std::endl;
    }
    else{
        std::cout << "not connected" << std::endl;
    }
}

void Graph::create_graph(int nodes){
    graph = new double* [nodes];
    degree_array  = new int [nodes];
    edges = 0;
    m = nodes;

    for (int i = 0; i <= nodes; i++){
        graph[i] = new double [nodes];
        degree_array[i] = 0;
    }

    for (int i = 0; i <= nodes; i++){
        for (int j = 0; j <= nodes; j++){
            if (i == j){
                graph[i][j] = 0;
            }
            else{
                graph[i][j] = __DBL_MAX__;
            }
        }   
    }

    std::cout << "success" << std::endl;
}

//Graph destructor
Graph::~Graph(){
    delete disjoint_obj;
    delete [] degree_array;
    for (int i = 0; i < m; i++){
        delete [] graph[i];
    }
    delete [] graph;
    m = 0;
    edges = 0;
}

//Graph constructor
Graph::Graph(){
    edges = 0;
    m = 0;
}

//Degree function
int Graph::degree(int u){
    try{
        if (u < 0 || u >= m){
            throw illegal_argument;
        }
    }
    catch(std::exception &obj){
        std::cout << obj.what();
    }

    if (u >= 0 && u < m){
        std::cout << "degree of " << u << " is " << degree_array[u] << std::endl;
        return degree_array[u];
    }
    else {
        return 0;
    }
}

//Total edges function
int Graph::total_edges(){
    std::cout << "edge count is " << edges << std::endl;
    return edges;
}

void Graph::insert_edge(int u, int v, double w){
    try{
        if (u < 0 || u >= m || v < 0 || v >= m || w <= 0){
            throw illegal_argument;
        }
    }
    catch(std::exception &obj){
        std::cout << obj.what();
    }
    if (u >= 0 && u < m && v >= 0 && v < m && w > 0){
        graph[u][v] = w;
        graph[v][u] = w;

        degree_array[u]++;
        degree_array[v]++;

        edges++;
        std::cout << "success" << std::endl;
    }
}

void Graph::delete_edge(int u, int v){
    try{
        if (u < 0 || u >= m || v < 0 || v >= m){
            throw illegal_argument;
        }
    }
    catch(std::exception &obj){
        std::cout << obj.what();
    }

    if (u >= 0 && u < m && v > 0 && v < m){
        if (graph[u][v] == __DBL_MAX__ && graph[v][u] == __DBL_MAX__){
            std::cout << "failure" << std::endl;
        }
        else{
            graph[u][v] = __DBL_MAX__;
            graph[v][u] = __DBL_MAX__;
            std::cout << "success" << std::endl;

            degree_array[u]--;
            degree_array[v]--;
            edges--;
        }
    }
}

void Graph::clear(){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            if (i == j){
                graph[i][j] = 0;
            }
            else{
                graph[i][j] = __DBL_MAX__;
            }
        }   
    }

    edges = 0;
    std::cout << "success" << std::endl;
}