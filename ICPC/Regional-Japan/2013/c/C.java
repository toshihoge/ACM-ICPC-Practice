import java.util.*;

public class C {
  private static final int SIZE = 210;
  
  private static HashMap<Integer, Integer> createNormalizeTable(int[] as, int[] bs) {
    HashSet<Integer> hs = new HashSet<Integer>();
    for (int a : as) {
      hs.add(a);
    }
    for (int b : bs) {
      hs.add(b);
    }
    Integer[] values = hs.toArray(new Integer[0]);
    Arrays.sort(values);
    HashMap<Integer, Integer> table = new HashMap<Integer, Integer>();
    for (int i = 0; i < values.length; i++) {
      table.put(values[i], i+2);
    }
    return table;
  }
  
  private static int[] convert(int n, int[] raws, HashMap<Integer, Integer> table) {
    int[] converted = new int[n];
    for (int i = 0; i < n; i++) {
      converted[i] = table.get(raws[i]);
    }
    return converted;
  }
  
  private static void dfs(int iBegin, int jBegin, boolean[][] vEdges, boolean[][] hEdges, boolean[][] visited) {
    // Maintain stack by myself, because 40,000 times recursive calls will stack-overflow.
    Stack<IJ> stack = new Stack<IJ>();
    stack.add(new IJ(iBegin, jBegin));
    while(!stack.empty()) {
      IJ ij = stack.pop();
      int i = ij.i;
      int j = ij.j;
      if (visited[i][j]) {
        continue;
      }
      visited[i][j] = true;
      if (!vEdges[i][j+1]) {
        stack.add(new IJ(i, j+1));
      }
      if (!vEdges[i][j]) {
        stack.add(new IJ(i, j-1));
      }
      if (!hEdges[i+1][j]) {
        stack.add(new IJ(i+1, j));
      }
      if (!hEdges[i][j]) {
        stack.add(new IJ(i-1, j));
      }
    }
  }
  
  // Mini visualizer
  private static void visualize(boolean[][] vEdges, boolean[][] hEdges) {
    char[][] map = new char[50][50];
    for (char[] cs : map) {
      Arrays.fill(cs, ' ');
    }
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        if (vEdges[i][j]) {
          map[2*i+1][2*j] = '|';
        }
        if (hEdges[i][j]) {
          map[2*i][2*j+1] = '-';
        }
      }
    }
    for (int i = 0; i < 50; i++) {
      System.out.println(map[i]);
    }
  }
  
  private static int solve(int n, int[] lsRaw, int[] tsRaw, int[] rsRaw, int[] bsRaw) {
    HashMap<Integer, Integer> vTable = createNormalizeTable(tsRaw, bsRaw);
    int[] ts = convert(n, tsRaw, vTable);
    int[] bs = convert(n, bsRaw, vTable);
    HashMap<Integer, Integer> hTable = createNormalizeTable(lsRaw, rsRaw);
    int[] ls = convert(n, lsRaw, hTable);
    int[] rs = convert(n, rsRaw, hTable);
    
    boolean[][] vEdges = new boolean[SIZE][SIZE];
    boolean[][] hEdges = new boolean[SIZE][SIZE];
    for (int i = 0; i < n; i++) {
      for (int j = bs[i]; j < ts[i]; j++) {
        vEdges[j][ls[i]] = true;
        vEdges[j][rs[i]] = true;
      }
      for (int j = ls[i]; j < rs[i]; j++) {
        hEdges[bs[i]][j] = true;
        hEdges[ts[i]][j] = true;
      }
      /*
      System.out.printf("%d %d %d %d\n", lsRaw[i], tsRaw[i], rsRaw[i], bsRaw[i]);
      System.out.printf("%d %d %d %d\n", ls[i], ts[i], rs[i], bs[i]);
      visualize(vEdges, hEdges);
      */
    }
    
    boolean[][] visited = new boolean[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
      visited[i][0] = true;
      visited[i][SIZE-1] = true;
      visited[0][i] = true;
      visited[SIZE-1][i] = true;
    }
    
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (visited[i][j]) {
          continue;
        }
        count++;
        dfs(i, j, vEdges, hEdges, visited);
      }
    }
    return count;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while(true) {
      int n = s.nextInt();
      if (n == 0) {
        break;
      }
      int[] ls = new int[n];
      int[] ts = new int[n];
      int[] rs = new int[n];
      int[] bs = new int[n];
      for (int i = 0; i < n; i++) {
        ls[i] = s.nextInt();
        ts[i] = s.nextInt();
        rs[i] = s.nextInt();
        bs[i] = s.nextInt();
      }
      System.out.println(solve(n, ls, ts, rs, bs));
    }
  }
}

class IJ {
  int i, j;
  IJ(int i, int j) {
    this.i = i;
    this.j = j;
  }
}
