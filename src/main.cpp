#include "Graph.h"
#include <iostream>
    
int main() {
    // Crear un grafo de tipo int con capacidad inicial para 5 nodos
    Graph<int> graph(5);

    // Agregar nodos
    graph.add_node(1);
    graph.add_node(2);
    graph.add_node(3);
    graph.add_node(4);
    graph.add_node(5);

    // Agregar aristas
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 4);
    graph.add_edge(3, 4);
    graph.add_edge(4, 5);

    std::cout << "Grafo creado con 5 nodos y algunas aristas.\n";

    // Probar Degree
    std::cout << "Grado del nodo 1: " << graph.Degree(1) << std::endl;
    std::cout << "Grado del nodo 4: " << graph.Degree(4) << std::endl;

    // Probar DFS
    std::cout << "\nDFS desde el nodo 1: ";
    graph.DFS(1);
    std::cout << std::endl;

    // Probar BFS
    std::cout << "BFS desde el nodo 1: ";
    graph.BFS(1);
    std::cout << std::endl;

    // Probar is_connected
    std::cout << "¿El grafo es conexo?: " << (graph.is_connected() ? "Sí" : "No") << std::endl;

    // Probar has_cycle
    std::cout << "¿El grafo tiene ciclos?: " << (graph.has_cycle() ? "Sí" : "No") << std::endl;

    // Probar is_acyclic
    std::cout << "¿El grafo es acíclico?: " << (graph.is_acyclic() ? "Sí" : "No") << std::endl;

    // Probar is_complete
    std::cout << "¿El grafo es completo?: " << (graph.is_complete() ? "Sí" : "No") << std::endl;

    // Probar degree_sequence
    std::vector<int> degreeSeq = graph.degree_sequence();
    std::cout << "Secuencia de grados: ";
    for (int d : degreeSeq) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    // Probar is_r_regular
    std::cout << "¿El grafo es 2-regular?: " << (graph.is_r_regular(2) ? "Sí" : "No") << std::endl;

    // Probar is_eulerian
    std::cout << "¿El grafo es Euleriano?: " << (graph.is_eulerian() ? "Sí" : "No") << std::endl;

    // Probar is_semieulerian
    std::cout << "¿El grafo es semi-Euleriano?: " << (graph.is_semieulerian() ? "Sí" : "No") << std::endl;

    return 0;
}