// all proper subset
for (int s = (S - 1) & S; s; s = (s - 1) & S) {
    // ...
}

// subset of length k
template<typename T>
void subset(int k, int n, T&& f) {
    int t = (1 << k) - 1;
    while (t < 1 << n) {
        f(t);
        int x = t & -t, y = t + x;
        t = ((t & ~y) / x >> 1) | y;
    }
}