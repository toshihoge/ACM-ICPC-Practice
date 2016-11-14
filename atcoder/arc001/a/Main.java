import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    String c = s.next();
    int[] counter = new int[5];
    for (int i = 0; i < n; i++) {
      counter[c.charAt(i) - '0']++;
    }
    int min = counter[1];
    int max = counter[1];
    for (int i = 2; i <= 4; i++) {
      min = Math.min(min, counter[i]);
      max = Math.max(max, counter[i]);
    }
    System.out.printf("%d %d\n", max, min);
  }
}