#include<iostream>
#include<queue>
#include<set>
#include<vector>

using namespace std;

typedef pair<int, int> Pos;
typedef pair<int, Pos> Node;

int solve(const vector<vector<pair<int, int> > > &graph, int c) {
  priority_queue<Node, vector<Node>, greater<Node> > q;
  set<Pos> visited;
  
  int answer = 1000;
  q.push(make_pair(0, make_pair(1, 0)));
  while (!q.empty()) {
    Node node = q.top();
    q.pop();
    int cost = node.first;
    Pos pos = node.second;
    if (visited.find(pos) != visited.end()) {
      continue;
    }
    visited.insert(pos);
    int index = pos.first;
    int pass = pos.second;
    if (index == graph.size()-1) {
      answer = min(answer, pass);
    } else {
      for (vector<pair<int, int> >::const_iterator it = graph[index].begin(); it != graph[index].end(); it++) {
        if (cost + it->second <= c) {
          q.push(make_pair(cost+it->second, make_pair(it->first, pass)));
        }
        if (pass+1 <= graph.size()) {
          q.push(make_pair(cost, make_pair(it->first, pass+1)));
        }
      }
    }
  }
  return answer;
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
