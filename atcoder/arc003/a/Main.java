import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    char[] scores = s.next().toCharArray();
    double sum = 0.0;
    for (char score : scores) {
      if (score == 'F') {
        continue;
      }
      sum += 4 - score + 'A';
    }
    System.out.println(sum / n);
  }
}
