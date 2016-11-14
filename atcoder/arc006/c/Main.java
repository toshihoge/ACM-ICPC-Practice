import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    ArrayList<Integer> boxes = new ArrayList<Integer>();
    for (int i = 0; i < n; i++) {
      int weight = s.nextInt();

      int index = -1;
      int topWeight = Integer.MAX_VALUE;
      for (int j = 0; j < boxes.size(); j++) {
        if (boxes.get(j) >= weight && boxes.get(j) < topWeight) {
          index = j;
          topWeight = boxes.get(j);
        }
      }
      if (index < 0) {
        boxes.add(weight);
      } else {
        boxes.set(index, weight);
      }
    }
    System.out.println(boxes.size());
  }
}
