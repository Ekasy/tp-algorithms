#ifndef ALGORITHMS_MATRIXGRAPH_H
#define ALGORITHMS_MATRIXGRAPH_H


#include <vector>
#include <iostream>

#include "IGraph.h"


class MatrixGraph : public IGraph {
public:
    MatrixGraph(int size) {
        graph_.resize(size);
        for (int i = 0; i < size; ++i) {
            graph_[i].resize(size, false);
        }
    }
    virtual ~MatrixGraph() = default;

    explicit MatrixGraph(const IGraph& graph) {
        graph_.clear();
        graph_.resize(graph.VerticesCount());

        for (int v = 0; v < graph.VerticesCount(); ++v) {
            graph_[v].resize(graph.VerticesCount(), false);
            std::vector<int> children = graph.GetNextVertices(v);
            for (auto & child : children) {
                graph_[v][child] = true;
            }
        }
    }

    void AddEdge(int from, int to) override {
        graph_[from][to] = true;
    }

    int VerticesCount() const override {
        return graph_.size();
    }

    std::vector<int> GetNextVertices(int vertex) const {
        std::vector<int> result;
        for (int i = 0; i < VerticesCount(); ++i) {
            if (graph_[vertex][i]) {
                result.push_back(i);
            }
        }
        return result;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> result;
        for (int i = 0; i < VerticesCount(); ++i) {
            if (graph_[i][vertex]) {
                result.push_back(i);
            }
        }
        return result;
    }

private:
    std::vector<std::vector<bool>> graph_;

};


#endif //ALGORITHMS_MATRIXGRAPH_H
