from cs50 import get_int

while True:
    Height = get_int("Height: ")
    if Height > 0 and Height <= 8:
        break
for r in range(Height):
    for s in range(Height-(r + 1)):
        print(" ",end="")
    for hash in range(r + 1):
        print("#", end="")
    print("  ",end="")
    for r_hash in range(r+1):
        print("#",end="")
    print("\n", end="")



