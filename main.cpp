#include "graph.cpp"
using namespace std;

const double damping_factor = 0.85;
const int max_iterations = 100; // 100 to get the most effichient pageranking scores
const double tolerance = 1e-5; // it's for getting sure that the algorithm has converged

vector<vector<int>> adjacency_list = {
  {1, 2},     // node 0 represents place A
  {2, 3},     // node 1 represents place B
  {0, 3},     // node 2 represents place C
  {3},        // node 3 represents place D
};
// initialize pagerank scores
vector<double> pagerank_scores(adjacency_list.size(), 1.0 / adjacency_list.size());

void pagerank() {
  vector<double> old_scores(adjacency_list.size(), 0.0);
  int num_iterations = 0;

  while (num_iterations < max_iterations) {
    old_scores = pagerank_scores;
    double sum = 0;

    for (int i = 0; i < adjacency_list.size(); i++) { // for each node
      double incoming_score = 0; //SOMME(P(i)/NBR_SORTANT)
      for (int j = 0; j < adjacency_list.size(); j++) { // for all linked node to node (i)
        if (i != j && find(adjacency_list[j].begin(), adjacency_list[j].end(), i) != adjacency_list[j].end()) {
          incoming_score += old_scores[j] / (double)adjacency_list[j].size();
        }
      }
      // PR(p)= (1-0.85)/N + 0.85*incomming_score
      pagerank_scores[i] = (1 - damping_factor) / (double)adjacency_list.size() + damping_factor * incoming_score;
      sum += pagerank_scores[i]; // will be used in % calculation
    }

    for (int i = 0; i < pagerank_scores.size(); i++) {
      pagerank_scores[i] /= sum; // pageranking in %
    }

    double error = 0;
    for (int i = 0; i < pagerank_scores.size(); i++) {
      error += abs(pagerank_scores[i] - old_scores[i]);
    }

    if (error < tolerance) { // the algorithm converged so we stop
      break;
    }

    num_iterations++;
  }
}

int main() {
  pagerank();
  for (int i = 0; i < pagerank_scores.size(); i++) {
    cout << "PageRank score for place " << char(i + 'A') << " is " << pagerank_scores[i] << endl;
  }
  return 0;
}

/**
 In this example, the graph is represented using an adjacency list,
 where each node represents a geographic location affected by
 a disaster and the edges represent the degree of influence or
 impact of the disaster between two places. The PageRank algorithm
 is then applied to the graph to compute the ranking of each location
 based on its importance in the overall network. The resulting scores are printed to the console.

we assume that the graph is connected, meaning that every location is reachable
 from every other location. If this is not the case, the algorithm may need
 to be modified to handle disconnected graphs.
 */

/**
 damping_factor, max_iterations, and tolerance are parameters used in the
 PageRank algorithm for determining the convergence of the algorithm and controlling its behavior:

damping_factor: This is a constant value between 0 and 1 that represents
 the probability that a user will randomly jump to another page rather than following a
 link on the current page. In other words, it models the likelihood that a user will
 become bored or disinterested with the current page and decide to navigate away from it.
 A typical value for the damping factor is 0.85.

max_iterations: This is the maximum number of iterations
 that the algorithm will perform before stopping, regardless of whether
 it has converged or not. Setting this value too low may result in an inaccurate ranking,
 while setting it too high may cause the algorithm to take a long time to converge.

tolerance: This is the threshold below which the algorithm is considered to have converged.
 When the change in PageRank scores between two iterations falls below this threshold,
 the algorithm is said to have converged and stops iterating.
 A typical value for the tolerance is 1e-5, which represents a very small change in the scores.

 */