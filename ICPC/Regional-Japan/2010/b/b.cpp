#include<iostream>
#include<cstdlib>

using namespace std;

#define INF (1<<30)

int solve(int n, const int* p, const int* t) {
  int d[n+1][5];
  
  if (p[1] > t[1]) {
    return -1;
  }
  d[1][1] = p[1];
  d[1][2] = INF;
  d[1][3] = INF;
  
  for (int i = 2; i <= n; i++) {
    for (int k = 1; k <= 3; k++) {
      d[i][k] = INF;
    }
    for (int k = 1; k <= 3; k++) {
      if ((k+1)*abs(p[i] - p[i-1]) <= t[i] - t[i-1]) {
        d[i][k+1] = min(d[i][k+1], d[i-1][k] + abs(p[i] - p[i-1]));
      }
      
      if ((k+1)*p[i-1] + p[i] <= t[i] - t[i-1]) {
        d[i][1] = min(d[i][1], d[i-1][k] + p[i-1] + p[i]);
      }
    }
    if (d[i][1] == INF && d[i][2] == INF && d[i][3] == INF) {
      return -i;
    }
  }
  return min(d[n][1], min(d[n][2], d[n][3])) + p[n];
}

int main() {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    int p[n+1];
    int t[n+1];
    for (int i = 1; i <= n; i++) {
      cin >> p[i] >> t[i];
    }
    int result = solve(n, p, t);
    if (result >= 0) {
      cout << "OK " << result << endl;
    } else {
      cout << "NG " << -result << endl;
    }
  }
}
