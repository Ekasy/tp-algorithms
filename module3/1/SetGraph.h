#ifndef ALGORITHMS_SETGRAPH_H
#define ALGORITHMS_SETGRAPH_H


#include <vector>
#include <set>

#include "IGraph.h"


class SetGraph : public IGraph {
public:
    SetGraph(int size) : graph_(size) {}
    virtual ~SetGraph() = default;

    explicit SetGraph(const IGraph& graph) {
        graph_.clear();
        graph_.resize(graph.VerticesCount());

        for (int v = 0; v < graph.VerticesCount(); ++v) {
            std::vector<int> children = graph.GetNextVertices(v);
            for (auto & child : children) {
                graph_[v].insert(child);
            }
        }
    }

    void AddEdge(int from, int to) override {
        graph_[from].insert(to);
    }

    int VerticesCount() const override {
        return graph_.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> result;
        result.resize(VerticesCount());
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
    std::vector<std::set<int>> graph_;

};

#endif //ALGORITHMS_SETGRAPH_H
