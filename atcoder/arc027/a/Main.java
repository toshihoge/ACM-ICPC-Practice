import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int h = s.nextInt();
    int m = s.nextInt();
    int t = 60*h + m;
    System.out.println(60*18 - t);
  }
}
