import java.util.*;

public class A {
  public static void main(String[] args) {
    ArrayList<Rectangle> list = new ArrayList<Rectangle>();
    for (int h = 1; h <= 150; h++) {
      for (int w = h+1; w <= 150; w++) {
        list.add(new Rectangle(h, w));
      }
    }
    Collections.sort(list);
    
    Scanner s = new Scanner(System.in);
    while (true) {
      int h = s.nextInt();
      int w = s.nextInt();
      if (h == 0) {
        break;
      }
      Rectangle r = new Rectangle(h, w);
      int index = Collections.binarySearch(list, r);
      Rectangle ans = list.get(index+1);
      System.out.printf("%d %d\n", ans.h, ans.w);
    }
  }
}

class Rectangle implements Comparable<Rectangle> {
  int d, h, w;
  
  Rectangle(int h, int w) {
    this.d = h*h + w*w;
    this.h = h;
    this.w = w;
  }
  
  public int compareTo(Rectangle r) {
    if (this.d != r.d) {
      return this.d - r.d;
    }
    return this.h - r.h;
  }
}
