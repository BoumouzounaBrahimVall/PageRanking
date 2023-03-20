//
// Created by S USER on 2/13/2023.
//

#ifndef PAGERANKING_NODE_H
#define PAGERANKING_NODE_H
#include <boost/graph/page_rank.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cmath>
#include <fstream>
#include <vector>
using namespace boost;
using namespace std;
typedef std::pair<int, int> Edge;
typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
using namespace std;
class Node {
private:
    string id;
    double longitude;
    double latitude;
    double house_price;
    string currency;
    string country;

public:
    Node(string& id, double latitude,double longitude, double house_price,string& currency,string& country)
            : id(id),latitude(latitude), longitude(longitude), house_price(house_price),currency(currency),country(country) {}

    double getLongitude() const ;
    double getLatitude() const ;
    double getHousePrice() const ;
    const string &getId() const ;
    const string &getCurrency() const;
    const string &getCountry() const ;
};


#endif //PAGERANKING_NODE_H
