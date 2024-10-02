#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include "Node.h"

template<class T>
class Graph {
private:
    std::vector<std::vector<int>> MatrizAdj;  // Matriz de adyacencia
    std::vector<Node<T>*> nodes;              // Vector de punteros a nodos
    inline int get_node_index(T u);
    bool is_connected_util(int u, std::vector<bool>& visited);
    bool has_cycle_util(int u, std::vector<bool>& visited, std::vector<int>& parent);
    void DFS_util(int u, std::vector<bool>& visited);

public:
    Graph(int size);
    void add_edge(T u, T v, int weight = 1);
    int Degree(T u);
    bool is_connected();
    bool has_cycle();
    bool is_acyclic();
    bool is_complete();
    void DFS(T u);
    void BFS(T u);
    std::vector<int> degree_sequence();
    bool is_r_regular(int r);
    bool is_semieulerian();
    bool is_eulerian();
    void add_node(T value);
};