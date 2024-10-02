#pragma once
#include <iostream>
#include <vector>


class Graph
{
private:
	std::vector<std::vector<int>> adj_matrix;
	bool directed;

	std::vector<bool> DFS(int u, std::vector<bool>& list);
public:

	Graph(int n, bool directed);
	void add_edge(int u, int v);
	void print();
	void DFS(int u);
	std::vector<bool> BFS(int u);
	int degree(int u);
	int min_degree(int u);
	int max_degree(int u);
	std::vector<int> degree_sequence();
	int number_of_components();
	bool is_connected();
	bool has_cycle(int u, std::vector<bool>& visited, std::vector<int>& parent);
	bool is_acyclic();
	bool is_complete();
	bool is_r_regular(int r);
	bool is_semieulerian();
	bool is_eulerian();
	std::vector<int> path(int u, int v);
};

