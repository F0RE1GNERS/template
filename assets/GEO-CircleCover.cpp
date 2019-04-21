// version 1
// union O(n^3 log n)
struct CV {
    LD yl, yr, ym; C o; int type;
    CV() {}
    CV(LD yl, LD yr, LD ym, C c, int t)
        : yl(yl), yr(yr), ym(ym), type(t), o(c) {}
};
pair<LD, LD> c_point_eval(const C& c, LD x) {
    LD d = fabs(c.p.x - x), h = rt(sq(c.r) - sq(d));
    return {c.p.y - h, c.p.y + h};
}
pair<CV, CV> pairwise_curves(const C& c, LD xl, LD xr) {
    LD yl1, yl2, yr1, yr2, ym1, ym2;
    tie(yl1, yl2) = c_point_eval(c, xl);
    tie(ym1, ym2) = c_point_eval(c, (xl + xr) / 2);
    tie(yr1, yr2) = c_point_eval(c, xr);
    return {CV(yl1, yr1, ym1, c, 1), CV(yl2, yr2, ym2, c, -1)};
}
bool operator < (const CV& a, const CV& b) { return a.ym < b.ym; }
LD cv_area(const CV& v, LD xl, LD xr) {
    LD l = rt(sq(xr - xl) + sq(v.yr - v.yl));
    LD d = rt(sq(v.o.r) - sq(l / 2));
    LD ang = atan(l / d / 2);
    return ang * sq(v.o.r) - d * l / 2;
}
LD circle_union(const vector<C>& cs) {
    int n = cs.size();
    vector<LD> xs;
    FOR (i, 0, n) {
        xs.push_back(cs[i].p.x - cs[i].r);
        xs.push_back(cs[i].p.x);
        xs.push_back(cs[i].p.x + cs[i].r);
        FOR (j, i + 1, n) {
            auto pts = c_c_intersection(cs[i], cs[j]);
            for (auto& p: pts) xs.push_back(p.x);
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end(), [](LD x, LD y) { return sgn(x - y) == 0; }), xs.end());
    LD ans = 0;
    FOR (i, 0, (int) xs.size() - 1) {
        LD xl = xs[i], xr = xs[i + 1];
        vector<CV> intv;
        FOR (k, 0, n) {
            auto& c = cs[k];
            if (sgn(c.p.x - c.r - xl) <= 0 && sgn(c.p.x + c.r - xr) >= 0) {
                auto t = pairwise_curves(c, xl, xr);
                intv.push_back(t.first); intv.push_back(t.second);
            }
        }
        sort(intv.begin(), intv.end());

        vector<LD> areas(intv.size());
        FOR (i, 0, intv.size()) areas[i] = cv_area(intv[i], xl, xr);

        int cc = 0;
        FOR (i, 0, intv.size()) {
            if (cc > 0) {
                ans += (intv[i].yl - intv[i - 1].yl + intv[i].yr - intv[i - 1].yr) * (xr - xl) / 2;
                ans += intv[i - 1].type * areas[i - 1];
                ans -= intv[i].type * areas[i];
            }
            cc += intv[i].type;
        }
    }
    return ans;
}

// version 2 (k-cover, O(n^2 log n))
inline LD angle(const P &p) { return atan2(p.y, p.x); }

// Points on circle
// p is coordinates relative to c
struct CP {
  P p;
  LD a;
  int t;
  CP() {}
  CP(P p, LD a, int t) : p(p), a(a), t(t) {}
};
bool operator<(const CP &u, const CP &v) { return u.a < v.a; }
LD cv_area(LD r, const CP &q1, const CP &q2) {
  return (r * r * (q2.a - q1.a) - cross(q1.p, q2.p)) / 2;
}

LD ans[N];
void circle_union(const vector<C> &cs) {
  int n = cs.size();
  FOR(i, 0, n) {
    // same circle, only the first one counts
    bool ok = true;
    FOR(j, 0, i)
    if (sgn(cs[i].r - cs[j].r) == 0 && cs[i].p == cs[j].p) {
      ok = false;
      break;
    }
    if (!ok)
      continue;
    auto &c = cs[i];
    vector<CP> ev;
    int belong_to = 0;
    P bound = c.p + P(-c.r, 0);
    ev.emplace_back(bound, -PI, 0);
    ev.emplace_back(bound, PI, 0);
    FOR(j, 0, n) {
      if (i == j)
        continue;
      if (c_c_relation(c, cs[j]) <= 2) {
        if (sgn(cs[j].r - c.r) >= 0) // totally covered
          belong_to++;
        continue;
      }
      auto its = c_c_intersection(c, cs[j]);
      if (its.size() == 2) {
        P p = its[1] - c.p, q = its[0] - c.p;
        LD a = angle(p), b = angle(q);
        if (sgn(a - b) > 0) {
          ev.emplace_back(p, a, 1);
          ev.emplace_back(bound, PI, -1);
          ev.emplace_back(bound, -PI, 1);
          ev.emplace_back(q, b, -1);
        } else {
          ev.emplace_back(p, a, 1);
          ev.emplace_back(q, b, -1);
        }
      }
    }
    sort(ev.begin(), ev.end());
    int cc = ev[0].t;
    FOR(j, 1, ev.size()) {
      int t = cc + belong_to;
      ans[t] += cross(ev[j - 1].p + c.p, ev[j].p + c.p) / 2;
      ans[t] += cv_area(c.r, ev[j - 1], ev[j]);
      cc += ev[j].t;
    }
  }
}