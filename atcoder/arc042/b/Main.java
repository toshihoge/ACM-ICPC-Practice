import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    double x = s.nextDouble();
    double y = s.nextDouble();
    int n = s.nextInt();
    double[] xs = new double[n];
    double[] ys = new double[n];
    for (int i = 0; i < n; i++) {
      xs[i] = s.nextDouble();
      ys[i] = s.nextDouble();
    }
    double answer = 1e100;
    for (int i = 0; i < n; i++) {
      double xs1 = xs[i];
      double ys1 = ys[i];
      double xs2 = xs[(i+1)%n];
      double ys2 = ys[(i+1)%n];
      double dx1 = xs1 - x;
      double dy1 = ys1 - y;
      double dx2 = xs2 - x;
      double dy2 = ys2 - y;
      double area = 0.5*Math.abs(dx1*dy2 - dx2*dy1);
      double length = Math.sqrt((xs1-xs2)*(xs1-xs2) + (ys1-ys2)*(ys1-ys2));
      double h = area / length / 0.5;
      answer = Math.min(answer, h);
    }
    System.out.println(answer);
  }
}
