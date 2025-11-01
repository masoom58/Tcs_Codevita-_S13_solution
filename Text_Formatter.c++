#include <bits/stdc++.h>
using namespace std;

bool isEmailOrURL(const string &word) {
    return word.find('@') != string::npos || 
           word.rfind("http://", 0) == 0 || 
           word.rfind("https://", 0) == 0;
}

bool isBullet(const string &word) {
    if (word == "*" || word == "-") return true;
    if (word.size() >= 2 && isdigit(word[0]) && (word[1] == '.' || word[1] == ')')) return true;
    return false;
}

vector<string> splitWords(const string &line) {
    vector<string> words;
    string word;
    for (char c : line) {
        if (isspace(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else word += c;
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

vector<vector<string>> splitParagraphs(const vector<string> &lines) {
    vector<vector<string>> paragraphs;
    vector<string> current;
    for (auto &line : lines) {
        if (line.empty()) {
            if (!current.empty()) {
                paragraphs.push_back(current);
                current.clear();
            }
        } else current.push_back(line);
    }
    if (!current.empty()) paragraphs.push_back(current);
    return paragraphs;
}

void wrapAndPrint(vector<string> words, int wEven, int wOdd, bool hyphen, int &lineIndex) {
    string line;
    int width;
    for (int i = 0; i < (int)words.size();) {
        width = (lineIndex % 2 == 0 ? wEven : wOdd);
        line.clear();
        int len = 0;
        while (i < (int)words.size()) {
            string word = words[i];
            int wl = word.size();
            if (len == 0) {
                if (wl <= width) {
                    line = word;
                    len = wl;
                    i++;
                } else {
                    if (isEmailOrURL(word)) {
                        cout << word << "\n";
                        lineIndex++;
                        i++;
                    } else if (hyphen && wl > 1) {
                        int cut = width - 1;
                        cout << word.substr(0, cut) << "-" << "\n";
                        words[i] = word.substr(cut);
                        lineIndex++;
                    } else {
                        cout << word << "\n";
                        lineIndex++;
                        i++;
                    }
                }
            } else {
                if (len + 1 + wl <= width) {
                    line += " " + word;
                    len += 1 + wl;
                    i++;
                } else {
                    if (isEmailOrURL(word)) break;
                    else if (hyphen && wl > 1 && wl > width - len - 1) {
                        int spaceLeft = width - len - 1;
                        if (spaceLeft > 1) {
                            line += " " + word.substr(0, spaceLeft - 1) + "-";
                            words[i] = word.substr(spaceLeft - 1);
                            break;
                        } else break;
                    } else break;
                }
            }
        }
        cout << line << "\n";
        lineIndex++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cin.ignore();
    vector<string> lines(N);
    for (int i = 0; i < N; i++) {
        string temp;
        getline(cin, temp);
        while (!temp.empty() && isspace(temp.back())) temp.pop_back();
        int start = 0;
        while (start < (int)temp.size() && isspace(temp[start])) start++;
        temp = temp.substr(start);
        lines[i] = temp;
    }
    string command;
    getline(cin, command);
    int wEven = 75, wOdd = 75;
    bool hyphen = false;
    vector<string> parts = splitWords(command);
    for (int i = 0; i < (int)parts.size(); i++) {
        if (parts[i] == "-w" && i + 1 < (int)parts.size()) wEven = wOdd = stoi(parts[i + 1]);
        else if (parts[i] == "-w-e" && i + 1 < (int)parts.size()) wEven = stoi(parts[i + 1]);
        else if (parts[i] == "-w-o" && i + 1 < (int)parts.size()) wOdd = stoi(parts[i + 1]);
        else if (parts[i] == "h") hyphen = true;
    }
    vector<vector<string>> paragraphs = splitParagraphs(lines);
    int lineIndex = 0;
    for (int p = 0; p < (int)paragraphs.size(); p++) {
        vector<string> words;
        for (auto &line : paragraphs[p]) {
            vector<string> w = splitWords(line);
            for (auto &x : w) {
                if (isBullet(x) && !words.empty()) {
                    wrapAndPrint(words, wEven, wOdd, hyphen, lineIndex);
                    words.clear();
                }
                words.push_back(x);
            }
        }
        if (!words.empty()) wrapAndPrint(words, wEven, wOdd, hyphen, lineIndex);
        if (p != (int)paragraphs.size() - 1) cout << "\n";
    }
    return 0;
}
