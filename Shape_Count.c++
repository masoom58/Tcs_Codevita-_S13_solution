#include <bits/stdc++.h>
using namespace std;

struct Line {
    int x1, y1, x2, y2;
};

int main() {
    int n;
    cin >> n;
    vector<Line> lines(n);
    for (int i = 0; i < n; i++) cin >> lines[i].x1 >> lines[i].y1 >> lines[i].x2 >> lines[i].y2;

    vector<Line> horizontal, vertical;
    for (auto &l : lines) {
        if (l.y1 == l.y2) {
            if (l.x1 > l.x2) swap(l.x1, l.x2);
            horizontal.push_back(l);
        } else if (l.x1 == l.x2) {
            if (l.y1 > l.y2) swap(l.y1, l.y2);
            vertical.push_back(l);
        }
    }

    long long total = 0;

    for (int i = 0; i < horizontal.size(); i++) {
        for (int j = i + 1; j < horizontal.size(); j++) {
            int y_top = horizontal[i].y1;
            int y_bottom = horizontal[j].y1;
            if (y_top == y_bottom) continue;

            vector<int> intersectingX;
            for (auto &v : vertical) {
                if (v.y1 <= y_top && v.y2 >= y_top && v.y1 <= y_bottom && v.y2 >= y_bottom) {
                    int vx = v.x1;
                    int x1_min = min(horizontal[i].x1, horizontal[j].x1);
                    int x1_max = max(horizontal[i].x2, horizontal[j].x2);
                    if (vx >= horizontal[i].x1 && vx <= horizontal[i].x2 && vx >= horizontal[j].x1 && vx <= horizontal[j].x2)
                        intersectingX.push_back(vx);
                }
            }

            int k = intersectingX.size();
            if (k >= 2) total += (long long)k * (k - 1) / 2;
        }
    }

    cout << total;
    return 0;
}
