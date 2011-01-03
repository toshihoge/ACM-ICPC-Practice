#include<iostream>
#include<cmath>
#include<queue>
#include<set>
#include<vector>

using namespace std;

typedef struct line {
  int xl;
  int yl;
  int xr;
  int yr;
  line(int _xl, int _yl, int _xr, int _yr) {
    xl = _xl;
    yl = _yl;
    xr = _xr;
    yr = _yr;
  }
} Line;

typedef struct pos {
  int left;
  int right;
  int height;
  pos(int _left, int _right, int _height) {
    left = _left;
    right = _right;
    height = _height;
  }
} POS;

bool operator < (const POS &p1, const POS &p2) {
  if (p1.left < p2.left) return true;
  if (p1.left > p2.left) return false;
  if (p1.right < p2.right) return true;
  if (p1.right > p2.right) return false;
  return p1.height < p2.height;
}

int getMaxY(const Line &line) {
  return max(line.yl, line.yr);
}

int getMinY(const Line &line) {
  return min(line.yl, line.yr);
}

double getX(int y, const Line &line) {
  if (line.yl == line.yr) {
    return line.xl;
  }
  return (double)(y - line.yl)*(line.xr - line.xl) / (line.yr - line.yl) + line.xl;
}

vector<POS> getNextPositions(const POS &pos, const vector<Line> &lines) {
  vector<POS> output;
  //+
  output.push_back(POS(pos.left, pos.right, min(getMaxY(lines[pos.left]), getMaxY(lines[pos.right]))));
  //-
  output.push_back(POS(pos.left, pos.right, max(getMinY(lines[pos.left]), getMinY(lines[pos.right]))));
  //=l go left
  if (lines[pos.left].yl == pos.height) {
    output.push_back(POS(pos.left-1, pos.right, pos.height));
  }
  //=l go right
  if (lines[pos.left].yr == pos.height) {
    output.push_back(POS(pos.left+1, pos.right, pos.height));
  }
  //=r go left
  if (lines[pos.right].yl == pos.height) {
    output.push_back(POS(pos.left, pos.right-1, pos.height));
  }
  //=r go right
  if (lines[pos.right].yr == pos.height) {
    output.push_back(POS(pos.left, pos.right+1, pos.height));
  }
  return output;
}

double solve(const vector<Line> &lines) {
  set<POS> visited;
  priority_queue<pair<double, POS> > q;
  
  q.push(make_pair(0.0, POS(0, lines.size() - 1, 0)));
  while (!q.empty()) {
    pair<double, POS> p = q.top();
    q.pop();
    double cost = -p.first;
    POS pos = p.second;
    if (pos.left == pos.right) {
      return cost;
    }
    if (visited.find(pos) != visited.end()) {
      continue;
    }
    visited.insert(pos);
    vector<POS> nexts = getNextPositions(pos, lines);
    
    double srcxl = getX(pos.height, lines[pos.left]);
    double srcxr = getX(pos.height, lines[pos.right]);
    for (vector<POS>::iterator it = nexts.begin(); it != nexts.end(); it++) {
      if (0 <= it->left && it->left < lines.size() && 0 <= it->right && it->right < lines.size() && visited.find(*it) == visited.end()) {
        int dy = pos.height - it->height;
        double dxl = getX(it->height, lines[it->left]) - srcxl;
        double dxr = getX(it->height, lines[it->right]) - srcxr;
        double nextcost = cost + sqrt(dxl*dxl + dy*dy) + sqrt(dxr*dxr + dy*dy);
        q.push(make_pair(-nextcost, *it));
      }
    }
  }
  return -1.0;
}

int main(void) {
  priority_queue<POS> q;
  
  while (true) {
    int n;
    cin >> n;
    if (n == 0) break;
    
    int x[n], y[n];
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i];
    }
    vector<Line> lines;
    lines.push_back(Line(x[0], y[0], x[0], y[0]));
    for (int i = 1; i < n; i++) {
      if (y[i-1] != y[i]) {
        lines.push_back(Line(x[i-1], y[i-1], x[i], y[i]));
      }
      lines.push_back(Line(x[i], y[i], x[i], y[i]));
    }
    printf("%.10f\n", solve(lines));
  }
}
