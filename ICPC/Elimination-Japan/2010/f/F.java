import java.util.*;

class Node {
  ProblemInfo problemInfo;
  String documentCandidate;
  ArrayList<Node> children;
  int depth;
  
  Node(ProblemInfo problemInfo, String documentCandidate, int depth) {
    this.problemInfo = problemInfo;
    this.documentCandidate = documentCandidate;
    this.depth = depth;
    children = null;
  }
  
  public String getCandidate() {
    return documentCandidate;
  }
  
  private static String reverseString(String str) {
    return new StringBuffer(str).reverse().toString();
  }
  
  public String getReverseCandidate() {
    return reverseString(documentCandidate);
  }
  
  public int length() {
    return documentCandidate.length();
  }
  
  public int getDepth() {
    return depth;
  }
  
  public ArrayList<Node> getChildren() {
    if (children == null) {
      children = new ArrayList<Node>();
      for (String piece: problemInfo.getPieces()) {
        for (String merged: Utils.mergeString(documentCandidate, piece, depth*problemInfo.pieceLength()+1, Integer.MAX_VALUE)) {
          if (!problemInfo.containsCandidate(merged) && isLcsUnderX(merged, problemInfo.getDocument(), problemInfo.getD())) {
            problemInfo.addCandidate(merged);
            children.add(new Node(problemInfo, merged, depth+1));
          }
        }
      }
    }
    return children;
  }
  
  private static boolean isLcsUnderX(String candidates, String document, int limit) {
    int[][] table = new int[candidates.length()+1][2*limit+1];
    
    for (int i = -limit; i <= limit; i++) {
      table[0][limit+i] = Math.abs(i);
    }
    
    int minCost = 100;
    for (int i = 0; i < candidates.length(); i++) {
      int matchCost;
      
      matchCost = candidates.charAt(i) != Utils.myCharAt(document, i-limit) ? 1 : 0;
      table[i+1][0] = Math.min(table[i][0]+matchCost, table[i][1]+1);
      minCost = table[i+1][0];
      
      for (int j = -limit+1; j <= limit-1; j++) {
        matchCost = candidates.charAt(i) != Utils.myCharAt(document, i+j) ? 1 : 0;
        table[i+1][limit+j] = Math.min(table[i][limit+j]+matchCost, Math.min(table[i][limit+j+1]+1, table[i+1][limit+j-1]+1));
        minCost = Math.min(table[i+1][limit+j], minCost);
      }
      
      matchCost = candidates.charAt(i) != Utils.myCharAt(document, i+limit) ? 1 : 0;
      table[i+1][2*limit] = Math.min(table[i][2*limit]+matchCost, table[i+1][2*limit-1]+1);
      minCost = Math.min(table[i+1][2*limit], minCost);
      
      if (minCost > limit) {
        return false;
      }
    }
    return minCost <= limit;
  }
}

class ProblemInfo {
  String document;
  String[] pieces;
  int d;
  HashSet<String> candidates;
  
  ProblemInfo(String document, String[] pieces, int d) {
    this.document = document;
    this.pieces = pieces;
    this.d = d;
    candidates = new HashSet<String>();
  }
  
  private static String reverseString(String str) {
    return new StringBuffer(str).reverse().toString();
  }
  
  private String[] reversePieces() {
    String[] output = new String[pieces.length];
    for (int i = 0; i < pieces.length; i++) {
      output[i] = reverseString(pieces[i]);
    }
    return output;
  }
  
  public String[] getPieces() {
    return pieces;
  }
  
  public ProblemInfo makeReverseProblemInfo() {
    return new ProblemInfo(reverseString(document), reversePieces(), d);
  }
  
  public String getDocument() {
    return document;
  }
  
  public int getD() {
    return d;
  }
  
  public int pieceLength() {
    return pieces[0].length();
  }
  
  public boolean containsCandidate(String candidate) {
    return candidates.contains(candidate);
  }
  
  public void addCandidate(String candidate) {
    candidates.add(candidate);
  }
}

class Utils {
  public static char myCharAt(String s, int index) {
    return index < 0 || s.length() <= index ? '-' : s.charAt(index);
  }
  
  public static ArrayList<String> mergeString(String head, String tail, int minLength, int maxLength) {
    int minMergedLength = Math.max(head.length(), tail.length());
    int minTargetLength = Math.max(minLength, minMergedLength);
    int maxMergedLength = head.length() + tail.length();
    int maxTargetLength = Math.min(maxMergedLength, maxLength);
    int minCommonLength = maxMergedLength - maxTargetLength;
    int maxCommonLength = maxMergedLength - minTargetLength;
    
    ArrayList<String> output = new ArrayList<String>();
    for (int commonLength = minCommonLength; commonLength <= maxCommonLength; commonLength++) {
      if (head.endsWith(tail.substring(0, commonLength))) {
        output.add(head + tail.substring(commonLength));
      }
    }
    return output;
  }
}

public class F {
  private static boolean isLcsUnderX(String candidate, String document, int limit) {
    if (Math.abs(candidate.length() - document.length()) > limit) {
      return false;
    }
    
    int[][] table = new int[candidate.length()+1][2*limit+1];
    for (int i = -limit; i <= limit; i++) {
      table[0][limit+i] = Math.abs(i);
    }

    int minCost = 100;
    for (int i = 0; i < candidate.length(); i++) {
      int matchCost;
      
      matchCost = candidate.charAt(i) != Utils.myCharAt(document, i-limit) ? 1 : 0;
      table[i+1][0] = Math.min(table[i][0]+matchCost, table[i][1]+1);
      minCost = table[i+1][0];
      
      for (int j = -limit+1; j <= limit-1; j++) {
        matchCost = candidate.charAt(i) != Utils.myCharAt(document, i+j) ? 1 : 0;
        table[i+1][limit+j] = Math.min(table[i][limit+j]+matchCost, Math.min(table[i][limit+j+1]+1, table[i+1][limit+j-1]+1));
        minCost = Math.min(table[i+1][limit+j], minCost);
      }
      
      matchCost = candidate.charAt(i) != Utils.myCharAt(document, i+limit) ? 1 : 0;
      table[i+1][2*limit] = Math.min(table[i][2*limit]+matchCost, table[i+1][2*limit-1]+1);
      minCost = Math.min(table[i+1][2*limit], minCost);
      
      if (minCost > limit) {
        return false;
      }
    }
    return table[candidate.length()][limit+document.length()-candidate.length()] <= limit;
  }
  
  private static void calculateDocumentCandidates(ProblemInfo problemInfo, Node forward, Node backward, HashSet<String> candidates) {
    if (forward.length() + backward.length() >= problemInfo.getDocument().length()-2) {
      ArrayList<String> mergedList = Utils.mergeString(forward.getCandidate(), backward.getReverseCandidate(), problemInfo.getDocument().length()-2, problemInfo.getDocument().length()+2);
      for (String merged: mergedList) {
        if (!candidates.contains(merged) && isLcsUnderX(merged, problemInfo.getDocument(), problemInfo.getD())) {
          candidates.add(merged);
        }
      }
      if (forward.length() + backward.length() >= problemInfo.getDocument().length()+2) {
        return;
      }
    }
    
    if (forward.getDepth() == backward.getDepth()) {
      for (Node child: forward.getChildren()) {
        calculateDocumentCandidates(problemInfo, child, backward, candidates);
      }
    } else {
      for (Node child: backward.getChildren()) {
        calculateDocumentCandidates(problemInfo, forward, child, candidates);
      }
    }
  }
  
  private static void printAnswers(HashSet<String> answerSet) {
    System.out.print(answerSet.size() + "\n");
    if (answerSet.size() <= 5) {
      String[] array = new String[answerSet.size()];
      array = answerSet.toArray(array);
      Arrays.sort(array);
      for (String str: array) {
        System.out.print(str + "\n");
      }
    }
  }
  
  private static void solve(ProblemInfo forwardInfo) {
    HashSet<String> answerSet = new HashSet<String>();
    calculateDocumentCandidates(forwardInfo, new Node(forwardInfo, "", 0), new Node(forwardInfo.makeReverseProblemInfo(), "", 0), answerSet);
    printAnswers(answerSet);
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      
      int d = s.nextInt();
      int n = s.nextInt();
      if (d == 0) {
        break;
      }
      String document = s.next();
      String[] pieces = new String[n];
      for (int i = 0; i < n; i++) {
        pieces[i] = s.next();
      }
      solve(new ProblemInfo(document, pieces, d));
    }
  }
}
