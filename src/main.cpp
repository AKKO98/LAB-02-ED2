#include "Graph.h"

int main() {
    // Crear un grafo con 7 vértices y no dirigido
    Graph g(7, false);

    // Agregar 10 aristas
    g.add_edge(0, 1);  // Arista 1
    g.add_edge(0, 2);  // Arista 2
    g.add_edge(1, 3);  // Arista 3
    g.add_edge(1, 4);  // Arista 4
    g.add_edge(2, 5);  // Arista 5
    g.add_edge(2, 6);  // Arista 6
    g.add_edge(3, 4);  // Arista 7
    g.add_edge(3, 5);  // Arista 8
    g.add_edge(4, 6);  // Arista 9
    g.add_edge(5, 6);  // Arista 10

    // Imprimir la matriz de adyacencia
    g.print();

    // Probar DFS desde el nodo 0
    std::cout << "\nDFS desde el nodo 0:" << std::endl;
    g.DFS(0);

    // Probar BFS desde el nodo 0
    std::cout << "\nBFS desde el nodo 0:" << std::endl;
    g.BFS(0);

    // Probar el grado de algunos nodos
    std::cout << "\nGrado del nodo 0: " << g.degree(0) << std::endl;
    std::cout << "Grado del nodo 1: " << g.degree(1) << std::endl;
    std::cout << "Grado del nodo 6: " << g.degree(6) << std::endl;

    // Probar el grado mínimo y máximo
    std::cout << "\nGrado mínimo: " << g.min_degree(0) << std::endl;
    std::cout << "Grado máximo: " << g.max_degree(0) << std::endl;

    // Probar la secuencia de grados
    std::vector<int> degreeSeq = g.degree_sequence();
    std::cout << "\nSecuencia de grados (de mayor a menor): ";
    for (int deg : degreeSeq) {
        std::cout << deg << " ";
    }
    std::cout << std::endl;

    // Probar si el grafo es conexo
    std::cout << "\nEl grafo es conexo: " << (g.is_connected() ? "Sí" : "No") << std::endl;

    // Probar el número de componentes conectadas
    std::cout << "Número de componentes: " << g.number_of_components() << std::endl;

    // Probar si el grafo tiene ciclo
    std::cout << "El grafo es acíclico: " << (g.is_acyclic() ? "Sí" : "No") << std::endl;

    // Probar si el grafo es completo
    std::cout << "El grafo es completo: " << (g.is_complete() ? "Sí" : "No") << std::endl;

    // Probar si el grafo es r-regular (e.g., 3-regular)
    int r = 3;
    std::cout << "El grafo es " << r << "-regular: " << (g.is_r_regular(r) ? "Sí" : "No") << std::endl;

    // Probar si el grafo es Euleriano
    std::cout << "El grafo es Euleriano: " << (g.is_eulerian() ? "Sí" : "No") << std::endl;

    // Probar si el grafo es semi-Euleriano
    std::cout << "El grafo es semi-Euleriano: " << (g.is_semieulerian() ? "Sí" : "No") << std::endl;

    // Probar el camino entre dos nodos
    int u = 0, v = 6;
    std::vector<int> path = g.path(u, v);
    std::cout << "\nCamino desde " << u << " hasta " << v << ": ";
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}