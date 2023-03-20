//
// Created by S USER on 2/13/2023.
//

#include "Node.h"
double Node::getLongitude() const { return longitude; }
double Node::getLatitude() const { return latitude; }
double Node::getHousePrice() const { return house_price; }
const string & Node::getId() const {return id;}
const string & Node::getCurrency() const {return currency;}
const string & Node::getCountry() const {return country;}