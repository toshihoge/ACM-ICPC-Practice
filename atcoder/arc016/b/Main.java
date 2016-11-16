import java.util.*;
import java.math.*;
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    char[] previous = new char[9];
    int count = 0;
    for (int i = 0; i < n; i++) {
      char[] current = s.next().toCharArray();
      for (int j = 0; j < 9; j++) {
        if (current[j] == 'x') {
          count++;
        }
        if (current[j] == 'o' && previous[j] != 'o') {
          count++;
        }
      }
      previous = current;
    }
    System.out.println(count);
  }
}
