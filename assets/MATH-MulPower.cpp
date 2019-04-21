LL mul(LL u, LL v, LL p) {
    return (u * v - LL((long double) u * v / p) * p + p) % p;
}
LL mul(LL u, LL v, LL p) { // better constant
    LL t = u * v - LL((long double) u * v / p) * p;
    return t < 0 ? t + p : t;
}
LL bin(LL x, LL n, LL MOD) {
    n %= (MOD - 1); // if MOD is prime
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = mul(x, x, MOD))
        if (n & 1) ret = mul(ret, x, MOD);
    return ret;
}