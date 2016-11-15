import java.util.*;
import java.math.*;
 
public class Main {
  private static final long MOD = 1000000007;
 
  private static long add(long a, long b) {
    return (a + b) % MOD;
  }
 
  private static long mul(long a, long b) {
    return (a * b) % MOD;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int[] d = new int[1<<17];
    for (int i = 0; i < n; i++) {
      d[s.nextInt()]++;
    }
 
    long[][] dptable = new long[4][1<<17];
    for (int i = dptable[3].length-2; i >= 0; i--) {
      dptable[3][i] = dptable[3][i+1] + d[i];
    }
    for (int i = 2; i >= 0; i--) {
      for (int j = dptable[i].length-2; j >= 0; j--) {
        dptable[i][j] = dptable[i][j+1];
        if (j*2 < dptable[i+1].length) {
          dptable[i][j] = add(dptable[i][j], mul(d[j], dptable[i+1][2*j]));
        }
      }
    }
    System.out.println(dptable[0][0]);
  }
}
