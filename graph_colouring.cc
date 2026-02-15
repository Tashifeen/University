#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <chrono>

#include "sos.h"   // uses your existing Sos class

using namespace std;

class Graph {
public:
  Graph(int n_, double p_): n(n_), p(p_), neighbours(n_) {
    long r = long(p*RAND_MAX);
    for(int i=1; i<n; ++i) {
      for(int j=0; j<i; ++j) {
        if (rand()<r) {
          neighbours[i].push_back(j);
        }
      }
    }
  }

  pair<int, vector<int>> best_colouring(int num_colours) {
    vector<int> partial_cost(n,0);
    vector<int> colouring(n, -1);
    colouring[0] = 0;
    vector<int> best_so_far(n);
    int best_cost = n+1;
    int current = 1;
    while (current>0) {
      if (colouring[current]<num_colours-1) {
        ++colouring[current];
        partial_cost[current] = partial_cost[current-1];
        for(int neigh: neighbours[current]) {
          if (colouring[neigh] == colouring[current])
            ++partial_cost[current];
        }
        if (current==n-1 && partial_cost[current]<best_cost) {
          best_cost = partial_cost[current];
          best_so_far = colouring;
        }
        if (current<n-1)
          ++current;
      } else {
        colouring[current] = -1;
        --current;
      }
    }
    return pair<int, vector<int>>(best_cost, best_so_far);
  }

private:
  int n;
  double p;
  vector<vector<int> > neighbours;
};

int main() {
  // Make runs reproducible (optional). Change seed if you want.
  srand(0);

  const double p = 0.5;
  const int trials = 20;

  ofstream out("gc_times.txt");
  if (!out) {
    cerr << "Error: could not open gc_times.txt\n";
    return 1;
  }

  // columns: n k t dt
  out << "n\tk\tt\tdt\n";
  cout << "n\tk\tmean_t(s)\terr_t(s)\n";
  cout << "-----------------------------------\n";

  for (int n = 10; n <= 17; ++n) {
    for (int k : {3, 4}) {
      Sos stats;

      for (int rep = 0; rep < trials; ++rep) {
        Graph graph(n, p);

        auto start = std::chrono::high_resolution_clock::now();
        volatile int cost = graph.best_colouring(k).first; // prevent over-optimization
        (void)cost;
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed = std::chrono::duration<double>(end - start).count();
        stats += elapsed;
      }

      double t  = stats.av();
      double dt = stats.err();

      out << n << "\t" << k << "\t" << t << "\t" << dt << "\n";
      cout << n << "\t" << k << "\t" << t << "\t" << dt << "\n";
    }
  }

  cout << "\nSaved: gc_times.txt (columns: n, k, t, dt)\n";
  return 0;
}
