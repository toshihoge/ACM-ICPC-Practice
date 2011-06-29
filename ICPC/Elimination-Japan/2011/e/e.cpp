#include<iostream>
#include<vector>
#include<map>

using namespace std;

typedef vector<vector<int> > vvi;
typedef pair<int, int> pii;
typedef struct {
  int mini;
  int minj;
  int maxi;
  int maxj;
} area;
typedef map<area, pii> cache;

bool operator< (const area &a1, const area &a2) {
  if (a1.mini != a2.mini) {
    return a1.mini < a2.mini;
  } else if (a1.minj != a2.minj) {
    return a1.minj < a2.minj;
  } else if (a1.maxi != a2.maxi) {
    return a1.maxi < a2.maxi;
  } else {
    return a1.maxj < a2.maxj;
  } 
}

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

int getSum(const area& a, const vvi &sumTable) {
  return sumTable[a.maxi][a.maxj] - sumTable[a.maxi][a.minj] -
      sumTable[a.mini][a.maxj] + sumTable[a.mini][a.minj];
}

pii merge(const pii &p1, const pii &p2) {
  if (p1.first == 0 || p2.first == 0) {
    return make_pair(0, 0);
  }
  return make_pair(p1.first + p2.first, min(p1.second, p2.second));
}

area makeArea(int mini, int minj, int maxi, int maxj) {
  area a;
  a.mini = mini;
  a.minj = minj;
  a.maxi = maxi;
  a.maxj = maxj;
  return a;
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
  for (int i = a.mini+1; i < a.maxi; i++) {
    pii temp = merge(
        solveDfsWithMemo(makeArea(a.mini, a.minj, i, a.maxj),
            sumTable, c, bound),
        solveDfsWithMemo(makeArea(i, a.minj, a.maxi, a.maxj),
            sumTable, c, bound));
    if (output < temp) {
      output = temp;
    }
  }
  for (int j = a.minj+1; j < a.maxj; j++) {
    pii temp = merge(
        solveDfsWithMemo(makeArea(a.mini, a.minj, a.maxi, j),
            sumTable, c, bound),
        solveDfsWithMemo(makeArea(a.mini, j, a.maxi, a.maxj),
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
