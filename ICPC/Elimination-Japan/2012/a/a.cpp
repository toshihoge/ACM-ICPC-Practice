#include<iostream>

using namespace std;

int main(void) {
  int table[1002][11][21];

  int year = 1;
  int month = 1;
  int day = 1;
  int count = 1;
  while (true) {
    table[year][month][day] = count;
    
    if (year == 1000) {
      break;
    }

    bool big_year = (year % 3 == 0) || (month % 2 == 1);
    day++;
    count++;
    if (big_year) {
      if (day == 21) {
        day = 1;
        month++;
      }
    } else {
      if (day == 20) {
        day = 1;
        month++;
      }
    }

    if (month == 11) {
      month = 1;
      year++;
    }
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int y, m, d;
    cin >> y >> m >> d;
    cout << table[1000][1][1] - table[y][m][d] << endl;
  }
}
