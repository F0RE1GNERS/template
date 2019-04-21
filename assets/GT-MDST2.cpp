namespace MDST {
    typedef pair<LL, int> P;
    
    int fa[N], stk[N], top, n;
    LL shift[N];
    bool vis[N];
    set<P> G[N];

    int Fa(int x) { return fa[x] == x? x: (fa[x] = Fa(fa[x])); }

    void init(int _n) {
        n = _n;
        iota(fa, fa+n+1, 0);
        fill(shift, shift+n+1, 0);
        fill(vis, vis+n+1, false);
    }

    void add_edge(int u, int v, int w) {
        G[v].emplace(w, u);
    }

    pair<bool, LL> solve(int root) {
        LL ans = 0;
        FOR(i, 1, n+1) {
            int u = i; top = 0;
            while(Fa(u) != Fa(root)) {
                vis[u] = true; stk[top++] = u;
                auto it = G[u].begin();
                while(it != G[u].end()) {
                    if(Fa(it->second) == Fa(u)) it = G[u].erase(it);
                    else break;
                }
                if(it == G[u].end()) return { false, -1LL };
                LL lb = it->first; int v = Fa(it->second);
                G[u].erase(it);
                ans += lb + shift[u];
                shift[u] = -lb;
                if(vis[v] && Fa(v) != Fa(root)) {
                    int x = v;
                    while(stk[top-1] != v) {
                        int y = stk[--top];
                        fa[Fa(y)] = Fa(x);
                        if(G[x].size()<G[y].size()) {
                            G[x].swap(G[y]);
                            swap(shift[x], shift[y]);
                        }
                        for(auto pr: G[y]) {
                            G[x].emplace(pr.first+shift[y]-shift[x], pr.second);
                        }
                        G[y].clear();
                    }
                }
                u = v;
            }
            while(top--) {
                fa[Fa(stk[top])] = root;
            }
        }
        FOR(i, 1, n+1) if(Fa(i) != Fa(root)) {
            return { false, -1 };
        }
        return { true, ans };
    }
}