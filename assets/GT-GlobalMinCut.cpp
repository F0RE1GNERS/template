
struct StoerWanger {
    LL n, vis[N];
    LL dist[N];
    LL g[N][N];

    void init(int nn, LL w[N][N]) {
        n = nn;
        FOR (i, 1, n + 1) FOR (j, 1, n + 1)
            g[i][j] = w[i][j];
        memset(dist, 0, sizeof(dist));
    }

    LL min_cut_phase(int clk, int &x, int &y) {
        int t;
        vis[t = 1] = clk;
        FOR (i, 1, n + 1) if (vis[i] != clk)
            dist[i] = g[1][i];
        FOR (i, 1, n) {
            x = t; t = 0;
            FOR (j, 1, n + 1)
                if (vis[j] != clk && (!t || dist[j] > dist[t]))
                    t = j;
            vis[t] = clk;
            FOR (j, 1, n + 1) if (vis[j] != clk)
                dist[j] += g[t][j];
        }
        y = t;
        return dist[t];
    }

    void merge(int x, int y) {
        if (x > y) swap(x, y);
        FOR (i, 1, n + 1)
            if (i != x && i != y) {
                g[i][x] += g[i][y];
                g[x][i] += g[i][y];
            }
        if (y == n) return;
        FOR (i, 1, n) if (i != y) {
            swap(g[i][y], g[i][n]);
            swap(g[y][i], g[n][i]);
        }
    }

    LL go() {
        LL ret = INF;
        memset(vis, 0, sizeof vis);
        for (int i = 1, x, y; n > 1; ++i, --n) {
            ret = min(ret, min_cut_phase(i, x, y));
            merge(x, y);
        }
        return ret;
    }
} sw;