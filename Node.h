//
// Created by S USER on 2/13/2023.
//

#ifndef PAGERANKING_NODE_H
#define PAGERANKING_NODE_H
#include <bits/stdc++.h>
using namespace std;


template<class T>
class Node{
private:
    T data; // the node data (in our case it's probably a Geographic point )
    double score; // the score of a node
    vector<Node> agency_liste; // all nodes accessible from this node (previuos Nodes)
    int nbrNext;
public:
    explicit Node(T);
    T getData() const;

    void setData(T );

    double getScore() const;

    void setScore(double );

    const vector<Node> &getAgencyListe() const;

    void setAgencyListe(const vector<Node> &);
    void add_agencyElement(Node<T> & );

public:

};



#endif //PAGERANKING_NODE_H
