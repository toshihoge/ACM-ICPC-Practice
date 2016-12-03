import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    double h = s.nextDouble();
    double bmi = s.nextDouble();
    System.out.println(bmi * h * h / 10000.0);
  }
}
