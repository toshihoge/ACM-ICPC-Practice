#include<iostream>

using namespace std;

bool shouldBeDayCarryUp(int year, int month, int day) {
  if (year % 3 == 0 || month % 2 == 1) {
    return day == 21;
  } else {
    return day == 20;
  }
}

int main(void) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int y, m, d;
    cin >> y >> m >> d;
    int count = 0;
    while (y < 1000) {
      d++;
      count++;
      if (shouldBeDayCarryUp(y, m, d)) {
        d = 1;
        m++;
      }

      if (m == 11) {
        m=1;
        y++;
      }
    }
    cout << count << endl;
  }
}
