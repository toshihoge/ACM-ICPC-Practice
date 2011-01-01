import java.util.*;

public class Main {
  private static HashSet<String> getRealMember(String groupName, HashMap<String, ArrayList<String> > groupDefinitions, HashMap<String, HashSet<String> > cache) {
    if (cache.get(groupName) != null) {
      return cache.get(groupName);
    }
    if (groupDefinitions.get(groupName) == null) {
      HashSet<String> s = new HashSet<String>();
      s.add(groupName);
      return s;
    }
    HashSet<String> output = new HashSet<String>();
    for (String s1 : groupDefinitions.get(groupName)) {
      for (String s2 : getRealMember(s1, groupDefinitions, cache)) {
        output.add(s2);
      }
    }
    cache.put(groupName, output);
    return output;
  }
  
  private static int solve(String[] input) {
    int n = input.length;
    HashMap<String, ArrayList<String> > groupDefinitions = new HashMap<String, ArrayList<String> >();
    String firstGroup = null;
    
    for (String s : input) {
      s = s.replaceAll("\\.", "");
      String[] array = s.split(":");
      ArrayList<String> members = new ArrayList<String>();
      for (String s1 : array[1].split(",")) {
        members.add(s1);
      }
      groupDefinitions.put(array[0], members);
      if (firstGroup == null) {
        firstGroup = array[0];
      }
    }
    
    return getRealMember(firstGroup, groupDefinitions, new HashMap<String, HashSet<String>>()).size();
  }
  
  public static void main (String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int n = Integer.parseInt(s.nextLine());
      if (n == 0) break;
      String[] input = new String[n];
      for (int i = 0; i < n; i++) {
        input[i] = s.nextLine();
      }
      System.out.println(solve(input));
    }
  }
}

