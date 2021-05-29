#ifndef ALGORITHMS_ARCGRAPH_H
#define ALGORITHMS_ARCGRAPH_H


#include <vector>
#include <utility>

#include "IGraph.h"


class ArcGraph : public IGraph {
public:
    ArcGraph(int size) : vertices_count(size) {}
    virtual ~ArcGraph() = default;

    explicit ArcGraph(const IGraph& graph) {
        graph_.clear();
        vertices_count = graph.VerticesCount();

        for (int v = 0; v < vertices_count; ++v) {
            std::vector<int> children = graph.GetNextVertices(v);
            for (auto & child : children) {
                graph_.emplace_back(std::make_pair(v, child));
            }
        }
    }

    void AddEdge(int from, int to) override {
        graph_.emplace_back(std::make_pair(from, to));
    }

    int VerticesCount() const override {
        return vertices_count;
    }

    std::vector<int> GetNextVertices(int vertex) const {
        std::vector<int> result;
        for (auto & pair : graph_) {
            if (pair.first == vertex) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> result;
        for (auto & pair : graph_) {
            if (pair.second == vertex) {
                result.push_back(pair.first);
            }
        }
        return result;
    }

private:
    std::vector<std::pair<int, int>> graph_;
    int vertices_count;
};


#endif //ALGORITHMS_ARCGRAPH_H
