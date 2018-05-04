import java.util.*;

class Drug
{
        private static Integer[] doseArray;
        private static String name;
        
        
}

class world
{     
        static Scanner userInput = new Scanner(System.in);
        
        public static void main(String[] args) 
        {
                System.out.print("Please type something: ");
                
                if (userInput.hasNextInt()) 
                {
                        Integer theNumberRead = userInput.nextInt();
                        
                        theNumberRead -= 2;
                        
                        System.out.println("Here is the number you entered minus 2."
                                           + " \nCause fuck you, that's why. Here: " 
                                           + theNumberRead + "\n\n\nCunt.");
                }
                else if (userInput.hasNextLine()) 
                {
                        String theStringRead = userInput.nextLine();
                        
                        System.out.println("Here is the string you typed: I love " + theStringRead + " penis.");
                        
                        try
                        {
                                Thread.sleep(1200);
                        }
                        catch(InterruptedException ex)
                        {
                                Thread.currentThread().interrupt();
                        }
                        
                        System.out.println("\n\n\nPervert.");
                        
                        
                }
                else System.out.print("You managed to fuck up. GG");
                
                /*
                 * If we were to have just the `if (userInput.hasNextInt())`
                 * End the user typed something that is NOT an integer.
                 * Then the program would just crash. 
                 * This is java. 
                 * You played Dark Souls. This is nothing to you. 
                 *
                 */
        }
        

}