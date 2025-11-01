#include <bits/stdc++.h>
using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> visited(n, vector<int>(m, 0));
    auto isValid = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    int switches = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] == 'C') {
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = 1;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (isValid(nx, ny) && !visited[nx][ny]) {
                            if (grid[nx][ny] == 'C') {
                                visited[nx][ny] = 1;
                                q.push({nx, ny});
                            } else if (grid[nx][ny] == 'R') {
                                switches++;
                                visited[nx][ny] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << switches << "\n";
    return 0;
}
