package src;

import java.util.Random;

public class RandomDecisionMaker {
  public static void main(String[] args) {
    Random rng = new Random();
    
    boolean decision = rng.nextBoolean();
    if (decision) {
      System.out.println("Yes");
    } else {
      System.out.println("Nope");
    }
  }
}