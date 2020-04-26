#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

/*
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("-O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
*/

#define mp make_pair
#define ll long long
#define ld long double
#define pb push_back
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fs first
#define sc second
#define getfiles ifstream cin("input.txt"); ofstream cout("output.txt");
#define endl '\n'
#define pii pair<int, int>

const int INF = 2000000005;
const ll BIG_INF = 2000000000000000005;
const int mod = 1000000007;
const int P = 31;
const ld PI = 3.141592653589793238462643;
const double eps = 1e-9;

using namespace std;
using namespace __gnu_pbds;

bool valid(int x, int y, int n, int m) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

mt19937 rng(time(0));

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int a[55][55];
vector<int> choice = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2};

signed main() {
    fast_io;

    ofstream cout("input.txt");

    int col = 36;
    cout << col << endl;
    for (int i = 0; i < col; i++) {
        cout << "Student_" << i + 1 << endl;
    }
    for (int i = 0; i < col; i++) {
        for (int j = i + 1; j < col; j++) {
            a[i][j] = a[j][i] = choice[rng() % choice.size()];
        }
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < col; i++) {
        cout << endl;
        for (int r = 0; r < 6; r++) {
            for (int c = 0; c < 3; c++) {
                cout << rng() % 2 << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
