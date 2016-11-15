import java.util.*;
import java.math.*;
 
class Cake implements Comparable<Cake> {
  int cost;
  int benefit;
 
  Cake(int cost, int benefit) {
    this.cost = cost;
    this.benefit = benefit;
  }
 
  public int compareTo(Cake cake) {
    return this.cost - cake.cost;
  }
}
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int p = s.nextInt();
    Cake[] cakes = new Cake[n];
    for (int i = 0; i < n; i++) {
      int cost = s.nextInt();
      int benefit = s.nextInt();
      cakes[i] = new Cake(cost, benefit);
    }
    Arrays.sort(cakes);
 
    int maxBenefit = 0;
    int[] dptable = new int[p + 101];
    for (int i = n-1; i >= 0; i--) {
      Cake cake = cakes[i];
      for (int j = p + cake.cost; j >= cake.cost; j--) {
        dptable[j] = Math.max(dptable[j], dptable[j-cake.cost]+cake.benefit);
      }
    }
    for (int i = 0; i <= p + 100; i++) {
      maxBenefit = Math.max(maxBenefit, dptable[i]);
    }
    System.out.println(maxBenefit);
  }
}
