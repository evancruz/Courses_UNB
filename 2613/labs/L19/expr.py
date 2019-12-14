class Expr:
    def __init__(self, oper, left, right):
            self.oper = oper
            self.left = left
            self.right = right
    
    def __eq__(self, other):
        if isinstance(self, other.__class__):
            # if self.oper != other.oper:
            #     return False
            # elif self.left != other.left:
            #     return False
            # elif self.right != other.right:
            #     return False
            # else: 
            #     return True
            if isinstance(self,other.__class__):
                return vars(self) == vars(other)
        else: 
            return NotImplemented

    def eval(self):
        def recur(branch):
            if isinstance(branch, Expr):
                return branch.eval()
            else:
                return branch

        if self.oper == "+":
            return recur(self.left) + recur(self.right)
        else:
            return recur(self.left) * (self.right)