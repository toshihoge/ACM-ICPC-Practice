#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef long long ll;

typedef struct {
  ll p;
  ll q;
  vector<char> history;
} node;

bool finish(const node &n, ll r, ll s) {
  return r <= n.p && n.p <= s && r <= n.q && n.q <= s;
}

void printHistory(const node &n) {
  if (n.history.size() == 0) {
    cout << " empty";
    return;
  }
  vector<char> temp = n.history;
  temp.push_back('X');
  int length = 1;
  for (int i = 1; i < temp.size(); i++) {
    if (temp[i-1] != temp[i]) {
      cout << " " << length << temp[i-1];
      length = 1;
    } else {
      length++;
    }
  }
}

node add(const node &n, ll a) {
  node output = n;
  output.p += a;
  output.q += a;
  output.history.push_back('A');
  return output;
}

node mul(const node &n, ll m) {
  node output = n;
  output.p *= m;
  output.q *= m;
  output.history.push_back('M');
  return output;
}

void solve(ll a, ll m, ll p, ll q, ll r, ll s) {
  node n;
  n.p = p;
  n.q = q;
  n.history.clear();

  queue<node> bfsq;
  bfsq.push(n);
  while(!bfsq.empty()) {
    node current = bfsq.front();
    bfsq.pop();
    if (finish(current, r, s)) {
      printHistory(current);
      return;
    }
    if (current.q > s) {
      continue;
    }
    bfsq.push(add(current, a));
    if (m > 1) {
      bfsq.push(mul(current, m));
    }
  }
  cout << " impossible";
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    ll a, m, p, q, r, s;
    cin >> a >> m >> p >> q >> r >> s;
    if (a == 0) {
      break;
    }
    cout << "Case " << casenumber << ":";
    solve(a, m, p, q, r, s);
    cout << endl;
  }
}
