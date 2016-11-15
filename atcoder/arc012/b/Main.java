import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    double va = s.nextDouble();
    double vb = s.nextDouble();
    double distance = s.nextDouble();
    for (int i = 0; i < n; i++) {
      distance = (distance / va) * vb;
    }
    System.out.printf("%.10f\n", distance);
  }
}
