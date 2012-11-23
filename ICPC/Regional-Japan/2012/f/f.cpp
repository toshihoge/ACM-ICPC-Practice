#include<cstdio>
#include<vector>

using namespace std;

typedef pair<int, int> edge;

edge edges[100010];

edge find_root_compress(int index) {
  if (edges[index].first == 0) {
    return make_pair(index, 0);
  } else {
    edge e = find_root_compress(edges[index].first);
    edges[index].first = e.first;
    edges[index].second += e.second;
    return edges[index];
  }
}

int main(void) {
  while(true) {
    int n, m;
    scanf("%d %d", &n, &m);
    if (n == 0) {
      break;
    }
    for (int i = 0; i <= n; i++) {
      edges[i] = make_pair(0, 0);
    }
    for (int i = 0; i < m; i++) {
      char s[16];
      scanf("%s", s);
      if (s[0] == '!') {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        edge ea = find_root_compress(a);
        edge eb = find_root_compress(b);
        if (ea.first != eb.first) {
          edges[ea.first] = make_pair(eb.first, - ea.second + eb.second + w);
        }
      } else {
        int a, b;
        scanf("%d %d", &a, &b);
        edge ea = find_root_compress(a);
        edge eb = find_root_compress(b);
        if (ea.first != eb.first) {
          printf("UNKNOWN\n");
        } else {
          printf("%d\n", ea.second - eb.second);
        }
      }
    }
  }
}

