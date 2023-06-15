#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)

template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(vector<S>(n, e())) {}
    explicit segtree(const vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <class F>
    int max_right(int l, const F& f) const {
        assert(0 <= l && l <= _n);
        // assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

   
    template <class F>
    int min_left(int r, const F& f) const {
        assert(0 <= r && r <= _n);
        // assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    // @param n `0 <= n`
    // @return minimum non-negative `x` s.t. `n <= 2**x`
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
};


// Range GCD Query + Binary Search
using Mono = int;
Mono op(Mono a, Mono b) { return gcd(a, b); }
Mono e() { return 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    int tt; cin >> tt;
    while (tt--) {
        int N; cin >> N;
        vector<int> A(N);
        REP(i, N) { cin >> A[i]; }

        segtree<Mono, op, e> seg(A);

        int L = N;
        RREP(i, N - 1) {
            if (A[i] <= A[i + 1]) { continue; }

            // [l, r)
            int l = seg.min_left(i + 1, [&](Mono m) -> Mono {
                return not (m <= A[i + 1]);
            });
            if (l == 0) { break; }
            l = min(l - 1, L);
            L = l;

            int g = seg.prod(l, i + 1);
            A[i] = g;
        }

        bool ok = is_sorted(A.begin(), A.end());
        string ans = (ok ? "YES" : "NO");
        cout << ans << '\n';
    }

    return 0;
}