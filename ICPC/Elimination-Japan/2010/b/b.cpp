#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int makeIndex(int i, int j, int w) {
  return i*w+j;
}

void addEdge(int p1, int p2, vector<vector<int> > &edges) {
  edges[p1].push_back(p2);
  edges[p2].push_back(p1);
}

void addEdge(int i1, int j1,  int i2, int j2, int w, vector<vector<int> > &edges) {
  addEdge(makeIndex(i1, j1, w), makeIndex(i2, j2, w), edges);
}


int dijkstra(int hw, const vector<vector<int> > &edges) {
  priority_queue<pair<int, int> > q;
  bool visited[hw];
  fill(visited, visited+hw, false);
  
  q.push(make_pair(-1, 0));
  while (!q.empty()) {
    pair<int, int> p = q.top();
    q.pop();
    int cost = -p.first;
    int index = p.second;
    if (visited[index]) {
      continue;
    }
    visited[index] = true;
    if (index == hw-1) {
      return cost;
    }
    for (vector<int>::const_iterator it = edges[index].begin(); it != edges[index].end(); it++) {
      if (!visited[*it]) {
        q.push(make_pair(-cost-1, *it));
      }
    }
  }
  return 0;
}

int main(void) {
  while (true) {
    int h, w;
    cin >> w >> h;
    if (w == 0) {
      break;
    }
    
    vector<vector<int> > edges(h*w);
    for (int i = 0; i < 2*h-1; i++) {
      if (i % 2 == 0) {
        for (int j = 0; j < w-1; j++) {
          int wall;
          cin >> wall;
          if (wall == 0) {
            addEdge(i/2, j, i/2, j+1, w, edges);
          }
        }
      } else {
        for (int j = 0; j < w; j++) {
          int wall;
          cin >> wall;
          if (wall == 0) {
            addEdge(i/2, j, i/2+1, j, w, edges);
          }
        }
      }
    }
    cout << dijkstra(h*w, edges) << endl;
  }
}
