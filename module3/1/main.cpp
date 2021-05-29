#include <iostream>
#include <algorithm>
#include <queue>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"


template<class Callback>
void dfs_aux(const IGraph& graph, std::vector<bool>& visited, int v, Callback callback) {
    visited[v] = true;
    callback(v);
    std::vector<int> children = graph.GetNextVertices(v);
    for (auto & child : children) {
        if (!visited[child]) {
            dfs_aux(graph, visited, child, callback);
        }
    }
}


template<class Callback>
void dfs(const IGraph& graph, Callback callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (std::size_t v = 0; v < graph.VerticesCount(); ++v) {
        if (!visited[v]) {
            dfs_aux(graph, visited, v, callback);
        }
    }
}


template<class Callback>
void bfs(const IGraph& graph, Callback callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;
    for (std::size_t v = 0; v < graph.VerticesCount(); ++v) {
        if (!visited[v]) {
            visited[v] = true;
            q.push(v);
            while (!q.empty()) {
                int current_vertex = q.front();
                q.pop();
                callback(current_vertex);

                std::vector<int> children = graph.GetNextVertices(current_vertex);
                for (auto & child : children) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
}


int main() {
    ListGraph lgraph(7);
    lgraph.AddEdge(0, 1);
    lgraph.AddEdge(1, 2);
    lgraph.AddEdge(2, 3);
    lgraph.AddEdge(3, 4);
    lgraph.AddEdge(4, 2);
    lgraph.AddEdge(4, 5);
    lgraph.AddEdge(2, 6);

    MatrixGraph mgraph(lgraph);
    SetGraph sgraph(mgraph);
    ArcGraph agraph(sgraph);


    std::cout << "Первый вывод - обход в глубину, второй - обход в ширину" << std::endl;
    std::cout << "Списки смежности:" << std::endl;
    dfs(lgraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl << "===========================" << std::endl;
    bfs(lgraph, [](int v) {
        std::cout << v << " ";
    });

    std::cout << std::endl << "Матрица смежности:" << std::endl;
    dfs(lgraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl << "===========================" << std::endl;
    bfs(lgraph, [](int v) {
        std::cout << v << " ";
    });

    std::cout << std::endl << "Граф в виде массива красно-черных деревьев:" << std::endl;
    dfs(lgraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl << "===========================" << std::endl;
    bfs(lgraph, [](int v) {
        std::cout << v << " ";
    });

    std::cout << std::endl << "Граф в виде массива пар:" << std::endl;
    dfs(lgraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl << "===========================" << std::endl;
    bfs(lgraph, [](int v) {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    return 0;
}
