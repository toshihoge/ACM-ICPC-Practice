//--------------------------------------
// Begin common header
//--------------------------------------
#include<algorithm>
#include<cmath>
#include<complex>
#include<cstdio>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<vector>

using namespace std;

typedef pair<int, int> Pii;
typedef complex<double> Cd;
typedef vector<int> Vi;
typedef vector<Vi> Vvi;
typedef vector<double> Vd;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define SORT(c) sort((c).begin(), (c).end())
#define WT while(true)

//--------------------------------------
// End common header
//--------------------------------------

typedef unsigned int Foot;
typedef unsigned int Status;
typedef pair<int, Status> Node;
typedef priority_queue<Node, vector<Node>, greater<Node> > Queue;

#define T 0
#define S 10
#define X 12

#define OUTSIDE_FOOT 0xFFFF

int getI(Foot f) {
  return f >> 8;
}

int getJ(Foot f) {
  return f & 0xFF;
}

Foot makeFoot(int i, int j, const Vvi &wall) {
  if (i < 0 || wall.size() <= i || j < 0 || wall[i].size() <= j ||
      wall[i][j] == X) {
    return OUTSIDE_FOOT;
  }
  return (i << 8) | j;
}

Foot getLeftFoot(Status s) {
  return s >> 16;
}

Foot getRightFoot(Status s) {
  return s & 0xFFFF;
}

Status makeStatus(Foot left, Foot right) {
  return (left << 16) | right;
}

bool isGoal(Foot f, const Vvi &wall) {
  if (f == OUTSIDE_FOOT) {
    return false;
  }
  return wall[getI(f)][getJ(f)] == T;
}

int solve(const Vvi &wall) {
  Queue queue;
  REP(i,wall.size()) {
    REP(j,wall[i].size()) {
      if (wall[i][j] == S) {
        Foot f = makeFoot(i, j, wall);
        queue.push(make_pair(0, makeStatus(f, OUTSIDE_FOOT)));
        queue.push(make_pair(0, makeStatus(OUTSIDE_FOOT, f)));
      }
    }
  }
  set<Status> visited;
  while(!queue.empty()) {
    Node node = queue.top();
    queue.pop();
    int cost = node.first;
    Status status = node.second;
    if (HAS(visited, status)) {
      continue;
    }
    visited.insert(status);
    Foot leftFoot = getLeftFoot(status);
    Foot rightFoot = getRightFoot(status);
    if (isGoal(leftFoot, wall) || isGoal(rightFoot, wall)) {
      return cost;
    }
    FOR(i, -3, 4) {
      FOR(j, -3, 0) {
        if (abs(i) + abs(j) <= 3) {
          int nextLeftFootI = getI(rightFoot) + i;
          int nextLeftFootJ = getJ(rightFoot) + j;
          Foot nextLeftFoot = makeFoot(nextLeftFootI, nextLeftFootJ, wall);
          if (nextLeftFoot != OUTSIDE_FOOT) {
            Status nextStatus = makeStatus(nextLeftFoot, rightFoot);
            if (!HAS(visited, nextStatus)) {
              int nextCost = cost + wall[nextLeftFootI][nextLeftFootJ];
              queue.push(make_pair(nextCost, nextStatus));
            }
          }
        }
      }
      FOR(j, 1, 4) {
        if (abs(i) + abs(j) <= 3) {
          int nextRightFootI = getI(leftFoot) + i;
          int nextRightFootJ = getJ(leftFoot) + j;
          Foot nextRightFoot = makeFoot(nextRightFootI, nextRightFootJ, wall);
          if (nextRightFoot != OUTSIDE_FOOT) {
            Status nextStatus = makeStatus(leftFoot, nextRightFoot);
            if (!HAS(visited, nextStatus)) {
              int nextCost = cost + wall[nextRightFootI][nextRightFootJ];
              queue.push(make_pair(nextCost, nextStatus));
            }
          }
        }
      }
    }
  }
  return -1;
}

int main(void) {
  WT {
    int w, h;
    cin >> w >> h;
    if (!w) {
      break;
    }
    Vvi wall(h);
    REP (i, h) {
      REP (j, w) {
        char c;
        cin >> c;
        switch (c) {
        case 'S':
          wall[i].push_back(S);
          break;
        case 'T':
          wall[i].push_back(T);
          break;
        case 'X':
          wall[i].push_back(X);
          break;
        default:
          wall[i].push_back(c - '0');
          break;
        }
      }
    }
    cout << solve(wall) << endl;
  }
}
