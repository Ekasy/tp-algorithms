#ifndef ALGORITHMS_IGRAPH_H
#define ALGORITHMS_IGRAPH_H


struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


#endif //ALGORITHMS_IGRAPH_H
