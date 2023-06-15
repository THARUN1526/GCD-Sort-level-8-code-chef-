import math
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int,input().split()))
    valid = True
    for i in range(1,n-1):
        while a[i]>a[i+1]:
            if math.gcd(a[i-1],a[i])==a[i]:break
            a[i] = math.gcd(a[i-1],a[i])
        if a[i]<a[i-1] or a[i]>a[i+1]:
            valid = False
            break
    if a[n-1]<a[n-2]: valid = False
    #print(a)
    if valid==True: print("YES")
    else: print("NO")