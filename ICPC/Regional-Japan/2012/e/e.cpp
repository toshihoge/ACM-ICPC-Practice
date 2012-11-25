#include<iostream>
#include<queue>
#include<set>
#include<vector>

using namespace std;

typedef vector<string> vs;
typedef pair<int, int> pii;
typedef vector<vector<bool> > vvb;
typedef pair<pii, int> ppiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef struct King {
  pii pos;
  int type;
  King(pii pos, int type) : pos(pos), type(type) {}
} King;
typedef pair<int, King> pik;
typedef vector<pik> vpik;
typedef set<King> sk;
typedef priority_queue<pik, vector<pik>, greater<pik> > pq;

int DI[] = {0, 1, 0, -1};
int DJ[] = {1, 0, -1, 0};

int KING_OSS_DRCT_0_I[] = {0, 2, 0, -1};
int KING_OSS_DRCT_0_J[] = {2, 0, -1, 0};
int KING_OSS_DRCT_1_I[] = {1, 2, 1, -1};
int KING_OSS_DRCT_1_J[] = {2, 1, -1, 1};

#define INF (1<<28)

bool operator<(const King& k1, const King& k2) {
  if (k1.pos != k2.pos) {
    return k1.pos < k2.pos;
  }
  return k1.type < k2.type;
};

vvi bfs_space(const pii &src, const vvb &obstacle) {
  vvi output(obstacle.size(), vi(obstacle[0].size(), INF));
  deque<ppiii> q;
  q.push_back(make_pair(src, 0));
  while (!q.empty()) {
    ppiii p = q.front();
    q.pop_front();
    pii ij = p.first;
    int i = ij.first;
    int j = ij.second;
    if (output[i][j] < INF) {
      continue;
    }
    output[i][j] = p.second;
    for (int k = 0; k < 4; k++) {
      int nexti = i + DI[k];
      int nextj = j + DJ[k];
      if (!obstacle[nexti][nextj] && output[nexti][nextj] == INF) {
        q.push_back(make_pair(make_pair(nexti, nextj), p.second+1));
      }
    }
  }
  return output;
}

void fill_king(const pii &kingpos, bool value, vvb &obstacles) {
  obstacles[kingpos.first  ][kingpos.second  ] = value;
  obstacles[kingpos.first  ][kingpos.second+1] = value;
  obstacles[kingpos.first+1][kingpos.second  ] = value;
  obstacles[kingpos.first+1][kingpos.second+1] = value;
}

vpik king_move_cost(const pii *spaces, const pii &kingpos, int basecost,
    vvb &obstacle) {
  fill_king(kingpos, true, obstacle);
  vvi table0 = bfs_space(spaces[0], obstacle);
  vvi table1 = bfs_space(spaces[1], obstacle);
  vpik output;
  for (int k = 0; k < 4; k++) {
    int i0 = kingpos.first  + KING_OSS_DRCT_0_I[k];
    int j0 = kingpos.second + KING_OSS_DRCT_0_J[k];
    int i1 = kingpos.first  + KING_OSS_DRCT_1_I[k];
    int j1 = kingpos.second + KING_OSS_DRCT_1_J[k];
    int min_cost = INF;
    min_cost = min(min_cost, basecost + table0[i0][j0] + table1[i1][j1] + 1);
    min_cost = min(min_cost, basecost + table0[i1][j1] + table1[i0][j0] + 1);
    if (min_cost < INF) {
      pii nextkingpos = make_pair(kingpos.first + DI[k], kingpos.second + DJ[k]);
      output.push_back(make_pair(min_cost, King(nextkingpos, (k+2)%4)));
    }
  }
  fill_king(kingpos, false, obstacle);
  return output;
}

bool is_king_goal(const pii &kingpos) {
  return kingpos.first == 1 && kingpos.second == 1;
}

int dijkstra(const pii *init_spaces, const pii &init_kingpos, vvb &obstacle) {
  if (is_king_goal(init_kingpos)) {
    return 0;
  }
  pq q;
  vpik inits = king_move_cost(init_spaces, init_kingpos, 0, obstacle);
  for (int i = 0; i < inits.size(); i++) {
    q.push(inits[i]);
  }
  sk s;
  while(!q.empty()) {
    pik p = q.top();
    q.pop();
    int cost = p.first;
    King king = p.second;
    if (s.count(king)) {
      continue;
    }
    s.insert(king);
    if (is_king_goal(king.pos)) {
      return cost;
    }
    pii spaces[2] = {
      make_pair(king.pos.first  + KING_OSS_DRCT_0_I[king.type],
                king.pos.second + KING_OSS_DRCT_0_J[king.type]),
      make_pair(king.pos.first  + KING_OSS_DRCT_1_I[king.type],
                king.pos.second + KING_OSS_DRCT_1_J[king.type])
    };
    vpik nexts = king_move_cost(spaces, king.pos, cost, obstacle);
    for (int i = 0; i < nexts.size(); i++) {
      pik next = nexts[i];
      if (s.count(next.second)) {
        continue;
      }
      q.push(next);
    }
  }
  return -1;
}

vvb parse_obstacles(const vs &initial_map) {
  vvb obstacles(initial_map.size()+2, vector<bool>(initial_map[0].size()+2, true));
  for (int i = 0; i < initial_map.size(); i++) {
    for (int j = 0; j < initial_map[i].size(); j++) {
      obstacles[i+1][j+1] = (initial_map[i][j] == '*');
    }
  }
  return obstacles;
}

void find_openspaces(const vs &initial_map, pii *spaces) {
  int count = 0;
  for (int i = 0; i < initial_map.size(); i++) {
    for (int j = 0; j < initial_map[i].size(); j++) {
      if (initial_map[i][j] == '.') {
        spaces[count] = make_pair(i+1, j+1);
        count++;
        if (count == 2) {
          return;
        }
      }
    }
  }
}

pii find_king(const vs &initial_map) {
  for (int i = 0; i < initial_map.size(); i++) {
    for (int j = 0; j < initial_map[i].size(); j++) {
      if (initial_map[i][j] == 'X') {
        return make_pair(i+1, j+1);
      }
    }
  }
  // never reaches
}

int solve(const vs &initial_map) {
  vvb obstacle = parse_obstacles(initial_map);
  pii spaces[2];
  find_openspaces(initial_map, spaces);
  pii king = find_king(initial_map);
  return dijkstra(spaces, king, obstacle);
}

int main(void) {
  while(true) {
    int h, w;
    cin >> h >> w;
    if (h == 0) {
      break;
    }
    vs initial_map;
    for (int i = 0; i < h; i++) {
      string line;
      cin >> line;
      initial_map.push_back(line);
    }
    cout << solve(initial_map) << endl;
  }
}
