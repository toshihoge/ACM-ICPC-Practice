import java.util.*;

class Node implements Comparable<Node> {
  String previous;
  String word;
  int cost;

  Node(String word, String previous, int cost) {
    this.word = word;
    this.previous = previous;
    this.cost = cost;
  }

  public int compareTo(Node node) {
    return this.cost - node.cost;
  }
}

public class Main {
  private static boolean connected(String w1, String w2) {
    int count = 0;
    for (int i = 0; i < w1.length(); i++) {
      if (w1.charAt(i) != w2.charAt(i)) {
        count++;
      }
    }
    return count == 1;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String first = s.next();
    String last = s.next();
    if (first.equals(last)) {
      System.out.println(0);
      System.out.println(first);
      System.out.println(last);
      return;
    }
    int n = s.nextInt();
    String[] words = new String[n+1];
    for (int i = 0; i < n; i++) {
      words[i] = s.next();
    }
    words[n] = last;

    PriorityQueue<Node> queue = new PriorityQueue<Node>();
    queue.add(new Node(first, "", 0));
    HashMap<String, String> previousMap = new HashMap<String, String>();
    while(!queue.isEmpty()) {
      Node node = queue.poll();
      if (previousMap.get(node.word) != null) {
        continue;
      }
      previousMap.put(node.word, node.previous);
      if (node.word.equals(last)) {
        String w = last;
        ArrayList<String> log = new ArrayList<String>();
        while (!w.equals("")) {
          log.add(w);
          w = previousMap.get(w);
        }
        System.out.println(log.size() - 2);
        for (int i = log.size() - 1; i >= 0; i--) {
          System.out.println(log.get(i));
        }
        return;
      }
      for (String next : words) {
        if (connected(node.word, next) && previousMap.get(next) == null) {
          queue.add(new Node(next, node.word, node.cost+1));
        }
      }
    }
    System.out.println(-1);
  }
}
