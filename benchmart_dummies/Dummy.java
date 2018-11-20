public class Dummy {
  public static int throwaway(final int useless) {
    int throwawayLong = 1337;
    for (int i = 0; i < 10000; ++i) {
      throwawayLong += i;
    }
    return throwawayLong;
  }
  
  public static void main(String[] args) {
    long startTime = System.nanoTime();
    
    System.out.println(throwaway(0xDEADBABE));
    
    long estimatedTime = System.nanoTime() - startTime;
    System.out.println(estimatedTime);
  }
}