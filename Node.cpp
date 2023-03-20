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


