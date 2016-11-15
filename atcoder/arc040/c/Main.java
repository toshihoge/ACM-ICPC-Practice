import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    boolean[][] painted = new boolean[n][n];
    for (int i = 0; i < n; i++) {
      String line = s.next();
      char[] array = line.toCharArray();
      for (int j = 0; j < n; j++) {
        painted[i][j] = array[j] == 'o';
      }
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
      for (int j = n-1; j >= 0; j--) {
        if (!painted[i][j]) {
          for (int k = 0; k <= j; k++) {
            painted[i][k] = true;
          }
          if (i+1 < n) {
            for (int k = j; k < n; k++) {
              painted[i+1][k] = true;
            }
          }
          count++;
          break;
        }
      }
    }
    System.out.println(count);
  }
}
