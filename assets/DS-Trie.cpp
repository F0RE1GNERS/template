namespace trie {
    const int M = 31;
    int ch[N * M][2], sz;
    void init() { memset(ch, 0, sizeof ch); sz = 2; }
    void ins(LL x) {
        int u = 1;
        FORD (i, M, -1) {
            bool b = x & (1LL << i);
            if (!ch[u][b]) ch[u][b] = sz++;
            u = ch[u][b];
        }
    }
}

// persistent
// !!! sz = 1

struct P { int w, ls, rs; };
P tr[M] = {{0, 0, 0}};
int sz;

int _new(int w, int ls, int rs) { tr[sz] = {w, ls, rs}; return sz++; }
int ins(int oo, int v, int d = 30) {
    P& o = tr[oo];
    if (d == -1) return _new(o.w + 1, 0, 0);
    bool u = v & (1 << d);
    return _new(o.w + 1, u == 0 ? ins(o.ls, v, d - 1) : o.ls, u == 1 ? ins(o.rs, v, d - 1) : o.rs);
}
int query(int pp, int qq, int v, int d = 30) {
    if (d == -1) return 0;
    bool u = v & (1 << d);
    P &p = tr[pp], &q = tr[qq];
    int lw = tr[q.ls].w - tr[p.ls].w;
    int rw = tr[q.rs].w - tr[p.rs].w;

    int ret = 0;
    if (u == 0) {
        if (rw) { ret += 1 << d; ret += query(p.rs, q.rs, v, d - 1); }
        else ret += query(p.ls, q.ls, v, d - 1);
    } else {
        if (lw) { ret += 1 << d; ret += query(p.ls, q.ls, v, d - 1); }
        else ret += query(p.rs, q.rs, v, d - 1);
    }
    return ret;
}