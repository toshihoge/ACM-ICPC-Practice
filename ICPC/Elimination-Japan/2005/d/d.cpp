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

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define WT while(true)

#define INF 10000

#define SHIFT_FOR_INDEX 8
#define MAX_NODE_SIZE (1<<13)
#define MASK_FOR_USED 0xFF

typedef int status;
typedef pair<double, status> node;
typedef priority_queue<node, vector<node>, greater<node> > pq;

int getIndex(status s) {
  return s >> SHIFT_FOR_INDEX;
}

int getUsed(status s) {
  return s & MASK_FOR_USED;
}

status makeStatus(int index, int used) {
  return (index << SHIFT_FOR_INDEX) | used;
}

string solve(const vi &t, const vvi &matrix, int src, int dst) {
  bool visited[MAX_NODE_SIZE];
  fill(visited, visited+MAX_NODE_SIZE, false);
  pq q;
  q.push(make_pair(0.0, makeStatus(src, 0)));
  while(!q.empty()) {
    node n = q.top();
    q.pop();
    double cost = n.first;
    status s = n.second;
    if (visited[s]) {
      continue;
    }
    visited[s] = true;
    int index = getIndex(s);
    int used = getUsed(s);
    if (index == dst) {
      ostringstream os;
      os << cost;
      return os.str();
    }
    REP(i,t.size()) {
      if ((used & (1<<i)) == 0) {
        int nextUsed = used | (1<<i);
        REP(nextIndex,matrix[index].size()) {
          status nextStatus = makeStatus(nextIndex, nextUsed);
          if (matrix[index][nextIndex] != INF && !visited[nextStatus]) {
            q.push(make_pair(cost + (double)matrix[index][nextIndex] / t[i],
                nextStatus));
          }
        }
      }
    }
  }
  return "Impossible";
}

int main(void) {
  WT {
    int n, m, p, a, b;
    cin >> n >> m >> p >> a >> b;
    if (!n) {
      break;
    }
    vi t(n);
    REP(i,n) {
      cin >> t[i];
    }
    vvi matrix(m+1, vi(m+1, INF));
    REP(i,p) {
      int x, y, z;
      cin >> x >> y >> z;
      matrix[x][y] = z;
      matrix[y][x] = z;
    }
    cout << solve(t, matrix, a, b) << endl;
  }
}
