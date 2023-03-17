//
// Created by S USER on 2/15/2023.
//
//#include "Graph.h"
#include "dump.cpp"
//double latitude;
//double longitude;
//double price;
int main() {
    // Create a vector of houses
    std::vector<House> houses;
    // ... populate the vector with data ...
    houses.push_back({12.3,13.5,4500});
    houses.push_back({16.3,19.5,8900});

    houses.push_back({65.3,34.5,1500});

    houses.push_back({-12.3,56.5,3000});

    // Create the graph and add nodes and edges
    const double threshold_distance = 10.0; // Set a threshold distance of 10 km
    Graph graph;
    create_graph(houses, graph);

    // Calculate the PageRank of each house in the graph
    std::vector<double> page_rank(boost::num_vertices(graph));
    calculate_page_rank(graph, page_rank);
    cout<<"here out:=================\n";
    // Print the PageRank of each house
    for (std::size_t i = 0; i < houses.size(); ++i) {
        std::cout << "House " << i << " has PageRank " << page_rank[i] << std::endl;
    }

    // ... visualize the data ...
}