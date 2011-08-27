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

typedef pair<int, int> Pii;
typedef complex<double> Cd;
typedef vector<int> Vi;
typedef vector<Vi> Vvi;
typedef vector<double> Vd;

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

int DI[] = {0, 1, 0, -1};
int DJ[] = {1, 0, -1, 0};

#define MAX_STATUS 4096

typedef int Status;
typedef pair<int, Status> Node;
typedef priority_queue<Node, vector<Node>, greater<Node> > Queue;

int getDirection(Status s) {
  return s & 0x3;
}

int getJ(Status s) {
  return (s >> 2) & 0x1F;
}

int getI(Status s) {
  return (s >> 7) & 0x1F;
}

Status makeStatus(int i, int j, int direction) {
  return (i << 7) | (j << 2) | direction;
}

int solve(const Vvi &board, const Vi &costTable) {
  bool visited[MAX_STATUS];
  fill(visited, visited+MAX_STATUS, false);
  Queue queue;
  queue.push(make_pair(0, makeStatus(0, 0, 0)));
  while (!queue.empty()) {
    Node node = queue.top();
    queue.pop();
    int cost = node.first;
    Status status = node.second;
    if (visited[status]) {
      continue;
    }
    visited[status] = true;
    int i = getI(status);
    int j = getJ(status);
    int direction = getDirection(status);
    if (i == board.size() - 1 && j == board[i].size() - 1) {
      return cost;
    }
    REP(k,4) {
      int nextDirection = (direction + k) % 4;
      int nextI = i + DI[nextDirection];
      int nextJ = j + DJ[nextDirection];
      if (nextI < 0 || board.size() <= nextI ||
          nextJ < 0 || board[nextI].size() <= nextJ) {
        continue;
      }
      Status nextStatus = makeStatus(nextI, nextJ, nextDirection);
      if (visited[nextStatus]) {
        continue;
      }
      int nextCost = cost + (board[i][j] == k ? 0 : costTable[k]);
      queue.push(make_pair(nextCost, nextStatus));
    }
  }
  return -1;
}

int main(void) {
  WT {
    int w, h;
    cin >> w >> h;
    if (!w) {
      break;
    }
    Vvi board(h, Vi(w, 0));
    REP(i,h) {
      REP(j,w) {
        cin >> board[i][j];
      }
    }
    Vi costTable(4);
    REP(i, 4) {
      cin >> costTable[i];
    }
    cout << solve(board, costTable) << endl;
  }
}
