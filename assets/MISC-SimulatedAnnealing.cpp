// Minimum Circle Cover
using LD = double;
const int N = 1E4 + 100;
int x[N], y[N], n;
LD eval(LD xx, LD yy) {
    LD r = 0;
    FOR (i, 0, n)
        r = max(r, sqrt(pow(xx - x[i], 2) + pow(yy - y[i], 2)));
    return r;
}
mt19937 mt(time(0));
auto rd = bind(uniform_real_distribution<LD>(-1, 1), mt);
int main() {
    int X, Y;
    while (cin >> X >> Y >> n) {
        FOR (i, 0, n) scanf("%d%d", &x[i], &y[i]);
        pair<LD, LD> ans;
        LD M = 1e9;
        FOR (_, 0, 100) {
            LD cur_x = X / 2.0, cur_y = Y / 2.0, T = max(X, Y);
            while (T > 1e-3) {
                LD best_ans = eval(cur_x, cur_y);
                LD best_x = cur_x, best_y = cur_y;
                FOR (___, 0, 20) {
                    LD nxt_x = cur_x + rd() * T, nxt_y = cur_y + rd() * T;
                    LD nxt_ans = eval(nxt_x, nxt_y);
                    if (nxt_ans < best_ans) {
                        best_x = nxt_x; best_y = nxt_y;
                        best_ans = nxt_ans;
                    }
                }
                cur_x = best_x; cur_y = best_y;
                T *= .9;
            }
            if (eval(cur_x, cur_y) < M) {
                ans = {cur_x, cur_y}; M = eval(cur_x, cur_y); 
            }
        }
        printf("(%.1f,%.1f).\n%.1f\n", ans.first, ans.second, eval(ans.first, ans.second));
    }
}