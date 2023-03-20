//
// Created by S USER on 3/19/2023.
//

#ifndef PAGERANKING_PAGERANKGRAPH_H
#define PAGERANKING_PAGERANKGRAPH_H
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
class Node {
private:
    double longitude;
    double latitude;
    double house_price;
public:
    Node(double longitude, double latitude, double house_price)
            : longitude(longitude), latitude(latitude), house_price(house_price) {}
    double getLongitude() const { return longitude; }
    double getLatitude() const { return latitude; }
    double getHousePrice() const { return house_price; }
};

class GraphBuilder {
private:
    Graph g;
    vector<Node> nodes;
public:
    GraphBuilder(vector<Node>& nodes) : nodes(nodes), g(nodes.size()) {}
    double calculate_distance(Node n1, Node n2) {
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
    void buildGraph() {
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

    Graph getGraph() const { return g; }
};

class PageRankCalculator {
private:
    vector<Node>& nodes;
    Graph& g;
    vector<double> rank_vec;
public:
    PageRankCalculator(vector<Node>& nodes, Graph& g) : nodes(nodes), g(g), rank_vec(num_vertices(g)) {}

    void calculatePageRank() {
        // apply the PageRank algorithm
        page_rank(g, &rank_vec[0]);
    }

    void printPageRank() {
        // print the ranks
        for (int i = 0; i < rank_vec.size(); i++) {
            std::cout << "Node " << i << " has PageRank " << rank_vec[i] << std::endl;
        }
    }
};

class FileReader {
public:
    static vector<Node> read_csv(const string& input_file_path) {
        ifstream input_file(input_file_path);
        string line;
        vector<Node> nodes{};
        int i = 0;
        while (getline(input_file, line)) {
            stringstream line_stream(line);
            string cell;
            vector<string> cells;

            while (getline(line_stream, cell, ',')) {
                cells.push_back(cell);
            }
            if (i == 0) { i = 1; }
            else {
                Node n(stof(cells[2]), stof(cells[1]), stof(cells[3]));
                cout << "Node:{ lat: " << n.getLatitude() << " lon:" << n.getLongitude() << " price: " << n.getHousePrice() << endl;
                nodes.push_back(n);
            }
            i++;
            cout << i << endl;
            if (i == 1000) break;
        }
        input_file.close();
        return nodes;
    }
};

class GraphWriter {
public:
    static void writeGraph(const Graph& g, const string& filename) {
        // write the graph to a Graphviz file for visualization
        std::ofstream graphviz_file(filename);
        write_graphviz(graphviz_file, g);
    }
};

int main() {
    // read data from excel file
    vector<Node> nodes = FileReader::read_csv(R"(C:\Users\S USER\Downloads\cleanTest.csv)");

    // create the graph
    GraphBuilder graphBuilder(nodes);
    return 0;
}

#endif //PAGERANKING_PAGERANKGRAPH_H
