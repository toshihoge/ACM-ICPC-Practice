#include<cstdio>
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<int, vll> outputInfo;

#define DEBUG cerr<<"Debug: "<<__LINE__<<endl
#define IMPOSSIBLE (" impossible")
#define EMPTY (" empty")
#define INF (1<<30)
#define IMPOSSIBLE_OUTPUT (make_pair(INF, vector<ll>()));

ll divAndFloor(ll a, ll b) {
  if (a < 0) {
    return 0;
  }
  return a/b+(a%b?1:0);
}

ll pow(ll m, int num) {
  ll output = 1;
  for (int i = 0; i < num; i++) {
    output *= m;
  }
  return output;
}

outputInfo solveFixedNumberOfM(
    ll a, ll m, ll p, ll q, ll r, ll s, int numberOfM) {
  ll u = divAndFloor(r - p*pow(m, numberOfM), a);
  ll v = (s - q*pow(m, numberOfM)) / a;
  if (v < u) {
    return IMPOSSIBLE_OUTPUT;
  }
  vector<ll> h(numberOfM+1);
  fill(h.begin(), h.end(), 0);
  for (int i = numberOfM; i >= 0; i--) {
    ll mi = pow(m, i);
    ll uDiv = divAndFloor(u, mi);
    ll vDiv = v / mi;
    if (uDiv <= vDiv) {
      h[i] = uDiv;
      break;
    } else {
      h[i] = uDiv-1;
      u -= h[i]*mi;
      v -= h[i]*mi;
    }
  }
  return make_pair(numberOfM, h);
}

ll totalOperators(const outputInfo &a) {
  ll output = a.first;
  for (int i = 0; i < a.second.size(); i++) {
    output += a.second[i];
  }
  return output;
}

outputInfo selectSmallerOne(const outputInfo &a, const outputInfo &b) {
  ll aOperators = totalOperators(a);
  ll bOperators = totalOperators(b);
  if (aOperators != bOperators) {
    if (aOperators < bOperators) {
      return a;
    } else {
      return b;
    }
  }
  int aIndex = a.second.size() - 1;
  int bIndex = b.second.size() - 1;
  while (min(aIndex, bIndex) >= 0) {
    if (a.second[aIndex] != b.second[bIndex]) {
      if (a.second[aIndex] > b.second[bIndex]) {
        return a;
      } else {
        return b;
      }
    }
    aIndex--;
    bIndex--;
  }
  return a;
}

bool isEmpty(const outputInfo &a) {
  return a.first == 0 && a.second.size() == 1 && a.second[0] == 0;
}

string convertToString(const outputInfo &a) {
  if (a.first == INF) {
    return IMPOSSIBLE;
  }
  if (isEmpty(a)) {
    return EMPTY;
  }
  vector<pair<int, char> > templist;
  for (int i = a.second.size()-1; i >= 0; i--) {
    if (a.second[i] > 0) {
      templist.push_back(make_pair(a.second[i], 'A'));
    }
    if (i > 0) {
      if (templist.size() > 0 && templist.back().second == 'M') {
        templist.back().first++;
      } else {
        templist.push_back(make_pair(1, 'M'));
      }
    }
  }
  ostringstream os;
  for (int i = 0; i < templist.size(); i++) {
    os << " " << templist[i].first << templist[i].second;
  }
  return os.str();
}

string solveMIsOne(ll a, ll p, ll q, ll r, ll s) {
  return convertToString(solveFixedNumberOfM(a, 1, p, q, r, s, 0));
}

string solveMNotOne(ll a, ll m, ll p, ll q, ll r, ll s) {
  outputInfo output = IMPOSSIBLE_OUTPUT;
  for (int numberOfM = 0; q*pow(m, numberOfM) <= s;
      numberOfM++) {
    output = selectSmallerOne(output, 
        solveFixedNumberOfM(a, m, p, q, r, s, numberOfM));
  }
  return convertToString(output);
}

string solve(ll a, ll m, ll p, ll q, ll r, ll s) {
  if (r <= p && p <= s && r <= q  && q <= s) {
    return EMPTY;
  }
  if (m == 1) {
    return solveMIsOne(a, p, q, r, s);
  } else {
    return solveMNotOne(a, m, p, q, r, s);
  }
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    ll a, m, p, q, r, s;
    cin >> a >> m >> p >> q >> r >> s;
    if (a == 0) {
      break;
    }
    printf("Case %d:%s\n", casenumber, solve(a, m, p, q, r, s).c_str());
  }
}
