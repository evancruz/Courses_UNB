import java.math.BigInteger;
import java.util.*;


public class MillerRabin {
   public static boolean isPrime(long n, int iteration) {
      if (n >= 3){
         //if it's divisible by 2 then it's even and not prime
         if (n % 2 == 0)
            return false;
      
      //if it get's here that means it is an odd number. s is even
      long s = n - 1;
      while (s % 2 == 0)
         s /= 2;

      /*composite if n is composite, otherwise probably prime
      write n − 1 as 2s·d with d odd by factoring powers of 2 from n − 1 */
      Random rand = new Random();
      for (int i = 0; i < iteration; i++) {
         long r = Math.abs(rand.nextLong());
         long a = r % (n - 1) + 1;
         long temp = s;
         long mod = modPow(a, temp, n);
         while (temp != n - 1 && mod != 1 && mod != n - 1) {
            mod = mulMod(mod, mod, n);
            temp *= 2;
         }
         if (mod != n - 1 && temp % 2 == 0)
         
            return false;
      }
      return true;
      } else {
         if (n == 0 || n == 1)
            return false;
         //n is 2
         return true;
      }
   }

   /** Function to calculate (a ^ b) % c **/
   public static long modPow(long a, long b, long c) {
      long res = 1;
      for (int i = 0; i < b; i++) {
         res *= a;
         res %= c;
      }
      return res % c;
   }

   /** Function to calculate (a * b) % c **/
   public static long mulMod(long a, long b, long mod) {
      return BigInteger.valueOf(a).multiply(BigInteger.valueOf(b)).mod(BigInteger.valueOf(mod)).longValue();
   }


   public static void main(String[] args) {
      Scanner scan = new Scanner(System.in);
      System.out.println("Enter number\n");
      long num = scan.nextLong();

      System.out.println("\nEnter iterations");
      int k = scan.nextInt();
      System.out.println("\nOutputs 1 if prime, 0 otherwise: ");

      boolean prime = isPrime(num, k);
      //output 1 if a is a prime, and 0 otherwise.
      if (prime)
         System.out.print(1);
      else
         System.out.print(0);

   }
}