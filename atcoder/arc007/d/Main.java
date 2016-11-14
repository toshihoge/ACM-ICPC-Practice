import java.util.*;
import java.math.*;

public class Main {
  private static boolean verify(String cs, int beginIndex, BigInteger first, BigInteger diff) {
    int index = beginIndex;
    BigInteger value = first;
    while (index < cs.length()) {
      value = value.add(diff);
      String valueString = value.toString();
      if (cs.length() - index >= valueString.length()) {
        if (!cs.startsWith(valueString, index)) {
          return false;
        }
      } else {
        if (!valueString.startsWith(cs.substring(index))) {
          return false;
        }
      }
      index += valueString.length();
    }
    return true;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String cs = s.next();
    if (cs.length() == 1) {
      if (cs.charAt(0) == '0') {
        System.out.println("10 1");
      } else {
        System.out.println(cs + " 1");
      }
      return;
    }

    int beginIndex;
    BigInteger first;
    if (cs.charAt(0) == '0') {
      beginIndex = 0;
      while (beginIndex < cs.length() && cs.charAt(beginIndex) == '0') {
        beginIndex++;
      }
      first = new BigInteger("1" + cs.substring(0, beginIndex));
    } else if (cs.charAt(1) == '0') {
      beginIndex = 1;
      while (beginIndex < cs.length() && cs.charAt(beginIndex) == '0') {
        beginIndex++;
      }
      first = new BigInteger(cs.substring(0, beginIndex));
    } else {
      beginIndex = 1;
      first = new BigInteger(cs.substring(0, 1));
    }

    if (beginIndex >= cs.length()) {
      System.out.println(first + " 1");
      return;
    }

    for (int width = 1; beginIndex + width <= cs.length(); width++) {
      BigInteger second = new BigInteger(cs.substring(beginIndex, beginIndex+width));
      if (first.compareTo(second) >= 0) {
        continue;
      }
      BigInteger diff = second.subtract(first);
      if (verify(cs, beginIndex, first, diff)) {
        System.out.print(first);
        System.out.print(" ");
        System.out.println(diff);
        return;
      }
    }

    BigInteger rest = new BigInteger(cs.substring(beginIndex));
    do {
      rest = rest.multiply(BigInteger.TEN);
    } while (first.compareTo(rest) > 0);

    if (first.compareTo(rest) == 0) {
      System.out.print(first);
      System.out.println(" 1");
    } else {
      System.out.print(first);
      System.out.print(" ");
      System.out.println(rest.subtract(first));
    }
  }
}
