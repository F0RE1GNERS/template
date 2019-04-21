// n equations, m variables
// a is an n x (m + 1) augmented matrix
// free is an indicator of free variable
// return the number of free variables, -1 for "404"
int n, m;
LD a[maxn][maxn], x[maxn];
bool free_x[maxn];
inline int sgn(LD x) { return (x > eps) - (x < -eps); }
int gauss(LD a[maxn][maxn], int n, int m) {
  memset(free_x, 1, sizeof free_x); memset(x, 0, sizeof x);
  int r = 0, c = 0;
  while (r < n && c < m) {
    int m_r = r;
    FOR (i, r + 1, n)
      if (fabs(a[i][c]) > fabs(a[m_r][c])) m_r = i;
    if (m_r != r)
      FOR (j, c, m + 1)
         swap(a[r][j], a[m_r][j]);
    if (!sgn(a[r][c])) {
      a[r][c] = 0; ++c;
      continue;
    }
    FOR (i, r + 1, n)
      if (a[i][c]) {
        LD t = a[i][c] / a[r][c];
        FOR (j, c, m + 1) a[i][j] -= a[r][j] * t;
      }
    ++r; ++c;
  }
  FOR (i, r, n)
    if (sgn(a[i][m])) return -1;
  if (r < m) {
    FORD (i, r - 1, -1) {
      int f_cnt = 0, k = -1;
      FOR (j, 0, m)
        if (sgn(a[i][j]) && free_x[j]) {
          ++f_cnt; k = j;
        }
      if(f_cnt > 0) continue;
      LD s = a[i][m];
      FOR (j, 0, m)
        if (j != k) s -= a[i][j] * x[j];
      x[k] = s / a[i][k];
      free_x[k] = 0;
    }
    return m - r;
  }
  FORD (i, m - 1, -1) {
    LD s = a[i][m];
    FOR (j, i + 1, m)
      s -= a[i][j] * x[j];
    x[i] = s / a[i][i];
  }
  return 0;
}