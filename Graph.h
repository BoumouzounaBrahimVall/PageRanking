//
// Created by S USER on 2/13/2023.
//

#ifndef PAGERANKING_GRAPH_H
#define PAGERANKING_GRAPH_H
#include "node.cpp"

template<class T>
class Graph {
    vector<Node<T>> nodes; // all nodes in our graph
public:
    void addNode(T data);
    Node<T> getNode(T );
    void pageRank();
};

template<class T>
void Graph<T>::pageRank() {
    vector<double> old_scores(nodes.size(), 0.0);
    int num_iterations = 0;
    vector<double> pagerank_scores(nodes.size(), 1.0 / nodes.size());

    while (num_iterations < 100) {
        old_scores = pagerank_scores;
        double sum = 0;

        for (int i = 0; i < nodes.size(); i++) { // for each node

            double incoming_score = 0; //SOMME(P(i)/NBR_SORTANT)
            vector<Node<T>> linkedElem(nodes[i].getAgencyListe());
            for (int j = 0; j < linkedElem.size(); j++) { // for all linked node to node (i)
                if (i != j && find(linkedElem[j].begin(), linkedElem[j].end(), i) != linkedElem[j].end()) {

                    incoming_score += old_scores[j] / (double)linkedElem[j].size();
                }
            }
            // PR(p)= (1-0.85)/N + 0.85*incomming_score
            pagerank_scores[i] = (1 - 0.85) / (double)nodes.size() + 0.85 * incoming_score;
            sum += pagerank_scores[i]; // will be used in % calculation
        }

        for (double & pagerank_score : pagerank_scores) {
            pagerank_score /= sum; // pageranking in %
        }

        double error = 0;
        for (int i = 0; i < pagerank_scores.size(); i++) {
            error += abs(pagerank_scores[i] - old_scores[i]);
        }

        if (error < 1e-5) { // the algorithm converged so we stop
            break;
        }
        num_iterations++;
    }
}

template<class T>
Node<T> Graph<T>::getNode(T data) {
    for (int i = 0; i < nodes.size() ; ++i) {
        if(nodes[i].getData()==data) return nodes[i];
    }
    return nullptr;
}

template<class T>
void Graph<T>::addNode(T data) {
    nodes.insert(Node(data));
}


#endif //PAGERANKING_GRAPH_H
