#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<vector<int>> getIntSequence(int i) {
    int number;
    string input;
    unordered_set<int> vector1;
    vector<vector<int>> v(i, vector<int>());

    getline(cin, input);
    for(int j = 0; j < i; j++) {
        getline(cin, input);
        stringstream stream(input);
        while (stream >> number) {
            if (j == 1) {
                if (vector1.find(number) != vector1.end()) {
                    v[j].push_back(number);
                }
            } else {
                v[j].push_back(number);
                vector1.insert(number);
            }
        }
    }

    return v;
}

// NÃO USAR USING NAMESPACE STD (malpratica)

vector<int> lis(vector<int> v) {
    size_t n = v.size();
    vector<int> s(n, 1);
    vector<int> c(n, 1);

    vector<int> max_i(1, 0); 
    vector<int> max_val(1, v[0]);
    vector<int> max_i_temp(1, 0);
    vector<int> max_val_temp(1, 0);
    int max = 1; 
    int count = 0;
    bool continued_from_max;
    bool set_max;

    for (size_t i = 1; i < n; i++) {
        continued_from_max = false;
        set_max = false;
        max_i_temp.clear();
        max_val_temp.clear();
        for (size_t j = 0; j < max_val.size(); j++) {
            if (max_val[j] < v[i]) {
                continued_from_max = true;
                if (s[i] < 1 + s[max_i[j]]) {
                    s[i] = 1 + s[max_i[j]];
                    c[i] = c[max_i[j]];
                    if (s[i] > max) {
                        max = s[i];
                        max_i_temp.push_back(i);
                        max_val_temp.push_back(v[i]);
                        set_max = true;
                    }
                }
                else if (s[i] == 1 + s[max_i[j]]) {
                    c[i] += c[max_i[j]];
                }
            }
        }
        if (continued_from_max) {
            max_i = max_i_temp;
            max_val = max_val_temp;
        }
        else {
            for (size_t j = 0; j < i; j++) {
                if (v[j] < v[i]) {
                    if (s[i] < 1 + s[j]) {
                        s[i] = 1 + s[j];
                        c[i] = c[j];
                        if (s[i] > max) {
                            max = s[i];
                            max_i.clear();
                            max_val.clear();
                            max_i.push_back(i);
                            max_val.push_back(v[i]);
                            set_max = true;
                        }
                    }
                    else if (s[i] == 1 + s[j]) {
                        c[i] += c[j];
                    }
                } 
            }
            if (s[i] == max && !set_max) {
                max_i.push_back(i);
                max_val.push_back(v[i]);
            }
        }
    }

    for (size_t i = 0; i < max_i.size(); i++) {
        count += c[max_i[i]];
    }

    return {max, count};
}

int lics(vector<int> v1, vector<int> v2) {
    size_t i, j, n = v1.size(), m = v2.size();
    vector<int> s(m, 0);
    
    for (i = 0; i < n; i++) {
        int current_sequence = 0;
        for (j = 0; j < m; j++) {
            if (v1[i] == v2[j]) {
                if (current_sequence + 1 > s[j])
                    s[j] = current_sequence + 1;
            } else if (v1[i] > v2[j]) {
                if (s[j] > current_sequence)
                    current_sequence = s[j];
            }
        }
    }
    int length = 0;
    for (i = 0; i < m; i++) {
        if (s[i] > length)
            length = s[i];
    }
    return length;
}

int main() {
    int i;
    vector<vector<int>> intSequence;

    cin >> i;
    intSequence = getIntSequence(i);
    
    if (i == 1) {
        vector<int> result;
        result = lis(intSequence[0]);
        cout << result[0] << ' ' << result[1] << endl;
    }

    if (i == 2) {
        int result;
        result = lics(intSequence[0], intSequence[1]);
        cout << result << endl;
    }

    return 0;
}