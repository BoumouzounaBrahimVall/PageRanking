//
// Created by S USER on 3/20/2023.
//

#include "PageRankCalculator.h"
vector<double> PageRankCalculator::calculatePageRank(Graph g) {
    // apply the PageRank algorithm
    // Graph g(node.size());
    vector<double> rank_vec(num_vertices(g));
    page_rank(g, &rank_vec[0]);

    rank_vec.insert(rank_vec.begin(),all_page_rank.begin(),all_page_rank.end());
    all_page_rank=rank_vec;
    return rank_vec;
}
void PageRankCalculator::printPageRank() {
    // print the ranks
    for (long i = 0; i < all_page_rank.size(); i++) {
        std::cout << "Node " << i << " has PageRank " << all_page_rank[i] << std::endl;
    }
}
const vector<Node> & PageRankCalculator::getNodes() const {
    return nodes;
}

void PageRankCalculator::setNodes(const vector<Node> &nodes) {
    PageRankCalculator::nodes = nodes;
}

const vector<double> & PageRankCalculator::getAllPageRank() const {
    return all_page_rank;
}

void PageRankCalculator::setAllPageRank(const vector<double> &allPageRank) {
    all_page_rank = allPageRank;
}