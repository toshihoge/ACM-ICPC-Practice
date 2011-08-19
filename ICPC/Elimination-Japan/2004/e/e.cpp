#include<cmath>
#include<complex>
#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

typedef complex<double> cd;

typedef vector<int> vi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)

#define EPS 1e-6
#define DEPTH 30.0

class Tank {
private:
  void addWater(int x, double w) {
    if (isLeaf || (left->isFull() && right->isFull())) {
      water += w;
      if (water > capacity) {
        double overflow = water - capacity;
        water = capacity;
        if (parent != NULL) {
          parent->addWater(x, overflow);
        }
      }
    } else if(!right->isFull() && !left->isFull()) {
      if (x < xsplitter) {
        left->addWater(x, w);
      } else {
        right->addWater(x, w);
      }
    } else if(!right->isFull()) {
      right->addWater(x, w);
    } else if(!left->isFull()) {
      left->addWater(x, w);
    }
  }
public:
  Tank *parent;
  double area;
  double capacity;
  double water;
  bool isLeaf;
  int xsplitter;
  int hsplitter;
  Tank *left;
  Tank *right;

  Tank(Tank *parent, double area, double capacity, bool isLeaf,
      int xsplitter, int hsplitter):
    parent(parent), area(area), capacity(capacity), water(0.0),
    isLeaf(isLeaf), xsplitter(xsplitter), hsplitter(hsplitter),
    left(NULL), right(NULL) {}

  ~Tank() {
    if (left != NULL) {
      delete left;
    }
    if (right != NULL) {
      delete right;
    }
  }

  void clearWater() {
    water = 0.0;
    if (left != NULL) {
      left->clearWater();
    }
    if (right != NULL) {
      right->clearWater();
    }
  }

  bool isFull() {
    return fabs(water - capacity) < EPS;
  }

  void pourWater(int x, double w) {
    if (isLeaf) {
      addWater(x, w);
    } else if (x < xsplitter) {
      left->pourWater(x, w);
    } else {
      right->pourWater(x, w);
    }
  }

  double getHeight(int x) {
    if (water > 0.0) {
      return hsplitter + water / area;
    }
    if (isLeaf) {
      return 0.0;
    }
    if (x < xsplitter) {
      return left->getHeight(x);
    } else {
      return right->getHeight(x);
    }
  }
};

Tank* initTanksSub(
    int begin, int end, const int* b, const int* h, Tank* parent) {
  double area = (b[end] - b[begin])*DEPTH;
  if (end - begin == 1) {
    return new Tank(parent, area, min(h[begin], h[end])*area, true, -1, 0);
  } else {  // end - begin > 1
    int index = begin+1;
    FOR(i, begin+2, end) {
      if (h[i] > h[index]) {
        index = i;
      }
    }
    Tank* output = new Tank(parent, area, 
        (min(h[begin], h[end]) - h[index])*area, false, b[index], h[index]);
    output->left  = initTanksSub(begin, index, b, h, output);
    output->right = initTanksSub(index, end, b, h, output);
    return output;
  }
}

Tank* initTanks(int n, const int* b, const int* h) {
  return initTanksSub(0, n-1, b, h, NULL);
}

double solve(Tank* root, int m, const int* f, const int* a, int p, int t) {
  root->clearWater();
  REP(i, m) {
    root->pourWater(f[i], a[i]*t);
  }
  return root->getHeight(p);
}

int main(void) {
  int d;
  cin >> d;
  REP(casenum,d) {
    int n;
    cin >> n;
    int b[n+2], h[n+2];
    b[0] = 0;
    b[n+1] = 100;
    h[0] = 50;
    h[n+1] = 50;
    REP(i,n) {
      cin >> b[i+1] >> h[i+1];
    }
    Tank* root = initTanks(n+2, b, h);

    int m;
    cin >> m;
    int f[m], a[m];
    REP(i,m) {
      cin >> f[i] >> a[i];
    }
    int l;
    cin >> l;
    REP(i,l) {
      int p, t;
      cin >> p >> t;
      printf("%.10f\n", solve(root, m, f, a, p, t));
    }
    delete root;
  }
}
