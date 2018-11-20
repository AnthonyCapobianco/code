public class Hypotenuse {
  private int sideA;
  private int sideB;
  private double hypotenuse;
    
  private double hypotenuse() {
    return Math.sqrt((sideA * sideA) + (sideB * sideB));
  }
  
  public Hypotenuse(final int sideA, final int sideB) {
    this.sideA = sideA;
    this.sideB = sideB;
    this.hypotenuse = hypotenuse();
  }
  
  public double getHypotenuse() {
    return this.hypotenuse;
  }
  
  public static void main(String[] args) throws Exception {
    if (args.length < 2) {
      System.out.println("Please provide two positive integers as argument.");
    }
    
    try {
      final int a = Integer.parseInt(args[0]);
      final int b = Integer.parseInt(args[1]);
      Hypotenuse h = new Hypotenuse(a, b);
      
      System.out.println(h.getHypotenuse());
      
    } catch (NumberFormatException numFormatExcept) {
      System.out.println("Please enter two positive integers");
      return;
    }
  }
}