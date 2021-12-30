#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> getIntSequence(int i) {
    int number;
    string input;
    vector<vector<int>> v(i, vector<int>());

    getline(cin, input);
    for(int j = 0; j < i; j++) {
        getline(cin, input);
        stringstream stream(input);

        while (stream >> number) {
            v[j].push_back(number);
        }
    }

    return v;
}

// NÃO USAR USING NAMESPACE STD (malpratica)

vector<int> lis(vector<int> v) {
    size_t n = v.size();
    vector<int> s(n, 1);
    vector<int> c(n, 1);
    int max = 1, count;

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (v[j] < v[i]) {
                if (s[i] < 1 + s[j]) {
                    s[i] = 1 + s[j];
                    c[i] = c[j];
                    if (s[i] > max) {
                        max = s[i];
                        count = 0;
                    }
                }
                else if (s[i] == 1 + s[j]) {
                    c[i] += c[j];
                }
            } 
        }
    }

    for (size_t i = 0; i < n; i++) {
        if(s[i] == max) {
            count += c[i];
        }
    }

    return {max, count};
}

int lics(vector<int> v1, vector<int> v2) {
    size_t i, j, n = v1.size(), m = v2.size();
    vector<vector<int>> s(n+1, vector<int>(m+1, 0));
    
    for (i = 1; i <= n; i++) {
        int current_sequence = 0;
        for (j = 1; j <= m; j++) {
            if (v1[i-1] == v2[j-1]) {
                if (current_sequence + 1 > s[i-1][j]) {
                    s[i][j] = current_sequence + 1;
                } else {
                    s[i][j] = s[i-1][j];
                }
            } else if (v1[i-1] > v2[j-1]) {
                if (s[i-1][j] > current_sequence) {
                    current_sequence = s[i-1][j];
                }
                s[i][j] = s[i-1][j];
            } else {
                s[i][j] = s[i-1][j];
            }
        }
    }
    int length = 0;
    i = n;
    for (j = 0; j <= m; j++) {
        if (s[i][j] > length)
            length = s[i][j];
    }
    return length;
}

int main() {
    int i;
    string input;
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