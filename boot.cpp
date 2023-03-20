#include <boost/graph/page_rank.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cmath>
#include <fstream>
#include <vector>

using namespace boost;
using namespace std;

struct Node {
    double longitude;
    double latitude;
    double house_price;
};

typedef std::pair<int, int> Edge;
typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

double calculate_distance(Node n1, Node n2) {
    double earth_radius = 6371; // km
    double lat1 = n1.latitude * M_PI / 180.0;
    double lat2 = n2.latitude * M_PI / 180.0;
    double delta_lat = (n2.latitude - n1.latitude) * M_PI / 180.0;
    double delta_lon = (n2.longitude - n1.longitude) * M_PI / 180.0;

    double a = std::sin(delta_lat/2) * std::sin(delta_lat/2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(delta_lon/2) * std::sin(delta_lon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));

    double distance = earth_radius * c;
    return distance;
}

std::vector<Node> read_excel_file(const std::string& filename) {
    std::vector<Node> nodes;
    std::ifstream input_file(filename);

    if (input_file.is_open()) {
        std::string line;
        while (std::getline(input_file, line)) {
            std::istringstream iss(line);
            std::string field;

            // read longitude
            if (!std::getline(iss, field, ','))
                continue;
            double longitude = std::stod(field);

            // read latitude
            if (!std::getline(iss, field, ','))
                continue;
            double latitude = std::stod(field);

            // read house price
            if (!std::getline(iss, field, ','))
                continue;
            double house_price = std::stod(field);

            // create a new node
            Node node = {longitude, latitude, house_price};
            nodes.push_back(node);
        }
        input_file.close();
    }
    return nodes;
}

vector<Node> read_csv_and_write_specific_columns(const string&  input_file_path) {
    ifstream input_file(input_file_path);
    string line;
    vector<Node> nodes{};
    int i =0;
    while (getline(input_file, line)) {
        stringstream line_stream(line);
        string cell;
        vector<string> cells;

        while (getline(line_stream, cell, ',')) {
            cells.push_back(cell);
        }
        if(i==0) {i=1;}
        else {
            Node n = {stof(cells[2]), stof(cells[1]), stof(cells[3])};
            cout<<"Node:{ lat: "<<n.latitude<<" lon:"<<n.longitude<<" price: "<<n.house_price<<endl;
            nodes.push_back(n);
        }
        i++;
        cout<<i<<endl;
        if(i==1000) break;
    }
    input_file.close();
    return nodes;
}


int main() {
    // read data from excel file
    std::vector<Node> nodes = read_csv_and_write_specific_columns(R"(C:\Users\S USER\Downloads\cleanTest.csv)");
    // create the graph
    Graph g(nodes.size());

    // add edges between nodes within 10 km of each other
    for (long i = 0; i < nodes.size(); i++) {
        for (long j = i+1; j < nodes.size(); j++) {
            double distance = calculate_distance(nodes[i], nodes[j]);
            if (distance <= 10) {
                Edge e(i, j);
                add_edge(e.first, e.second, g);
            }
        }
    }

    // apply the PageRank algorithm
    std::vector<double> rank_vec(num_vertices(g));
    page_rank(g, &rank_vec[0]);

    // print the ranks
    for (int i = 0; i < rank_vec.size(); i++) {
        std::cout << "Node " << i << " has PageRank " << rank_vec[i] << std::endl;
    }

    // write the graph to a Graphviz file for visualization
    std::ofstream graphviz_file("graph.dot");
    write_graphviz(graphviz_file, g);
    return 0;
}
