import math
from appJar import gui

p = 65537
g = 3

def compute(btnName):
   global p
   global g

   if btnName == "ComY":
      x = int(app.getEntry("xEntry"))
      y = math.pow(g,x) % p
      app.setEntry("yEntry", y)
   
   elif btnName == "c1":
      r = int(app.getEntry("rEntry"))
      c1 = math.pow(g,r) % p
      app.setEntry("c1Entry", c1)

   else:
      r = float(app.getEntry("rEntry"))
      m = float(app.getEntry("mEntry"))
      y = float(app.getEntry("yEntry"))
      # c2= m * y^r mod p
      c2 = m * (math.pow(y, r) % p)
      app.setEntry("c2Entry", c2)


def dec():
   global p
   global g

   c2 = float(app.getEntry("c2Entry"))
   c1 = float(app.getEntry("c1Entry"))
   x = float(app.getEntry("xEntry"))
   msg = (c2/math.pow(c1,x) ) % p
   app.setEntry("mEntry2", msg)

app = gui()
app.addLabel("title", "0. Given a large prime p=65537, a primary root g=3", 0, 0)

app.addLabel("1", "1. Choose a private key x", 1, 0)
app.addLabel("x=", "x=", 2, 0)
app.addEntry("xEntry", 2, 1)

app.addLabel("2", "2. Compute the coresponding public key y = g^x mod p", 3, 0)
app.addButtons(["ComY"], compute, 3, 1)
app.addLabel("y=", "y=", 4, 0)
app.addEntry("yEntry", 4, 1)

app.addLabel("3", "3. Input a message m", 5, 0)
app.addLabel("m=", "m=", 6, 0)
app.addEntry("mEntry", 6, 1)

app.addLabel("4", "4. Encrypt", 7, 0)
app.addLabel("4.1", "4.1 Choose a random number r", 8,0)
app.addEntry("rEntry", 8, 1)
app.addLabel("4.2", "4.2 Compute c1=g^r mod p", 9, 0)
app.addButtons(["c1"], compute, 9, 1)
app.addEntry("c1Entry", 9, 2)
app.addLabel("4.3", "4.3 Compute c2= m * y^r mod p", 10, 0)
app.addButtons(["c2"], compute, 10, 1)
app.addEntry("c2Entry", 10, 2)

app.addLabel("5", "5. Decrypt C=(c1,c2 )", 11, 0)
app.addLabel("m", "m=c2/(c1)^x mod p", 12, 0)
app.addButtons(["dec"], dec, 12, 1)
app.addEntry("mEntry2", 12, 2)


app.go()
