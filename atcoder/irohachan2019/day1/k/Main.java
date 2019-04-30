import java.util.*;

public class Main {
  private static final long P = 1000000007;
  
  private static long add(long a, long b) {
    return (a + b) % P;
  }
  
  private static long mul(long a, long b) {
    long k = 100000;
    
    long aH = a / k;
    long aL = a % k;
    long bH = b / k;
    long bL = b % k;
    return ((aH * bH * (k * k % P)) + (aH * bL + aL * bH) * k + aL * bL) % P;
    
    
//    return (a * b) % P;
  }
  
  private static long getDigitFactor(long n) {
    long digitFactor = 1;
    while (digitFactor * 10 <= n) {
      digitFactor *= 10;
    }
    return digitFactor*10;
  }
  
  private static long solve(int n, int[] m, long[][] a) {
    long[] countFactor = new long[n];
    countFactor[0] = 1;
    for (int i = 1; i < n; i++) {
      countFactor[i] = mul(countFactor[i-1], m[i-1]);
    }
    
    long answer = 0;
    long digitShiftFactor = 1;
    for (int i = n-1; i >= 0; i--) {
      long nextDigitShiftFactor = 0;
      for (int j = 0; j < m[i]; j++) {
//        System.err.printf("%d %d %d\n", countFactor[i], a[i][j], digitShiftFactor);
        answer = add(answer, mul(mul(countFactor[i], a[i][j]), digitShiftFactor));
        nextDigitShiftFactor = add(nextDigitShiftFactor, mul(getDigitFactor(a[i][j]), digitShiftFactor));
      }
      digitShiftFactor = nextDigitShiftFactor;
    }
    return answer;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    int n = s.nextInt();
    int[] m = new int[n];
    long[][] a = new long[n][];
    for (int i = 0; i < n; i++) {
      m[i] = s.nextInt();
      a[i] = new long[m[i]];
      for (int j = 0; j < m[i]; j++) {
        a[i][j] = s.nextLong();
      }
    }
    System.out.println(solve(n, m, a));
    
  }
}

