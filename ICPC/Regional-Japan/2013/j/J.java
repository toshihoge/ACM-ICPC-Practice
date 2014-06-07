import java.util.*;

class ParserPosition<T> {
  T t;
  int index;
  
  ParserPosition(T t, int index) {
    this.t = t;
    this.index = index;
  }
}

class Parser {
  private char[] text;
  
  Parser(char[] text) {
    this.text = text;
  }
  
  public Pattern parse() {
    ParserPosition<Pattern> parserPosition = parsePattern(1);
    return parserPosition.t;
  }
  
  private ParserPosition<Pattern> parsePattern(int index) {
    ArrayList<Simple> simples = new ArrayList<Simple>();
    while(true) {
      ParserPosition<Simple> simple = parseSimple(index);
      simples.add(simple.t);
      index = simple.index;
      switch (text[index]) {
        case ')':
        case '$':
          return new ParserPosition<Pattern>(new Pattern(simples), index);
        case '|':
          index++;
          break;
        default:  // . or A-Z or ( or *
          throw new RuntimeException("Unexpected char: " + index);
      }
    }
  }
  
  private ParserPosition<Simple> parseSimple(int index) {
    ArrayList<Basic> basics = new ArrayList<Basic>();
    while (true) {
      ParserPosition<Basic> basic = parseBasic(index);
      basics.add(basic.t);
      index = basic.index;
      switch (text[index]) {
        case ')':
        case '|':
        case '$':
          return new ParserPosition<Simple>(new Simple(basics), index);
        case '*':
          throw new RuntimeException("Unexpected char: " + index);
        default:  // . or A-Z or (
          // do nothing in this loop and parseBasic again in next loop.
          break;
      }
    }
  }
  
  private ParserPosition<Basic> parseBasic(int index) {
    ParserPosition<Elementary> elementary = parseElementary(index);
    if (text[elementary.index] == '*') {
      return new ParserPosition<Basic>(
          new Basic(elementary.t, true),
          elementary.index + 1);
    } else {
      return new ParserPosition<Basic>(
          new Basic(elementary.t, false),
          elementary.index);
    }
  }
  
  private ParserPosition<Elementary> parseElementary(int index) {
    if (text[index] == '(') {
      ParserPosition<Pattern> pattern = parsePattern(index+1);
      if (text[pattern.index] != ')') {
        throw new RuntimeException("Unexpected char: " + pattern.index);
      }
      return new ParserPosition<Elementary>(
          new Elementary(pattern.t, '-'),
          pattern.index+1);
    } else {
      return new ParserPosition<Elementary>(
          new Elementary(null, text[index]),
          index+1);
    }
  }
}

class Pattern {
  ArrayList<Simple> simples;
  
  Pattern(ArrayList<Simple> simples) {
    this.simples = simples;
  }
  
  public NfaNode createNfa(NfaNode parent) {
    NfaNode patternLast = new NfaNode();
    for (Simple simple : simples) {
      NfaNode simpleLast = simple.createNfa(parent);
      simpleLast.addNode(NfaNode.EPSILON, patternLast);
    }
    return patternLast;
  }
}

class Simple {
  ArrayList<Basic> basics;
  
  Simple(ArrayList<Basic> basics) {
    this.basics = basics;
  }
  
  public NfaNode createNfa(NfaNode parent) {
    for (Basic basic : basics) {
      parent = basic.createNfa(parent);
    }
    return parent;
  }
}

class Basic {
  Elementary elementary;
  boolean hasAsterisc;
  
  Basic(Elementary elementary, boolean hasAsterisc) {
    this.elementary = elementary;
    this.hasAsterisc = hasAsterisc;
  }
  
  public NfaNode createNfa(NfaNode parent) {
    if (hasAsterisc) {
      NfaNode dummyParent = new NfaNode();
      parent.addNode(NfaNode.EPSILON, dummyParent);
      NfaNode elementaryLast = elementary.createNfa(dummyParent);
      elementaryLast.addNode(NfaNode.EPSILON, dummyParent);
      return dummyParent;
    } else {
      return elementary.createNfa(parent);
    }
  }
}

class Elementary {
  Pattern pattern;
  char c;
  
  Elementary(Pattern pattern, char c) {
    this.pattern = pattern;
    this.c = c;
  }
  
  public NfaNode createNfa(NfaNode parent) {
    if (pattern != null) {
      return pattern.createNfa(parent);
    } else {
      NfaNode next = new NfaNode();
      parent.addNode(c, next);
      return next;
    }
  }
}

class NfaNode {
  public static final char EPSILON = '-';
  public static final char DOT = '.';
  
  ArrayList<Character> nextLabels;
  ArrayList<NfaNode> nextNodes;
  HashMap<Character, HashSet<NfaNode> > dfaEdges;
  
  NfaNode() {
    nextLabels = new ArrayList<Character>();
    nextNodes = new ArrayList<NfaNode>();
    dfaEdges = new HashMap<Character, HashSet<NfaNode>>();
  }
  
  public void addNode(char label, NfaNode next) {
    nextLabels.add(label);
    nextNodes.add(next);
  }
  
  private void dfsEpsilonMove(HashSet<NfaNode> visited) {
    if (visited.contains(this)) {
      return;
    }
    visited.add(this);
    for (int i = 0; i < nextLabels.size(); i++) {
      if (nextLabels.get(i) == EPSILON) {
        nextNodes.get(i).dfsEpsilonMove(visited);
      }
    }
  }
  
  private boolean allEpsilonMoves() {
    for (char c : nextLabels) {
      if (c != EPSILON) {
        return false;
      }
    }
    return true;
  }
  
  public HashSet<NfaNode> getReachableNodesByEpsilonMoves(NfaNode end) {
    HashSet<NfaNode> nodes = dfaEdges.get(EPSILON);
    if (nodes != null) {
      return nodes;
    }
    nodes = new HashSet<NfaNode>();
    dfsEpsilonMove(nodes);
    for (Iterator<NfaNode> it = nodes.iterator(); it.hasNext();) {
      NfaNode node = it.next();
      if (node != end && node.allEpsilonMoves()) {
        it.remove();
      }
    }
    dfaEdges.put(EPSILON, nodes);
    return nodes;
  }
  
  public HashSet<NfaNode> getDfaEdge(char label, NfaNode end) {
    HashSet<NfaNode> nodes = dfaEdges.get(label);
    if (nodes != null) {
      return nodes;
    }
    nodes = new HashSet<NfaNode>();
    for (int i = 0; i < nextLabels.size(); i++) {
      if (nextLabels.get(i) == label || nextLabels.get(i) == DOT) {
        nodes.addAll(nextNodes.get(i).getReachableNodesByEpsilonMoves(end));
      }
    }
    dfaEdges.put(label, nodes);
    return nodes;
  }
}

class DfaNode {
  HashSet<NfaNode> state;
  HashMap<Character, DfaNode> edges;
  
  DfaNode(HashSet<NfaNode> state) {
    this.state = state;
    this.edges = new HashMap<Character, DfaNode>();
  }
  
  public static DfaNode createDfa(NfaNode begin, NfaNode end, int depth) {
    HashSet<NfaNode> initNodes = begin.getReachableNodesByEpsilonMoves(end);
    initNodes.remove(end);
    DfaNode initDfaNode = new DfaNode(initNodes);
    
    ArrayList<DfaNode> before = new ArrayList<DfaNode>();
    before.add(initDfaNode);
    for (int i = 0; i < depth-1; i++) {
      ArrayList<DfaNode> after = new ArrayList<DfaNode>();
      for (DfaNode dfaNode : before) {
        for (char label = 'A'; label <= 'Z'; label++) {
          HashSet<NfaNode> nextState = new HashSet<NfaNode>();
          for (NfaNode nfaNode : dfaNode.state) {
            nextState.addAll(nfaNode.getDfaEdge(label, end));
          }
          nextState.remove(end);
          if (nextState.size() == 0) {
            continue;
          }
          
          DfaNode nextDfaNode = new DfaNode(nextState);
          int index = after.indexOf(nextDfaNode);
          if (index < 0) {
            after.add(nextDfaNode);
            dfaNode.edges.put(label, nextDfaNode);
          } else {
            dfaNode.edges.put(label, after.get(index));
          }
        }
      }
      before = after;
    }
    
    // For last move, only consider accept node.
    HashSet<NfaNode> endSet = new HashSet<NfaNode>();
    endSet.add(end);
    DfaNode endNode = new DfaNode(endSet);
    for (DfaNode dfaNode : before) {
      for (char label = 'A'; label <= 'Z'; label++) {
        for (NfaNode nfaNode : dfaNode.state) {
          if(nfaNode.getDfaEdge(label, end).contains(end)) {
            dfaNode.edges.put(label, endNode);
            break;
          }
        }
      }
    }
    initDfaNode.removeUnreachableEdges(endNode, new HashSet<DfaNode>());
    return initDfaNode;
  }
  
  private boolean shouldBeRemoved(DfaNode accept) {
    return this != accept && this.edges.size() == 0;
  }
  
  private void removeUnreachableEdges(DfaNode accept, HashSet<DfaNode> visited) {
    if (visited.contains(this)) {
      return;
    }
    visited.add(this);
    
    for (char label = 'A'; label <= 'Z'; label++) {
      DfaNode child = edges.get(label);
      if (child == null) {
        continue;
      }
      child.removeUnreachableEdges(accept, visited);
      if (child.shouldBeRemoved(accept)) {
        edges.remove(label);
      }
    }
  }
  
  public DfaNode proceed(char c) {
    return edges.get(c);
  }
  
  public boolean equals(Object object) {
    if (object instanceof DfaNode) {
      DfaNode dfaNode = (DfaNode) object;
      return this.state.equals(dfaNode.state);
    }
    return false;
  }
}


class DfsState {
  int i;
  int j;
  boolean reachGoal;
  char[][] solution;
  DfaNode[] ps;
  DfaNode[] qs;
  DfsState parent;
  
  DfsState(int i, int j, char[][] solution, DfaNode[] ps, DfaNode[] qs, DfsState parent) {
    this.i = i;
    this.j = j;
    this.reachGoal = false;
    this.solution = solution;
    this.ps = ps;
    this.qs = qs;
    this.parent = parent;
  }
  
  public static DfsState createInitialInstance(ArrayList<DfaNode> psInput, ArrayList<DfaNode> qsInput) {
    char[][] solution = new char[psInput.size()][qsInput.size()];
    for (char[] s : solution) {
      Arrays.fill(s, '.');
    }
    DfaNode[] ps = new DfaNode[psInput.size()];
    for (int i = 0; i < psInput.size(); i++) {
      ps[i] = psInput.get(i);
    }
    DfaNode[] qs = new DfaNode[qsInput.size()];
    for (int i = 0; i < qsInput.size(); i++) {
      qs[i] = qsInput.get(i);
    }
    return new DfsState(0, 0, solution, ps, qs, null);
  }
  
  public boolean isGoal() {
    return i == solution.length;
  }
  
  public ArrayList<DfsState> getNexts() {
    ArrayList<DfsState> nexts = new ArrayList<DfsState>();
    for (char c = 'A'; c <= 'Z'; c++) {
      DfaNode[] nextPs = (DfaNode[])(ps.clone());
      nextPs[i] = ps[i].proceed(c);
      if (nextPs[i] == null) {
        continue;
      }
      DfaNode[] nextQs = (DfaNode[])(qs.clone());
      nextQs[j] = qs[j].proceed(c);
      if (nextQs[j] == null) {
        continue;
      }
      
      char[][] nextSolution = new char[solution.length][solution[0].length];
      for (int a = 0; a < solution.length; a++) {
        for (int b = 0; b < solution[a].length; b++) {
          nextSolution[a][b] = solution[a][b];
        }
      }
      nextSolution[i][j] = c;
      
      int nextI = i;
      int nextJ = j + 1;
      if (nextJ >= solution[i].length) {
        nextJ = 0;
        nextI++;
      }
      
      nexts.add(new DfsState(nextI, nextJ, nextSolution, nextPs, nextQs, this));
    }
    return nexts;
  }
  
  public boolean sameSolution(DfsState state) {
    for (int a = 0; a < this.solution.length; a++) {
      for (int b = 0; b < this.solution[a].length; b++) {
        if (this.solution[a][b] == '.' || state.solution[a][b] == '.') {
          return true;
        }
        if (this.solution[a][b] != state.solution[a][b]) {
          return false;
        }
      }
    }
    return true;
  }
  
  public void markReachGoal() {
    reachGoal = true;
    if (parent != null) {
      parent.markReachGoal();
    }
  }
  
  public int hashCode() {
    int output = 0;
    output += 4*i + j;
    for (DfaNode p : ps) {
      output *= 13;
      output += p.hashCode();
    }
    for (DfaNode q : qs) {
      output *= 13;
      output += q.hashCode();
    }
    return output;
  }
  
  public boolean equals(Object object) {
    if (object instanceof DfsState) {
      DfsState state = (DfsState)object;
      if (this.i != state.i || this.j != state.j) {
        return false;
      }
      for (int a = 0; a < this.ps.length; a++) {
        if (this.ps[a] != state.ps[a]) {
          return false;
        }
      }
      for (int a = 0; a < this.qs.length; a++) {
        if (this.qs[a] != state.qs[a]) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  
  public String getSolutionString() {
    String output = "";
    for (int a = 0; a < solution.length; a++) {
      for (int b = 0; b < solution[a].length; b++) {
        output += solution[a][b];
      }
      output += "\n";
    }
    return output;
  }
}

public class J {
  private static final String AMBIGUOUS = "ambiguous\n";
  private static final String NONE = "none\n";
  
  private static DfaNode createDfaNode(String input, int depth) {
    Pattern pattern = new Parser(input.toCharArray()).parse();
    NfaNode begin = new NfaNode();
    NfaNode accept = pattern.createNfa(begin);
    DfaNode dfaNode = DfaNode.createDfa(begin, accept, depth);
    return dfaNode;
  }
  
  private static void generateAllRotationDfs(int index, int n, boolean[] used, DfaNode[] rotated, DfaNode[] source, ArrayList<ArrayList<DfaNode>> output) {
    if (index == n) {
      ArrayList<DfaNode> rotation = new ArrayList<DfaNode>();
      for (DfaNode node : rotated) {
        rotation.add(node);
      }
      output.add(rotation);
      return;
    }
    
    for (int i = 0; i < n; i++) {
      if (used[i]) {
        continue;
      }
      used[i] = true;
      rotated[i] = source[i];
      generateAllRotationDfs(index+1, n, used, rotated, source, output);
      used[i] = false;
    }
  }
  
  private static ArrayList<ArrayList<DfaNode>> generateAllRotation(int n, DfaNode[] dfaNodes) {
    ArrayList<ArrayList<DfaNode>> output = new ArrayList<ArrayList<DfaNode>>();
    generateAllRotationDfs(0, n, new boolean[n], new DfaNode[n], dfaNodes, output);
    return output;
  }
  
  private static String solveFixedOrderDfs(DfsState state, HashMap<DfsState, DfsState> visited, String knownSolution) {
    DfsState value  = visited.get(state);
    if (value != null) {
      if (value.reachGoal && !value.sameSolution(state)) {
        return AMBIGUOUS;
      }
      return knownSolution;
    }
    visited.put(state, state);
    
    if (state.isGoal()) {
      state.markReachGoal();
      return state.getSolutionString();
    }
    
    for (DfsState next : state.getNexts()) {
      knownSolution = solveFixedOrderDfs(next, visited, knownSolution);
      if (AMBIGUOUS.equals(knownSolution)) {
        return AMBIGUOUS;
      }
    }
    return knownSolution;
  }
  
  private static String solveFixedOrder(ArrayList<DfaNode> ps, ArrayList<DfaNode> qs, String knownSolution) {
    return solveFixedOrderDfs(DfsState.createInitialInstance(ps, qs), new HashMap<DfsState, DfsState>(), knownSolution);
  }
  
  public static String solve(int h, int w, String[] ps, String[] qs) {
    DfaNode[] dfaPs = new DfaNode[h];
    for (int i = 0; i < h; i++) {
      dfaPs[i] = createDfaNode(ps[i], w);
    }
    ArrayList<ArrayList<DfaNode>> dfaPsRotations = generateAllRotation(h, dfaPs);
    
    DfaNode[] dfaQs = new DfaNode[w];
    for (int i = 0; i < w; i++) {
      dfaQs[i] = createDfaNode(qs[i], h);
    }
    ArrayList<ArrayList<DfaNode>> dfaQsRotations = generateAllRotation(w, dfaQs);
    
    String knownSolution = null;
    for (ArrayList<DfaNode> dfaPsRotation : dfaPsRotations) {
      for (ArrayList<DfaNode> dfaQsRotation : dfaQsRotations) {
        knownSolution = solveFixedOrder(dfaPsRotation, dfaQsRotation, knownSolution);
        if (AMBIGUOUS.equals(knownSolution)) {
          return AMBIGUOUS;
        }
      }
    }
    if (knownSolution != null) {
      return knownSolution;
    }
    return NONE;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    while(true) {
      int h = s.nextInt();
      int w = s.nextInt();
      if (h == 0) {
        break;
      }
      String[] ps = new String[h];
      for (int i = 0; i < h; i++) {
        ps[i] = s.next();
      }
      String[] qs = new String[w];
      for (int i = 0; i < w; i++) {
        qs[i] = s.next();
      }
      System.out.print(solve(h, w, ps, qs));
    }
  }
}
