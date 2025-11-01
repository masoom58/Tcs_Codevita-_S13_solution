#include <bits/stdc++.h>
using namespace std;

int LIS_Length(vector<int>& seq) {
    vector<int> lis;
    for (int x : seq) {
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end())
            lis.push_back(x);
        else
            *it = x;
    }
    return lis.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    string temp;
    getline(cin, temp);

    getline(cin, temp);

    vector<string> shuffled(N);
    for (int i = 0; i < N; i++)
        getline(cin, shuffled[i]);

    getline(cin, temp);

    vector<string> original(N);
    for (int i = 0; i < N; i++)
        getline(cin, original[i]);

    unordered_map<string, int> pos;
    for (int i = 0; i < N; i++)
        pos[original[i]] = i;

    vector<int> order;
    for (auto &line : shuffled)
        order.push_back(pos[line]);

    int lis_len = LIS_Length(order);
    cout << (N - lis_len) << "\n";

    return 0;
}
