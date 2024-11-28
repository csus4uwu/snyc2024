#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i - 1];
    }

    auto f = [&](int x, int y) {
        return pre[y] - pre[x - 1];
    };

    vector<int> b(a);
    ranges::sort(b);

    Fenwick<int> fen(2 * n);

    vector<int> cnt(n);
    for (int i = n - 1; ~i; i--) {
        int x = lower_bound(b.begin(), b.end(), 1e8 - a[i]) - b.begin();
        cnt[i] = fen.rangeSum(x, n);
        int id = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        fen.add(id, 1);
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll tem = f(i + 1, n) + 1ll * a[i - 1] * (n - i) - 1ll * cnt[i - 1] * 1e8;
        ans += tem;
    }
    cout << ans << endl;
    
    return 0;
}