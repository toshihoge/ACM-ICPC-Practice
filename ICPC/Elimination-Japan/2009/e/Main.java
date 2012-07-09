import java.util.*;

class MaximumBipartiteMatchingSolver {
  boolean[][] matrix;
  int n;
  private boolean dfs(int index, boolean[] visit) {
    if (index == n-1) {
      return true;
    }
    visit[index] = true;
    for (int i = 0; i < n; i++) {
      if (!matrix[index][i] || visit[i]) {
        continue;
      }
      if (dfs(i, visit)) {
        matrix[index][i] = false;
        matrix[i][index] = true;
        return true;
      }
    }
    return false;
  }

  private int maximumElement(ArrayList<Integer> elements) {
    int maximum = 0;
    for (int e: elements) {
      maximum = Math.max(maximum, e);
    }
    return maximum;
  }

  public int solve(
      ArrayList<Integer> srcs, ArrayList<Integer> dsts) {
    int maxSrc = maximumElement(srcs) + 1;
    int maxDst = maximumElement(dsts) + 1;
    n = maxSrc + maxDst + 2;
    matrix = new boolean[n][n];
    for (int i = 0; i < maxSrc; i++) {
      matrix[n-2][i] = true;
    }
    for (int i = 0; i < maxDst; i++) {
      matrix[i + maxSrc][n-1] = true;
    }
    for (int i = 0; i < srcs.size(); i++) {
      matrix[srcs.get(i)][dsts.get(i) + maxSrc] = true;
    }

    int maching = 0;
    while (dfs(n-2, new boolean[n])) {
      maching++;
    }
    return maching;
  }
}

public class Main {

  private static int gcd(int a, int b) {
    return a%b == 0 ? b : gcd(b, a%b);
  }

  private static int solve(int m, int n, int[] b, int[] r) {
    ArrayList<Integer> srcs = new ArrayList<Integer>();
    ArrayList<Integer> dsts = new ArrayList<Integer>();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (gcd(b[i], r[j]) > 1) {
          srcs.add(i);
          dsts.add(j);
        }
      }
    }
    return new MaximumBipartiteMatchingSolver().solve(srcs, dsts);
  }
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    while (true) {
      int m = s.nextInt();
      int n = s.nextInt();
      if (m == 0) {
        break;
      }
      int[] b = new int[m];
      int[] r = new int[n];
      for (int i = 0; i < m; i++) {
        b[i] = s.nextInt();
      }
      for (int i = 0; i < n; i++) {
        r[i] = s.nextInt();
      }
      System.out.println(solve(m, n, b, r));
    }
  }
}
