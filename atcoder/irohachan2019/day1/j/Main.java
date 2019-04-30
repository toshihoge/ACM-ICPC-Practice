import java.util.*;

class ModUtils {
  private static final long P = 1000000007;
  
  public static long add(long a, long b) {
    return (a + b) % P;
  }
  
  public static long mul(long a, long b) {
    return (a * b) % P;
  }
  
  public static long pow(long a, long n) {
    if (n == 0) {
      return 1;
    }
    
    long p = pow(a, n/2);
    long p2 = mul(p, p);
    if (n % 2 == 0) {
      return p2;
    } else {
      return mul(p2, a);
    }
  }
  
  public static long inverse(long a) {
    return pow(a, P-2);
  }
}

class CombinationUtil {
  long[] fact;
  
  CombinationUtil(int n) {
    fact = new long[n];
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < n; i++) {
      fact[i] = ModUtils.mul(fact[i-1], i);
    }
  }
  
  public long comb(int n, int k) {
    long a = fact[n];
    long b = ModUtils.mul(fact[k], fact[n-k]);
    long ib = ModUtils.inverse(b);
    return ModUtils.mul(a, ib);
  }
}

class Solver {
  CombinationUtil combinationUtil;
  
  Solver() {
    combinationUtil = new CombinationUtil(100100);
  }
  
  private static int[] solveEquation(double a, double b, double c) {
    double d = b * b - 4 * a * c;
    if (d < 0) {
      return new int[]{};
    }
    if (d == 0) {
      double ans = -b / 2.0 / a;
      double roundAns = Math.round(ans);
      if (Math.abs(ans - roundAns) < 1e-6) {
        return new int[]{(int)roundAns};
      } else {
        return new int[]{};
      }
    }
    
    double dSqrt = Math.sqrt(d);
    double ans1 = (-b + dSqrt) / 2.0 / a;
    double ans2 = (-b - dSqrt) / 2.0 / a;
    double roundAns1 = Math.round(ans1);
    double roundAns2 = Math.round(ans2);
    double diff1 = Math.abs(ans1 - roundAns1);
    double diff2 = Math.abs(ans2 - roundAns2);
    if (diff1 < 1e-6 && diff2 < 1e-6) {
      return new int[]{(int)roundAns1, (int)roundAns2};
    } else if (diff1 < 1e-6) {
      return new int[]{(int)roundAns1};
    } else if (diff2 < 1e-6) {
      return new int[]{(int)roundAns2};
    } else {
      return new int[]{};
    }
  }
  
  private long solveEven(int n, long k) {
    // a+b=L
    // 2*a*b = k
    // 2*a*(L-a)=k
    // a*(2L-2a)=k
    // 2a^2-2La+k=0
    // a = L+-(L^2-2k)^0.5/2
    int[] as = solveEquation(2, -n, k);
    long answer = 0;
    for (int a : as) {
      if (0 <= a && a <= n/2) {
        answer = ModUtils.add(answer, combinationUtil.comb(n/2, a));
      }
    }
    return answer;
  }
  
  private long solveOdd(int n, long k) {
    // 1: a, 0: b, center: 1
    // 2*a*b+b
    // 1: a, 0: b, center: 0
    // 2*a*b+a
    
    // 2*a*b+a = k
    // 2*a*(L-a)+a = k
    // -2a^2+2La+a = k
    // 2a^2-(2L+1)a+k
    int[] as = solveEquation(2, -n, k);
    long answer = 0;
    for (int a : as) {
      if (0 <= a && a <= n/2) {
        answer = ModUtils.add(answer, combinationUtil.comb(n/2, a));
      }
    }
    
    // 2*a*b+b = k
    // 2*a*(L-a)+(L-a) = k
    // -2a^2+(2L-1)a+L=k
    // 2a^2-(2L-1)a+(k-L)=0
    as = solveEquation(2, -(n-2), k-n/2);
    for (int a : as) {
      if (0 <= a && a <= n/2) {
        answer = ModUtils.add(answer, combinationUtil.comb(n/2, a));
      }
    }
    
    return answer;
    
  }
  
  public long solve(int n, long k) {
    if (n % 2 == 0) {
      return solveEven(n, k);
    } else {
      return solveOdd(n, k);
    }
  }
}

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    Solver solver = new Solver();
    int q = s.nextInt();
    for (int i = 0; i < q; i++) {
      int n = s.nextInt();
      long k = s.nextLong();
      System.out.println(solver.solve(n, k));
    }
  }
}
