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

typedef pair<int, int> pii;
typedef complex<double> cd;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define WT while(true)

int DIGITS[] = {1000, 100, 10, 1};
char SYMBOLS[] = {'m', 'c', 'x', 'i'};

vi split(int number) {
  vi output;
  REP(i,4) {
    output.push_back(number / DIGITS[i]);
    number %= DIGITS[i];
  }
  return output;
}

string makeMcxi(int number) {
  vi splitted = split(number);
  ostringstream os;
  REP(i, 4) {
    if (splitted[i] >= 2) {
      os << splitted[i];
    }
    if (splitted[i] >= 1) {
      os << SYMBOLS[i];
    }
  }
  return os.str();
}

int parse(const string &s) {
  int output = 0;
  int factor = 1;
  REP(i,s.size()) {
    switch (s[i]) {
    case 'm':
      output += 1000*factor;
      factor = 1;
      break;
    case 'c':
      output += 100*factor;
      factor = 1;
      break;
    case 'x':
      output += 10*factor;
      factor = 1;
      break;
    case 'i':
      output += factor;
      break;
    default:
      factor = s[i] - '0';
      break;
    }
  }
  return output;
}

string solve(const string &s1, const string &s2) {
  return makeMcxi(parse(s1) + parse(s2));
}

int main(void) {
  int n;
  cin >> n;
  REP(i,n) {
    string s1, s2;
    cin >> s1 >> s2;
    cout << solve(s1, s2) << endl;
  }
}
