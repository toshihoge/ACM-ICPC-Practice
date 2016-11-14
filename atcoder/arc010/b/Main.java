import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int[] holidays = new int[367];
    {
      Calendar calendar = Calendar.getInstance();
      calendar.set(2012, 0, 1);
      while (calendar.get(Calendar.YEAR) == 2012) {
        if (calendar.get(Calendar.DAY_OF_WEEK) == Calendar.SATURDAY ||
            calendar.get(Calendar.DAY_OF_WEEK) == Calendar.SUNDAY) {
          holidays[calendar.get(Calendar.DAY_OF_YEAR)]++;
        }
        calendar.add(Calendar.DATE, 1);
      }
    }
    for (int i = 0; i < n; i++) {
      String line = s.next();
      String[] array = line.split("/");
      int month = Integer.parseInt(array[0]) - 1;
      int date = Integer.parseInt(array[1]);
      Calendar calendar = Calendar.getInstance();
      calendar.set(2012, month, date);
      holidays[calendar.get(Calendar.DAY_OF_YEAR)]++;
    }
    for (int i = 1; i <= 365; i++) {
      if (holidays[i] > 1) {
        holidays[i+1] += holidays[i] - 1;
        holidays[i] = 1;
      }
    }
    int longest = 0;
    for (int i = 1; i <= 366; i++) {
      int j = i;
      while (j <= 366 && holidays[j] > 0) {
        longest = Math.max(longest, j - i + 1);
        j++;
      }
    }
    System.out.println(longest);
  }
}
