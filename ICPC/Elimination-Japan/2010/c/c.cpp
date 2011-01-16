#include<iostream>
#include<vector>

using namespace std;

#define INF (1<<28)
#define MAX 1000000

int dpAll[MAX];
int dpOdd[MAX];

int makeTetraNum(int n) {
  return n*(n+1)*(n+2)/6;
}

int main(void) {
  vector<int> tetraNumbers;
  tetraNumbers.push_back(0);
  for (int i = 1; true; i++) {
    int t = makeTetraNum(i);
    if (t > MAX) {
      break;
    }
    tetraNumbers.push_back(t);
  }
  
  
  fill(dpAll, dpAll+MAX, INF);
  fill(dpOdd, dpOdd+MAX, INF);
  dpAll[0] = 0;
  dpOdd[0] = 0;
  for (int i = 1; i<MAX; i++) {
    for (int j = 1; j < tetraNumbers.size() && i-tetraNumbers[j] >= 0; j++) {
      dpAll[i] = min(dpAll[i], dpAll[i-tetraNumbers[j]]+1);
      if (tetraNumbers[j]%2 == 1) {
        dpOdd[i] = min(dpOdd[i], dpOdd[i-tetraNumbers[j]]+1);
      }
    }
  }
  
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    printf("%d %d\n", dpAll[n], dpOdd[n]);
  }
}
