import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int summer1 = 0;
    int summer2 = 0;
    int summer3 = 0;
    int summerNight = 0;
    int winter2 = 0;
    int winter1 = 0;
    
    for (int i = 0; i < n; i++) {
      double maxT = s.nextDouble();
      double minT = s.nextDouble();
      if (maxT >= 35.0) {
        summer1++;
      } else if (maxT >= 30.0) {
        summer2++;
      } else if (maxT >= 25.0) {
        summer3++;
      }

      if (minT >= 25.0) {
        summerNight++;
      }

      if (maxT < 0.0) {
        winter1++;
      } else if (minT < 0.0) {
        winter2++;
      }
    }
    System.out.printf("%d %d %d %d %d %d\n", summer1, summer2, summer3, summerNight, winter2, winter1);
  }
}
