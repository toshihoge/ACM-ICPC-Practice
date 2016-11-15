import java.util.*;

public class Main {
  private static String convert(String word) {
    word = word.toLowerCase();
    word = word.replaceAll("[bc]", "1");
    word = word.replaceAll("[dw]", "2");
    word = word.replaceAll("[tj]", "3");
    word = word.replaceAll("[fq]", "4");
    word = word.replaceAll("[lv]", "5");
    word = word.replaceAll("[sx]", "6");
    word = word.replaceAll("[pm]", "7");
    word = word.replaceAll("[hk]", "8");
    word = word.replaceAll("[ng]", "9");
    word = word.replaceAll("[zr]", "0");
    word = word.replaceAll("[aeiouy,\\.]", "");
    return word;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    ArrayList<String> numbers = new ArrayList<String>();
    for (int i = 0; i < n; i++) {
      String number = convert(s.next());
      if (!number.equals("")) {
        numbers.add(number);
      }
    }
    if (numbers.size() > 0) {
      System.out.print(numbers.get(0));
      for (int i = 1; i < numbers.size(); i++) {
        System.out.print(" ");
        System.out.print(numbers.get(i));
      }
    }
    System.out.println();
  }
}
