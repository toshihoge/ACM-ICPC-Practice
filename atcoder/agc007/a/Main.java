import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int h = s.nextInt();
    int w = s.nextInt();
    boolean[][] visited = new boolean[h+1][w+1];
    for (int i = 0; i < h; i++) {
      String line = s.next();
      for (int j = 0; j < w; j++) {
        visited[i][j] = line.charAt(j) == '#';
      }
    }
    
    int pi = 0;
    int pj = 0;
    while (pi != h-1 || pj != w-1) {
      visited[pi][pj] = false;
      if (visited[pi][pj+1]) {
        pj++;
      } else if (visited[pi+1][pj]) {
        pi++;
      } else {
        throw new RuntimeException("No destination");
      }
      for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
          if (i < pi || j < pj) {
            if (visited[i][j]) {
              System.out.println("Impossible");
              return;
            }
          }
        }
      }
    }
    System.out.println("Possible");
  }
}
