import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();

    int[] cdCases = new int[n+1];
    for (int i = 1; i <= n; i++) {
      cdCases[i] = i;
    }

    int listeningCd = 0;
    for (int i = 1; i <= m; i++) {
      int nextListeningCd = s.nextInt();
      for (int j = 1; j <= n; j++) {
        if (cdCases[j] == nextListeningCd) {
          cdCases[j] = listeningCd;
          break;
        }
      }
      listeningCd = nextListeningCd;
    }

    for (int i = 1; i <= n; i++) {
      System.out.println(cdCases[i]);
    }
  }
}
