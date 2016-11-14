import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String str = s.next();
    String[] array = str.split("/");
    int year = Integer.parseInt(array[0]);
    int month = Integer.parseInt(array[1]);
    int date = Integer.parseInt(array[2]);
    Calendar calendar = Calendar.getInstance();
    calendar.set(year, month - 1, date);
    while (true) {
      year = calendar.get(Calendar.YEAR);
      month = calendar.get(Calendar.MONTH) + 1;
      date = calendar.get(Calendar.DATE);
      if (year % (month * date) == 0) {
        System.out.printf("%04d/%02d/%02d\n", year, month, date);
        return;
      }
      calendar.add(Calendar.DATE, 1);
    }
  }
}
