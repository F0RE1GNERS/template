// can be used in timing
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<int> permutation(N);
for (int i = 0; i < N; i++)
    permutation[i] = i;
shuffle(permutation.begin(), permutation.end(), rng);
for (int i = 0; i < N; i++)
    permutation[i] = i;
for (int i = 1; i < N; i++)
    swap(permutation[i], permutation[uniform_int_distribution<int>(0, i)(rng)]);
// pseudo-random
unsigned rnd() {
    static unsigned A = 1 << 16 | 3, B = 33333331, C = 2341;
    return C = A * C + B;
}
mt19937 mt(time(0));
auto rd = bind(uniform_real_distribution<double>(0, 1), mt);
auto rd2 = bind(uniform_int_distribution<int>(1, 6), mt);