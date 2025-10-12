
def rabin_karp(T, P, d, q):
    n = len(T)
    m = len(P)
    h = d ** (m-1)
    p = 0
    t = 0
    for i in range(m):
        p = (d * p + ord(P[i]))
        t = (d * t + ord(T[i]))
    for s in range(n-m + 1):
        if p == t:
            if P == T[s: s + m]:
                return s
        if s < n - m:
            t = (d * (t - ord(T[s]) * h) + ord(T[s+m]))
    return -1


n = int(input())
a = input()
b = input()

s = rabin_karp(b*2, a, 256, 1)
print(s)
