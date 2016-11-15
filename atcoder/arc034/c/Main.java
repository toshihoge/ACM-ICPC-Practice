import java.util.*;
import java.math.*;
 
public class Main {
  private static final long MOD = 1000000007;
 
  private static long mul(long a, long b) {
    return (a * b) % MOD;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int a = s.nextInt();
    int b = s.nextInt();
    HashMap<Integer, Integer> mapping = new HashMap<Integer, Integer>();
    for (int i = b+1; i <= a; i++) {
      int j = i;
      for (int k = 2; k < (1 << 16); k++) {
        int count = 0;
        while (j % k == 0) {
          j /= k;
          count++;
        }
        if (count > 0) {
          if (mapping.get(k) == null) {
            mapping.put(k, count);
          } else {
            mapping.put(k, mapping.get(k) + count);
          }
        }
      }
      if (j > 1) {
        if (mapping.get(j) == null) {
          mapping.put(j, 1);
        } else {
          mapping.put(j, mapping.get(j) + 1);
        }
      }
    }
    long answer = 1;
    for (int count : mapping.values()) {
      answer = mul(answer, count+1);
    }
    System.out.println(answer);
  }
}
