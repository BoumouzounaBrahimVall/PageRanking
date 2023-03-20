//
// Created by S USER on 3/20/2023.
//

#include "GraphBuilder.h"
 double GraphBuilder::calculate_distance(Node n1, Node n2) {
    double earth_radius = 6371; // km
    double lat1 = n1.getLatitude() * M_PI / 180.0;
    double lat2 = n2.getLatitude() * M_PI / 180.0;
    double delta_lat = (n2.getLatitude() - n1.getLatitude()) * M_PI / 180.0;
    double delta_lon = (n2.getLongitude() - n1.getLongitude()) * M_PI / 180.0;

    double a = std::sin(delta_lat/2) * std::sin(delta_lat/2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(delta_lon/2) * std::sin(delta_lon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));

    double distance = earth_radius * c;
    return distance;
}
void GraphBuilder::buildGraph() {
    // add edges between nodes within 10 km of each other
    for (long i = 0; i < nodes.size(); i++) {
        for (long j = i + 1; j < nodes.size(); j++) {
            double distance = calculate_distance(nodes[i], nodes[j]);
            if (distance <= 10) {
                Edge e(i, j);
                add_edge(e.first, e.second, g);
            }
        }
    }
}
vector<Node> GraphBuilder::getNodes() const { return nodes; }
Graph GraphBuilder::getGraph() const { return g; }