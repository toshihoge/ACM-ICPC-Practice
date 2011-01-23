#include<cstdio>
#include<iostream>
#include<vector>
#include<set>

using namespace std;

#define FULL_MASK 0xFFFFFFFFFFFFFFFFULL
#define INVALID_BOARD 0xFFFFFFFFFFFFFFFFULL

typedef unsigned long long ull;

int di[] = {1, 0, -1, 0};
int dj[] = {0, 1, 0, -1};

int getIndex(int i, int j, int n) {
  return n*i+j;
}

vector<vector<pair<int, int> > > generateShiftTable(int n, const vector<vector<bool> > &walls) {
  vector<vector<pair<int, int> > > output(4);
  for (int type = 0; type < 4; type++) {
    for (int srci = 0; srci < n; srci++) {
      int dsti = srci + di[type];
      if (0 <= dsti && dsti < n) {
        for (int srcj = 0; srcj < n; srcj++) {
          int dstj = srcj + dj[type];
          if (0 <= dstj && dstj < n) {
            int src = getIndex(srci, srcj, n);
            int dst = getIndex(dsti, dstj, n);
            if (!walls[src][dst]) {
              output[type].push_back(make_pair(src, dst));
            }
          }
        }
      }
    }
  }
  return output;
}

ull getValue(ull board, int index) {
  return (board >> (4*index)) & 0xFULL;
}

ull deleteValue(ull board, int index) {
  return board & (FULL_MASK ^ (0xFULL << (4*index)));
}

ull insertValue(ull board, int index, ull value) {
  return board | (value << (4*index));
}

pair<ull, ull> shiftSub(pair<ull, ull> board, int src, int dst) {
  ull srcStone = getValue(board.first, src);
  
  if (srcStone == 0) {
    return board;
  }
  ull dstStone = getValue(board.first, dst);
  ull dstHole = getValue(board.second, dst);
  if (dstStone == 0 && dstHole == 0) {
    return make_pair(insertValue(deleteValue(board.first, src), dst, srcStone), board.second);
  }
  if (dstHole != 0) {
    if (dstHole == srcStone) {
      return make_pair(deleteValue(board.first, src), deleteValue(board.second, dst));
    } else {
      return make_pair(INVALID_BOARD, INVALID_BOARD);
    }
  } else {
    return board;
  }
}

pair<ull, ull> shift(pair<ull, ull> board, const vector<pair<int, int> > &table) {
  while (true) {
    pair<ull, ull> next = board;
    for (int i = 0; i < table.size(); i++) {
      next = shiftSub(next, table[i].first, table[i].second);
      if (next.first == INVALID_BOARD) {
        return make_pair(INVALID_BOARD, INVALID_BOARD);
      }
    }
    if (next == board) {
      return next;
    }
    board = next;
  }
}

int bfs(pair<ull, ull> initial, const vector<vector<pair<int, int> > > &shiftTable) {
  int moves = 1;
  set<ull> visited;
  vector<pair<ull, ull> > before;
  vector<pair<ull, ull> > after;
  
  before.push_back(initial);
  visited.insert(initial.first);
  while (!before.empty()) {
    for (int a = 0; a < before.size(); a++) {
      for (int b = 0; b < 4; b++) {
        pair<ull, ull> next = shift(before[a], shiftTable[b]);
        if (next.first == INVALID_BOARD) {
          continue;
        }
        if (next.first == 0) {
          return moves;
        }
        if (visited.find(next.first) == visited.end()) {
          visited.insert(next.first);
          after.push_back(next);
        }
      }
    }
    moves++;
    before = after;
    after.clear();
  }
  return -1;
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    int n, m, w, i, j, i1, j1, i2, j2;
    cin >> n >> m >> w;
    if (n == 0) {
      break;
    }
    ull stonesAndHoles[2] = {0, 0};
    for (int a = 0; a < 2; a++) {
      for (int k = 1; k <= m; k++) {
        cin >> i >> j;
        stonesAndHoles[a] = insertValue(stonesAndHoles[a], getIndex(i, j, n), k);
      }
    }
    vector<vector<bool> > walls(n*n, vector<bool>(n*n));
    for (int k = 0; k < w; k++) {
      cin >> i1 >> j1 >> i2 >> j2;
      int index1 = getIndex(i1, j1, n);
      int index2 = getIndex(i2, j2, n);
      walls[index1][index2] = true;
      walls[index2][index1] = true;
    }
    int answer = bfs(make_pair(stonesAndHoles[0], stonesAndHoles[1]), generateShiftTable(n, walls));
    if (answer > 0) {
      printf("Case %d: %d moves\n\n", casenumber, answer);
    } else {
      printf("Case %d: impossible\n\n", casenumber);
    }
  }
}
