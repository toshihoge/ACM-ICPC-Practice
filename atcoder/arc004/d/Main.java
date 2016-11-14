import java.util.*;

public class Main {
  private final static long MOD = 1000000007;

  private static long mul(long a, long b) {
    return (a * b) % MOD;
  }

  private static long add(long a, long b) {
    return (a + b) % MOD;
  }

  private static void split(int n, boolean plus, HashMap<Integer, Integer> mapping) {
    for (int i = 2; i*i <= n; i++) {
      int counter = 0;
      while (n % i == 0) {
        counter++;
        n /= i;
      }
      if (counter > 0) {
        if (mapping.get(i) == null) {
          mapping.put(i, plus ? counter : -counter);
        } else {
          mapping.put(i, mapping.get(i) + (plus ? counter : -counter));
        }
      }
    }
    if (n > 1) {
      if (mapping.get(n) == null) {
        mapping.put(n, plus ? 1 : -1);
      } else {
        mapping.put(n, mapping.get(n) + (plus ? 1 : -1));
      }
    }
  }

  private static long comb(int n, int k) {
    HashMap<Integer, Integer> mapping = new HashMap<Integer, Integer>();
    for (int i = n; i > n-k; i--) {
      split(i, true, mapping);
    }
    for (int i = 1; i <= k; i++) {
      split(i, false, mapping);
    }
    long result = 1;
    for (Map.Entry<Integer, Integer> entry : mapping.entrySet()) {
      int key = entry.getKey();
      int count = entry.getValue();
      for (int i = 0; i < count; i++) {
        result = mul(result, key);
      }
    }
    return result;
  }

  private static Collection<Integer> getPowerFactors(int n) {
    HashMap<Integer, Integer> mapping = new HashMap<Integer, Integer>();
    split(n, true, mapping);
    return mapping.values();
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);

    int n = Math.abs(s.nextInt());
    int m = s.nextInt();

    // 2^(m-1) PI C(a+m-1, a)
    long result = 1;
    for (int i = 0; i < m-1; i++) {
      result = mul(result, 2);
    }

    Collection<Integer> powerFactors = getPowerFactors(n);
    for (int powerFactor : powerFactors) {
      result = mul(result, comb(powerFactor+m-1, powerFactor));
    }
    System.out.println(result);
  }
}
