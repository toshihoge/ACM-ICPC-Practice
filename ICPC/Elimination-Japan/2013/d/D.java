import java.util.*;

public class D {
  public static void main(String[] args) {
    
    Solver solver = new Solver();
    solver.init();
    Scanner s = new Scanner(System.in);
    
    while (true) {
      int m = s.nextInt();
      int n = s.nextInt();
      if (m == 0) {
        break;
      }
      Info info = solver.solve(m, n);
      System.out.printf("%d %d\n", info.number, info.lastPrime);
    }
  }
}

class Solver {
  private static final int MAX_N = 1048576;
  private static final int ROOT_N = 1024;
  
  private int[] indexIs;
  private int[] indexJs;
  private int[][] map;
  private boolean[] prime;
  
  private Info[][] cache;
  
  private void initPrimeTable() {
    prime = new boolean[MAX_N];
    Arrays.fill(prime, true);
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i*i < MAX_N; i++) {
      if (prime[i]) {
        for (int j = i; i*j < MAX_N; j++) {
          prime[i*j] = false;
        }
      }
    }
  }
  
  private void initMap() {
    indexIs = new int[MAX_N];
    indexJs = new int[MAX_N];
    map = new int[ROOT_N][ROOT_N];
    for (int[] array : map) {
      Arrays.fill(array, MAX_N);
    }
    
    int k = 1;
    int i = ROOT_N / 2;
    int j = ROOT_N / 2;
    
    indexIs[k] = i;
    indexJs[k] = j;
    map[i][j] = k;
    
    int[] di = new int[]{0, -1,  0, 1};
    int[] dj = new int[]{1,  0, -1, 0};
    int[] time = new int[]{1, 1, 2, 2};
    output: while (true) {
      for (int a = 0; a < 4; a++) {
        for (int b = 0; b < time[a]; b++) {
          i += di[a];
          j += dj[a];
          k++;
          if (k >= MAX_N || i < 0 || j < 0 || i >= ROOT_N || j >= ROOT_N) {
            break output;
          }
          
          indexIs[k] = i;
          indexJs[k] = j;
          map[i][j] = k;
        }
      }
      for (int a = 0; a < 4; a++) {
        time[a] += 2;
      }
    }
  }
  
  public void init() {
    initPrimeTable();
    initMap();
  }
  
  private Info memoDfs(int m, int i, int j) {
    if (i < 0 || j < 0 || ROOT_N <= i || ROOT_N <= j) {
      return new Info();
    }
    if (cache[i][j] != null) {
      return cache[i][j];
    }
    
    int n = map[i][j];
    if (n > m) {
      cache[i][j] = new Info();
      return cache[i][j];
    }
    
    int nextI = i+1;
    Info largestChild = new Info();
    for (int nextJ = j-1; nextJ <= j+1; nextJ++) {
      Info child = memoDfs(m, nextI, nextJ);
      if (child.isLarge(largestChild)) {
        largestChild = child;
      }
    }
    
    cache[i][j] = new Info(largestChild.number, largestChild.lastPrime);
    if (prime[n]) {
      cache[i][j].number++;
      if (cache[i][j].lastPrime == 0) {
        cache[i][j].lastPrime = n;
      }
    }
    return cache[i][j];
  }
  
  public Info solve(int m, int n) {
    cache = new Info[ROOT_N][ROOT_N];
    return memoDfs(m, indexIs[n], indexJs[n]);
  }
}

class Info {
  int number;
  int lastPrime;
  
  Info() {
    number = 0;
    lastPrime = 0;
  }
  
  Info(int number, int lastPrime) {
    this.number = number;
    this.lastPrime = lastPrime;
  }
  
  // if this > info then true
  public boolean isLarge(Info info) {
    if (this.number != info.number) {
      return this.number > info.number;
    }
    return this.lastPrime > info.lastPrime;
  }
}
