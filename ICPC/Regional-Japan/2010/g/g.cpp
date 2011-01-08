#include<iostream>
#include<queue>
#include<set>

using namespace std;

int solve(const vector<vector<pair<int, int> > > &graph, int c) {
  set<int> visited;
  priority_queue<pair<int, int> > q;
  priority_queue<pair<int, int> > nextq;
  
  q.push(make_pair(0, 1));
  int pass = 0;
  while (true) {
    while(!q.empty()) {
      pair<int, int> p = q.top();
      q.pop();
      int cost = -p.first;
      int index = p.second;
      if (index == graph.size() - 1) {
        return pass;
      }
      if (visited.find(index) != visited.end()) {
        continue;
      }
      visited.insert(index);
      for (vector<pair<int, int> >::const_iterator it = graph[index].begin(); it != graph[index].end(); it++) {
        if (cost + it->second <= c) {
          q.push(make_pair(-cost-it->second, it->first));
        }
        nextq.push(make_pair(-cost, it->first));
      }
    }
    pass++;
    q = nextq;
    nextq = priority_queue<pair<int, int> >();
    visited.clear();
  }
}

int main(void) {
  while (true) {
    int n, m, c;
    cin >> n >> m >> c;
    if (n == 0) break;
    vector<vector<pair<int, int> > > graph(n+1);
    for (int i = 0; i < m; i++) {
      int f, t, cost;
      cin >> f >> t >> cost;
      graph[f].push_back(make_pair(t, cost));
    }
    cout << solve(graph, c) << endl;
  }
}
