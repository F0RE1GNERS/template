// do not forget down when findint L/R most son
// make_root if not sure

namespace lct {
    extern struct P *const null;
    const int M = N;
    struct P {
        P *fa, *ls, *rs;
        int v, maxv;
        bool rev;

        bool has_fa() { return fa->ls == this || fa->rs == this; }
        bool d() { return fa->ls == this; }
        P*& c(bool x) { return x ? ls : rs; }
        void do_rev() {
            if (this == null) return;
            rev ^= 1;
            swap(ls, rs);
        }
        P* up() {
            maxv = max(v, max(ls->maxv, rs->maxv));
            return this;
        }
        void down() {
            if (rev) {
                rev = 0;
                ls->do_rev(); rs->do_rev();
            }
        }
        void all_down() { if (has_fa()) fa->all_down(); down(); }
    } *const null = new P{0, 0, 0, 0, 0, 0}, pool[M], *pit = pool;

    void rot(P* o) {
        bool dd = o->d();
        P *f = o->fa, *t = o->c(!dd);
        if (f->has_fa()) f->fa->c(f->d()) = o; o->fa = f->fa;
        if (t != null) t->fa = f; f->c(dd) = t;
        o->c(!dd) = f->up(); f->fa = o;
    }
    void splay(P* o) {
        o->all_down();
        while (o->has_fa()) {
            if (o->fa->has_fa())
                rot(o->d() ^ o->fa->d() ? o : o->fa);
            rot(o);
        }
        o->up();
    }
    void access(P* u, P* v = null) {
        if (u == null) return;
        splay(u); u->rs = v;
        access(u->up()->fa, u);
    }
    void make_root(P* o) {
        access(o); splay(o); o->do_rev();
    }
    void split(P* o, P* u) {
        make_root(o); access(u); splay(u);
    }
    void link(P* u, P* v) {
        make_root(u); u->fa = v;
    }
    void cut(P* u, P* v) {
        split(u, v);
        u->fa = v->ls = null; v->up();
    }
    bool adj(P* u, P* v) {
        split(u, v);
        return v->ls == u && u->ls == null && u->rs == null;
    }
    bool linked(P* u, P* v) {
        split(u, v);
        return u == v || u->fa != null;
    }
    P* findrt(P* o) {
        access(o); splay(o);
        while (o->ls != null) o = o->ls;
        return o;
    }
    P* findfa(P* rt, P* u) {
        split(rt, u);
        u = u->ls;
        while (u->rs != null) {
            u = u->rs;
            u->down();
        }
        return u;
    }
}
// maintain subtree size
P* up() {
    sz = ls->sz + rs->sz + _sz + 1;
    return this;
}
void access(P* u, P* v = null) {
    if (u == null) return;
    splay(u);
    u->_sz += u->rs->sz - v->sz;
    u->rs = v;
    access(u->up()->fa, u);
}
void link(P* u, P* v) {
    split(u, v);
    u->fa = v; v->_sz += u->sz;
    v->up();
}

//////////////////////
// latest spanning tree
//////////////////////
namespace lct {
    extern struct P* null;
    struct P {
        P *fa, *ls, *rs;
        int v;
        P *minp;
        bool rev;

        bool has_fa() { return fa->ls == this || fa->rs == this; }
        bool d() { return fa->ls == this; }
        P*& c(bool x) { return x ? ls : rs; }
        void do_rev() { if (this == null) return; rev ^= 1; swap(ls, rs); }

        P* up() {
            minp = this;
            if (minp->v > ls->minp->v) minp = ls->minp;
            if (minp->v > rs->minp->v) minp = rs->minp;
            return this;
        }
        void down() { if (rev) { rev = 0; ls->do_rev(); rs->do_rev(); }}
        void all_down() { if (has_fa()) fa->all_down(); down(); }
    } *null = new P{0, 0, 0, INF, 0, 0}, pool[maxm], *pit = pool;
    void rot(P* o) {
        bool dd = o->d();
        P *f = o->fa, *t = o->c(!dd);
        if (f->has_fa()) f->fa->c(f->d()) = o; o->fa = f->fa;
        if (t != null) t->fa = f; f->c(dd) = t;
        o->c(!dd) = f->up(); f->fa = o;
    }
    void splay(P* o) {
        o->all_down();
        while (o->has_fa()) {
            if (o->fa->has_fa()) rot(o->d() ^ o->fa->d() ? o : o->fa);
            rot(o);
        }
        o->up();
    }
    void access(P* u, P* v = null) {
        if (u == null) return;
        splay(u); u->rs = v;
        access(u->up()->fa, u);
    }
    void make_root(P* o) { access(o); splay(o); o->do_rev(); }
    void split(P* u, P* v) { make_root(u); access(v); splay(v); }
    bool linked(P* u, P* v) { split(u, v); return u == v || u->fa != null; }
    void link(P* u, P* v) { make_root(u); u->fa = v; }
    void cut(P* u, P* v) { split(u, v); u->fa = v->ls = null; v->up(); }
}

using namespace lct;
int n, m;
P *p[maxn];
struct Q {
    int tp, u, v, l, r;
};
vector<Q> q;

int main() {
    null->minp = null;
    cin >> n >> m;
    FOR (i, 1, n + 1) p[i] = new (pit++) P{null, null, null, INF, p[i], 0};
    int clk = 0;
    map<pair<int, int>, int> mp;
    FOR (_, 0, m) {
        int tp, u, v; scanf("%d%d%d", &tp, &u, &v);
        if (u > v) swap(u, v);
        if (tp == 0) mp.insert({{u, v}, clk});
        else if (tp == 1) {
            auto it = mp.find({u, v}); assert(it != mp.end());
            q.push_back({1, u, v, it->second, clk});
            mp.erase(it);
        } else q.push_back({0, u, v, clk, clk});
        ++clk;
    }
    for (auto& x: mp) q.push_back({1, x.first.first, x.first.second, x.second, clk});
    sort(q.begin(), q.end(), [](const Q& a, const Q& b)->bool { return a.l < b.l; });
    map<P*, int> mp2;
    FOR (i, 0, q.size()) {
        Q& cur = q[i];
        int u = cur.u, v = cur.v;
        if (cur.tp == 0) {
            if (!linked(p[u], p[v])) puts("N");
            else puts(p[v]->minp->v >= cur.r ? "Y" : "N");
            continue;
        }
        if (linked(p[u], p[v])) {
            P* t = p[v]->minp;
            if (t->v > cur.r) continue;
            Q& old = q[mp2[t]];
            cut(p[old.u], t); cut(p[old.v], t);
        }
        P* t = new (pit++) P {null, null, null, cur.r, t, 0};
        mp2[t] = i;
        link(t, p[u]); link(t, p[v]);
    }
}