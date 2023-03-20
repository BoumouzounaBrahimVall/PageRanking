#include "FileReader.cpp"


int main() {

    PageRankCalculator pageCal=FileReader::read_csv_optimal(R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\cleanedV1.csv)",R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\pageRanked dataSet\pageRankV1.csv)");
    cout<<"ended \n";

    return 0;
}