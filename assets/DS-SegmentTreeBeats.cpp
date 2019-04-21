namespace R {
#define lson o * 2, l, (l + r) / 2
#define rson o * 2 + 1, (l + r) / 2 + 1, r
    int m1[N], m2[N], cm1[N];
    LL sum[N];
    void up(int o) {
        int lc = o * 2, rc = lc + 1;
        m1[o] = max(m1[lc], m1[rc]);
        sum[o] = sum[lc] + sum[rc];
        if (m1[lc] == m1[rc]) {
            cm1[o] = cm1[lc] + cm1[rc];
            m2[o] = max(m2[lc], m2[rc]);
        } else {
            cm1[o] = m1[lc] > m1[rc] ? cm1[lc] : cm1[rc];
            m2[o] = max(min(m1[lc], m1[rc]), max(m2[lc], m2[rc]));
        }
    }
    void mod(int o, int x) {
        if (x >= m1[o]) return;
        assert(x > m2[o]);
        sum[o] -= 1LL * (m1[o] - x) * cm1[o];
        m1[o] = x;
    }
    void down(int o) {
        int lc = o * 2, rc = lc + 1;
        mod(lc, m1[o]); mod(rc, m1[o]);
    }
    void build(int o, int l, int r) {
        if (l == r) { int t; read(t); sum[o] = m1[o] = t; m2[o] = -INF; cm1[o] = 1; }
        else { build(lson); build(rson); up(o); }
    }
    void update(int ql, int qr, int x, int o, int l, int r) {
        if (r < ql || qr < l || m1[o] <= x) return;
        if (ql <= l && r <= qr && m2[o] < x) { mod(o, x); return; }
        down(o);
        update(ql, qr, x, lson); update(ql, qr, x, rson);
        up(o);
    }
    int qmax(int ql, int qr, int o, int l, int r) {
        if (r < ql || qr < l) return -INF;
        if (ql <= l && r <= qr) return m1[o];
        down(o);
        return max(qmax(ql, qr, lson), qmax(ql, qr, rson));
    }
    LL qsum(int ql, int qr, int o, int l, int r) {
        if (r < ql || qr < l) return 0;
        if (ql <= l && r <= qr) return sum[o];
        down(o);
        return qsum(ql, qr, lson) + qsum(ql, qr, rson);
    }
}