import java.util.*;

class Solver {
  int n;
  long k;
  long[] a;
  int[][] sumDigits;
  
  Solver(int n, long k, long[] a) {
    this.n = n;
    this.k = k;
    this.a = a;
  }
  
  private int[][] buildSumDigits() {
    int[][] sumDigits = new int[n+1][64];
    Arrays.fill(sumDigits[0], 0);
    for (int i = 1; i <= n; i++) {
      int[] m2 = mod2(a[i-1]);
      for (int j = 0; j < 64; j++) {
        sumDigits[i][j] = sumDigits[i-1][j] + m2[j];
      }
    }
    return sumDigits;
  }
  
  private int[] mod2(long v) {
    int[] array = new int[64];
    for (int i = 0; i < 64; i++) {
      array[i] = (int)((v >> i) & 1);
    }
    return array;
  }
  
  private boolean exceedOrEqualTo(int[] endArray, int[] beginArray, int[] b) {
    for (int i = 63; i >= 0; i--) {
      if (endArray[i] - beginArray[i] > 0 && b[i] == 0) {
        return true;
      }
      if (endArray[i] - beginArray[i] == 0 && b[i] > 0) {
        return false;
      }
    }
    return true;
  }
  
  private long count(long threshold) {
    int[] m2 = mod2(threshold);
    long sum = 0;
    int beginIndex = 0;
    int endIndex = 1;
    while (endIndex < n+1) {
      while (!exceedOrEqualTo(sumDigits[endIndex], sumDigits[beginIndex], m2)) {
        endIndex++;
        if (endIndex == n+1) {
          return sum;
        }
      }
      sum += n+1 - endIndex;
      beginIndex++;
    }
    return sum;
  }
  
  public long solve() {
    sumDigits = buildSumDigits();
    
    long minValue = 0L;
    long maxValue = 1L << 61;
    while (maxValue - minValue > 1) {
      long midValue = (maxValue + minValue) / 2;
      if (count(midValue) >= k) {
        minValue = midValue;
      } else {
        maxValue = midValue;
      }
    }
    return minValue;
  }
}

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    int n = s.nextInt();
    long k = s.nextLong();
    long[] a = new long[n];
    for (int i = 0; i < n; i++) {
      a[i] = s.nextLong();
    }
    Solver solver = new Solver(n, k, a);
    System.out.println(solver.solve());
  }
}
