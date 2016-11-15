import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String dayOfWeek = s.next();
    if (dayOfWeek.equals("Monday")) {
      System.out.println(5);
    } else if (dayOfWeek.equals("Tuesday")) {
      System.out.println(4);
    } else if (dayOfWeek.equals("Wednesday")) {
      System.out.println(3);
    } else if (dayOfWeek.equals("Thursday")) {
      System.out.println(2);
    } else if (dayOfWeek.equals("Friday")) {
      System.out.println(1);
    } else {
      System.out.println(0);
    }
  }
}
