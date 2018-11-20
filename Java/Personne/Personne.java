import java.util.*;

class Program {
  public static void main(String[] args) {
    int clientAge = 0;
    String s;
    
    if (clientAge < 18) {
      s = "Minor";
    } else {
      s = "Adult";
    }
    
    System.out.println(s);
  }
}