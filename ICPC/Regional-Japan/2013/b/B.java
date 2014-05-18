import java.util.*;

public class B {
  private static int getNextMeetTime(int length, ArrayList<Ant> ants) {
    int time = Integer.MAX_VALUE;
    for (int i = 1; i < ants.size(); i++) {
      Ant left = ants.get(i-1);
      Ant right = ants.get(i);
      if (0 < left.pos && right.pos < length && left.drct > 0 && right.drct < 0) {
        time = Math.min(time, (right.pos - left.pos) / 2);
      }
    }
    return time;
  }
  
  private static void move(ArrayList<Ant> ants, int time) {
    for (Ant ant : ants) {
      ant.pos += ant.drct * time;
    }
    for (int i = 1; i < ants.size(); i++) {
      Ant left = ants.get(i-1);
      Ant right = ants.get(i);
      if (left.pos == right.pos) {
        if (left.pos % 2 == 1) {
          // Swap
          ants.set(i-1, right);
          ants.set(i, left);
        } else {
          // Turn
          left.drct = -1;
          right.drct = 1;
        }
      }
    }
  }
  
  private static Ant getLastExitLeft(int length, ArrayList<Ant> ants) {
    Ant lastAnt = null;
    for (Ant ant : ants) {
      if (0 < ant.pos && ant.pos < length && ant.drct < 0) {
        lastAnt = ant;
      }
    }
    return lastAnt;
  }
  
  private static Ant getLastExitRight(int length, ArrayList<Ant> ants) {
    Ant lastAnt = null;
    // Use reverse order to get a leftmost ant still in tunnel.
    for (int i = ants.size() - 1; i >= 0; i--) {
      Ant ant = ants.get(i);
      if (0 < ant.pos && ant.pos < length && ant.drct > 0) {
        lastAnt = ant;
      }
    }
    return lastAnt;
  }
  
  private static String solve(int length, ArrayList<Ant> ants) {
    int totalTime = 0;
    while(true) {
      int nextMeetTime = getNextMeetTime(length, ants);
      if (nextMeetTime == Integer.MAX_VALUE) {
        break;
      }
      totalTime += nextMeetTime;
      move(ants, nextMeetTime);
    }
    Ant lastLeftAnt = getLastExitLeft(length, ants);
    int leftExitTime = 0;
    if (lastLeftAnt != null) {
      leftExitTime = lastLeftAnt.pos;
    }
    Ant lastRightAnt = getLastExitRight(length, ants);
    int rightExitTime = 0;
    if (lastRightAnt != null) {
      rightExitTime = length - lastRightAnt.pos;
    }
    if (rightExitTime > leftExitTime || lastLeftAnt == null) {
      return String.format("%d %d", (totalTime + rightExitTime) / 2, lastRightAnt.id);
    }
    return String.format("%d %d", (totalTime + leftExitTime) / 2, lastLeftAnt.id);
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while(true) {
      int n = s.nextInt();
      if (n == 0) {
        break;
      }
      int length = 2*s.nextInt();
      ArrayList<Ant> ants = new ArrayList<Ant>();
      for (int i = 1; i <= n; i++) {
        String str = s.next();
        int drct = 1;
        if (str.equals("L")) {
          drct = -1;
        }
        int pos = 2*s.nextInt();
        ants.add(new Ant(i, pos, drct));
      }
      System.out.println(solve(length, ants));
    }
  }
}

class Ant {
  int id;
  int pos;
  int drct;
  
  Ant(int id, int pos, int drct) {
    this.id = id;
    this.pos = pos;
    this.drct = drct;
  }
}
