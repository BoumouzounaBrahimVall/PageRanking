#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Node {
    double longitude;
    double latitude;
    double house_price;
};

std::vector<Node> read_excel_file(std::string filename) {
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

int main() {
    std::vector<Node> nodes = read_excel_file("C:\\Users\\S USER\\Downloads\\testvall.xlsx");
    for (int i = 0; i < nodes.size(); i++) {
        std::cout << "Node " << i << " - Longitude: " << nodes[i].longitude
                  << ", Latitude: " << nodes[i].latitude
                  << ", House Price: " << nodes[i].house_price << std::endl;
    }
    return 0;
}
