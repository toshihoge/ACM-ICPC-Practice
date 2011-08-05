#include<algorithm>
#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef pair<int, int> pii;

#define N (1 << 21)
#define DEBUG cerr<<"Debug: "<<__LINE__<<endl

bool escapable(const pii* sorted, int n, int turn) {
  priority_queue<pii, vector<pii>, greater<pii> > uq;
  priority_queue<pii, vector<pii>, less<pii> > lq;

  uq.push(make_pair(2*N, 2*N));
  lq.push(make_pair(-2*N, 2*N));

  int currentIndex = 0;
  int currentX = -turn;
  while (currentX <= turn) {
    while (true) {
      int lqtop = lq.top().first;
      int uqtop = uq.top().first;
      if (lqtop >= uqtop-1 || lqtop >= turn || uqtop <= -turn) {
        break;
      }
      if (currentIndex >= n) {
        return true;
      }
      pii p = sorted[currentIndex++];
      if (p.first < currentX - turn) {
        continue;
      } else if (p.first <= currentX + turn) {
        if (p.second >= 0) {
          uq.push(make_pair(p.second - turn, p.first + turn));
        }
        if (p.second <= 0) {
          lq.push(make_pair(p.second + turn, p.first + turn));
        }
      } else {
        return true;
      }
    }
    currentX = min(uq.top().second, lq.top().second) + 1;
    for(;uq.top().second < currentX; uq.pop());
    for(;lq.top().second < currentX; lq.pop());
  }
  return false;
}

int solve(const pii* inputs, int n) {
  pii sorted[n];
  for (int i = 0; i < n; i++) {
    sorted[i] = inputs[i];
  }
  sort(sorted, sorted + n);
  if (escapable(sorted, n, N)) {
    return -1;
  }
  int min = 0;
  int max = N;
  while (max - min >= 2) {
    int mid = (max + min)/2;
    if (escapable(sorted, n, mid)) {
      min = mid;
    } else {
      max = mid;
    }
  }
  return max;
}

int main(void) {
  for(int casenumber=1; true; casenumber++) {
    int n;
    cin >> n;
    if (n == -1) {
      break;
    }
    pii inputs[n];
    for (int i = 0; i < n; i++) {
      cin >> inputs[i].first >> inputs[i].second;
    }
    int result = solve(inputs, n);
    if (result == -1) {
      printf("Case %d: never\n", casenumber);
    } else {
      printf("Case %d: %d\n", casenumber, result);
    }
  }
}
