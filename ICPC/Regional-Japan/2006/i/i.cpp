#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef unsigned long long ull;
typedef vector<vector<pair<int, int> > > Edges;

typedef struct node {
  int index;
  int cost;
  vi history;
  ull historySet;
} Node;

bool operator < (const Node &n1, const Node &n2) {
  if (n1.cost != n2.cost) return n1.cost > n2.cost;
  for (int i = 0; true; i++) {
    if (n1.history[i] != n2.history[i]) return n1.history[i] > n2.history[i];
  }
}

void printPath(const Node &node) {
  cout << node.history[0];
  for (int i = 1; i < node.history.size(); i++) {
    cout << "-" << node.history[i];
  }
  cout << endl;
}

bool alreadyVisited(ull historySet, int index) {
  return (historySet & (1ULL << index)) != 0;
}

ull addHistorySet(ull currentSet, int index) {
  return currentSet | (1ULL << index);
}

bool reachable(int current, int b, ull &historySet, const Edges &edges) {
  if (current == b) {
    return true;
  }
  for (int i = 0; i < edges[current].size(); i++) {
    int nextIndex = edges[current][i].first;
    if (alreadyVisited(historySet, nextIndex)) {
      continue;
    }
    historySet = addHistorySet(historySet, nextIndex);
    if (reachable(nextIndex, b, historySet, edges)) {
      return true;
    }
  }
  return false;
}

void solve(int n, int k, int a, int b, const Edges &edges) {
  int visitedCount[n+1];
  fill(visitedCount, visitedCount + (n+1), 0);
  
  Node initial;
  initial.index = a;
  initial.cost = 0;
  initial.history.push_back(a);
  initial.historySet = addHistorySet(0, a);
  
  priority_queue<Node> q;
  q.push(initial);
  while (!q.empty()) {
    Node node = q.top();
    q.pop();
    if (visitedCount[node.index] >= k) {
      continue;
    }
    visitedCount[node.index]++;
    if (node.index == b && visitedCount[node.index] == k) {
      printPath(node);
      return;
    }
    for (int i = 0; i < edges[node.index].size(); i++) {
      int nextIndex = edges[node.index][i].first;
      ull tempHistorySet = addHistorySet(node.historySet, nextIndex);
      if (alreadyVisited(node.historySet, nextIndex) || !reachable(nextIndex, b, tempHistorySet, edges) || visitedCount[nextIndex] >= k) {
        continue;
      }
      Node next;
      next.index = nextIndex;
      next.cost = node.cost + edges[node.index][i].second;
      next.history = node.history;
      next.history.push_back(nextIndex);
      next.historySet = addHistorySet(node.historySet, nextIndex);
      q.push(next);
    }
  }
  cout << "None" << endl;
}

int main(void) {
  while (true) {
    int n, m, k, a, b;
    cin >> n >> m >> k >> a >> b;
    if (n == 0) {
      break;
    }
    Edges edges(n+1);
    for (int i = 0; i < m; i++) {
      int x, y, d;
      cin >> x >> y >> d;
      edges[x].push_back(make_pair(y, d));
    }
    solve(n, k, a, b, edges);
  }
}
