#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<vvc> vvvc;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef struct D3 {
  double x, y, z;
  D3() : x(0.0), y(0.0), z(0.0) {}
  D3(double  x, double y, double z) : x(x), y(y), z(z) {}
} D3;
typedef struct Face {
  D3 center;
  int type;
  Face(D3 center, int type) : center(center), type(type) {}
  Face(int x, int y, int z, int type) : center(x, y, z), type(type) {}
} Face;
typedef struct Edge {
  D3 src, dst;
  Edge(const D3 &i, const D3 &j) : src(min(i, j)), dst(max(i, j)) {}
} Edge;
typedef struct Point {
  vi edges;
  D3 center;
  Point(const D3 &center) : edges(), center(center) {}
} Point;
typedef pair<double, int> pdi;
typedef priority_queue<pdi, vector<pdi>, greater<pdi> > pq;

#define FACE_X 0
#define FACE_Y 1
#define FACE_Z 2

#define MAX_DENOMINATOR 7

#define DEBUG cout<<"Debug: "<<__LINE__<<endl

D3 FACE_CENTER_TO_EDGE[3][4] = 
{
  {
    D3( 0, -1, -1),
    D3( 0,  1, -1),
    D3( 0,  1,  1),
    D3( 0, -1,  1)
  },
  {
    D3(-1,  0, -1),
    D3( 1,  0, -1),
    D3( 1,  0,  1),
    D3(-1,  0,  1)
  },
  {
    D3(-1, -1,  0),
    D3( 1, -1,  0),
    D3( 1,  1,  0),
    D3(-1,  1,  0)
  }
};

bool operator<(const D3 &i, const D3 &j) {
  if (i.x != j.x) return i.x < j.x;
  if (i.y != j.y) return i.y < j.y;
  return i.z < j.z;
}
D3 operator+(const D3 &d, const D3 &e) {
  return D3(d.x + e.x, d.y + e.y, d.z + e.z); 
}
D3 operator-(const D3 &d, const D3 &e) {
  return D3(d.x - e.x, d.y - e.y, d.z - e.z); 
}
D3 operator*(double f, const D3 &d) {
  return D3(f*d.x, f*d.y, f*d.z); 
}
bool operator==(const D3 &d, const D3 &e) {
  return d.x == e.x && d.y == e.y && d.z == e.z;
}
double abs(const D3 &d) {
  return sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
}
void printD3(const D3 &d) {
  cout << d.x << ", " << d.y << ", " << d.z << endl;
}

int gcd(int a, int b) {
  return a%b == 0 ? b : gcd(b, a%b);
}
vd constructMesh() {
  vd output;
  for (int a = 2; a <= MAX_DENOMINATOR; a++) {
    for (int b = 1; b <= a-1; b++) {
      if (gcd(a, b) > 1) {
        continue;
      }
      output.push_back((double)b / a);
    }
  }
  return output;
}

vector<Face> constructFaces(const vvvc &input) {
  vector<Face> faces;
  for (int i = 1; i < 5; i++) {
    int i2 = 2*i;
    for (int j = 1; j < 5; j++) {
      int j2 = 2*j;
      for (int k = 1; k < 5; k++) {
        int k2 = 2*k;
        if (input[i-1][j][k] != input[i][j][k]) {
          faces.push_back(Face(i2, j2+1, k2+1, FACE_X));
        }
        if (input[i][j-1][k] != input[i][j][k]) {
          faces.push_back(Face(i2+1, j2, k2+1, FACE_Y));
        }
        if (input[i][j][k-1] != input[i][j][k]) {
          faces.push_back(Face(i2+1, j2+1, k2, FACE_Z));
        }
      }
    }
  }
  return faces;
}

bool equalsEdge(const Edge &e1, const Edge &e2) {
  return e1.src == e2.src && e1.dst == e2.dst; 
}

void addEdge(vector<Edge> &edges, const Edge &e) {
  for (int i = 0; i < edges.size(); i++) {
    if (equalsEdge(edges[i], e)) {
      return;
    }
  }
  edges.push_back(e);
}

vector<Edge> constructEdges(const vector<Face> &faces) {
  vector<Edge> edges;
  for (int i = 0; i < faces.size(); i++) {
    for (int j = 0; j < 4; j++) {
      addEdge(edges, Edge(
          faces[i].center + FACE_CENTER_TO_EDGE[faces[i].type][j],
          faces[i].center + FACE_CENTER_TO_EDGE[faces[i].type][(j+1)%4]));
    }
  }
  return edges;
}

double sumAbsEachDiff(const D3 &i, const D3 &j) {
  return abs(i.x - j.x) + abs(i.y - j.y) + abs(i.z - j.z);
}

bool edgeOnFace(const Edge &e, const Face &f) {
  return sumAbsEachDiff(e.src, f.center) == 2 &&
      sumAbsEachDiff(e.dst, f.center) == 2;
}

bool connectedEdges(const Edge &e1, const Edge &e2, const vector<Face> &faces) {
  for (int i = 0; i < faces.size(); i++) {
    if (edgeOnFace(e1, faces[i]) && edgeOnFace(e2, faces[i])) {
      return true;
    }
  }
  return false;
}

vvi constructEdgeGraph(const vector<Face> &faces, const vector<Edge> &edges) {
  vvi nextEdge(edges.size());
  for (int i = 0; i < edges.size(); i++) {
    for (int j = i+1; j < edges.size(); j++) {
      if (connectedEdges(edges[i], edges[j], faces)) {
        nextEdge[i].push_back(j);
        nextEdge[j].push_back(i);
      }
    }
  }
  return nextEdge;
}

bool isOneOfEndPoint(const D3 &p, const vector<Edge> &edges) {
  for (int i = 0; i < edges.size(); i++) {
    if (edges[i].src == p || edges[i].dst == p) {
      return true;
    }
  }
  return false;
}

void addPoint(vector<Point> &points, vvi &edge2point, int edge_id) {
  points.back().edges.push_back(edge_id);
  edge2point[edge_id].push_back(points.size() - 1);
}

void constructPoints(const vector<Edge> &edges, const vd &mesh,
    vector<Point> &points, vvi &edge2point) {
  points.clear();
  for (int x = 2; x <= 8; x += 2) {
    for (int y = 2; y <= 8; y += 2) {
      for (int z = 2; z <= 8; z += 2) {
        D3 p(x, y, z);
        if (isOneOfEndPoint(p, edges)) {
          points.push_back(Point(p));
          for (int i = 0; i < edges.size(); i++) {
            if (edges[i].src == p) {
              addPoint(points, edge2point, i);
            } else if (edges[i].dst == p) {
              addPoint(points, edge2point, i);
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < edges.size(); i++) {
    D3 p = edges[i].src;
    D3 v = edges[i].dst - edges[i].src;
    for (int j = 0; j < mesh.size(); j++) {
      points.push_back(Point(p + mesh[j]*v));
      addPoint(points, edge2point, i);
    }
  }
}

int findD3(const D3 &p, const vector<Point> &points) {
  for (int i = 0; i < points.size(); i++) {
    if (points[i].center == p) {
      return i;
    }
  }
  return -1;
}

double dijkstra(const vvi &edgeGraph, const vector<Point> &points,
    const vvi &edge2point, const D3 &src, const D3 &dst) {
  pq q;
  q.push(make_pair(0.0, findD3(src, points)));
  int dst_id = findD3(dst, points);
  bool visited[points.size()];
  fill(visited, visited + points.size(), false);
  while (!q.empty()) {
    pdi p = q.top();
    q.pop();
    double distance = p.first;
    int current_id = p.second;
    if (visited[current_id]) {
      continue;
    }
    visited[current_id] = true;
    if (current_id == dst_id) {
      return distance;
    }
    for (int i = 0; i < points[current_id].edges.size(); i++) {
      int edge_id = points[current_id].edges[i];
      for (int j = 0; j < edgeGraph[edge_id].size(); j++) {
        int next_edge_id = edgeGraph[edge_id][j];
        for (int k = 0; k < edge2point[next_edge_id].size(); k++) {
          int next_point_id = edge2point[next_edge_id][k];
          if (visited[next_point_id]) {
            continue;
          }
          q.push(make_pair(distance + 
              abs(points[current_id].center - points[next_point_id].center),
              next_point_id));
        }
      }
    }
  }
  return -1.0;
}

double solve(int x0, int y0, int z0, int x1, int y1, int z1,
    const vvvc &input, const vd &mesh) {
  D3 src(2*z0+2, 2*y0+2, 2*x0+2), dst(2*z1+2, 2*y1+2, 2*x1+2);
  vector<Face> faces = constructFaces(input);
  vector<Edge> edges = constructEdges(faces);
  vvi edgeGraph = constructEdgeGraph(faces, edges);
  vector<Point> points;
  vvi edge2point(edges.size());
  constructPoints(edges, mesh, points, edge2point);
  return 0.5 * dijkstra(edgeGraph, points, edge2point, src, dst);
}

int main(void) {
  vd mesh = constructMesh();
  while (true) {
    int x0, y0, z0, x1, y1, z1;
    cin >> x0 >> y0 >> z0 >> x1 >> y1 >> z1;
    if (x0 == 0 && y0 == 0 && z0 == 0 &&
        x1 == 0 && y1 == 0 && z1 == 0) {
      break;
    }
    vvvc input(5, vvc(5, vc(5, '.')));
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
        string line;
        cin >> line;
        for (int k = 1; k <= 3; k++) {
          input[i][j][k] = line[k-1];
        }
      }
    }
    printf("%.5f\n", solve(x0, y0, z0, x1, y1, z1, input, mesh));
  }
}
