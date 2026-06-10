#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;

ll min(ll v1, ll v2) {
    return (v1 < v2) ? v1 : v2;
}

// aplica o problema das linhas de produção
ll meudp(ll* a1, ll* a2, ll* t1_trans, ll* t2_trans, ll e1, ll e2, ll x1, ll x2, int n) {
    long long f1 = e1 + a1[1];
    long long f2 = e2 + a2[1];

    for (int j = 2; j <= n; j++) {
        long long next_f1 = min(f1 + a1[j], f2 + t2_trans[j - 1] + a1[j]);
        long long next_f2 = min(f2 + a2[j], f1 + t1_trans[j - 1] + a2[j]);
        
        f1 = next_f1;
        f2 = next_f2;
    }

    return min(f1 + x1, f2 + x2);
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    ll e1, e2, x1, x2;
    cin >> e1 >> e2;
    cin >> x1 >> x2;

    ll* a1_t     = new ll[n + 1];
    ll* a2_t     = new ll[n + 1];
    ll* t1_trans = new ll[n + 1]; 
    ll* t2_trans = new ll[n + 1];
    ll* p1_pen   = new ll[n + 1];
    ll* p2_pen   = new ll[n + 1];
    bool* auditado = new bool[2 * n + 1];
    
    for (int i = 0; i <= 2 * n; i++) {
        auditado[i] = false;
    }

    for (int i = 1; i <= n; i++)    cin >> a1_t[i];
    for (int i = 1; i <= n; i++)    cin >> a2_t[i];
    for (int i = 1; i < n; i++)     cin >> t1_trans[i];
    for (int i = 1; i < n; i++)     cin >> t2_trans[i];
    for (int i = 1; i <= n; i++)    cin >> p1_pen[i];
    for (int i = 1; i <= n; i++)    cin >> p2_pen[i];

    int auditados_tot = 0;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        if (!auditado[u] && !auditado[v]) {
            auditado[u] = true;
            auditado[v] = true;
            auditados_tot += 2;
        }
    }

    // aplica a penalização para os que foram auditados
    for (int j = 1; j <= n; j++) {
        if (auditado[j]) {
            a1_t[j] += p1_pen[j];
        }
        if (auditado[n + j]) {
            a2_t[j] += p2_pen[j];
        }
    }

    int t_min = meudp(a1_t, a2_t, t1_trans, t2_trans, e1, e2, x1, x2, n);

    cout << auditados_tot << " " << t_min << endl;

    return 0;
}
