#include<iostream>
#include<vector>

using namespace std;

typedef vector<vector<int> > vvi;

int DI[4] = {1, 0, -1, 0};
int DJ[4] = {0, 1, 0, -1};

bool inside(const vvi &map, int i, int j) {
  return 0 <= i && i < map.size() && 0 <= j && j < map[i].size();
}

int countDfs(vvi &map, int i, int j, int target) {
  if (inside(map, i, j) && map[i][j] == target) {
    map[i][j] = -1;
    int output = 1;
    for (int k = 0; k < 4; k++) {
      output += countDfs(map, i+DI[k], j+DJ[k], target);
    }
    return output;
  }
  return 0;
}

int count(vvi &map) {
  return countDfs(map, 0, 0, map[0][0]);
}

void changeColorSubDfs(vvi &map, int i, int j, int current, int next) {
  if (inside(map, i, j) && map[i][j] == current) {
    map[i][j] = next;
    for (int k = 0; k < 4; k++) {
      changeColorSubDfs(map, i+DI[k], j+DJ[k], current, next);
    }
  }
}

vvi changeColor(const vvi &map, int target) {
  if (map[0][0] == target) {
    return map;
  }
  vvi nextMap = map;
  changeColorSubDfs(nextMap, 0, 0, map[0][0], target);
  return nextMap;
}

int dfs(const vvi &map, int depth, int c) {
  if (depth == 4) {
    vvi finalMap = changeColor(map, c);
    return count(finalMap);
  }
  int output = 0;
  for (int i = 1; i <= 6; i++) {
    if (map[0][0] != i) {
      output = max(output, dfs(changeColor(map, i), depth+1, c));
    }
  }
  return output;
}

int solve(const vvi &input, int c) {
  return dfs(input, 0, c);
}

int main(void) {
  while (true) {
    int h, w, c;
    cin >> h >> w >> c;
    if (h == 0 && w == 0 && c == 0) {
      break;
    }
    vvi input(h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        int color;
        cin >> color;
        input[i].push_back(color);
      }
    }
    cout << solve(input, c) << endl;
  }
}
