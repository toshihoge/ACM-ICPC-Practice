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

#define INF 10000

#define MAX_STATUS (1<<16)
#define SHIFT_CURRENT 10
#define SHIFT_PREVIOUS 5
#define MASK 0x1F

typedef int status;
typedef pair<double, status> node;

status makeStatus(int current, int previous, int velocity) {
  return (current << SHIFT_CURRENT) | (previous << SHIFT_PREVIOUS) | velocity;
}

int getCurrent(status s) {
  return (s >> SHIFT_CURRENT) & MASK;
}

int getPrevious(status s) {
  return (s >> SHIFT_PREVIOUS) & MASK;
}

int getVelocity(status s) {
  return s & MASK;
}

string solve(int s, int g, const vvi &distances, const vvi &limitations) {
  priority_queue<node, vector<node>, greater<node> > q; 
  q.push(make_pair(0.0, makeStatus(s, 0, 0)));
  bool visited[MAX_STATUS];
  fill(visited, visited + MAX_STATUS, false);
  while(!q.empty()) {
    node n = q.top();
    q.pop();
    double cost = n.first;
    status s = n.second;
    if (visited[s]) {
      continue;
    }
    visited[s] = true;
    int current = getCurrent(s);
    int previous = getPrevious(s);
    int velocity = getVelocity(s);
    if (current == g && velocity == 1) {
      ostringstream os;
      os << cost;
      return os.str();
    }
    REP(i, distances[current].size()) {
      if (distances[current][i] != INF && i != previous) {
        for (int nextVelocity = max(velocity-1, 1);
            nextVelocity <= min(velocity+1, limitations[current][i]);
            nextVelocity++) {
          status nextStatus = makeStatus(i, current, nextVelocity);
          if (!visited[nextStatus]) {
            q.push(make_pair(
                cost + (double)distances[current][i] / nextVelocity,
                nextStatus));
          }
        }
      }
    }
  }
  return "unreachable";
}

int main(void) {
  WT {
    int n, m;
    cin >> n >> m;
    if (!n) {
      break;
    }
    int s, g;
    cin >> s >> g;
    vvi distances(n+1, vi(n+1, INF));
    vvi limitations(n+1, vi(n+1, 0));
    REP(i,m) {
      int x, y, d, c;
      cin >> x >> y >> d >> c;
      distances[x][y] = d;
      distances[y][x] = d;
      limitations[x][y] = c;
      limitations[y][x] = c;
    }
    cout << solve(s, g, distances, limitations) << endl;
  }
}
