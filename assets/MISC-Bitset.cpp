// auto p = reinterpret_cast<unsigned*>(&x);
const int M = (1E4 + 200) / 64;
typedef unsigned long long ULL;
const ULL ONE = 1;

struct Bitset {
    ULL a[M];
    void go(int x) {
        int offset = x / 64; x %= 64;
        for (int i = offset, j = 0; i + 1 < M; ++i, ++j) {
            a[j] |= a[i] >> x;
            if (x) a[j] |= a[i + 1] << (64 - x);
        }
    }
    void init() { memset(a, 0, sizeof a); }
    void set(int x) {
        int offset = x / 64; x %= 64;
        a[offset] |= (ONE << x);
    }
    void prt() {
        FOR (i, 0, M) FOR (j, 0, 64) putchar((a[i] & (ONE << j)) ? '1' : '0');
        puts("");
    }
    int lowbit() {
        FOR (i, 0, M) if (a[i]) return i * 64 + __builtin_ctzll(a[i]);
        assert (0);
    }
    int highbit(int x) {
        // the highest bit in [0,x)
        int offset = x / 64; x %= 64;
        FORD (i, offset, -1) {
            if (!a[i]) continue;
            if (i == offset) {
                FORD (j, x - 1, -1) if ((ONE << j) & a[i]) { return i * 64 + j; }
            } else return i * 64 + 63 - __builtin_clzll(a[i]);
        }
        assert (0);
    }
};