import random
import math
import re
import os
from fractions import gcd
from appJar import gui

def primeNumber(n):
## This program checks to see if a number is prime or not
   squareRoot = int(math.sqrt(n))+1;
   if all(n%i!=0 for i in range(2,squareRoot)): 
      return True
   else:
      return False

def primeGenerator(n,outfileName):
   outfile = open(outfileName, "w")
   primeList = []
   for num in range(2,n):
      if primeNumber(num):
         print(num, file=outfile) 
         primeList.append(num)
   outfile.close()


def getPrime(file):
   primesFile = open(file)
   # get number of lines for each file
   numberOfPrimes = len(primesFile.readlines(  ))
 
   # get a random index for each file
   rand = random.SystemRandom()
   randomIndex = rand.randrange(1, numberOfPrimes)
   
   # reset file pointer to beginning and use randomIndex to get a prime
   primesFile.seek(0,0)
   primeNumbers = primesFile.readlines()
   return int(primeNumbers[randomIndex])

 
# GUI
p = 0
q = 0
n = 0
z = 0
e = 0
d = 0

# Choose e (with e<n) that has no common factors with z. (e, z are “relatively prime”)
def  getE():
   for e in range(2,z): 
      if math.gcd(e,z)== 1: 
         break
   return e
def press(btnName):
   global p
   global q
   global n
   global z
   global e
   global d
   if btnName == "Gen":
      primeGenerator(1000, "primesP.txt")
      primeGenerator(5000, "primesQ.txt")
      
      # generate p and q
      p = getPrime('primesP.txt')
      q = getPrime('primesQ.txt')
      app.setEntry("pLabel", p)
      app.setEntry("qLabel", q)
   if btnName == "Com": 
      n = p*q
      app.setEntry("nLabel", n)
      z = (p-1)*(q-1)
      e = getE()
      app.setEntry("eLabel", e)
   if btnName == "Cal":
      # Choose d such that ed-1 is exactly divisible by z. (in other words: ed mod z = 1 ).
      for i in range(1,10): 
         x = 1 + i*z
         if x % e == 0: 
            d = int(x/e) 
            break
      app.setEntry("dLabel", d)
   if btnName == "Enc":
      m = int(app.getEntry("mLabel"))
      # Had to break it down like this since I would get overflow errors
      ciphertext = 1
      for i in range(0, e):
         ciphertext = ciphertext*m % n
      app.setEntry('cipherLabel', ciphertext)

   if btnName == "Dec":
      ciphertext = int(app.getEntry("cipherLabel"))
      plaintext = 1
      for i in range(0, d):
         plaintext = plaintext*ciphertext % n
      app.setEntry("plainLabel", plaintext)



app = gui()
app.addLabel("title", "RSA Encryption/Decryption", 0, 0)

app.addLabel("1", "1. Generate primes p and q. (1000 < p, q < 5000)", 1, 0)
app.addButtons(["Gen"], press)
app.addLabel("p= ", "p=", 3, 0)
app.addEntry("pLabel",  3, 1)
app.addLabel("q= ", "q=", 4, 0)
app.addEntry("qLabel",  4, 1)

app.addLabel("2", "2. Compute n = pq", 5,0) 
app.addButtons(["Com"], press, 5,1)
app.addLabel("n= ", "n=", 6, 0)
app.addEntry("nLabel",  6, 1)

app.addLabel("3", "3. public key e = ", 7,0) 
app.addEntry("eLabel",  7, 1)

app.addLabel("4", "4. Calculate the private key d", 8,0) 
app.addButtons(["Cal"], press, 8,1)
app.addLabel("d= ", "d=", 9, 0)
app.addEntry("dLabel",  9, 1)

app.addLabel("5", "5. input a message m, where m is an int", 10,0) 
app.addLabel("m= ", "m=", 10, 1)
app.addEntry("mLabel",  10, 2)

app.addLabel("6", "6. Encrypt c=m^e mod n", 11,0) 
app.addButtons(["Enc"], press, 11,1)
app.addLabel("c= ", "c=", 11, 2)
app.addEntry("cipherLabel",  11, 3)

app.addLabel("7", "7. Decrypt m=cd mod n", 12,0) 
app.addButtons(["Dec"], press, 12,1)
app.addLabel("plain", "m=", 12, 2)
app.addEntry("plainLabel",  12, 3)
app.go()

