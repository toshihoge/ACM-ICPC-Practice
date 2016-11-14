import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int a = s.nextInt();
    int b = s.nextInt();
    int diff = Math.abs(a - b);
    int[] answer = new int[]{
      0, 1, 2, 3, 2, 1, 2, 3, 3, 2,
      1, 2, 3, 4, 3, 2, 3, 4, 4, 3,
      2, 3, 4, 5, 4, 3, 4, 5, 5, 4,
      3, 4, 5, 6, 5, 4, 5, 6, 6, 5,
      4
    };
    System.out.println(answer[diff]);
  }
}
