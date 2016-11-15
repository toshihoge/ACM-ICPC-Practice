import java.util.*;
import java.math.*;
 
public class Main {
  private static final long MOD = 1000000007;
 
  private static long mul(long a, long b) {
    return (a * b) % MOD;
  }
 
  private static long pow(long a, long n) {
    if (n == 0) {
      return 1;
    }
 
    long v = pow(a, n/2);
    long vv = mul(v, v);
    if (n % 2 == 0) {
      return vv;
    } else {
      return mul(a, vv);
    }
  }
 
  private static long sub(long a, long b) {
    return (a + MOD - b) % MOD;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    HashMap<Integer, Integer> counterMap = new HashMap<Integer, Integer>();
    for (int i = 0; i < n; i++) {
      int a = s.nextInt();
      if (i == 0 && a > 0) {
        System.out.println(0);
        return;
      }
      if (i > 0 && a == 0) {
        System.out.println(0);
        return;
      }
      if (counterMap.get(a) == null) {
        counterMap.put(a, 1);
      } else {
        counterMap.put(a, counterMap.get(a) + 1);
      }
    }
 
    long[] counter = new long[counterMap.size()];
    for (int i = 0; i < counter.length; i++) {
      if (counterMap.get(i) == null) {
        System.out.println(0);
        return;
      }
      counter[i] = counterMap.get(i);
    }
 
    long result = 1;
    for (int i = 1; i < counter.length; i++) {
      // result *= (2^counter[i-1] - 1)^counter[i]
      // result *= 2^((counter[i]-1)*counter[i]/2)
      result = mul(result, pow(sub(pow(2, counter[i-1]), 1), counter[i]));
      result = mul(result, pow(2, (counter[i] - 1)*counter[i]/2));
    }
    System.out.println(result);
  }
}
