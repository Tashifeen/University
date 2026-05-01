#include <vector>
#include <iostream>
#include <sstream> 
#include <math.h>
#include <random>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <queue>
#include <stdio.h>
#include "disjointSets.h"
using namespace std;

/* Structure to hold posision of vertices */

struct Position {
  double x;
  double y;
  Position() {}
  Position(double x1, double y1): x(x1), y(y1) {}
  double norm() const {
    return sqrt(x*x + y*y);
  }
};

inline
Position operator+(const Position& p1, const Position& p2) {
  return Position(p1.x+p2.x, p1.y+p2.y);
}

inline
Position operator-(const Position& p1, const Position& p2) {
  return Position(p1.x-p2.x, p1.y-p2.y);
}

inline
double dot(const Position& p1, const Position& p2) {
  return p1.x*p2.x + p1.y*p2.y;
}

inline
Position operator*(double c, const Position& p) {
  return Position(c*p.x, c*p.y);
}

ostream& operator<<(ostream& out, const Position& e) {
  out << "(" << e.x << "," << e.y << ")";
  return out;
}


/* Stucture to hold edge information */

struct Edge {
  unsigned vertex1;
  unsigned vertex2;
  double distance;

  Edge() {}
  Edge(int v1, int v2, double d): vertex1(v1), vertex2(v2), distance(d) {}
};


bool operator<(const Edge& e1, const Edge& e2) {
  return e1.distance > e2.distance;  // Ensure min-heap not max-heap
}


/* Graph class */

class Graph {
private:
  unsigned num_vertices;
  unsigned num_edges;
  vector<vector<Edge>> adjacencyList;
  vector<Position> vertices;

public:
  Graph(unsigned n, double edgeProb): num_vertices(n), adjacencyList(n) {
    vertices.reserve(n);  // set capacity to 10
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<double> randCoordinate(-50.0, 50.0);
    double len = 75.0/sqrt(n);
    // create n Vertices that are nicely spaced
    bool too_many_iterations;
    do {  // redo if necessary
      too_many_iterations = false;
      for(unsigned i=0; i<n; ++i) {
	Position pos;
	bool okPosition;
	do {
	  okPosition = true;
	  pos = Position(randCoordinate(gen), randCoordinate(gen));
	  if (pos.norm() < 15) {
	    okPosition = false;
	  }
	  if (okPosition) {
	    for(unsigned j=0; j<i; ++j) {
	      if ((pos - vertices[j]).norm() < len) {
		okPosition = false;
		break;
	      }
	    }
	  }
	} while(!okPosition);
	vertices.push_back(pos);
      }

      if (edgeProb>1.0) {
	cout << "error: edgeProb must be less than 1\n";
      }
      if (edgeProb>0.75) {
	cout << "warning: high edgeProb migh mean we cannot generate a pretty graph\n";
      }
      num_edges = (unsigned) (edgeProb*n*n/2);
    
      std::uniform_int_distribution<int> randVertex(0, n-1);
      int cnt = 0;
      for(unsigned i=0; i<num_edges; ++i) {
	unsigned v1, v2;
	bool okEdge;
	if (too_many_iterations)
	    break;
	do {
	  v1 = randVertex(gen);
	  v2 = randVertex(gen);
	  okEdge = true;
	  ++cnt;
	  if (cnt>10000) {
	    too_many_iterations = true;
	    okEdge = false;
	    break;
	  }
	  if (v1 == v2) {
	    okEdge = false;
	  }
	  if (okEdge) {
	    // stop repetitions of edges
	    for (unsigned k=0; k<adjacencyList[v1].size(); ++k) {
	      if (adjacencyList[v1][k].vertex2 == v2) {
		okEdge = false;
		break;
	      }
	    }
	  }
	  if (okEdge) {
	    // stop edges going close to vertices
	    for(unsigned j=0; j<n; ++j) {
	      if (j==v1 || j==v2)
		continue;
	      Position d13 = vertices[v1] - vertices[j];
	      Position d23 = vertices[v2] - vertices[j];
	      double n13 = dot(d13, d13);
	      double n23 = dot(d23, d23);
	      double d = dot(d13, d23);
	      double t = (n13-d)/(n23+n13-2.0*d);
	      if (t>0.0 && t<1.0) {
		if (((1.0-t)*d13 + t*d23).norm()< 15) {
		  okEdge = false;
		  break;
		}
	      }
	    }
	  }
	  if (too_many_iterations)
	    break;
	} while(!okEdge);
	if (too_many_iterations) {
	  break;
	}
	Edge e(v1, v2, (vertices[v1] - vertices[v2]).norm());
	adjacencyList[v1].push_back(e);
	e.vertex1 = v2;
	e.vertex2 = v1;
	adjacencyList[v2].push_back(e);
      }
      if (too_many_iterations) {
	break;
      }
    } while (too_many_iterations);
  }

  unsigned size() const {return num_vertices;}

  const vector<Edge>& edges_connecting(int vertex) {
    return adjacencyList[vertex];
  }
  
  void print() {
    int cnt = 0;
    for(const Position& pos: vertices) {
      cout << "vertex[" << cnt++ << "] = (" << pos.x
	   << "," << pos.y << ")\n";
    }
    int cnt_edges = 0;
    for(unsigned i=0; i<size(); ++i) {
      for(const Edge e: edges_connecting(i)) {
	if (e.vertex2<i)
	  continue;
	cout << "edge[" << cnt_edges << "] = " << i << "-"
	     << e.vertex2 << ", "
	     << e.distance << endl;
	++cnt_edges;
      }
    }
    cout << "Number of edges = " << num_edges << endl;
  }

  void draw() const {
    vector<Edge> edges;
    draw(edges);
  }
  
  void draw(const vector<Edge>& highlightEdges, string title="", string file_name="tmpfile.py") const {
    ofstream plot(file_name);

    plot << "import numpy as np\n";
    plot << "import matplotlib.pyplot as plt\n";
    plot << "fig, ax = plt.subplots()\n";
    plot << "ax.set_aspect('equal', adjustable='datalim')\n";
    if (title!="") {
      plot << "plt.title(\"" << title << "\")\n";
    }

    for(unsigned i=0; i<size(); ++i) {
      for(const Edge& e: adjacencyList[i]) {
	if (e.vertex2<i)
	  continue;
	plot << matplotlibEdge(e);
      }
    }
    for(const Edge& e: highlightEdges) {
      plot << matplotlibEdge(e, "b", 1, 2);
    }
	  
    int cnt = 0;
    for(const Position& p: vertices) {
      plot << "cir = plt.Circle(" << p << ", 5, color=\"red\", fill=True, zorder=2)\n";
      plot << "ax.add_patch(cir)\n";
      plot << "plt.text(" << p.x << "," << p.y << "," << cnt++
	   << ", ha=\"center\", ma=\"center\", va=\"center\", zorder=3)\n";
    }
    plot << "plt.show()\n";
    plot.close();
    sleep(0.2);
    string cmd = "python3 " + string(file_name) + " &";
    system(cmd.c_str());
  }

  vector<Edge> prims();
  vector<Edge> kruskals();

private:
  inline
  string matplotlibEdge(const Edge& e, string col="ro", int zorder=0, double lw=1) const {
    Position v1 = vertices[e.vertex1];
    Position v2 = vertices[e.vertex2];
    stringstream ss;
    ss << "plt.plot([" << v1.x << "," << v2.x << "],["
       << v1.y << "," << v2.y << "], \""
       << col << "-\", zorder=" << zorder << ", linewidth=" << lw << ")\n";
    return ss.str();
  }
};


vector<Edge> Graph::prims() {
  vector<Edge> mst;

  // You need to fill this in

  draw(mst, "Prim's Algorithm", "prims.py");
  return mst;
}

vector<Edge> Graph::kruskals() {
  vector<Edge> mst;
  
  // You need to fill this in
  
  draw(mst, "Kruskal's Algorithm", "kruskals.py");
  return mst;
}


int main() {
  Graph graph(15, 0.3);
  graph.print();

  // For illustrive purposes
  graph.draw(graph.edges_connecting(0), "Edges connecting vertex 0");

  graph.prims();
  graph.kruskals();

}
