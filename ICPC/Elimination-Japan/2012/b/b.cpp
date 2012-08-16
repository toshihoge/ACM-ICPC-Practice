#include<algorithm>
#include<iostream>

using namespace std;

#define MAX_N 30

int next(int an, int len) {
  int digits[len];
  for (int i = 0; i < len; i++, an /= 10) {
    digits[i] = an % 10;
  }
  sort(digits, digits + len);
  int small = 0;
  int large = 0;
  for (int i = 0; i < len; i++) {
    small *= 10;
    small += digits[i];
    large *= 10;
    large += digits[len - 1 - i];
  }
  return large - small;
}

void solve(int a0, int len) {
  int a[MAX_N];
  a[0] = a0;
  for (int i = 1; true; i++) {
    a[i] = next(a[i-1], len);
    for (int j = 0; j < i; j++) {
      if (a[j] == a[i]) {
        cout << j << " " << a[i] << " " << i-j << endl;
        return;
      }
    }
  }
}

int main(void) {
  while (true) {
    int a0, len;
    cin >> a0 >> len;
    if (len == 0) {
      break;
    }
    solve(a0, len);
  }
}
