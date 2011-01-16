#include<iostream>

using namespace std;

int main(void) {
  int d[4][2] = {
    {-1,  0},
    { 0, -1},
    { 1,  0},
    { 0,  1},
  };
  
  
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    
    int minp[2] = {0, 0};
    int maxp[2] = {0, 0};
    
    int p[n][2];
    p[0][0] = 0;
    p[0][1] = 0;
    
    for (int i = 1; i < n; i++) {
      int prev, type;
      cin >> prev >> type;
      for (int j = 0; j < 2; j++) {
        p[i][j] = p[prev][j] + d[type][j];
        minp[j] = min(minp[j], p[i][j]);
        maxp[j] = max(maxp[j], p[i][j]);
      }
    }
    printf("%d %d\n", maxp[0]-minp[0]+1, maxp[1]-minp[1]+1);
  }
}
