import string

letters = string.ascii_uppercase

with open("tie.in", "w") as f:
    for i in range(1,20,2):
        for j in range(1,4):
            if i != 19:
                f.write("place {}{}\n".format(letters[i-1],j))
                f.write("place {}{}\n".format(letters[i],j))
    for i in range(1,20,2):          
        for j in range(4,8):
            if i != 19:
                f.write("place {}{}\n".format(letters[i],j))
                f.write("place {}{}\n".format(letters[i-1],j))
    for i in range(1,20,2):          
        for j in range(8,12):
            if i != 19:
                f.write("place {}{}\n".format(letters[i-1],j))
                f.write("place {}{}\n".format(letters[i],j))
    for i in range(1,20,2):          
        for j in range(12,16):
            if i != 19:
                f.write("place {}{}\n".format(letters[i],j))
                f.write("place {}{}\n".format(letters[i-1],j))
    for i in range(1,20,2):          
        for j in range(16,20):
            if i != 19:
                f.write("place {}{}\n".format(letters[i-1],j))
                f.write("place {}{}\n".format(letters[i],j))
    for j in range(19,15,-1):
        f.write("place {}{}\n".format(letters[18],j))
        f.write("place {}{}\n".format(letters[18],j-4))
    for j in range(11,7,-1):
        f.write("place {}{}\n".format(letters[18],j))
        f.write("place {}{}\n".format(letters[18],j-4))
    for j in range(3,0,-1):
        f.write("place {}{}\n".format(letters[18],j))