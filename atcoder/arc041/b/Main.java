import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    int[][] b = new int[n][m];
    for (int i = 0; i < n; i++) {
      String line = s.next();
      for (int j = 0; j < m; j++) {
        b[i][j] = line.charAt(j) - '0';
      }
    }
    int[][] a = new int[n][m];
    for (int i = 0; i < n-2; i++) {
      for (int j = 1; j < m-1; j++) {
        if (b[i][j] > 0) {
          a[i+1][j] = b[i][j];
          b[i][j] -= a[i+1][j];
          b[i+1][j-1] -= a[i+1][j];
          b[i+1][j+1] -= a[i+1][j];
          b[i+2][j] -= a[i+1][j];
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        System.out.print(a[i][j]);
      }
      System.out.println();
    }
  }
}
