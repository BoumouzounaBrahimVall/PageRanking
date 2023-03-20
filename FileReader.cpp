

#include "FileReader.h"
 PageRankCalculator FileReader::read_csv_optimal(const string& input_file_path,const string& output_file_path) {
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
