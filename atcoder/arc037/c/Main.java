import java.util.*;
import java.math.*;
 
class BFinder {
  long[] b;
  BFinder(long[] b) {
    this.b = new long[b.length];
    for (int i = 0; i < b.length; i++) {
      this.b[i] = 2*b[i];
    }
    Arrays.sort(this.b);
  }
 
  public int getBCount(long target) {
    int index = Arrays.binarySearch(b, 2*target+1);
    if (index >= 0) {
      throw new RuntimeException("Unexpected binarySearch result.");
    }
    int count = -(index + 1);
    return count;
  }
}
 
public class Main {
  private static long getCount(long[] a, BFinder bFinder, long target) {
    long sum = 0;
    for (long av : a) {
      sum += bFinder.getBCount(target / av);
    }
    return sum;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    long k = s.nextLong();
    long[] a = new long[n];
    long[] b = new long[n];
    for (int i = 0; i < n; i++) {
      a[i] = s.nextLong();
    }
    for (int i = 0; i < n; i++) {
      b[i] = s.nextLong();
    }
    BFinder bFinder = new BFinder(b);
 
    long vMin = 0;
    long vMax = 1L<<62;
    while(vMax - vMin > 1) {
      long vMid = (vMax + vMin) / 2;
      long vMidCount = getCount(a, bFinder, vMid);
 
      if (vMidCount < k) {
        vMin = vMid;
      } else {
        vMax = vMid;
      }
    }
    System.out.println(vMax);
  }
}
