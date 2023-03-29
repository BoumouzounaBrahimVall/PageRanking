//
// Created by S USER on 3/20/2023.
//

#ifndef PAGERANKING_GRAPHBUILDER_H
#define PAGERANKING_GRAPHBUILDER_H
#include "Node.cpp"
class GraphBuilder {
private:
    Graph g;
    vector<Node> nodes;
public:
    explicit GraphBuilder(vector<Node>& nodes) : nodes(nodes), g(nodes.size()) {}
    static double calculate_distance(Node , Node );
    void buildGraph(int ) ;
    vector<Node> getNodes() const ;
    Graph getGraph() const ;
};

#endif //PAGERANKING_GRAPHBUILDER_H
