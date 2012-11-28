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
typedef struct PointEdgeInfo {
  int edge_id;
  double rate;
  PointEdgeInfo(int edge_id, double rate) : edge_id(edge_id), rate(rate) {}
} PointEdgeInfo;
typedef struct Point {
  vector<PointEdgeInfo> infos;
  D3 center;
  bool grid;
  Point(const D3 &center, bool grid) : infos(), center(center), grid(grid) {}
} Point;
typedef vector<PointEdgeInfo> Advice;
typedef struct QNode {
  double distance;
  int current_id;
  int previous_id;
  QNode(double distance, int current_id, int previous_id) :
      distance(distance), current_id(current_id), previous_id(previous_id) {}
} QNode;
typedef priority_queue<QNode, vector<QNode>, greater<QNode> > pq;

#define FACE_X 0
#define FACE_Y 1
#define FACE_Z 2

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

bool operator>(const QNode &n1, const QNode &n2) {
  return n1.distance > n2.distance;
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

void addPoint(vector<Point> &points, vvi &edge2point, int edge_id, double rate) {
  points.back().infos.push_back(PointEdgeInfo(edge_id, rate));
  edge2point[edge_id].push_back(points.size() - 1);
}

void constructPoints(const vector<Edge> &edges,
    const Advice &advisor, double width,
    vector<Point> &points, vvi &edge2point) {
  points.clear();
  for (int x = 2; x <= 8; x += 2) {
    for (int y = 2; y <= 8; y += 2) {
      for (int z = 2; z <= 8; z += 2) {
        D3 p(x, y, z);
        if (isOneOfEndPoint(p, edges)) {
          points.push_back(Point(D3(p), true));
          for (int i = 0; i < edges.size(); i++) {
            if (edges[i].src == p) {
              addPoint(points, edge2point, i, 0.0);
            } else if (edges[i].dst == p) {
              addPoint(points, edge2point, i, 1.0);
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < advisor.size(); i++) {
    int edge_id = advisor[i].edge_id;
    double center = advisor[i].rate;
    D3 p = edges[edge_id].src;
    D3 v = edges[edge_id].dst - edges[edge_id].src;
    for (int j = -3; j <= 3; j++) {
      double rate = center + j*width/4.0;
      if (0.0 < rate && rate < 1.0) {
        points.push_back(Point(p + rate*v, false));
        addPoint(points, edge2point, edge_id, rate);
      }
    }
  }
}

int findD3(const D3 &p, const vector<Point> &points) {
  for (int i = 0; i < points.size(); i++) {
    if (points[i].grid && points[i].center == p) {
      return i;
    }
  }
  return -1;
}

Advice makeAdvice(int dst_id, const int* back_point,
    const vector<Point> &points) {
  Advice advice;
  int current_id = dst_id;
  while (current_id >= 0) {
    advice.push_back(points[current_id].infos[0]);
    current_id = back_point[current_id];
  }
  return advice;
}

pair<double, Advice> dijkstra(const vvi &edgeGraph, const vector<Point> &points,
    const vvi &edge2point, const D3 &src, const D3 &dst) {
  pq q;
  q.push(QNode(0.0, findD3(src, points), -1));
  int dst_id = findD3(dst, points);
  int back_point[points.size()];
  fill(back_point, back_point + points.size(), -2);
  while (!q.empty()) {
    QNode node = q.top();
    q.pop();
    double distance = node.distance;
    int current_id = node.current_id;
    int previous_id = node.previous_id;
    if (back_point[current_id] >= -1) {
      continue;
    }
    back_point[current_id] = node.previous_id;
    if (current_id == dst_id) {
      return make_pair(distance, makeAdvice(current_id, back_point, points));
    }
    for (int i = 0; i < points[current_id].infos.size(); i++) {
      int edge_id = points[current_id].infos[i].edge_id;
      for (int j = 0; j < edgeGraph[edge_id].size(); j++) {
        int next_edge_id = edgeGraph[edge_id][j];
        for (int k = 0; k < edge2point[next_edge_id].size(); k++) {
          int next_point_id = edge2point[next_edge_id][k];
          if (back_point[next_point_id] >= 0) {
            continue;
          }
          q.push(QNode(distance +
              abs(points[current_id].center - points[next_point_id].center),
              next_point_id, current_id));
        }
      }
    }
  }
  // never reaches
}

double solve(int x0, int y0, int z0, int x1, int y1, int z1, const vvvc &input) {
  D3 src(2*z0+2, 2*y0+2, 2*x0+2), dst(2*z1+2, 2*y1+2, 2*x1+2);
  vector<Face> faces = constructFaces(input);
  vector<Edge> edges = constructEdges(faces);
  vvi edgeGraph = constructEdgeGraph(faces, edges);
  Advice nextAdvice;
  for (int i = 0; i < edges.size(); i++) {
    nextAdvice.push_back(PointEdgeInfo(i, 0.5));
  }
  double width = 0.5;
  double answer = 0.0;
  for (int i = 0; i < 60; i++) {
    vector<Point> points;
    vvi edge2point(edges.size());
    constructPoints(edges, nextAdvice, width, points, edge2point);
    pair<double, Advice> pda = dijkstra(edgeGraph, points, edge2point, src, dst);
    answer = pda.first;
    nextAdvice = pda.second;
    width *= 0.5;
  }
  return 0.5*answer;
}

int main(void) {
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
    printf("%.5f\n", solve(x0, y0, z0, x1, y1, z1, input));
  }
}
