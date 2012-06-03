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

#define INF (1<<28)

Pii makeEdge(int cost, int index) {
  return make_pair(cost, index);
}

int getCost(Pii p) {
  return p.first;
}

int getIndex(Pii p) {
  return p.second;
}

void dijkstra(int src, const vector<vector<Pii> > &edges, vector<Pii> &result, int limit) {
  priority_queue<Pii, vector<Pii>, greater<Pii> > q;
  set<int> visited;

  q.push(makeEdge(0, src));
  while(!q.empty()) {
    Pii p = q.top();
    q.pop();
    int cost = getCost(p);
    int index = getIndex(p);
    if (HAS(visited, index)) {
      continue;
    }
    visited.insert(index);
    result.push_back(p);
    EACH(it, edges[index]) {
      int nextIndex = getIndex(*it);
      if (HAS(visited, nextIndex)) {
        continue;
      }
      int nextCost = cost + getCost(*it);
      if (nextCost <= limit) {
        q.push(makeEdge(nextCost, nextIndex));
      }
    }
  }
}

int solve(int n, int m, int c, const string &src, const string &dst, const string *c1s, const string *c2s, const int *d, const string *g) {
  map<string, int> dic1;
  REP(i, n) {
    if (!HAS(dic1, c1s[i])) {
      int size = dic1.size();
      dic1[c1s[i]] = size;
    }
    if (!HAS(dic1, c2s[i])) {
      int size = dic1.size();
      dic1[c2s[i]] = size;
    }
  }

  vector<vector<Pii> > edges1(dic1.size());
  REP(i, n) {
    int index1 = dic1[c1s[i]];
    int index2 = dic1[c2s[i]];
    edges1[index1].push_back(makeEdge(d[i], index2));
    edges1[index2].push_back(makeEdge(d[i], index1));
  }

  vector<string> lpgs;
  bool hasLpg[dic1.size()];
  fill(hasLpg, hasLpg+dic1.size(), false);
  hasLpg[dic1[src]] = true;
  hasLpg[dic1[dst]] = true;
  REP(i, m) {
    hasLpg[dic1[g[i]]] = true;
  }

  vector<vector<Pii> > edges2(dic1.size());
  REP(i, dic1.size()) {
    if (hasLpg[i]) {
      vector<Pii> result1;
      dijkstra(i, edges1, result1, 10*c);
      EACH(it, result1) {
        if (hasLpg[it->second]) {
          edges2[i].push_back(*it);
        }
      }
    }
  }

  vector<Pii> result2;
  dijkstra(dic1[src], edges2, result2, INF);
  EACH(it, result2) {
    if (it->second == dic1[dst]) {
      return it->first;
    }
  }
  return -1;
}

int main(void) {
  WT {
    int n, m, c;
    cin >> n >> m >> c;
    if (!n) {
      break;
    }
    string src, dst;
    cin >> src >> dst;

    string c1s[n], c2s[n];
    int d[n];
    REP(i, n) {
      cin >> c1s[i] >> c2s[i] >> d[i];
    }
    string g[m];
    REP(i, m) {
      cin >> g[i];
    }
    cout << solve(n, m, c, src, dst, c1s, c2s, d, g) << endl;
  }
}
