import java.util.*;
 
public class Main {
  private static boolean isLeapYear(int y) {
    if (y % 400 == 0) {
      return true;
    }
    if (y % 100 == 0) {
      return false;
    }
    if (y % 4 == 0) {
      return true;
    }
    return false;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int y = s.nextInt();
    System.out.println(isLeapYear(y) ? "YES" : "NO");
  }
}