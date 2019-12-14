import math
from appJar import gui

p = 65537
g = 3

# computeX button
def computeX():
   global p
   global g
   x = int(app.getEntry("xEntry"))
   X = math.pow(g, x) % p
   app.setEntry("XEntry", X)


def computeY():
   global p
   global g
   y = int(app.getEntry("yEntry"))
   Y = math.pow(g, y) % p
   app.setEntry("YEntry", Y)

def cal(btnName):
   global p
   global g
   if btnName == "Cal1":
      Y = float(app.getEntry("YEntry"))
      x = float(app.getEntry("xEntry"))
      res = math.pow(Y,x) % p
      app.setEntry("KEntry1", res)
   else:
      X = float(app.getEntry("XEntry"))
      y = float(app.getEntry("yEntry"))
      res = math.pow(X, y) % p
      app.setEntry("KEntry2", res)


app = gui()
app.addLabel("title", "Given a large prime p=65537, a primary root g=3", 0, 0)

app.addLabel("1", "1. Choose a random number x", 1, 0)
app.addLabel("x=", "x=", 2, 0)
app.addEntry("xEntry", 2, 1)

app.addLabel("2", "2. Compute X=g^x mod p", 3, 0)
app.addButtons(["ComX"], computeX, 3, 1)
app.addLabel("X=", "X=", 4, 0)
app.addEntry("XEntry", 4, 1)


app.addLabel("3", "3. Choose a random number y", 5, 0)
app.addLabel("y=", "y=", 6, 0)
app.addEntry("yEntry", 6, 1)
app.addLabel("4", "4. Compute Y=g^y mod p", 7, 0)
app.addButtons(["ComY"], computeY, 7,1)
app.addLabel("Y=", "Y=", 8, 0)
app.addEntry("YEntry", 8, 1)

app.addLabel("5", "5. Calculate the session key K=g^xy mod p", 9, 0)
app.addLabel("K=", "K=Y^x mod p=", 10, 0)
app.addEntry("KEntry1", 10, 1)
app.addButtons(["Cal1"], cal, 10, 2)
app.addLabel("K=X", "K=X^y mod p=", 10, 3)
app.addEntry("KEntry2", 10, 4)
app.addButtons(["Cal2"], cal, 10, 5)

app.go()
