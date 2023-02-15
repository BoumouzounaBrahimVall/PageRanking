//
// Created by S USER on 2/13/2023.
//

#include "Node.h"

template<class T>
 Node<T>::Node(T dt) {
    data=dt;
    score=0;
}
template<class T>
T Node<T>::getData() const {
    return data;
}

template<class T>
void Node<T>::setData(T dt) {
    Node::data = dt;
}

template<class T>
double Node<T>::getScore() const {
    return score;
}

template<class T>
void Node<T>::setScore(double scre) {
    Node::score = scre;
}

template<class T>
const vector<Node<T>> &Node<T>::getAgencyListe() const {
    return agency_liste;
}

template<class T>
void Node<T>::setAgencyListe(const vector<Node> &agencyListe) {
    agency_liste = agencyListe;
}

template<class T>
void Node<T>::add_agencyElement(Node<T> &elem) {
    this->agency_liste.insert(elem);
}
