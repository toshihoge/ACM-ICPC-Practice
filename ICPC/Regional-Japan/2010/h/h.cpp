#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int patternWidth = 1000;

typedef struct node {
  char* p;
  int i;
  int j;
} Node;

bool operator < (const Node &n1, const Node &n2) {
  if (strncmp(n1.p, n2.p, patternWidth) < 0) {
    return true;
  }
  return false;
}

int decode(char c) {
  if ('A' <= c && c <= 'Z') {
    return c - 'A';
  } else if('a' <= c && c <= 'z') {
    return c - 'a' + 26;
  } else if('0' <= c && c <= '9') {
    return c - '0' + 52;
  } else if(c == '+') {
    return 62;
  } else { // c == '/'
    return 63;
  }
}

void decode(char* buf, string line) {
  for (int i = 0; i < line.length(); i++) {
    int d = decode(line[i]);
    for (int j = 5; j >= 0; j--) {
      if (d & 1) {
        buf[6*i+j] = '1';
      } else {
        buf[6*i+j] = '0'; 
      }
      d >>= 1;
    }
  }
}

#define IN 1010
#define PN  110

char ibuf[IN][IN];
char pbuf[PN][PN];
char rotatedBuf[PN][PN];
bool isp[IN][IN];
Node nodes[1000010];

int count1[IN][IN];
int count2[IN][IN];

void rotatePBuf(int p) {
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < p; j++) {
      rotatedBuf[p-1-j][i] = pbuf[i][j];
    }
  }
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < p; j++) {
      pbuf[i][j] = rotatedBuf[i][j];
    }
  }
}

int solve(int w, int h, int p, const string* image, const string* pattern) {
  patternWidth = p;
  
  for (int i = 0; i < h; i++) {
    decode(ibuf[i], image[i]);
    ibuf[i][w] = '\0';
  }
  int total = h*(w-p+1);
  int k = 0;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w-(p-1); j++) {
      nodes[k].p = &(ibuf[i][j]);
      nodes[k].i = i;
      nodes[k].j = j;
      k++;
    }
  }
  sort(nodes, nodes + total);
  
  for (int i = 0; i < p; i++) {
    decode(pbuf[i], pattern[i]);
    pbuf[i][p] = '\0';
  }
  
  for (int i = 0; i < h-p+1; i++) {
    for (int j = 0; j < w-p+1; j++) {
      isp[i][j] = false;
    }
  }
  
  for (int r = 0; r < 4; r++) {
    for (int i = 0; i < h-p+1; i++) {
      for (int j = 0; j < w-p+1; j++) {
        count1[i][j] = 0;
        count2[i][j] = 0;
      }
    }
    
    for (int a = 0; a < p; a++) {
      Node target;
      target.p = pbuf[a];
      pair<Node*, Node*> bounds = equal_range(nodes, nodes + total, target);
      
      for (Node* it = bounds.first; it != bounds.second; it++) {
        if (it->i >= a) {
          count1[it->i - a][it->j]++;
        }
        if (it->i >= p-1-a) {
          count2[it->i - p+1+a][it->j]++;
        }
      }
    }
    
    for (int i = 0; i < h-p+1; i++) {
      for (int j = 0; j < w-p+1; j++) {
        if (count1[i][j] == p || count2[i][j] == p) {
          isp[i][j] = true;
        }
      }
    }
    
    
    
    rotatePBuf(p);
  }
  
  int count = 0;
  for (int i = 0; i < h-p+1; i++) {
    for (int j = 0; j < w-p+1; j++) {
      if (isp[i][j]) {
        count++;
      }
    }
  }
  return count;
}

int main(void) {
  int t1 = 0;
  while(true) {
    int w, h, p;
    cin >> w >> h >> p;
    if (w == 0) break;
    string image[h];
    string pattern[p];
    for (int i = 0; i < h; i++) {
      cin >> image[i];
    }
    for (int i = 0; i < p; i++) {
      cin >> pattern[i];
    }
    cout << solve(w, h, p, image, pattern) << endl;
  }
}
