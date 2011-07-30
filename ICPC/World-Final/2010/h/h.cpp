#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<vector<int> > graph;

#define MAX_N 100000

// Global
graph g;
int timer;
int num[MAX_N];
int low[MAX_N];
bool jointPoint[MAX_N];
bool hasJointPoint;

void markJointPointDfs(int current, int prev) {
  num[current] = timer;
  low[current] = timer;
  timer++;
  for (int i = 0; i < g[current].size(); i++) {
    int next = g[current][i];
    if (num[next] == 0) {
      markJointPointDfs(next, current);
      low[current] = min(low[current], low[next]);
      if ((num[current] == 1 && num[next] != 2) ||
          (num[current] != 1 && low[next] >= num[current])) {
        jointPoint[current] = true;
        hasJointPoint = true;
      }
    } else if(next != prev) {
      low[current] = min(low[current], num[next]);
    }
  }
}

bool markJointPoint() {
  int n = g.size();
  fill(jointPoint, jointPoint + n, false);
  fill(num, num + n, 0);
  timer = 1;
  hasJointPoint = false;
  markJointPointDfs(1, -1);
  return hasJointPoint;
}

int dfs(int index, int& visitedJointPoint, bool* visited,
    bool &visitedTwoJointPoints) {
  visited[index] = true;
  int count = 1;
  for (int i = 0; i < g[index].size(); i++) {
    int next = g[index][i];
    if (visited[next]) {
      continue;
    }
    if (jointPoint[next]) {
      if (visitedJointPoint == -1) {
        visitedJointPoint = next;
      } else if (visitedJointPoint != next) {
        visitedTwoJointPoints = true;
      }
      continue;
    }
    count += dfs(next, visitedJointPoint, visited, visitedTwoJointPoints);
  }
  return count;
}

pair<int, ll> solveWithJointPoints() {
  int n = g.size();
  bool visited[n];
  fill(visited, visited+n, false);
  int numberOfShafts = 0;
  ll numberOfWays = 1;
  for (int i = 1; i < n; i++) {
    if (!visited[i] && !jointPoint[i]) {
      int visitedJointPoint = -1;
      bool visitedTwoJointPoints = false;
      int count = dfs(i, visitedJointPoint, visited, visitedTwoJointPoints);
      if (!visitedTwoJointPoints) {
        numberOfShafts++;
        numberOfWays *= (ll)count;
      }
    }
  }
  return make_pair(numberOfShafts, numberOfWays);
}

pair<int, ll> solve(int n, const pii *edges, int maxIndex) {
  g.clear();
  g = graph(maxIndex + 1);
  for (int i = 0; i < n; i++) {
    g[edges[i].first].push_back(edges[i].second);
    g[edges[i].second].push_back(edges[i].first);
  }
  if (markJointPoint()) {
    return solveWithJointPoints();
  } else {
    return make_pair(2, (ll)maxIndex*((ll)(maxIndex-1))/2L);
  }
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    pii edges[n];
    int maxIndex = 1;
    for (int i = 0; i < n; i++) {
      cin >> edges[i].first >> edges[i].second;
      maxIndex = max(maxIndex, edges[i].first);
      maxIndex = max(maxIndex, edges[i].second);
    }
    pair<int, ll> solution = solve(n, edges, maxIndex);
    printf("Case %d: %d %lld\n", casenumber, solution.first, solution.second);
  }
}

