#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int> > graph;
typedef pair<int, int> pii;
typedef priority_queue<pii, vector<pii>, greater<pii> > pq;

#define INF (1<<16)
#define N 1000

#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

vi BLANK_COST_TABLE(N);

int dijkstra(const graph &g, int src, int forbidden, const vi &costTable, 
    int limitation) {
  pq queue;
  queue.push(make_pair(0, src));

  vi output(g.size());
  fill(output.begin(), output.end(), INF);
  while (!queue.empty() && output[g.size()-1] == INF) {
    pii p = queue.top();
    queue.pop();
    int cost = p.first;
    int index = p.second;
    if (output[index] != INF) {
      continue;
    }
    output[index] = cost;
    for (int i = 0; i < g[index].size(); i++) {
      int nextIndex = g[index][i];
      if (output[nextIndex] != INF) {
        continue;
      }
      if (index == src && nextIndex == forbidden) {
        continue;
      }
      if (cost+1+costTable[nextIndex] > limitation) {
        continue;
      }
      queue.push(make_pair(cost+1, nextIndex));
    }
  }
  return output[g.size()-1];
}

int dijkstraWithFixedBrokenDoor(const graph &g, int src, int forbidden) {
  return dijkstra(g, src, forbidden, BLANK_COST_TABLE, INF);
}

int dijkstraStartFromRoomWithBrokenDoor(const graph &g, int src, int w) {
  int output = 0;
  output = max(output, dijkstraWithFixedBrokenDoor(g, src, src-1));
  output = max(output, dijkstraWithFixedBrokenDoor(g, src, src+1));
  output = max(output, dijkstraWithFixedBrokenDoor(g, src, src-w));
  output = max(output, dijkstraWithFixedBrokenDoor(g, src, src+w));
  return output;
}

bool reachableWithLimitation(const graph &g, const vi &costTable, int limit) {
  return dijkstra(g, 0, -1, costTable, limit) != INF;
}

int solve(const graph &g, int w) {
  vi costTable;
  for (int i = 0; i < g.size(); i++) {
    costTable.push_back(dijkstraStartFromRoomWithBrokenDoor(g, i, w));
  }
  for (int i = 0; i < 2*g.size(); i++) {
    if (reachableWithLimitation(g, costTable, i)) {
      return i;
    }
  }
  return -1;
}

int makeIndex(int i, int j, int w) {
  return i*w + j;
}

int main(void) {
  fill(BLANK_COST_TABLE.begin(), BLANK_COST_TABLE.end(), 0);
  while (true) {
    int h, w;
    cin >> h >> w;
    if (h == 0 && w == 0) {
      break;
    }
    graph g(h*w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w-1; j++) {
        int door;
        cin >> door;
        if (door == 0) {
          int index1 = makeIndex(i, j, w);
          int index2 = makeIndex(i, j+1, w);
          g[index1].push_back(index2);
          g[index2].push_back(index1);
        }
      }
      if (i < h-1) {
        for (int j = 0; j < w; j++) {
          int door;
          cin >> door;
          if (door == 0) {
            int index1 = makeIndex(i, j, w);
            int index2 = makeIndex(i+1, j, w);
            g[index1].push_back(index2);
            g[index2].push_back(index1);
          }
        }
      }
    }
    cout << solve(g, w) << endl;
  }
}
