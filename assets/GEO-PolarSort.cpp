int quad(P p) {
    int x = sgn(p.x), y = sgn(p.y);
    if (x > 0 && y >= 0) return 1;
    if (x <= 0 && y > 0) return 2;
    if (x < 0 && y <= 0) return 3;
    if (x >= 0 && y < 0) return 4;
    assert(0);
}

struct cmp_angle {
    P p;
    bool operator () (const P& a, const P& b) {
        int qa = quad(a - p), qb = quad(b - p);
        if (qa != qb) return qa < qb; // compare quad
        int d = sgn(cross(a, b, p));
        if (d) return d > 0;
        return dist(a - p) < dist(b - p);
    }
};