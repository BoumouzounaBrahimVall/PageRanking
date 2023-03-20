//
// Created by S USER on 3/20/2023.
//

#ifndef PAGERANKING_FILEREADER_H
#define PAGERANKING_FILEREADER_H
#include "PageRankCalculator.cpp"
class FileReader {
public:
/*
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
*/
    static PageRankCalculator read_csv_optimal(const string& ,const string& );

};


#endif //PAGERANKING_FILEREADER_H
