#ifndef ALGORITHMS_LISTGRAPH_H
#define ALGORITHMS_LISTGRAPH_H


#include <vector>
#include <iostream>

#include "IGraph.h"


class ListGraph : public IGraph {
public:
    ListGraph(std::size_t a_vertices_count) : vertices_count_(a_vertices_count) {
        graph_.resize(vertices_count_);
    }

    explicit ListGraph(const IGraph& graph) {
        graph_.clear();
        graph_.resize(graph.VerticesCount());
        vertices_count_ = graph.VerticesCount();

        for (int v = 0; v < graph.VerticesCount(); ++v) {
            graph_[v] = graph.GetNextVertices(v);
        }
    }

    virtual ~ListGraph() = default;

    void AddEdge(int from, int to) override {
        graph_[from].push_back(to);
    }

    int VerticesCount() const override {
        return vertices_count_;
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> result;
        result.resize(graph_[vertex].size());
        std::copy(graph_[vertex].begin(), graph_[vertex].end(), result.begin());
        return result;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> result;
        for (int parent = 0; parent < graph_.size(); ++parent) {
            for (auto & child : graph_[parent]) {
                if (child == vertex) {
                    result.push_back(parent);
                }
            }
        }
        return result;
    }

private:
    std::vector<std::vector<int>> graph_;
    std::size_t vertices_count_;

};


#endif //ALGORITHMS_LISTGRAPH_H
