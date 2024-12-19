#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

// Функция для проверки, является ли строка допустимой
bool isValid(const string& s) {
    int count = 0;
    for (char c : s) {
        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
        }
        if (count < 0) {
            return false; // Слишком много закрывающих скобок
        }
    }
    return count == 0; // Проверка на сбалансированность
}

// Функция для удаления недопустимых скобок
vector<string> removeInvalidParentheses(const string& s) {
    int leftRemove = 0, rightRemove = 0;

    // Подсчет количества недопустимых скобок
    for (char c : s) {
        if (c == '(') {
            leftRemove++;
        } else if (c == ')') {
            if (leftRemove > 0) {
                leftRemove--;
            } else {
                rightRemove++;
            }
        }
    }

    unordered_set<string> result;
    queue<string> q;
    q.push(s);
    bool found = false;

    while (!q.empty()) {
        int size = q.size();
        unordered_set<string> currentLevel;

        for (int i = 0; i < size; i++) {
            string current = q.front();
            q.pop();

            if (isValid(current)) {
                result.insert(current);
                found = true;
            }

            if (!found) { // Генерируем новые строки только если еще не нашли допустимую
                for (int j = 0; j < current.size(); j++) {
                    if (current[j] == '(' || current[j] == ')') {
                        string next = current.substr(0, j) + current.substr(j + 1);
                        currentLevel.insert(next);
                    }
                }
            }
        }

        if (!found) { // Обновляем очередь только если не нашли допустимые строки
            for (const auto& str : currentLevel) {
                q.push(str);
            }
        }
    }

    return vector<string>(result.begin(), result.end());
}

int main() {
    string s = "(a)())()";
    vector<string> validStrings = removeInvalidParentheses(s);

    cout << "Допустимые строки: " << endl;
    for (const string& str : validStrings) {
        cout << str << endl;
    }

    return 0;
}
