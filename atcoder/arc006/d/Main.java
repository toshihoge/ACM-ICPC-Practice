import java.util.*;

public class Main {
  private static int gcd(int a, int b) {
    return a%b == 0 ? b : gcd(b, a%b);
  }

  private static void fillDetected(boolean[][] detected, int i, int j, int w) {
    for (int a = 0; a < w; a++) {
      for (int b = 0; b < w; b++) {
        detected[i+a][j+b] = true;
      }
    }
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int h = s.nextInt();
    int w = s.nextInt();
    boolean[][] black = new boolean[h][w];
    for (int i = 0; i < h; i++) {
      String line = s.next();
      for (int j = 0; j < w; j++) {
        black[i][j] = line.charAt(j) == 'o';
      }
    }

    int[][] runLengthHorizontal = new int[h][w];
    for (int i = 0; i < h; i++) {
      int j = 0;
      while (j < w) {
        if (black[i][j]) {
          int k = j;
          while (black[i][k]) {
            k++;
          }
          runLengthHorizontal[i][j] = k - j;
          j = k;
        } else {
          j++;
        }
      }
    }

    int[][] runLengthVertical = new int[h][w];
    for (int j = 0; j < w; j++) {
      int i = 0;
      while (i < h) {
        if (black[i][j]) {
          int k = i;
          while (black[k][j]) {
            k++;
          }
          runLengthVertical[i][j] = k - i;
          i = k;
        } else {
          i++;
        }
      }
    }
/*
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        System.out.printf("%2d", runLengthVertical[i][j]);
      }
      System.out.println();
    }
*/
    int a = 0;
    int b = 0;
    int c = 0;
    boolean[][] detected = new boolean[h][w];
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (detected[i][j]) {
          continue;
        }
        if (runLengthHorizontal[i][j] > 0) {
          int g = gcd(runLengthHorizontal[i][j],
              runLengthVertical[i][j]);
          int width = runLengthHorizontal[i][j] / g;
          int height = runLengthVertical[i][j] / g;
//          System.out.printf("%d %d %d %d %d\n", i, j, g, width, height);

          if (width == 1 && height == 1) {
            // a:0, b:270, c:270
            int height2 = runLengthVertical[i+g][j-g] / g;
//            System.out.printf("%d %d %d\n", i+g, j-g, height2);
            if (height2 == 1) {
              // a:0
              a++;
              fillDetected(detected, i-g, j-3*g, 7*g);
            } else if (height2 == 4) {
              // b:270
              b++;
              fillDetected(detected, i-g, j-2*g, 7*g);
            } else if (height2 == 3) {
              // c:270
              c++;
              fillDetected(detected, i-g, j-2*g, 7*g);
            } else {
              System.out.println(height2);
              throw new RuntimeException("Unknown");
            }
          } else if (width == 1 && height == 3) {
            // a:180
            a++;
            fillDetected(detected, i-g, j-g, 7*g);
          } else if (width == 3 && height == 1) {
            // a:90, a:270, c:0, c:90, c:180
            int height2 = runLengthVertical[i][j+g] / g;
            int height3 = runLengthVertical[i+g][j-g] / g;
            if (height2 == 5 && height3 == 0) {
              // a:90
              a++;
              fillDetected(detected, i-g, j-g, 7*g);
            } else if (height2 == 5 && height3 == 1) {
              // a:270
              a++;
              fillDetected(detected, i-g, j-3*g, 7*g);
            } else if (height2 == 1) {
              // c:0, c:90, c:180
              c++;
              fillDetected(detected, i-g, j-2*g, 7*g);
            } else {
              throw new RuntimeException("Unknown");
            }
          } else if (width == 4 && height == 5) {
            // b:0
            b++;
            fillDetected(detected, i-g, j-g, 7*g);
          } else if (width == 5 && height == 4) {
            // b:90
            b++;
            fillDetected(detected, i-g, j-g, 7*g);
          } else if (width == 4 && height == 1) {
            // b:180
            b++;
            fillDetected(detected, i-g, j-2*g, 7*g);
          } else {
            throw new RuntimeException("Unknown");
          }
        }
      }
    }
    System.out.printf("%d %d %d\n", a, b, c);
  }
}
