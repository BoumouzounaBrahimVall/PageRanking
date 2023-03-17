#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/page_rank.hpp>

#include <bits/stdc++.h>
#include <cmath>
#include <vector>
using namespace std;
// Define the House struct to hold the latitude, longitude, and price of each house
struct House {
    double latitude;
    double longitude;
    double price;
};

// Define a function to calculate the distance between two houses using the Haversine formula
double haversine_distance(const House& house1, const House& house2) {
    const double R = 6371.0; // Earth's radius in km
    const double lat1 = house1.latitude * M_PI / 180.0; // Convert degrees to radians
    const double lat2 = house2.latitude * M_PI / 180.0;
    const double lon1 = house1.longitude * M_PI / 180.0;
    const double lon2 = house2.longitude * M_PI / 180.0;

    const double dlat = std::sin((lat2 - lat1) / 2.0);
    const double dlon = std::sin((lon2 - lon1) / 2.0);
    const double a = dlat * dlat + std::cos(lat1) * std::cos(lat2) * dlon * dlon;
    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    return R * c;
}

// Define the graph type using an adjacency_list with weighted edges
typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,House, EdgeWeightProperty> Graph;

// Define a function to create the graph from a vector of houses
void create_graph(const std::vector<House>& houses, Graph& graph) {
    const std::size_t n = houses.size();
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            const double distance = haversine_distance(houses[i], houses[j]);
            if (distance < 10) { // THRESHOLD_DISTANCE is a constant value
                boost::add_edge(i, j, distance, graph);
            }
        }
    }
}
// Define a function to calculate the PageRank of each house in the graph
void calculate_page_rank(const Graph& graph, std::vector<double>& page_ranks) {
    const double damping_factor = 0.85;
    const double epsilon = 1e-6;
    const std::size_t max_iterations = 100;

    typedef std::map<Graph::vertex_descriptor, double> RankMap;
    RankMap rank_map;
    page_rank(graph,boost::make_assoc_property_map(rank_map));
    //int i=0;
    for (auto vertex_pair : rank_map) {
        page_ranks[vertex_pair.first]=vertex_pair.second;
        std::cout << "Vertex " << vertex_pair.first << " has rank " << vertex_pair.second << std::endl;
    }


    /*
     boost::page_rank(
             graph,
             boost::make_iterator_property_map(page_rank.begin(), boost::get(boost::vertex_index, graph)),
             boost::pagerank_damping_factor(damping_factor),
             boost::pagerank_tol(epsilon),
             boost::pagerank_max_iter(max_iterations)
     );*/
}

