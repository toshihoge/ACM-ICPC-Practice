import java.util.*;

public class A {
  private static int solve(int n, int k, int s, int[][][] memo) {
    if (n < 0 || k < 0 || s < 0) {
      return 0;
    }
    if (k == 0) {
      if (s == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    if (memo[n][k][s] >= 0) {
      return memo[n][k][s];
    }
    memo[n][k][s] = 0;
    for (int i = n; i > 0; i--) {
      memo[n][k][s] += solve(i-1, k-1, s-i, memo);
    }
    return memo[n][k][s];
  }
  
  public static void main(String[] args) {
    int[][][] memo = new int[21][11][156];
    for (int[][] memo1 : memo) {
      for (int[] memo2 : memo1) {
        Arrays.fill(memo2, -1);
      }
    }
    
    Scanner sc = new Scanner(System.in);
    while(true) {
      int n = sc.nextInt();
      int k = sc.nextInt();
      int s = sc.nextInt();
      if (n == 0) {
        break;
      }
      System.out.println(solve(n, k, s, memo));
    }
  }
}
