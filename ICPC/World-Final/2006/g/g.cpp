#include<algorithm>
#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef pair<int, int> PI;
typedef priority_queue<PI, vector<PI>, greater<PI> > PQ;

int calculateMemorySize(int n, const int* lengths, const int* order, int m, const int* ids, const int* begins, const int* ends) {
  vector<PQ> pqs(n+1);
  int message = 0;
  int id = order[message];
  int begin = 1;
  int bufferSize = 0;
  int maxBufferUsage = 0;
  for (int i = 0; i < m; i++) {
    pqs[ids[i]].push(make_pair(begins[i], ends[i]));
    bufferSize += ends[i]+1-begins[i];
    while (message < n && !pqs[id].empty() && pqs[id].top().first == begin) {
      PI p = pqs[id].top();
      pqs[id].pop();
      begin = p.second + 1;
      bufferSize -= (p.second+1-p.first);
      if (begin > lengths[id]) {
        message++;
        id = order[message];
        begin = 1;
      }
    }
    maxBufferUsage = max(maxBufferUsage, bufferSize);
  }
  return maxBufferUsage;
}

int solve(int n, const int* lengths, int m, const int* ids, const int* begins, const int* ends) {
  int order[n];
  for (int i = 0; i < n; i++) {
    order[i] = i+1;
  }
  int result = 1<<28;
  do {
    result = min(result, calculateMemorySize(n, lengths, order, m, ids, begins, ends));
  } while (next_permutation(order, order+n));
  return result;
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    int n, m;
    cin >> n >> m;
    if (n == 0) {
      break;
    }
    int lengths[n+1];
    for (int i = 1; i <= n; i++) {
      cin >> lengths[i];
    }
    int ids[m], begins[m], ends[m];
    for (int i = 0; i < m; i++) {
      cin >> ids[i] >> begins[i] >> ends[i];
    }
    printf("Case %d: %d\n\n", casenumber, solve(n, lengths, m, ids, begins, ends));
  }
}
