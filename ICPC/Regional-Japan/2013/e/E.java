import java.util.*;

public class E {
  private static int solve(int ch, int cv, int[] src, int[] dst) {
    Node.setCostConstant(ch, cv);
    Board srcBoard = new Board(src);
    Board dstBoard = new Board(dst);
    
    PriorityQueue<Node> queue = new PriorityQueue<Node>();
    queue.add(new Node(0, srcBoard));
    
    HashSet<Board> hs = new HashSet<Board>();
    while (!queue.isEmpty()) {
      Node node = queue.poll();
      if (hs.contains(node.board)) {
        continue;
      }
      hs.add(node.board);
      if (dstBoard.equals(node.board)) {
        return node.cost;
      }
      for (Node nextNode : node.getNextMoves()) {
        queue.add(nextNode);
      }
    }
    throw new RuntimeException();
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int ch = s.nextInt();
      int cv = s.nextInt();
      if (ch == 0) {
        break;
      }
      int[] src = new int[9];
      int[] dst = new int[9];
      for (int i = 0; i < 9; i++) {
        src[i] = s.nextInt();
      }
      for (int i = 0; i < 9; i++) {
        dst[i] = s.nextInt();
      }
      System.out.println(solve(ch, cv, src, dst));
    }
  }
}

class Board {
  int[] body;
  
  Board(int[] body) {
    this.body = body;
  }
  
  public boolean equals(Object obj) {
    if (!(obj instanceof Board)) {
      return false;
    }
    Board board = (Board)obj;
    for (int i = 0; i < 9; i++) {
      if (this.body[i] != board.body[i]) {
        return false;
      }
    }
    return true;
  }
  
  public int hashCode() {
    int output = 0;
    for (int v : body) {
      output *= 9;
      output += v;
    }
    return output;
  }
  
  private int findZeroIndex() {
    for (int i = 0; i < 9; i++) {
      if (body[i] == 0) {
        return i;
      }
    }
    throw new RuntimeException();
  }
  
  private static void swapZero(int[] body, int zeroIndex, int diff) {
    int dstIndex = (zeroIndex + diff + 9) % 9;
    body[zeroIndex] = body[dstIndex];
    body[dstIndex] = 0;
  }
  
  public Board[] getMoves(int d) {
    int zeroIndex = findZeroIndex();
    int[] body1 = (int[])body.clone();
    swapZero(body1, zeroIndex, d);
    int[] body2 = (int[])body.clone();
    swapZero(body2, zeroIndex, -d);
    return new Board[]{new Board(body1), new Board(body2)};
  }
}

class Node implements Comparable<Node> {
  static int ch;
  static int cv;
  
  int cost;
  Board board;
  
  Node (int cost, Board board) {
    this.cost = cost;
    this.board = board;
  }
  
  public int compareTo(Node node) {
    return this.cost - node.cost;
  }
  
  public Node[] getNextMoves() {
    Board[] verticals = board.getMoves(3);
    Board[] horizontals = board.getMoves(1);
    return new Node[]{
      new Node(cost + cv, verticals[0]),
      new Node(cost + cv, verticals[1]),
      new Node(cost + ch, horizontals[0]),
      new Node(cost + ch, horizontals[1]),
    };
  }
  
  public static void setCostConstant(int ch, int cv) {
    Node.ch = ch;
    Node.cv = cv;
  }
}
