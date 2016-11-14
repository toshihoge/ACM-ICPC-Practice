import java.util.*;

public class Main {
  private static int convert(int x) {
    if (x < 1) {
      return 2 - x;
    }
    if (x > 9) {
      return 18 - x;
    }
    return x;
  }

  private static char get(char[][] map, int y, int x) {
//    System.out.printf("\n%d %d %d %d\n", y, x, convert(y), convert(x));
    return map[convert(y)][convert(x)];
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int x = s.nextInt();
    int y = s.nextInt();
    String direction = s.next();
    char[][] map = new char[10][10];
    for (int i = 1; i <= 9; i++) {
      String line = s.next();
      for (int j = 1; j <= 9; j++) {
        map[i][j] = line.charAt(j-1);
      }
    }
    int dx;
    if (direction.contains("R")) {
      dx = 1;
    } else if (direction.contains("L")) {
      dx = -1;
    } else {
      dx = 0;
    }

    int dy;
    if (direction.contains("D")) {
      dy = 1;
    } else if (direction.contains("U")) {
      dy = -1;
    } else {
      dy = 0;
    }

    for (int i = 0; i < 4; i++) {
      System.out.print(get(map, y+i*dy, x+i*dx));
    }
    System.out.println();
  }
}
