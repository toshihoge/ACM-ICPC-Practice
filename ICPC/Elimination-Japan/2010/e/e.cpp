#include<iostream>
#include<queue>
#include<vector>

using namespace std;

typedef pair<string, int> PSI;

string solve(int n, int s, int g, const vector<vector<PSI> > &edges) {
  bool visited[n];
  vector<priority_queue<PSI, vector<PSI>, greater<PSI> > > qs(12*n+6);
  string strongest = "|";
  
  qs[0].push(make_pair("", s));
  for (int length = 0; length < 12*n; length++) {
    fill(visited, visited+n, false);
    
    while (!qs[length].empty()) {
      PSI p = qs[length].top();
      qs[length].pop();
      if (visited[p.second]) continue;
      visited[p.second] = true;
      if (p.second == g) {
        if (p.first < strongest) {
          if (p.first.length() > 6*n) return "NO";
          strongest = p.first;
        }
        break;
      }
      for (vector<PSI>::const_iterator it = edges[p.second].begin(); it != edges[p.second].end(); it++) {
        string nextLabel = p.first + it->first;
        qs[nextLabel.length()].push(make_pair(nextLabel, it->second));
      }
    }
  }
  if (strongest == "|") return "NO";
  return strongest;
}

int main(void) {
  while (true) {
    int n, a, s, g;
    cin >> n >> a >> s >> g;
    if (n == 0) break;
    vector<vector<PSI> > edges(n);
    for (int i = 0; i < a; i++) {
      int src, dst;
      string label;
      cin >> src >> dst >> label;
      edges[src].push_back(make_pair(label, dst));
    }
    cout << solve(n, s, g, edges) << endl;
  }
}
