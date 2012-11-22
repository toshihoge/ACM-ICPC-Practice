#include<iostream>

using namespace std;

#define W  300
#define HW 150
#define NORM_LIMIT 20000

typedef long long ll;

int main(void) {
  int ginkgo_number[W][W];
  for (int m = -HW; m < HW; m++) {
    ll mm = m*m;
    if (mm > NORM_LIMIT) {
      if (m > 0) {
        break;
      }
      continue;
    }
    for (int n = -HW; n < HW; n++) {
      ll nn = n*n;
      if (mm + nn > NORM_LIMIT) {
        if (n > 0) {
          break;
        }
        continue;
      }
      for (int x = -HW; x < HW; x++) {
        ll xx = x*x;
        if (xx * (mm + nn) > NORM_LIMIT) {
          if (x > 0) {
            break;
          }
          continue;
        }
        for (int y = -HW; y < HW; y++) {
          ll yy = y*y;
          if ((xx + yy) * (mm + nn) > NORM_LIMIT) {
            if (y > 0) {
              break;
            }
            continue;
          }
          int p = m*x - n*y;
          int q = m*y + n*x;
          ginkgo_number[p + HW][q + HW]++;
        }
      }
    }
  }

  int t;
  for (cin >> t; t > 0; t--) {
    int m, n;
    cin >> m >> n;
    cout << (ginkgo_number[m + HW][n + HW] == 8 ? 'P' : 'C') << endl;
  }
}
