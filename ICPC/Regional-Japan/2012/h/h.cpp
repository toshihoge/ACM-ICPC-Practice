#include<iostream>
#include<set>
#include<stack>
#include<vector>

using namespace std;

typedef struct {
  int type;
  int i;
  int j;
} constraint;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef set<int>::const_iterator sici;
typedef vector<si> vsi;
typedef vector<pair<int, int> > vpii;
typedef vector<bool> vb;

#define DEBUG cout<<"Debug: "<<__LINE__<<endl
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)

vsi build_graph(int n, int m, const constraint *cs) {
  vsi graph(n);
  for (int a = 0; a < m; a++) {
    int type = cs[a].type;
    int i = cs[a].i;
    int j = cs[a].j;
    if (type == 1) {
      graph[j].insert(i);
    } else if (type == 2) {
      graph[i].insert(j);
      graph[j].insert(i);
    }
  }
  return graph;
}

void visit(const vsi &graph, int v, vvi &scc, stack<int> &s, vector<bool> &ins,
    vi &lower, vi &number, int &time) {
  time++;
  lower[v] = time;
  number[v] = time;
  s.push(v);
  ins[v] = true;
  EACH(it, graph[v]) {
    int w = *it;
    if (number[w] == 0) {
      visit(graph, w, scc, s, ins, lower, number, time);
      lower[v] = min(lower[v], lower[w]);
    } else if(ins[w]) {
      lower[v] = min(lower[v], lower[w]);
    }
  }
  if (lower[v] == number[v]) {
    scc.push_back(vector<int>());
    while(true) {
      int w = s.top();
      s.pop();
      ins[w] = false;
      scc.back().push_back(w);
      if (v == w) {
        break;
      }
    }
  }
}

vvi strongly_connected_components(const vsi &graph) {
  vvi scc;
  int n = graph.size();
  vi number(n), lower(n);
  stack<int> s;
  vector<bool> ins(n);
  int time = 0;
  for (int u = 0; u < n; u++) {
    if (number[u] == 0) {
      visit(graph, u, scc, s, ins, lower, number, time);
    }
  }
  return scc;
}

vi build_group2scc(int n, const vvi &scc) {
  vi group2scc(n);
  for (int i = 0; i < scc.size(); i++) {
    for (int j = 0; j < scc[i].size(); j++) {
      group2scc[scc[i][j]] = i;
    }
  }
  return group2scc;
}

vpii extract_scc_constraints(int n, int m, const constraint *cs,
    int scc_size, const vi &group2scc, int type) {
  vector<vector<bool> > matrix(scc_size, vector<bool>(scc_size, false));
  for (int a = 0; a < m; a++) {
    if (cs[a].type == type) {
      int i = group2scc[cs[a].i];
      int j = group2scc[cs[a].j];
      matrix[i][j] = true;
    }
  }
  vpii output;
  for (int i = 0; i < scc_size; i++) {
    for (int j = 0; j < scc_size; j++) {
      if (matrix[i][j]) {
        output.push_back(make_pair(i, j));
      }
    }
  }
  return output;
  
}

vsi build_scc_graph(int scc_size, const vpii &scc_edge_pairs) {
  vsi scc_graph(scc_size);
  EACH(it, scc_edge_pairs){
    if (it->first != it->second) {
      scc_graph[it->second].insert(it->first);
    }
  }
  return scc_graph;
}


void add_common_member(const vpii &common_pairs, vsi &scc_graph) {
  int dummy = -1;
  EACH(it, common_pairs){
    scc_graph[it->first].insert(dummy);
    scc_graph[it->second].insert(dummy);
    dummy--;
  }
}

void build_flatten_scc_graph_dfs(int index, vsi &flatten_scc_graph,
    const vsi &scc_graph) {
  if (flatten_scc_graph[index].size() > 0) {
    return;
  }
  EACH(it1, scc_graph[index]) {
    flatten_scc_graph[index].insert(*it1);
    if (*it1 >= 0) {
      build_flatten_scc_graph_dfs(*it1, flatten_scc_graph, scc_graph);
      EACH(it2, flatten_scc_graph[*it1]) {
        flatten_scc_graph[index].insert(*it2);
      }
    }
  }
}

vsi build_flatten_scc_graph(const vsi &scc_graph) {
  int scc_size = scc_graph.size();
  vsi flatten_scc_graph(scc_size);
  for (int i = 0; i < scc_size; i++) {
    build_flatten_scc_graph_dfs(i, flatten_scc_graph, scc_graph);
  }
  return flatten_scc_graph;
}

bool has_negative(const si &s) {
  EACH(it, s) {
    if (*it < 0) {
      return true;
    }
  }
  return false;
}

vector<bool> build_strictly_non_empty(const vsi &flatten_scc_graph) {
  vector<bool> strictly_non_empty;
  for (int i = 0; i < flatten_scc_graph.size(); i++) {
    strictly_non_empty.push_back(has_negative(flatten_scc_graph[i]));
  }
  return strictly_non_empty;
}

bool has_common_negative(const si &s1, const si &s2) {
  EACH(it, s1) {
    if (*it < 0 && s2.count(*it) > 0) {
      return true;
    }
  }
  return false;
}

vi get_common_positive(const si &s1, const si &s2) {
  vi output;
  EACH(it, s1) {
    if (*it > 0 && s2.count(*it) > 0) {
      output.push_back(*it);
    }
  }
  return output;
}

bool mark_strictly_empty(int index, const vsi &flatten_scc_graph,
    vector<bool> &strictly_empty) {
  EACH(it, flatten_scc_graph[index]) {
    if (*it < 0) {
      return false;
    }
    strictly_empty[*it] = true;
  }
  return true;
}

bool verify_disjointness(const vpii &disjoint_pairs,
    const vsi &flatten_scc_graph, const vb &nonempty, vb &empty) {
  EACH (it1, disjoint_pairs) {
    const si *s1 = &flatten_scc_graph[it1->first];
    const si *s2 = &flatten_scc_graph[it1->second];
    if (has_common_negative(*s1, *s2)) {
      return false;
    }
    vi common_groups = get_common_positive(*s1, *s2);
    EACH(it2, common_groups) {
      if (nonempty[*it2]) {
        return false;
      }
      empty[*it2] = true;
    }
  }

  return true;
}

bool verify_unequalness(const vpii &unequal_pairs, const vb &empty) {
  EACH (it, unequal_pairs) {
    if (it->first == it->second) {
      return false;
    }
    if (empty[it->first] && empty[it->second]) {
      return false;
    }
  }
  return true;
}

bool acceptable(int n, int m, const constraint *cs) {
  vvi scc = strongly_connected_components(build_graph(n, m, cs));
  vi group2scc = build_group2scc(n, scc);
  vsi scc_graph = build_scc_graph(scc.size(), 
      extract_scc_constraints(n, m, cs, scc.size(), group2scc, 1));
  add_common_member(
      extract_scc_constraints(n, m, cs, scc.size(), group2scc, 5), scc_graph);
  vsi flatten_scc_graph = build_flatten_scc_graph(scc_graph);
  vb nonempty = build_strictly_non_empty(flatten_scc_graph);
  vb empty(scc.size(), false);
  if (!verify_disjointness(
      extract_scc_constraints(n, m, cs, scc.size(), group2scc, 4),
      flatten_scc_graph, nonempty, empty)) {
    return false;
  }
  return verify_unequalness(
      extract_scc_constraints(n, m, cs, scc.size(), group2scc, 3), empty);
}

int solve(int n, int m, const constraint *cs) {
  int min_number = 1;
  int max_number = m+1;
  while(max_number - min_number > 1) {
    int mid_number = (max_number + min_number) / 2;
    if (acceptable(n, mid_number, cs)) {
      min_number = mid_number;
    } else {
      max_number = mid_number;
    }
  }
  return min_number;
}

int main(void) {
  while(true) {
    int n, m;
    cin >> n >> m;
    if (n == 0) {
      break;
    }
    n++;
    constraint cs[m];
    for (int i = 0; i < m; i++) {
      cin >> cs[i].type >> cs[i].i >> cs[i].j;
    }
    cout << solve(n, m, cs) << endl;
  }
}
