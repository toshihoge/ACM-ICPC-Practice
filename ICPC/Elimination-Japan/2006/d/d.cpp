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

int DI[] = {1, 0, -1, 0};
int DJ[] = {0, 1, 0, -1};

int distanceBlock(int i, int j, const vvi &board, int k) {
  for (int t = 1; true; t++) {
    switch (board[i+t*DI[k]][j+t*DJ[k]]) {
    case 1:
      return t-1;
    case 3:
      return t;
    case 4:
      return 0;
    }
  }
}

bool iterativeDeepening(int current, int depth, int i, int j, vvi &board) {
  if (board[i][j] == 3) {
    return true;
  }
  if (current >= depth) {
    return false;
  }
  REP(k,4) {
    int t = distanceBlock(i, j, board, k);
    if (t == 0) {
      continue;
    }
    int nextI = i+t*DI[k];
    int nextJ = j+t*DJ[k];
    board[nextI+DI[k]][nextJ+DJ[k]] = 0;
    if (iterativeDeepening(current+1, depth, nextI, nextJ, board)) {
      return true;
    }
    board[nextI+DI[k]][nextJ+DJ[k]] = 1;
  }
  return false;
}

pii findX(vvi &board, int x) {
  REP(i,board.size()) {
    REP(j,board[i].size()) {
      if (board[i][j] == x) {
        return make_pair(i, j);
      }
    }
  }
  return make_pair(-1, -1);
}

int solve(vvi &board) {
  pii src = findX(board, 2);
  board[src.first][src.second] = 0;

  REP(depth,11) {
    if (iterativeDeepening(
        0, depth, src.first, src.second, board)) {
      return depth;
    }
  }
  return -1;
}

int main(void) {
  WT {
    int w, h;
    cin >> w >> h;
    if (!h) {
      break;
    }
    vvi board(h+2, vi(w+2, 4));
    REP(i,h) {
      REP(j,w) {
        cin >> board[i+1][j+1];
      }
    }
    cout << solve(board) << endl;
  }
}
