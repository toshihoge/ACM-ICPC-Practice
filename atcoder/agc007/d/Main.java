import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    if (n > 2000) {
      throw new RuntimeException("too many");
    }
    long e = s.nextLong();
    long t = s.nextLong();
    long[] x = new long[n+1];
    for (int i = 1; i <= n; i++) {
      x[i] = s.nextLong();
    }
    long[] dptable = new long[n+1];
    dptable[0] = 0;
    for (int i = 1; i <= n; i++) {
      dptable[i] = dptable[i-1] + t;
      for (int k = 1; k < i; k++) {
        dptable[i] = Math.min(
            dptable[i],
            dptable[k-1] + 2*(x[i] - x[k]) + Math.max(t - 2*x[i] + 2*x[k], 0));
      }
    }
    System.out.println(e + dptable[n]);
  }
}
