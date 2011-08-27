#include<iostream>
#include<vector>
#include<map>

using namespace std;

typedef vector<vector<int> > vvi;
typedef pair<int, int> pii;
typedef unsigned int area;
typedef map<area, pii> cache;

vvi makeSumTable(const vvi &input) {
  vvi sumTable(input.size() + 1);
  for (int j = 0; j <= input[0].size(); j++) {
    sumTable[0].push_back(0);
  }
  for (int i = 0; i < input.size(); i++) {
    sumTable[i+1].push_back(0);
    for (int j = 0; j < input[i].size(); j++) {
      sumTable[i+1].push_back(input[i][j] + sumTable[i+1][j] +
          sumTable[i][j+1] - sumTable[i][j]);
    }
  }
  return sumTable;
}

#define MASK 0x3F
int getMaxI(const area &a) {
  return a & MASK; 
}

int getMaxJ(const area &a) {
  return (a >> 6) & MASK;
}

int getMinI(const area &a) {
  return (a >> 12) & MASK;
}

int getMinJ(const area &a) {
  return (a >> 18) & MASK;
}

area makeArea(int mini, int minj, int maxi, int maxj) {
  return (minj << 18) | (mini << 12) | (maxj << 6) | maxi;
}

int getSum(const area& a, const vvi &sumTable) {
  int maxi = getMaxI(a);
  int maxj = getMaxJ(a);
  int mini = getMinI(a);
  int minj = getMinJ(a);
  return sumTable[maxi][maxj] - sumTable[maxi][minj] -
      sumTable[mini][maxj] + sumTable[mini][minj];
}

pii merge(const pii &p1, const pii &p2) {
  if (p1.first == 0 || p2.first == 0) {
    return make_pair(0, 0);
  }
  return make_pair(p1.first + p2.first, min(p1.second, p2.second));
}

pii solveDfsWithMemo(const area& a, const vvi &sumTable, cache &c, int bound) {
  cache::iterator it = c.find(a);
  if (it != c.end()) {
    return it->second;
  }
  if (getSum(a, sumTable) < bound) {
    c[a] = make_pair(0, 0);
    return make_pair(0, 0);
  }
  pii output = make_pair(1, getSum(a, sumTable));
  int mini = getMinI(a);
  int minj = getMinJ(a);
  int maxi = getMaxI(a);
  int maxj = getMaxJ(a);
  for (int i = mini+1; i < maxi; i++) {
    pii temp = merge(
        solveDfsWithMemo(makeArea(mini, minj, i, maxj),
            sumTable, c, bound),
        solveDfsWithMemo(makeArea(i, minj, maxi, maxj),
            sumTable, c, bound));
    if (output < temp) {
      output = temp;
    }
  }
  for (int j = minj+1; j < maxj; j++) {
    pii temp = merge(
        solveDfsWithMemo(makeArea(mini, minj, maxi, j),
            sumTable, c, bound),
        solveDfsWithMemo(makeArea(mini, j, maxi, maxj),
            sumTable, c, bound));
    if (output < temp) {
      output = temp;
    }
  }
  c[a] = output;
  return output;
}

pii solve(const vvi &input, int s) {
  vvi sumTable = makeSumTable(input); 
  area whole = makeArea(0, 0, input.size(), input[0].size());
  int wholeRequire = getSum(whole, sumTable);
  cache c;
  pii result = solveDfsWithMemo(whole, sumTable, c, wholeRequire - s);
  return make_pair(result.first, result.second + s - wholeRequire);
}

int main(void) {
  while (true) {
    int h, w, s;
    cin >> h >> w >> s;
    if (h == 0 && w == 0 && s == 0) {
      break;
    }
    vvi input(h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        int k;
        cin >> k;
        input[i].push_back(k);
      }
    }
    pii answer = solve(input, s);
    cout << answer.first << " " << answer.second << endl;
  }
}
