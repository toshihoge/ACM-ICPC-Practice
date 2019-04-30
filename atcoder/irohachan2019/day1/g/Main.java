import java.util.*;

public class Main {
  private static long solve(int n, int m, int k, long[] a) {
    /*
    if (m * k < n) {
      return -1;
    }
    */
    long[][] dptable = new long[m+1][n+1];
    for (long[] list : dptable) {
      Arrays.fill(list, Long.MIN_VALUE);
    }
    dptable[0][0] = 0;
    for (int d = 1; d <= n; d++) {
      for (int i = 1; i <= m; i++) {
        for (int db = Math.max(0, d - k); db < d; db++) {
          dptable[i][d] = Math.max(dptable[i][d], dptable[i-1][db] + a[d-1]);
        }
      }
    }
    
    /*
    for (int i = 0; i <= m; i++) {
      for (int j = 0; j <= n; j++) {
        System.out.printf("%d ", dptable[i][j]);
      }
      System.out.println();
    }
    */  
    
    long maxValue = Long.MIN_VALUE;
    for (int d = Math.max(0, n - k + 1); d <= n; d++) {
      maxValue = Math.max(maxValue, dptable[m][d]);
    }
    if (maxValue < 0) {
      return -1;
    }
    return maxValue;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    int k = s.nextInt();
    long[] a = new long[n];
    for (int i = 0; i < n; i++) {
      a[i] = s.nextLong();
    }
    System.out.println(solve(n, m, k, a));
  }
}
