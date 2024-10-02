#include "Graph.h"

template <class T>
Graph<T>::Graph(int size) {
    MatrizAdj.resize(size, std::vector<int>(size, 0));
}

template <class T>
int Graph<T>::get_node_index(T u) {
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->value == u) return i;
    }
    return -1;
}

template <class T>
bool Graph<T>::is_connected_util(int u, std::vector<bool>& visited) {
    visited[u] = true;
    for (int v = 0; v < MatrizAdj.size(); ++v) {
        if (MatrizAdj[u][v] != 0 && !visited[v]) {
            is_connected_util(v, visited);
        }
    }
}

template <class T>
void Graph<T>::add_edge(T u, T v, int weight) {
    int index_u = get_node_index(u);
    int index_v = get_node_index(v);
    if (index_u == -1 || index_v == -1) return;
    MatrizAdj[index_u][index_v] = weight;
    MatrizAdj[index_v][index_u] = weight;
}

template <class T>
int Graph<T>::Degree(T u) {
    int index_u = get_node_index(u);
    if (index_u == -1) return -1;
    int degree = 0;
    for (int v = 0; v < MatrizAdj.size(); ++v) {
        if (MatrizAdj[index_u][v] != 0) degree++;
    }
    return degree;
}

template <class T>
bool Graph<T>::is_connected() {
    std::vector<bool> visited(MatrizAdj.size(), false);
    is_connected_util(0, visited);
    return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

template <class T>
bool Graph<T>::has_cycle() {
    std::vector<bool> visited(MatrizAdj.size(), false);
    std::vector<int> parent(MatrizAdj.size(), -1);
    for (int u = 0; u < MatrizAdj.size(); ++u) {
        if (!visited[u] && has_cycle_util(u, visited, parent)) return true;
    }
    return false;
}

template <class T>
bool Graph<T>::has_cycle_util(int u, std::vector<bool>& visited, std::vector<int>& parent) {
    visited[u] = true;
    for (int v = 0; v < MatrizAdj.size(); ++v) {
        if (MatrizAdj[u][v] != 0) {
            if (!visited[v]) {
                parent[v] = u;
                if (has_cycle_util(v, visited, parent)) return true;
            }
            else if (parent[u] != v) {
                return true;
            }
        }
    }
    return false;
}

template <class T>
bool Graph<T>::is_acyclic() {
    return !has_cycle();
}

template <class T>
bool Graph<T>::is_complete() {
    for (int i = 0; i < MatrizAdj.size(); ++i) {
        for (int j = i + 1; j < MatrizAdj.size(); ++j) {
            if (MatrizAdj[i][j] == 0) return false;
        }
    }
    return true;
}

template <typename T>
void Graph<T>::DFS(T u) {
    int index_u = get_node_index(u);
    if (index_u == -1) return;

    std::vector<bool> visited(MatrizAdj.size(), false);
    DFS_util(index_u, visited);
}

template <class T>
void Graph<T>::BFS(T u) {
    int index_u = get_node_index(u);
    if (index_u == -1) return;
    std::vector<bool> visited(MatrizAdj.size(), false);
    std::queue<int> q;
    visited[index_u] = true;
    q.push(index_u);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::cout << nodes[curr]->value << " ";

        for (int v = 0; v < MatrizAdj.size(); ++v) {
            if (MatrizAdj[curr][v] != 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

template <class T>
void Graph<T>::DFS_util(int u, std::vector<bool>& visited) {
    visited[u] = true;
    std::cout << nodes[u]->value << " ";

    for (int v = 0; v < MatrizAdj.size(); ++v) {
        if (MatrizAdj[u][v] != 0 && !visited[v]) {
            DFS_util(v, visited);
        }
    }
}

template <class T>
std::vector<int> Graph<T>::degree_sequence() {
    std::vector<int> degrees;
    for (Node<T>* node : nodes) {
        degrees.push_back(Degree(node->value));
    }
    std::sort(degrees.begin(), degrees.end(), std::greater<int>());
    return degrees;
}

template <class T>
bool Graph<T>::is_r_regular(int r) {
    for (Node<T>* node : nodes) {
        if (Degree(node->value) != r) return false;
    }
    return true;
}

template <class T>
bool Graph<T>::is_semieulerian() {
    int odd_degree_count = 0;
    for (Node<T>* node : nodes) {
        if (Degree(node->value) % 2 != 0) odd_degree_count++;
    }
    return odd_degree_count == 2;
}

template <class T>
bool Graph<T>::is_eulerian() {
    int odd_degree_count = 0;
    for (Node<T>* node : nodes) {
        if (Degree(node->value) % 2 != 0) odd_degree_count++;
    }
    return odd_degree_count == 0;
}

template <class T>
void Graph<T>::add_node(T value) {
    Node<T>* newNode = new Node<T>(value);
    nodes.push_back(newNode);
    MatrizAdj.resize(nodes.size(), std::vector<int>(nodes.size(), 0));
    for (auto& row : MatrizAdj) {
        row.resize(nodes.size());
    }
}