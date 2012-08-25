#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

struct Edge {
  int x_, ymin_, ymax_;

  Edge (int x, int ymin, int ymax)
      : x_(x), ymin_(ymin), ymax_(ymax) {}
};

typedef vector<vector<char> > vvc;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<Edge> vedge;

vvc parseLines(int h, int w, const string *lines) {
  vvc map(h, vector<char>(w, 0));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      map[i][j] = (lines[i][j] == '#' ? 1 : 0);
    }
  }
  return map;
}

int countCorners(const vvc& map) {
  int counter = 0;
  for (int i = 1; i < map.size(); i++) {
    for (int j = 1; j < map[i].size(); j++) {
      if (map[i-1][j-1] + map[i-1][j] + map[i][j-1] + map[i][j] == 3) {
        counter++;
      }
    }
  }
  return counter;
}

vvc transpose(const vvc& map) {
  vvc transposed(map[0].size(), vector<char>(map.size(), 0));
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      transposed[j][i] = map[i][j];
    }
  }
  return transposed;
}

vector<Edge> gatherHorizontalEdges(const vvc& map) {
  vector<Edge> edges;
  for (int i = 1; i < map.size(); i++) {
    for (int j = 1; j < map[i].size(); j++) {
      if (map[i-1][j-1] + map[i][j-1] == 1 &&
          map[i-1][j] + map[i][j] == 2) {
        int k = j;
        for (; k < map[i].size(); k++) {
          int n = map[i-1][k] + map[i][k];
          if (n == 1) {
            edges.push_back(Edge(i, j, k));
            break;
          } else if (n == 0) {
            break;
          }
        }
        j = k;
      }
    }
  }
  return edges;
}

bool conflict(const Edge& hEdge, const Edge& vEdge) {
  return hEdge.ymin_ <= vEdge.x_ && vEdge.x_ <= hEdge.ymax_ &&
      vEdge.ymin_ <= hEdge.x_ && hEdge.x_ <= vEdge.ymax_;
}

vpii gatherConflictedPairs(const vedge& hEdges, const vedge& vEdges) {
  vector<pair<int, int> > conflictedPairs;
  for (int i = 0; i < hEdges.size(); i++) {
    for (int j = 0; j < vEdges.size(); j++) {
      if (conflict(hEdges[i], vEdges[j])) {
        conflictedPairs.push_back(make_pair(i, j));
      }
    }
  }
  return conflictedPairs;
}

bool findMatch(int v, int* prev, bool* visit, int hSize, const vpii& pairs) {
  if (v < 0) {
    return true;
  }
  for (int i = 0; i < hSize; i++) {
    if (visit[i] ||
        !binary_search(pairs.begin(), pairs.end(), make_pair(i, v))) {
      continue;
    }
    visit[i] = true;
    if (findMatch(prev[i], prev, visit, hSize, pairs)) {
      prev[i] = v;
      return true;
    }
  }
  return false;
}

int maximumMatch(int hSize, int vSize, const vpii& pairs) {
  int count = 0;
  int prev[hSize];
  fill(prev, prev + hSize, -1);
  for (int i = 0; i < vSize; i++) {
    bool visit[hSize];
    fill(visit, visit + hSize, false);
    if (findMatch(i, prev, visit, hSize, pairs)) {
      count++;
    }
  }
  return count;
}

int solve(int h, int w, const string* lines) {
  vvc map = parseLines(h, w, lines);
  vector<Edge> hEdges = gatherHorizontalEdges(map);
  vector<Edge> vEdges = gatherHorizontalEdges(transpose(map));

  vpii conflictedPairs = gatherConflictedPairs(hEdges, vEdges);
  sort(conflictedPairs.begin(), conflictedPairs.end());
  return 1 + countCorners(map) - hEdges.size() - vEdges.size()
      + maximumMatch(hEdges.size(), vEdges.size(), conflictedPairs);
}

int main(void) {
  while (true) {
    int h, w;
    cin >> h >> w;
    if (h == 0) {
      break;
    }
    string lines[h];
    for (int i = 0; i < h; i++) {
      cin >> lines[i];
    }
    cout << solve(h, w, lines) << endl;
  }
}
