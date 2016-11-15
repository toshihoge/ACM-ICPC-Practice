import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    double maxScore = 0.0;
    for (int i = 0; i < n; i++) {
      double score = 0.0;
      score += s.nextDouble();
      score += s.nextDouble();
      score += s.nextDouble();
      score += s.nextDouble();
      score += 110.0 / 900.0 * s.nextDouble();
      maxScore = Math.max(maxScore, score);
    }
    System.out.println(maxScore);
  }
}
