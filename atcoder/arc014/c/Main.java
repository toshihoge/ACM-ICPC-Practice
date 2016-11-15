import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    String order = s.next();
    int r = 0;
    int g = 0;
    int b = 0;
    for (char c : order.toCharArray()) {
      switch (c) {
        case 'R':
          r++;
          break;
        case 'G':
          g++;
          break;
        case 'B':
          b++;
          break;
      }
    }
    System.out.println((r % 2) + (g % 2) + (b % 2));
  }
}
