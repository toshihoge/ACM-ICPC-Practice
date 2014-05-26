import java.util.*;

public class I {
  private static final int LOG2_MAX = 20;
  
  private static int getOdd(int v) {
    while (v % 2 == 0) {
      v /= 2;
    }
    return v;
  }
  
  private static int log2(int pow2v) {
    for (int output = 0; true; output++) {
      if ((pow2v >> output) == 1) {
        return output;
      }
    }
  }
  
  private static void getEndInfo(int begin, int endMin, int endMax, int[][] src, ArrayList<EndInfo> endInfos) {
    if (src[begin][endMin] == src[begin][endMax]) {
      return;
    }
    if (endMax - endMin > 1) {
      int endMid = (endMin + endMax) / 2;
      getEndInfo(begin, endMin, endMid, src, endInfos);
      getEndInfo(begin, endMid, endMax, src, endInfos);
    } else if (src[begin][endMax] > 0) {
      endInfos.add(new EndInfo(endMax, src[begin][endMax]));
    }
  }
  
  private static void fillNextTable(int m, int[][] src, int[][] dst) {
    ArrayList<ArrayList<EndInfo>> endInfoMatrix = new ArrayList<ArrayList<EndInfo>>();
    for (int begin = 0; begin < m; begin++) {
      ArrayList<EndInfo> endInfos = new ArrayList<EndInfo>();
      getEndInfo(begin, begin, m, src, endInfos);
      endInfoMatrix.add(endInfos);
    }
    endInfoMatrix.add(new ArrayList<EndInfo>());
    for (int begin = 0; begin < m; begin++) {
      for (EndInfo endInfo1 : endInfoMatrix.get(begin)) {
        for (EndInfo endInfo2 : endInfoMatrix.get(endInfo1.end)) {
          dst[begin][endInfo2.end] = Math.max(dst[begin][endInfo2.end], endInfo1.value + endInfo2.value);
        }
      }
    }
  }
  
  private static void expand(int m, int[][] dst) {
    for (int w = 1; w < m; w++) {
      dst[0][w+1] = Math.max(dst[0][w+1], dst[0][w]);
      for (int begin = 1; begin + w + 1 <= m; begin++) {
        dst[begin][begin+w+1] = Math.max(dst[begin][begin+w+1], dst[begin][begin+w]);
        dst[begin-1][begin+w] = Math.max(dst[begin-1][begin+w], dst[begin][begin+w]);
      }
      dst[m-w-1][m] = Math.max(dst[m-w-1][m], dst[m-w][m]);
    }
  }
  
  private static int solveSub(int m, ArrayList<ArrayList<Integer>> input) {
    int output = 0;
    
    int[][] src = null;
    for (int size = 0; size < LOG2_MAX; size++) {
      int[][] dst = new int[m+1][m+1];
      for (int index : input.get(size)) {
        dst[index][index+1] = 1;
      }
      if (size - 1 >= 0) {
        fillNextTable(m, src, dst);
      }
      expand(m, dst);
      output = Math.max(output, dst[0][m]);
      src = dst;
    }
    return output;
  }
  
  private static int solve(int n, int[] a) {
    HashSet<Integer> odds = new HashSet<Integer>();
    for (int v : a) {
      odds.add(getOdd(v));
    }
    int output = 0;
    for (int odd : odds) {
      ArrayList<ArrayList<Integer>> input = new ArrayList<ArrayList<Integer>>();
      
      for (int i = 0; i < LOG2_MAX; i++) {
        input.add(new ArrayList<Integer>());
      }
      
      int index = 0;
      for (int i = 0; i < n; i++) {
        if (getOdd(a[i]) == odd) {
          input.get(log2(a[i] / odd)).add(index++);
        }
      }
      output = Math.max(output, solveSub(index, input));
    }
    return output;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while(true) {
      int n = s.nextInt();
      if (n == 0) {
        break;
      }
      int[] a = new int[n];
      for (int i = 0; i < n; i++) {
        a[i] = s.nextInt();
      }
      System.out.println(solve(n, a));
    }
  }
}

class EndInfo {
  int end;
  int value;
  EndInfo(int end, int value) {
    this.end = end;
    this.value = value;
  }
}
