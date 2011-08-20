//--------------------------------------
// Begin common header
//--------------------------------------
#include<algorithm>
#include<cmath>
#include<complex>
#include<cstdio>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<vector>

using namespace std;

typedef pair<int, int> pii;
typedef complex<double> cd;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define SORT(c) sort((c).begin(), (c).end())
#define WT while(true)

//--------------------------------------
// End common header
//--------------------------------------

typedef vector<char> vc;
typedef vector<vc> vvc;

int DI[] = {1, 0, -1, 0};
int DJ[] = {0, 1, 0, -1};

vector<pii> findInterestedPoints(const vvc &room) {
  vector<pii> output;
  output.push_back(make_pair(-1, -1));
  REP(i,room.size()) {
    REP(j,room[i].size()) {
      switch (room[i][j]) {
      case 'o':
        output[0] = make_pair(i, j);
        break;
      case '*':
        output.push_back(make_pair(i, j));
        break;
      }
    }
  }
  return output;
}

int calculateCost(const vvc &room, pii src, pii dst) {
  deque<pair<int, pii> > q;
  q.push_back(make_pair(0, src));
  vector<vector<bool> > visited(
      room.size(), vector<bool>(room[0].size(), false));
  while(!q.empty()) {
    pair<int, pii> p = q.front();
    q.pop_front();
    int cost = p.first;
    int i = p.second.first;
    int j = p.second.second;
    if (visited[i][j]) {
      continue;
    }
    if (p.second == dst) {
      return cost;
    }
    visited[i][j] = true;
    REP(k,4) {
      int nextI = i + DI[k];
      int nextJ = j + DJ[k];
      if (visited[nextI][nextJ] || room[nextI][nextJ] == 'x') {
        continue;
      }
      q.push_back(make_pair(cost+1, make_pair(nextI, nextJ)));
    }
  }
  return -1;
}

void dfs(int index, int last, int n, int currentCost, bool* visited,
    int& minCost, const vvi &matrix) {
  if (index == n) {
    minCost = min(minCost, currentCost);
    return;
  }
  if (currentCost >= minCost) {
    return;
  }
  REP(i,n) {
    if (visited[i]) {
      continue;
    }
    visited[i] = true;
    dfs(index+1, i, n, currentCost+matrix[last][i], visited, minCost, matrix);
    visited[i] = false;
  }
}

int solve(const vvc &room) {
  vector<pii> points = findInterestedPoints(room);
  int n = points.size();
  vvi matrix(n, vi(n, 0));
  REP(i,n) {
    FOR(j,i+1,n) {
      int cost = calculateCost(room, points[i], points[j]);
      if (cost < 0) {
        return -1;
      }
      matrix[i][j] = cost;
      matrix[j][i] = cost;
    }
  }
  int minCost = (1<<20);
  bool visited[n];
  fill(visited, visited+n, false);
  visited[0] = true;
  dfs(1, 0, n, 0, visited, minCost, matrix);
  return minCost;
}

int main(void) {
  WT {
    int w, h;
    cin >> w >> h;
    if (!w) {
      break;
    }
    vvc room(h+2, vc(w+2, 'x'));
    REP(i,h) {
      string line;
      cin >> line;
      REP(j,w) {
        room[i+1][j+1] = line[j];
      }
    }
    cout << solve(room) << endl;
  }
}
