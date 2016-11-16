import java.util.*;
import java.math.*;

class Fraction {
  // a / b
  BigInteger a;
  BigInteger b;

  Fraction(BigInteger a, BigInteger b) {
    this.a = a;
    this.b = b;
  }

  static BigInteger gcd(BigInteger a, BigInteger b) {
    // return a%b == 0 ? b : gcd(b, a%b);
    return a.mod(b).equals(BigInteger.ZERO) ? b : gcd(b, a.mod(b));
  }

  Fraction mul(Fraction f) {
    BigInteger g1 = gcd(this.a, f.b);
    BigInteger g2 = gcd(f.a, this.b);
    return new Fraction(
        this.a.divide(g1).multiply(f.a.divide(g2)),
        this.b.divide(g2).multiply(f.b.divide(g1)));
  }
}

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    String[] large = new String[n];
    String[] small = new String[n];
    int[] m = new int[n];
    HashMap<String, Integer> nameToIndex = new HashMap<String, Integer>();
    ArrayList<String> indexToName = new ArrayList<String>();
    for (int i = 0; i < n; i++) {
      large[i] = s.next();
      m[i] = s.nextInt();
      small[i] = s.next();

      if (nameToIndex.get(large[i]) == null) {
        nameToIndex.put(large[i], nameToIndex.size());
        indexToName.add(large[i]);
      }
      if (nameToIndex.get(small[i]) == null) {
        nameToIndex.put(small[i], nameToIndex.size());
        indexToName.add(small[i]);
      }
    }

    int size = nameToIndex.size();
    Fraction[][] matrix = new Fraction[size][size];
    for (int i = 0; i < n; i++) {
      int smallIndex = nameToIndex.get(small[i]);
      int largeIndex = nameToIndex.get(large[i]);
      matrix[smallIndex][largeIndex] = new Fraction(new BigInteger("" + m[i]), BigInteger.ONE);
      matrix[largeIndex][smallIndex] = new Fraction(BigInteger.ONE, new BigInteger("" + m[i]));
    }

    for (int k = 0; k < size; k++) {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (matrix[i][j] == null && matrix[i][k] != null && matrix[k][j] != null) {
            matrix[i][j] = matrix[i][k].mul(matrix[k][j]);
          }
        }
      }
    }

    int maxI = -1;
    int maxJ = -1;
    BigInteger maxA = BigInteger.ZERO;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (matrix[i][j] != null && matrix[i][j].b.equals(BigInteger.ONE) && matrix[i][j].a.compareTo(maxA) > 0) {
          maxA = matrix[i][j].a;
          maxI = i;
          maxJ = j;
        }
      }
    }
    System.out.println(
        "1" + indexToName.get(maxJ) + "=" + maxA + indexToName.get(maxI));
  }
}
