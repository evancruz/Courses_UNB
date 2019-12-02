import java.util.*;
import java.math.BigInteger;

class ExtendedEucAlgo {
   public static void main(String[] args) {
      Random rand = new Random();
      System.out.println(rand.nextLong());
      
      System.out.println("Enter two large positive longeger numbers of length 1024 bits");

      Scanner scan = new Scanner(System.in);
      long a = scan.nextLong();
      long b = scan.nextLong();

      long [] res = xEucAlgo(a, b);
      System.out.println("c:" + res[0] + " d:" + res[1]);
      scan.close();
   }

   
   public static long[] xEucAlgo(long a, long b) {
      long x = 0;
      long y = 1;
      long u = 1;
      long v = 0;

      while (a != 0) {
         long q = b / a;
         long r = b % a;
         
         long m = x - u * q;
         long n = y - v * q;
         
         b = a;
         a = r;
         x = u;
         y = v;
         u = m;
         v = n;
      }
      long[] res = {x, y};
      return res;
   }
}




