import java.util.*;
import java.math.*;
 
public class Main {
  private static final long MOD = 1000000007;
 
  public static long add(long a, long b) {
    return (a + b) % MOD;
  }
 
  public static long mul(long a, long b) {
    return (a * b) % MOD;
  }
 
  public static long fact(int n) {
    long output = 1;
    for (int i = 1; i <= n; i++) {
      output = mul(output, i);
    }
    return output;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int[] t = new int[n];
    int[] counter = new int[10001];
    for (int i = 0; i < n; i++) {
      t[i] = s.nextInt();
      counter[t[i]]++;
    }
    Arrays.sort(t);
    long penalty = 0;
    long currentTime = 0;
    for (int time : t) {
      currentTime += time;
      penalty += currentTime;
    }
    System.out.println(penalty);
 
    long count = 1;
    for (int i = 0; i < counter.length; i++) {
      count = mul(count, fact(counter[i]));
    }
    System.out.println(count);
  }
}
