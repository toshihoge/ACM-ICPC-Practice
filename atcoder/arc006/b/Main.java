import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String line = s.nextLine();
    String[] array = line.split(" ");
    int n = Integer.parseInt(array[0]);
    int l = Integer.parseInt(array[1]);
    ArrayList<Integer> swap = new ArrayList<Integer>();
    for (int i = 0; i < l; i++) {
      line = s.nextLine();
      for (int j = 1; j < line.length(); j += 2) {
        if (line.charAt(j) == '-') {
          swap.add(j / 2);
        }
      }
    }

    int[] shuffle = new int[n];
    for (int i = 0; i < n; i++) {
      shuffle[i] = i+1;
    }

    for (int swapIndex : swap) {
      int temp = shuffle[swapIndex];
      shuffle[swapIndex] = shuffle[swapIndex+1];
      shuffle[swapIndex+1] = temp;
    }

    line = s.nextLine();
    for (int i = 0; i < line.length(); i += 2) {
      if (line.charAt(i) == 'o') {
        System.out.println(shuffle[i/2]);
      }
    }
  }
}
