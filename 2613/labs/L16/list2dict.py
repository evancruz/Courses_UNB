def list2dict(lst):
    return {i+1: lst[i] for i in range (0, len(lst))}

def swapem(dict):
    return{val: key for key, val in dict.items()}