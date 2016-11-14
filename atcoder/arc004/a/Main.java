import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    double[] xs = new double[n];
    double[] ys = new double[n];
    for (int i = 0; i < n; i++) {
      xs[i] = s.nextDouble();
      ys[i] = s.nextDouble();
    }
    double length = 0.0;
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        double dx = xs[j] - xs[i];
        double dy = ys[j] - ys[i];
        length = Math.max(length, Math.sqrt(dx*dx + dy*dy));
      }
    }
    System.out.println(length);
  }
}
