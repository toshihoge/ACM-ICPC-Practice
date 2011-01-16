#include<iostream>
#include<vector>

using namespace std;

#define EPS 1e-6

class Piece {
public:
  vector<Piece> children;
  vector<pair<int, int> > positions;
  double xmin;
  double xmax;
  int weightSingle;
  int weightTotal;
  double gSingle;
  double gTotal;
  
  bool isStable() {
    double gSum = gSingle*weightSingle;
    weightTotal = weightSingle;
    for (vector<Piece>::iterator it = children.begin(); it != children.end(); it++) {
      if (!it->isStable()) {
        return false;
      }
      weightTotal += it->weightTotal;
      gSum += it->weightTotal*it->gTotal;
    }
    gTotal = gSum/weightTotal;
    return xmin+EPS < gTotal && gTotal < xmax-EPS;
  }
  
  void addPosition(int i, int j, const vector<vector<int> > &map) {
    gSingle = (gSingle*weightSingle + (double)j + 0.5) / (weightSingle+1);
    weightSingle++;
    positions.push_back(make_pair(i, j));
    if (map[i+1][j] != map[i][j] && map[i+1][j] != 0) {
      xmin = min(xmin, (double)j);
      xmax = max(xmax, (double)j+1);
    }
  }
  
  Piece () {
    xmin = 100.0;
    xmax = -100.0;
    weightSingle = 0;
    weightTotal = 0;
    gSingle = 0.0;
    gTotal = 0.0;
  }
};

int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};

void dfs(int i, int j, int v, Piece &piece, const vector<vector<int> > &map, vector<vector<bool> > &visited) {
  if (visited[i][j] || map[i][j] != v) return;
  visited[i][j] = true;
  piece.addPosition(i, j, map);
  for (int k = 0; k<4; k++) {
    dfs(i+di[k], j+dj[k], v, piece, map, visited);
  }
}

Piece parse(int i, int j, const vector<vector<int> > &map, vector<vector<bool> > &visited) {
  Piece output;
  dfs(i, j, map[i][j], output, map, visited);
  for(vector<pair<int, int> >::iterator it = output.positions.begin(); it != output.positions.end(); it++) {
    if (map[it->first-1][it->second] != 0 && !visited[it->first-1][it->second]) {
      output.children.push_back(parse(it->first-1, it->second, map, visited));
    }
  }
  return output;
}

bool solve(int w, int h, const vector<vector<int> > &map) {
  vector<vector<bool> > visited(h+2);
  for (int i = 0; i < h+2; i++) {
    for (int j = 0; j < w+2; j++) {
      visited[i].push_back(false);
    }
  }
  
  for (int j = 0; j < w; j++) {
    if (map[h][j] != 0) {
      return parse(h, j, map, visited).isStable();
    }
  }
  return false;
}

int main(void) {
  while (true) {
    int w, h;
    cin >> w >> h;
    if (w == 0) break;
    
    vector<vector<int> > map(h+2);
    for (int j = 0; j < w+2; j++) {
      map[0].push_back(0);
      map[h+1].push_back(10);
    }
    for (int i = 1; i <= h; i++) {
      map[i].push_back(0);
      string str;
      cin >> str;
      for (int j = 1; j <= w; j++) {
        if (str[j-1] == '.') {
          map[i].push_back(0);
        } else {
          map[i].push_back(str[j-1] - '0');
        }
      }
      map[i].push_back(0);
    }
    cout << (solve(w, h, map) ? "STABLE" : "UNSTABLE") << endl;
  }
}
