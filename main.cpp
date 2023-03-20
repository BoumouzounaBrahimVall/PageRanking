#include "FileReader.cpp"


int main() {
    // read data from excel file
    // vector<Node> nodes = FileReader::read_csv(R"(C:\Users\S USER\Downloads\data test\testvall.csv)");

    PageRankCalculator pageCal=FileReader::read_csv_optimal(R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\cleanedV1.csv)",R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\pageRanked dataSet\pageRankV1.csv)");
    cout<<"ended \n";
    //  pageCal.printPageRank();

    return 0;
}