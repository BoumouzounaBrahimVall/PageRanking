//
// Created by S USER on 3/20/2023.
//

#ifndef PAGERANKING_PAGERANKCALCULATOR_H
#define PAGERANKING_PAGERANKCALCULATOR_H
#include "GraphBuilder.cpp"
class PageRankCalculator {
private:
    vector<Node> nodes;
    vector<double> all_page_rank;
public:
    explicit PageRankCalculator() : nodes() ,all_page_rank() {}
    vector<double> calculatePageRank(Graph ) ;
    void printPageRank();
    const vector<Node> &getNodes() const ;
    void setNodes(const vector<Node> &);
    const vector<double> &getAllPageRank() const;
    void setAllPageRank(const vector<double> &) ;
};


#endif //PAGERANKING_PAGERANKCALCULATOR_H
