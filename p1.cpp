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

int main() {
    int i;
    string input;
    vector<vector<int>> intSequence;
    vector<int> result;

    cin >> i;
    intSequence = getIntSequence(i);
    
    if (i == 1) {
        result = lis(intSequence[0]);
        cout << result[0] << ' ' << result[1] << endl;
    }

    return 0;
}