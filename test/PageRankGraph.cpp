
#include <boost/graph/page_rank.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cmath>
#include <fstream>
#include <vector>

using namespace boost;
using namespace std;
typedef std::pair<long, long> Edge;
typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
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

    double getLongitude() const { return longitude; }
    double getLatitude() const { return latitude; }
    double getHousePrice() const { return house_price; }
    const string &getId() const {return id;}
    const string &getCurrency() const {return currency;}
    const string &getCountry() const {return country;}
};

class GraphBuilder {
private:
    Graph g;
    vector<Node> nodes;
public:
    explicit GraphBuilder(vector<Node>& nodes) : nodes(nodes), g(nodes.size()) {}
    static double calculate_distance(Node n1, Node n2) {
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
    vector<Node> getNodes() const { return nodes; }
    Graph getGraph() const { return g; }
};

class PageRankCalculator {
private:
    vector<Node> nodes;
    vector<double> all_page_rank;
public:
    explicit PageRankCalculator() : nodes() ,all_page_rank() {}

    vector<double> calculatePageRank(Graph g) {
        // apply the PageRank algorithm
       // Graph g(node.size());
        vector<double> rank_vec(num_vertices(g));
        page_rank(g, &rank_vec[0]);

        rank_vec.insert(rank_vec.begin(),all_page_rank.begin(),all_page_rank.end());
        all_page_rank=rank_vec;

      //  node.insert(node.begin(),nodes.begin(),nodes.end());
       // nodes=node;
        return rank_vec;
    }

     void printPageRank() {
        // print the ranks
        for (long i = 0; i < all_page_rank.size(); i++) {
            std::cout << "Node " << i << " has PageRank " << all_page_rank[i] << std::endl;
        }
    }
    const vector<Node> &getNodes() const {
        return nodes;
    }

    void setNodes(const vector<Node> &nodes) {
        PageRankCalculator::nodes = nodes;
    }

    const vector<double> &getAllPageRank() const {
        return all_page_rank;
    }

    void setAllPageRank(const vector<double> &allPageRank) {
        all_page_rank = allPageRank;
    }
};

class FileReader {
public:

    static vector<Node> read_csv(const string& input_file_path) {
        ifstream input_file(input_file_path);
        string line;
        vector<Node> nodes{};
        long i = 0;
        while (getline(input_file, line)) {
            stringstream line_stream(line);
            string cell;
            vector<string> cells;

            while (getline(line_stream, cell, ',')) {
                cells.push_back(cell);
            }
            if (i == 0) { i = 1; }
            else {
                Node n(cells[0],stof(cells[1]), stof(cells[2]), stof(cells[3]),cells[4],cells[5]);
                cout << "Node:{ lat: " << n.getLatitude() << " lon:" << n.getLongitude() << " price: " << n.getHousePrice() << endl;
                nodes.push_back(n);
            }
            i++;
            cout << i << endl;
            if (i == 3000) break;
        }
        input_file.close();
        return nodes;
    }

    static PageRankCalculator read_csv_optimal(const string& input_file_path,const string& output_file_path) {
        ifstream input_file(input_file_path);
        ofstream output_file(output_file_path);//output_file_path

        string line;
        vector<Node> nodes{};
        PageRankCalculator pageCal;
        long i = 0;
        const int CHUNK_SIZE = 1000; // read 1000 lines at a time
        while (getline(input_file, line)) {
            stringstream line_stream(line);
            string cell;
            vector<string> cells;

            while (getline(line_stream, cell, ',')) {
                cells.push_back(cell);
            }
            if (i == 0) {
                output_file<<"id,lat,lon,price,currency,country,page_rank"<<endl;
                i = 1; }
            else {
                Node n(cells[0],stof(cells[1]), stof(cells[2]), stof(cells[3]),cells[4],cells[5]);
             //  cout << "Node:{ lat: " << n.getLatitude() << " lon:" << n.getLongitude() << " price: " << n.getHousePrice() <<" }"<<endl;
                nodes.push_back(n);
            }
            i++;

            if (i % CHUNK_SIZE == 0) {
                GraphBuilder graphBuilder(nodes);
                graphBuilder.buildGraph();
                vector<double> pg=pageCal.calculatePageRank(graphBuilder.getGraph());
                for(int j=0;j<nodes.size();j++) {
                    output_file<<nodes[j].getId()<<","<<nodes[j].getLatitude()<<","<<nodes[j].getLongitude()
                            <<","<<nodes[j].getHousePrice()<<","<<nodes[j].getCurrency()<<","<<nodes[j].getCountry()<<","<<pg[j]<<endl;
                }
                nodes.clear(); // clear the nodes vector to free up memory
            }
          //  if(i==3000) break;
        }
        // process the remaining nodes
        if (!nodes.empty()) {
            GraphBuilder graphBuilder(nodes);
            graphBuilder.buildGraph();
            vector<double> pg=pageCal.calculatePageRank(graphBuilder.getGraph());
            for(int j=0;j<nodes.size();j++) {
                output_file<<nodes[j].getId()<<","<<nodes[j].getLatitude()<<","<<nodes[j].getLongitude()
                           <<","<<nodes[j].getHousePrice()<<","<<nodes[j].getCurrency()<<","<<nodes[j].getCountry()<<","<<pg[j]<<endl;
            }
        }

        input_file.close();
        output_file.close();
        return pageCal;
    }

};

/*
class FileReader {
public:
    static vector<Node> read_csv(const string& input_file_path, int chunk_size) {
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
                nodes.push_back(n);
            }
            i++;
            if (i % chunk_size == 0) {
                // Process the chunk
                GraphBuilder graphBuilder(nodes);
                graphBuilder.buildGraph();
                PageRankCalculator pageRankCalculator(graphBuilder.getNodes(), graphBuilder.getGraph());
                pageRankCalculator.calculatePageRank();

                // Accumulate the results
                for (long j = 0; j < nodes.size(); j++) {
                    pageRankCalculator.rank_vec[j] += pageRankCalculator.rank_vec[j];
                }

                nodes.clear();
            }
        }
        input_file.close();

        // Process the remaining nodes
        if (!nodes.empty()) {
            GraphBuilder graphBuilder(nodes);
            graphBuilder.buildGraph();
            PageRankCalculator pageRankCalculator(graphBuilder.getNodes(), graphBuilder.getGraph());
            pageRankCalculator.calculatePageRank();

            // Accumulate the results
            for (long j = 0; j < nodes.size(); j++) {
                pageRankCalculator.rank_vec[j] += pageRankCalculator.rank_vec[j];
            }
        }

        return rank_vec;
    }
};
*/

int main() {
    // read data from excel file
   // vector<Node> nodes = FileReader::read_csv(R"(C:\Users\S USER\Downloads\data test\testvall.csv)");

    PageRankCalculator pageCal=FileReader::read_csv_optimal(R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\cleanedV1.csv)",R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\pageRanked dataSet\pageRankV1.csv)");
    cout<<"ended \n";
  //  pageCal.printPageRank();

    return 0;
}



class GraphWriter {
public:
    static void writeGraph(const Graph& g, const string& filename) {
        // write the graph to a Graphviz file for visualization
        std::ofstream graphviz_file(filename);
        write_graphviz(graphviz_file, g);
    }
};