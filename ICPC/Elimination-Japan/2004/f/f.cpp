#include<cmath>
#include<complex>
#include<cstdio>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<vector>

using namespace std;

typedef complex<double> cd;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<set<int> > vsi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define WT while(true)

pair<string, string> splitLoads(const string& line) {
  int index = line.find("-");
  return make_pair(line.substr(0, index),
      line.substr(index+1, line.length() - index - 1));
}

void assignIndexIfNeeded(map<string, int> &dictionary, string load) {
  if (!HAS(dictionary, load)) {
    int currentSize = dictionary.size();
    dictionary[load] = currentSize;
  }
}

map<string, int> makeDictionary(int n, const string* lines) {
  map<string, int> dictionary;
  REP(i,n) {
    pair<string, string> p = splitLoads(lines[i]);
    assignIndexIfNeeded(dictionary, p.first);
    assignIndexIfNeeded(dictionary, p.second);
  }
  return dictionary;
}

pair<vsi, vsi> extractConnectedLoads(
    int n, const string* lines, const map<string, int> &dic) {
  vector<set<int> > higherLoads(dic.size());
  vector<set<int> > lowerLoads(dic.size());
  REP(i,n) {
    pair<string, string> p = splitLoads(lines[i]);
    int indexHigher = dic.find(p.first)->second;
    int indexLower = dic.find(p.second)->second;
    higherLoads[indexLower].insert(indexHigher);
    lowerLoads[indexHigher].insert(indexLower);
  }
  return make_pair(higherLoads, lowerLoads);
}

bool hasCommonLoad(const set<int> &seti, const set<int> &setj) {
  EACH(i,seti) {
    if (HAS(setj, *i)) {
      return true;
    }
  }
  return false;
}

// i >= j
bool isStrongerOrEqual(int i, int j, const vector<set<int> > &higherLoads,
    const vector<set<int> > &lowerLoads) {
  set<int> higherThanI = higherLoads[i];
  set<int> higherThanJ = higherLoads[j];
  set<int> lowerThanI = lowerLoads[i];
  set<int> lowerThanJ = lowerLoads[j];

  if (HAS(higherThanJ,i)) {
    return true;
  }
  return (hasCommonLoad(higherThanI, higherThanJ) ||
      hasCommonLoad(lowerThanI, lowerThanJ)) &&
      !hasCommonLoad(higherThanI, lowerThanJ) &&
      !hasCommonLoad(lowerThanI, higherThanJ);
}

vvi makeMatrix(int n, const string* lines, const map<string, int> &dic,
    const vsi &higherLoads, const vsi &lowerLoads) {
  int m = dic.size();
  vvi matrix(m);
  REP(i,m) {
    REP(j,m) {
      if (i != j && isStrongerOrEqual(i, j, higherLoads, lowerLoads)) {
        matrix[i].push_back(j);
      }
    }
  }
  return matrix;
}

void assignDirectionsDfs(int index, int d, vi &directions,
    const vsi &higherLoads, const vsi &lowerLoads) {
  if (directions[index] >= 0) {
    return;
  }
  directions[index] = d;
  EACH(j,higherLoads[index]) {
    assignDirectionsDfs(*j, 1-d, directions, higherLoads, lowerLoads);
  }
  EACH(j,lowerLoads[index]) {
    assignDirectionsDfs(*j, 1-d, directions, higherLoads, lowerLoads);
  }
}

vi assignDirection(int m, const vsi &higherLoads, const vsi &lowerLoads) {
  vi directions(m, -1);
  REP(i,m) {
    if (directions[i] == -1) {
      assignDirectionsDfs(i, 0, directions, higherLoads, lowerLoads);
    }
  }
  return directions;
}

bool dijkstra(int src, int dst, const vvi &matrix) {
  bool visited[matrix.size()];
  fill(visited, visited+matrix.size(), false);
  deque<pii> q;
  q.push_back(make_pair(src, 0));
  while(!q.empty()) {
    pii p = q.front();
    q.pop_front();
    int index = p.first;
    int cost = p.second;
    if (visited[index]) {
      continue;
    }
    visited[index] = true;
    if (index == dst) {
      return true;
    }
    REP(i,matrix[index].size()) {
      int nextIndex = matrix[index][i];
      if (visited[nextIndex]) {
        continue;
      }
      q.push_back(make_pair(nextIndex, cost+1));
    }
  }
  return false;
}

string solve(string line, const map<string, int> &dic, const vvi &matrix,
    const vi &directions) {
  pair<string, string> p = splitLoads(line);
  if (HAS(dic, p.first) && HAS(dic, p.second)) {
    int src = dic.find(p.first)->second;
    int dst = dic.find(p.second)->second;
    return dijkstra(src, dst, matrix) && directions[src] != directions[dst] ?
        "YES" : "NO";
  }
  return "NO";
}

int main(void) {
  WT {
    int n;
    cin >> n;
    if (!n) {
      break;
    }
    string lines[n];
    REP(i,n) {
      cin >> lines[i];
    }
    map<string, int> dic = makeDictionary(n, lines);
    pair<vsi, vsi> bothLoads = extractConnectedLoads(n, lines, dic);
    vsi higherLoads = bothLoads.first;
    vsi lowerLoads = bothLoads.second;
    vvi matrix = makeMatrix(n, lines, dic, higherLoads, lowerLoads);
    vi directions = assignDirection(dic.size(), higherLoads, lowerLoads);
    cout << dic.size() << endl;

    int m;
    cin >> m;
    REP(i,m) {
      string line;
      cin >> line;
      pair<string, string> cross = splitLoads(line);
      cout << solve(line, dic, matrix, directions) << endl;
    }
  }
}
