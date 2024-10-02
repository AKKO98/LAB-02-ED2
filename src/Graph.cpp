#include "Graph.h"
#include <queue>



Graph::Graph(int n, bool directed)
    : adj_matrix(std::vector<std::vector<int> >(n, std::vector<int>(n, 0))), directed(directed)
{
}

void Graph::add_edge(int u, int v)
{
    // Arista de u to v
    adj_matrix[u][v] = 1;
    // Arista de v to u (Para no direcionales)
    if (!directed)
        adj_matrix[v][u] = 1;
}

void Graph::print()
{
    std::cout << "Matris de adyacencia: " << std::endl;
    int n = adj_matrix.size();
    for (int i = 0; i < n; i++) {
        std::cout << i << ": [ ";
        for (int j = 0; j < n; j++) {
            if (adj_matrix[i][j] != 0)
            {
                std::cout << j << ", ";
            }
        }
        std::cout << "]";
        std::cout << std::endl;
    }
}

void Graph::DFS(int u)
{
    std::vector<bool> visit(adj_matrix.size(), false);
    DFS(u, visit);
    std::cout << std::endl;
}

std::vector<bool> Graph::BFS(int u)
{
    std::vector<bool> visit(adj_matrix.size(), false);  // Vector para marcar nodos visitados
    std::queue<int> q;  // Cola para gestionar los nodos que deben ser explorados

    visit[u] = true;  // Marcar nodo u como visitado
    q.push(u);  // Encolar el nodo inicial

    while (!q.empty()) {
        // Desencolar el nodo actual
        u = q.front();
        q.pop();
        std::cout << u << " ";  // Imprimir el nodo visitado

        // Recorrer todos los nodos vecinos de u
        for (int v = 0; v < adj_matrix[u].size(); ++v) {
            // Si hay una arista entre u y v, y v no ha sido visitado
            if (adj_matrix[u][v] == 1 && !visit[v]) {
                visit[v] = true;  // Marcar como visitado
                q.push(v);  // Encolar el nodo v
            }
        }
    }
    std::cout << std::endl;
    return visit;
}

int Graph::degree(int u)
{
    int degree = 0;
    for (int v = 0; v < adj_matrix[u].size(); ++v) {
        if (adj_matrix[u][v] == 1) {
            ++degree;
        }
    }
    return degree;
}

int Graph::min_degree(int u)
{
    int minDeg = degree(0);
    for (int i = 1; i < adj_matrix.size(); ++i) {
        minDeg = std::min(minDeg, degree(i));
    }
    return minDeg;
}

int Graph::max_degree(int u)
{
    int maxDeg = degree(0);
    for (int i = 1; i < adj_matrix.size(); ++i) {
        maxDeg = std::max(maxDeg, degree(i));
    }
    return maxDeg;
}

std::vector<int> Graph::degree_sequence()
{
    std::vector<int> degrees;
    for (int i = 0; i < adj_matrix.size(); ++i) {
        degrees.push_back(degree(i));
    }
    std::sort(degrees.begin(), degrees.end(), std::greater<int>());
    return degrees;
}

int Graph::number_of_components()
{
    std::vector<bool> visited(adj_matrix.size(), false);
    int components = 0;

    for (int i = 0; i < adj_matrix.size(); ++i) {
        if (!visited[i]) {
            DFS(i, visited);  // Realizar DFS para cada componente no visitada
            ++components;     // Incrementar el número de componentes
        }
    }
    return components;
}

bool Graph::is_connected()
{
    std::vector<bool> visited(adj_matrix.size(), false);
    DFS(0, visited);  // Realizar DFS desde el primer nodo

    // Verificar si todos los nodos fueron visitados
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

bool Graph::has_cycle(int u, std::vector<bool>& visited, std::vector<int>& parent) {
    visited[u] = true;

    for (int v = 0; v < adj_matrix[u].size(); ++v) {
        if (adj_matrix[u][v] == 1) {
            if (!visited[v]) {
                parent[v] = u;
                if (has_cycle(v, visited, parent)) return true;
            }
            else if (v != parent[u]) {
                return true;  // Se encontró un ciclo
            }
        }
    }
    return false;
}

bool Graph::is_acyclic() {
    std::vector<bool> visited(adj_matrix.size(), false);
    std::vector<int> parent(adj_matrix.size(), -1);

    for (int u = 0; u < adj_matrix.size(); ++u) {
        if (!visited[u]) {
            if (has_cycle(u, visited, parent)) return false;
        }
    }
    return true;
}

bool Graph::is_complete() {
    int n = adj_matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && adj_matrix[i][j] == 0) {
                return false;  // Si hay nodos no conectados, no es completo
            }
        }
    }
    return true;
}

bool Graph::is_r_regular(int r) {
    for (int i = 0; i < adj_matrix.size(); ++i) {
        if (degree(i) != r) {
            return false;  // Si algún nodo no tiene grado r, no es r-regular
        }
    }
    return true;
}

bool Graph::is_semieulerian() {
    int odd_count = 0;

    for (int i = 0; i < adj_matrix.size(); ++i) {
        if (degree(i) % 2 != 0) {
            odd_count++;
        }
    }

    return (odd_count == 2);
}

bool Graph::is_eulerian() {
    if (!is_connected()) return false;

    for (int i = 0; i < adj_matrix.size(); ++i) {
        if (degree(i) % 2 != 0) {
            return false;  // Si algún nodo tiene grado impar, no es euleriano
        }
    }

    return true;
}

std::vector<int> Graph::path(int u, int v) {
    std::vector<int> parent(adj_matrix.size(), -1);
    std::vector<bool> visited(adj_matrix.size(), false);
    std::queue<int> q;

    visited[u] = true;
    q.push(u);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == v) break;  // Si llegamos al nodo v, terminamos

        for (int i = 0; i < adj_matrix[node].size(); ++i) {
            if (adj_matrix[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i] = node;
                q.push(i);
            }
        }
    }

    // Reconstruir el camino desde v hacia u
    std::vector<int> path;
    for (int at = v; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    if (path.front() == u) return path;  // Verificar que realmente sea un camino
    return {};  // Si no es un camino válido, retornar un vector vacío
}

std::vector<bool> Graph::DFS(int u, std::vector<bool>& visit)
{
    visit[u] = true;
    std::cout << u << " ";  // Imprimir el nodo visitado

    // Recorrer todos los nodos para verificar conexiones
    for (int v = 0; v < adj_matrix[u].size(); ++v) {
        if (adj_matrix[u][v] == 1 && !visit[v]) {  // Si hay una arista y no ha sido visitado
            DFS(v, visit);  // Llamada recursiva
        }
    }
    return visit;
}