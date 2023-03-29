#include "FileReader.cpp"
#include  <chrono>
using namespace std::chrono;
int main() {

    PageRankCalculator pageCal=FileReader::read_csv_optimal(R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\cleanedV2.csv)",R"(C:\Users\S USER\Documents\dataSet\archive\cleaned data\pageRanked dataSet\pageRankV2.csv)");
    pageCal.printPageRank();



    cout<<"\n\n\n ";

    string id="1",Cur="USD",country="Argentina";
    Node n(id,-24.8258,-65.4708,12000,Cur,country);
    string id2="1",Cur2="USD",country2="Argentina";
    Node n2(id2,-38.9829,-68.3508,52000,Cur2,country2);

    auto start = high_resolution_clock::now(); // start the clock
    cout<<"distance entre maison 1 et  maison 2 : "<<GraphBuilder::calculate_distance(n,n2)<<" Km";
    auto stop = high_resolution_clock::now(); // end the clock
    auto duration = duration_cast<microseconds>(stop - start); //calculate the duration of execution
    cout<<"\nduree de calcule de distance :"<<duration.count()<<" microseconds\n";

    return 0;
}