import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int[] cards = new int[n];
    for (int i = 0; i < n; i++) {
      cards[i] = s.nextInt();
    }
    Arrays.sort(cards);
    int sum = 0;
    for (int i = n-1; i >= 0; i-=2) {
      sum += cards[i];
    }
    System.out.println(sum);
  }
}
