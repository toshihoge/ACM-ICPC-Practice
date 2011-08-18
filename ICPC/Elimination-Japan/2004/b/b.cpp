#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)

int DI[4] = {1, 0, -1, 0};
int DJ[4] = {0, 1, 0, -1};

int dfs(vector<vector<char> > &table, int i, int j) {
  if (table[i][j] == '#') {
    return 0;
  }
  table[i][j] = '#';
  int sum = 1;
  REP(k,4) {
    sum += dfs(table, i+DI[k], j+DJ[k]);
  }
  return sum;
}

int solve(vector<vector<char> > &table) {
  REP(i,table.size()) {
    REP(j,table[0].size()) {
      if (table[i][j] == '@') {
        return dfs(table, i, j);
      }
    }
  }
  return -1;
}


int main(void) {
  while (true) {
    int w, h;
    cin >> w >> h;
    if (w == 0 && h == 0) {
      break;
    }
    vector<vector<char> > table(h+2, vector<char>(w+2, '#'));
    REP(i,h) {
      string line;
      cin >> line;
      REP(j,w) {
        table[i+1][j+1] = line[j];
      }
    }
    cout << solve(table) << endl;
  }
}
