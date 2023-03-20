//
// Created by S USER on 3/20/2023.
//

#ifndef PAGERANKING_PAGERANKCALCULATOR_H
#define PAGERANKING_PAGERANKCALCULATOR_H
#include "GraphBuilder.h"
class PageRankCalculator {
private:
    vector<Node> nodes;
    vector<double> all_page_rank;
public:
    explicit PageRankCalculator() : nodes() ,all_page_rank() {}

    vector<double> calculatePageRank(Graph g) {
        // apply the PageRank algorithm
        // Graph g(node.size());
        vector<double> rank_vec(num_vertices(g));
        page_rank(g, &rank_vec[0]);

        rank_vec.insert(rank_vec.begin(),all_page_rank.begin(),all_page_rank.end());
        all_page_rank=rank_vec;

        //  node.insert(node.begin(),nodes.begin(),nodes.end());
        // nodes=node;
        return rank_vec;
    }

    void printPageRank() {
        // print the ranks
        for (long i = 0; i < all_page_rank.size(); i++) {
            std::cout << "Node " << i << " has PageRank " << all_page_rank[i] << std::endl;
        }
    }
    const vector<Node> &getNodes() const {
        return nodes;
    }

    void setNodes(const vector<Node> &nodes) {
        PageRankCalculator::nodes = nodes;
    }

    const vector<double> &getAllPageRank() const {
        return all_page_rank;
    }

    void setAllPageRank(const vector<double> &allPageRank) {
        all_page_rank = allPageRank;
    }
};


#endif //PAGERANKING_PAGERANKCALCULATOR_H
