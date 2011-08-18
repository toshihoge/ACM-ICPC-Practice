#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)

void cut(int n, int p, int c, vi& deck) {
  REP(i,c) {
    deck.push_back(deck[n-p-c+1]);
    deck.erase(deck.begin() + (n-p-c+1));
  }
}

int main(void) {
  while (true) {
    int n, r;
    cin >> n >> r;
    if (n == 0 && r == 0) {
      break;
    }
    vi deck;
    REP(i,n) {
      deck.push_back(i+1);  
    }
    REP(i,r) {
      int p, c;
      cin >> p >> c;
      cut(n, p, c, deck);
    }
    cout << deck[n-1] << endl;
  }
}
