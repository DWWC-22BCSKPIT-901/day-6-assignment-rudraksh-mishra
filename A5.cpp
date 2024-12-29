#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<vector<int>> adj_list;
    vector<vector<int>> char_counts;
    int n;
    
    void build_adjacency_list(vector<int>& parent) {
        adj_list.resize(n);
        for (int i = 1; i < n; i++) {
            adj_list[parent[i]].push_back(i);
            adj_list[i].push_back(parent[i]);
        }
    }
    
    bool can_form_palindrome(const vector<int>& count_a, const vector<int>& count_b) {
        vector<int> diff(26, 0);
        for (int i = 0; i < 26; i++) {
            diff[i] = abs(count_a[i] - count_b[i]);
        }
        
        int odd_count = 0;
        for (int d : diff) {
            if (d % 2 == 1) odd_count++;
        }
        
        return odd_count <= 1;
    }
    
    void compute_char_counts(int node, int parent, string& s) {
        char_counts[node] = vector<int>(26, 0);
        
        if (parent != -1) {
            char_counts[node][s[node] - 'a']++;
        }
        
        for (int child : adj_list[node]) {
            if (child != parent) {
                compute_char_counts(child, node, s);
                for (int i = 0; i < 26; i++) {
                    char_counts[node][i] += char_counts[child][i];
                }
            }
        }
    }
    
    vector<int> get_path_counts(int u, int v, vector<int>& parent) {
        vector<int> path_counts(26, 0);
        vector<bool> u_path(n, false);
        int curr = u;
        while (curr != -1) {
            u_path[curr] = true;
            if (curr != u) {
                path_counts[s[curr] - 'a']++;
            }
            curr = parent[curr];
        }
        
        curr = v;
        while (curr != -1 && !u_path[curr]) {
            path_counts[s[curr] - 'a']++;
            curr = parent[curr];
        }
        
        return path_counts;
    }

public:
    int count_palindrome_paths(vector<int>& parent, string s) {
        n = parent.size();
        this->s = s;
        build_adjacency_list(parent);
        
        char_counts.resize(n);
        compute_char_counts(0, -1, s);
        
        int result = 0;
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                vector<int> path_counts = get_path_counts(u, v, parent);
                if (can_form_palindrome(path_counts, vector<int>(26, 0))) {
                    result++;
                }
            }
        }
        
        return result;
    }
    
private:
    string s;
};

void test_case(vector<int> parent, string s, int expected) {
    Solution solution;
    int result = solution.count_palindrome_paths(parent, s);
    cout << "Input: parent = [";
    for (int i = 0; i < parent.size(); i++) {
        if (i > 0) cout << ",";
        cout << parent[i];
    }
    cout << "], s = \"" << s << "\"" << endl;
    cout << "Output: " << result << endl;
    cout << "Expected: " << expected << endl;
    cout << "Result: " << (result == expected ? "PASS" : "FAIL") << endl;
    cout << "-------------------" << endl;
}

int main() {
    test_case({-1,0,0,1,1,2}, "abacbe", 3);
    test_case({-1,0,0,0}, "aabc", 2);
    test_case({-1}, "z", 0);
    return 0;
}
