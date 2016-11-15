import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    double a = s.nextDouble();
    double b = s.nextDouble();
    double maxv = 0.0;
    double minv = 1e100;
    double total = 0.0;
    for (int i = 0; i < n; i++) {
      double v = s.nextDouble();
      maxv = Math.max(maxv, v);
      minv = Math.min(minv, v);
      total += v;
    }
 
    double diff = maxv - minv;
    if (diff == 0.0 && b > 0) {
      System.out.println(-1);
      return;
    }
    double p = b / diff;
    double average = p * total / n;
    double q = a - average;
    System.out.printf("%.20f %.20f\n", p, q);
  }
}
