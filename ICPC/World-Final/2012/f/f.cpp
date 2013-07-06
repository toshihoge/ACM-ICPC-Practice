#include<algorithm>
#include<iostream>

using namespace std;

bool acceptable(int midDiff, int n, int k, const int* p) {
  int index = 1;
  int pair = 0;
  while (index < 2*n*k) {
    if (p[index] - p[index-1] <= midDiff) {
      if (index > 2*k*pair+1) {
        return false;
      }
      pair++;
      if (pair >= n) {
        return true;
      }
      index += 2;
    } else {
      index++;
    }
  }
  return false;
}

int solve(int n, int k, const int* p) {
  int maxDiff = p[2*n*k-1] - p[0];
  int minDiff = p[1] - p[0] - 1;
  while(maxDiff - minDiff > 1) {
    int midDiff = (maxDiff + minDiff) / 2;
    if (acceptable(midDiff, n, k, p)) {
      maxDiff = midDiff;
    } else {
      minDiff = midDiff;
    }
  }
  return maxDiff;
}

int main(void) {
  int n, k;
  cin >> n >> k;
  int p[2*n*k];
  for (int i = 0; i < 2*n*k; i++) {
    cin >> p[i];
  }
  sort(p, p + (2*n*k));
  cout << solve(n, k, p) << endl;
}
