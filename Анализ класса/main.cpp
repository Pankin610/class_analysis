#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

const int N = 55;

int n, friends[N][N], friend_mask[N], res = 0, best_res = -1000000000;
string name[N], filename;
bool vis[N], seatable[N][7][4];
vector< vector< pair<int, int> > > seating(7, vector< pair<int, int> >(4, make_pair(-1, -1))), best_seating(7, vector< pair<int, int> >(4, make_pair(-1, -1)));

unordered_map<string, int> id;

void dfs(int v, vector<int>& cur) {
    vis[v] = true;
    cur.push_back(v);

    for (int i = 1; i <= n; i++) {
        if (friends[v][i] > 0 && !vis[i])
            dfs(i, cur);
    }
}

void getIndependantGroups() {
    vector<vector<int>> groups;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            groups.push_back(vector<int>(0));
            dfs(i, groups.back());
        }
    }

    cout << "Независимых групп: " << groups.size() << endl;
    for (int i = 0; i < groups.size(); i++) {
        cout << "Группа " << i + 1 << ": ";
        for (int j = 0; j < groups[i].size(); j++) {
            cout << name[groups[i][j]];
            if (j + 1 < groups[i].size())
                cout << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

inline void del(vector<int> &d, int i) {
    swap(d[i], d.back());
    d.pop_back();
}

void brute(int mask, int i, int &res, int addable) {
    if (addable == 0 || i == n) {
        if (__builtin_popcount(mask) > __builtin_popcount(res)) {
            res = mask;
        }
        return;
    }
    if (((addable>>i)&1) == 1) {
        brute(mask | (1 << i), i + 1, res, addable & friend_mask[i + 1]);
    }
    brute(mask, i + 1, res, addable & (((1 << n) - 1) ^ (1 << i)));
}

void getMaxClique() {
    int res = 0;
    brute(0, 0, res, (1 << n) - 1);

    cout << "Самая большая кампания друзей (где каждый дружит с каждым): ";
    for (int i = 0; i < n; i++) {
        if (((res>>i)&1) == 1) {
            cout << name[i + 1];
            if ((1 << (i + 1)) <= res)
                cout << ", ";
        }
    }
    cout << endl;
}

const int MX = 36 + 18 + 5;

struct edge {
    int v, p, rev;
    edge(int v, int p, int rev) {
        this->v = v;
        this->p = p;
        this->rev = rev;
    }
    edge(){}
};
vector<edge> g[MX];
pair<int, int> desk[40];

inline void addEdge(int u, int v, int p) {
    g[u].push_back(edge(v, p, g[v].size()));
    g[v].push_back(edge(u, 0, g[u].size() - 1));
}

bool dfs(int v) {
    if (v == MX - 1)
        return true;
    if (vis[v])
        return false;
    vis[v] = true;
    random_shuffle(g[v].begin(), g[v].end());
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i].p == 0)
            continue;
        if (dfs(g[v][i].v)) {
            g[v][i].p--;
            g[g[v][i].v][g[v][i].rev].p++;
            return true;
        }
    }
    return false;
}

bool getRandomSeating() {
    seating = vector<vector<pair<int, int>>>(7, vector< pair<int, int> >(4, make_pair(-1, -1)));

    fill(g, g + MX, vector<edge>(0));
    for (int i = 1; i <= 36; i++) {
        addEdge(0, i, 1);
        for (int row = 1; row <= 6; row++) {
            for (int col = 1; col <= 3; col++) {
                if (seatable[i][row][col]) {
                    addEdge(i, 37 + (row - 1) * 3 + col - 1, 1);
                }
            }
        }
    }
    for (int row = 1; row <= 6; row++) {
        for (int col = 1; col <= 3; col++) {
            addEdge(37 + (row - 1) * 3 + col - 1, MX - 1, 2);
        }
    }

    int flow = 0;

    fill(vis, vis + MX, false);
    while(dfs(0)) {
        fill(vis, vis + MX, false);
        flow++;
    }

    for (int i = 1; i <= 36; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (g[i][j].v >= 37 && g[i][j].p == 0) {
                int row = (g[i][j].v - 37) / 3 + 1, col = (g[i][j].v - 37) % 3 + 1;
                if (seating[row][col].first == -1)
                    seating[row][col].first = i;
                else
                    seating[row][col].second = i;
                desk[i] = make_pair(row, col);
            }
        }
    }

    res = 0;
    for (int row = 1; row <= 6; row++) {
        for (int col = 1; col <= 3; col++) {
            res += friends[seating[row][col].first][seating[row][col].second];
        }
    }

    return (flow == 36);
}

pair<int, int> to_swap[36 * 36 + 5];
int o;
inline void Anneale() {
    o = 0;
    for (int i = 1; i <= 36; i++) {
        for (int j = i + 1; j <= 36; j++) {
            if (seatable[i][desk[j].first][desk[j].second] && seatable[j][desk[i].first][desk[i].second]) {
                int delta = 0;
                delta -= friends[seating[desk[j].first][desk[j].second].first][seating[desk[j].first][desk[j].second].second];
                delta -= friends[seating[desk[i].first][desk[i].second].first][seating[desk[i].first][desk[i].second].second];

                if (seating[desk[i].first][desk[i].second].first != i) {
                    swap(seating[desk[i].first][desk[i].second].first, seating[desk[i].first][desk[i].second].second);
                }
                if (seating[desk[j].first][desk[j].second].first != j) {
                    swap(seating[desk[j].first][desk[j].second].first, seating[desk[j].first][desk[j].second].second);
                }

                swap(seating[desk[j].first][desk[j].second].first, seating[desk[i].first][desk[i].second].first);

                delta += friends[seating[desk[j].first][desk[j].second].first][seating[desk[j].first][desk[j].second].second];
                delta += friends[seating[desk[i].first][desk[i].second].first][seating[desk[i].first][desk[i].second].second];

                swap(seating[desk[j].first][desk[j].second].first, seating[desk[i].first][desk[i].second].first);

                if (delta > 0) {
                    to_swap[o] = make_pair(i, j);
                    o++;
                }
            }
        }
    }
    if (o == 0) {
        if (res > best_res) {
            best_seating = seating;
            best_res = res;
        }
        return;
    }

    int x = rand() % o;
    int i = to_swap[x].first, j = to_swap[x].second;

    res -= friends[seating[desk[j].first][desk[j].second].first][seating[desk[j].first][desk[j].second].second];
    res -= friends[seating[desk[i].first][desk[i].second].first][seating[desk[i].first][desk[i].second].second];

    if (seating[desk[i].first][desk[i].second].first != i) {
        swap(seating[desk[i].first][desk[i].second].first, seating[desk[i].first][desk[i].second].second);
    }
    if (seating[desk[j].first][desk[j].second].first != j) {
        swap(seating[desk[j].first][desk[j].second].first, seating[desk[j].first][desk[j].second].second);
    }

    swap(seating[desk[j].first][desk[j].second].first, seating[desk[i].first][desk[i].second].first);
    swap(desk[i], desk[j]);

    res += friends[seating[desk[j].first][desk[j].second].first][seating[desk[j].first][desk[j].second].second];
    res += friends[seating[desk[i].first][desk[i].second].first][seating[desk[i].first][desk[i].second].second];

    Anneale();
}

void getSeating() {
    while(n < 36) {
        n++;
        name[n] = "Пустое место";
        for (int row = 1; row <= 6; row++) {
            for (int col = 1; col <= 3; col++) {
                seatable[n][row][col] = true;
            }
        }
    }

    if (!getRandomSeating()) {
        while(name[n] == "Пустое место")
            n--;
        cout << "Рассадки, удовлетворяющей вашим требованиям, не существует." << endl;
        return;
    }

    clock_t tim = clock();
    while((double)(clock() - tim) / CLOCKS_PER_SEC < 5.0) {
        Anneale();
        getRandomSeating();
    }

    seating = best_seating;
    cout << "Коэфициент дружбы в рассадке: " << best_res << endl;
}

inline void readData() {
    cout << "Введите название файла с данными." << endl;
    cin >> filename;
    ifstream cin(filename);

    cin >> n;
    if (n > 36) {
        cout << "Слишком много учеников";
        exit(0);
    }
    for (int i = 1; i <= n; i++) {
        cin >> name[i];
        id[name[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> friends[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            friends[i][j] = friends[j][i] = min(friends[i][j], friends[j][i]);
            if (friends[i][j] > 0) {
                friend_mask[i] |= (1 << (j - 1));
                friend_mask[j] |= (1 << (i - 1));
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int row = 1; row <= 6; row++) {
            for (int col = 1; col <= 3; col++) {
                cin >> seatable[i][row][col];
            }
        }
    }
}

signed main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    readData();

    getIndependantGroups();
    getMaxClique();
    getSeating();


    return 0;
}
