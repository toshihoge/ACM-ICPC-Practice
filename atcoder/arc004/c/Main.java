import java.util.*;
import java.math.*;
 
public class Main {
  private static long gcd(long a, long b) {
    return a % b == 0 ? b : gcd(b, a%b);
  }

  private static long solve(long a, long b, long n) {
    if (n % b != 0) {
      return 0;
    }
    BigInteger biN = new BigInteger("" + n);
    BigInteger biNPlusOne = biN.add(BigInteger.ONE);
    BigInteger two = new BigInteger("2");
    BigInteger total = biN.multiply(biNPlusOne).divide(two);
    BigInteger biB = new BigInteger("" + b);
    BigInteger biA = new BigInteger("" + a);
    BigInteger subTotal = biA.multiply(biN).divide(biB);
    BigInteger m = total.subtract(subTotal);
    if (m.compareTo(BigInteger.ONE) < 0 || m.compareTo(biN) > 0) {
      return 0;
    }
    return m.longValue();
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String input = s.next();
    String[] array = input.split("/");
    long aRaw = Long.parseLong(array[0]);
    long bRaw = Long.parseLong(array[1]);
    long g = gcd(aRaw, bRaw);
    long a = aRaw / g;
    long b = bRaw / g;
    long k = 2 * a / b;
    boolean impossible = true;
    for (long n = Math.max(1, k-4); n <= k+4; n++) {
      long m = solve(a, b, n);
      if (m > 0) {
        impossible = false;
        System.out.printf("%d %d\n", n, m);
      }
    }
    if (impossible) {
      System.out.println("Impossible");
    }
  }
}
