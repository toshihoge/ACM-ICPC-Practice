import java.util.*;

class Competitor implements Comparable<Competitor> {
  int rank;
  int age;

  Competitor(int rank, int age) {
    this.rank = rank;
    this.age = age;
  }

  public int compareTo(Competitor c) {
    return -this.age + c.age;
  }
}

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int k = s.nextInt();
    int[] x = new int[n+1];
    for (int i = 1; i <= n; i++) {
      x[i] = s.nextInt();
    }

    PriorityQueue<Competitor> queue = new PriorityQueue<Competitor>();
    for (int i = 1; i <= k; i++) {
      queue.add(new Competitor(i, x[i]));
    }
    System.out.println(queue.peek().rank);

    for (int i = k+1; i <= n; i++) {
      if (queue.peek().age > x[i]) {
        queue.poll();
        queue.add(new Competitor(i, x[i]));
      }
      System.out.println(queue.peek().rank);
    }
  }
}
