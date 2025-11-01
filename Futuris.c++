#include <bits/stdc++.h>
using namespace std;

struct VarData {
    map<string, int> vars;
};

int getValue(string s, VarData &data) {
    if (isdigit(s[0]) || (s[0] == '-' && s.size() > 1)) return stoi(s);
    return data.vars[s];
}

bool evalCondition(string cond, VarData &data) {
    string a, op, b;
    stringstream ss(cond);
    ss >> a >> op >> b;
    int x = getValue(a, data);
    int y = getValue(b, data);
    if (op == "==") return x == y;
    if (op == "!=") return x != y;
    if (op == "<") return x < y;
    if (op == ">") return x > y;
    return false;
}

void execute(vector<string> &code, int &i, VarData &data) {
    while (i < code.size()) {
        string line = code[i];
        if (line == "end") return;
        vector<string> parts;
        stringstream ss(line);
        string word;
        while (ss >> word) parts.push_back(word);

        if (parts[0] == "print") {
            string val = parts[1];
            if (isdigit(val[0]) || (val[0] == '-' && val.size() > 1))
                cout << val << endl;
            else
                cout << data.vars[val] << endl;
            i++;
        } 
        else if (parts[0] == "if") {
            string cond = line.substr(3);
            i++;
            bool res = evalCondition(cond, data);
            if (res) {
                if (i < code.size() && code[i] == "Yes") i++;
                execute(code, i, data);
                if (i < code.size() && code[i] == "No") {
                    int depth = 1;
                    i++;
                    while (i < code.size() && depth > 0) {
                        if (code[i] == "if" || code[i].rfind("for ", 0) == 0) depth++;
                        else if (code[i] == "end") depth--;
                        i++;
                    }
                }
            } else {
                int depth = 0;
                while (i < code.size()) {
                    if (code[i] == "Yes") {
                        depth = 1;
                        i++;
                        while (i < code.size() && depth > 0) {
                            if (code[i] == "if" || code[i].rfind("for ", 0) == 0) depth++;
                            else if (code[i] == "end") depth--;
                            i++;
                        }
                    } else if (code[i] == "No") {
                        i++;
                        execute(code, i, data);
                        break;
                    } else i++;
                }
            }
        } 
        else if (parts[0] == "for") {
            string var = parts[1];
            int start = getValue(parts[2], data);
            int endVal = getValue(parts[3], data);
            i++;
            vector<string> inner;
            int startIdx = i;
            int depth = 1;
            while (i < code.size() && depth > 0) {
                if (code[i].rfind("for ", 0) == 0 || code[i].rfind("if ", 0) == 0) depth++;
                else if (code[i] == "end") depth--;
                if (depth > 0) inner.push_back(code[i]);
                i++;
            }
            for (int k = start; k <= endVal; k++) {
                data.vars[var] = k;
                int temp = 0;
                execute(inner, temp, data);
            }
        } 
        else i++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> lines;
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) continue;
        lines.push_back(line);
        if (line.find(' ') == string::npos && all_of(line.begin(), line.end(), ::isupper)) break;
    }
    vector<string> varNames;
    stringstream ss(lines.back());
    string var;
    while (ss >> var) varNames.push_back(var);
    vector<int> values;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss2(line);
        int v;
        while (ss2 >> v) values.push_back(v);
        break;
    }
    VarData data;
    for (int i = 0; i < varNames.size(); i++) data.vars[varNames[i]] = values[i];
    lines.pop_back();
    int idx = 0;
    execute(lines, idx, data);
    return 0;
}
