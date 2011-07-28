#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

#define MAX_N 210

#define DRCTS 4

int mini;
int minj;
int maxi;
int maxj;
int color;

bool map[MAX_N][MAX_N];
int testbed[MAX_N][MAX_N];

int DI[DRCTS] = {1, 0, -1, 0};
int DJ[DRCTS] = {0, 1, 0, -1};
char CHAR_TABLE[] = {'W', 'A', 'K', 'J', 'S', 'D'};

int decodeChar(char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  } else if('a' <= c && c <= 'f') {
    return c - 'a' + 10;
  } else {
    exit(0);
  }
}

bool decode(string s, int index) {
  int i = index/4;
  int j = 3 - index%4;
  return ((decodeChar(s[i]) >> j) & 1) == 1;
}

void moveToTestbed(int i, int j) {
  if (!map[i][j])return;
  map[i][j] = false;
  testbed[i][j] = color;
  mini = min(mini, i-1);
  minj = min(minj, j-1);
  maxi = max(maxi, i+1);
  maxj = max(maxj, j+1);
  for (int k = 0; k < DRCTS; k++) {
    moveToTestbed(i + DI[k], j + DJ[k]);
  }
}

void paintDfs(int i, int j) {
  if (i < mini || maxi < i || j < minj || maxj < j ||
      testbed[i][j] == color){
    return;
  }
  testbed[i][j] = color;
  for (int k = 0; k < DRCTS; k++) {
    paintDfs(i + DI[k], j + DJ[k]);
  }
}

int countHoles() {
  int count = -1;
  for (int i = mini; i <= maxi; i++) {
    for (int j = minj; j <= maxj; j++) {
      if (testbed[i][j] != color) {
        count++;
        paintDfs(i, j);
      }
    }
  }
  return count;
}

string solve(int h, int w, const string* lines) {
  for (int i = 0; i < h+2; i++) {
    for (int j = 0; j < 4*w+2; j++) {
      map[i][j] = false;
      testbed[i][j] = 0;
    }
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= 4*w; j++) {
      map[i][j] = decode(lines[i-1], j-1);
    }
  }
  color = 0;
  vector<char> list;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= 4*w; j++) {
      if (map[i][j]) {
        mini = i;
        maxi = i;
        minj = j;
        maxj = j;
        color++;
        moveToTestbed(i, j);
        list.push_back(CHAR_TABLE[countHoles()]);
      }
    }
  }
  sort(list.begin(), list.end());
  ostringstream os;
  for (int i = 0; i < (int)list.size(); i++) {
    os << list[i];
  }
  return os.str();
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    int h, w;
    cin >> h >> w;
    if (h == 0 && w == 0) {
      break;
    }
    string lines[h];
    for (int i = 0; i < h; i++) {
      cin >> lines[i];
    }
    cout << "Case " << casenumber << ": " << solve(h, w, lines) << endl;
  }
}
