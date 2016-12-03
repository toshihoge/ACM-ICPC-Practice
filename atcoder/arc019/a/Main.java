import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String input = s.next();
    input = input.replaceAll("O", "0");
    input = input.replaceAll("D", "0");
    input = input.replaceAll("I", "1");
    input = input.replaceAll("Z", "2");
    input = input.replaceAll("S", "5");
    input = input.replaceAll("B", "8");
    System.out.println(input);
  }
}
