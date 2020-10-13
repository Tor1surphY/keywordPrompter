#include "../../include/query_offline/queryImplement.hpp"

#include <set>
#include <algorithm>

using std::pair;
using std::min;
using std::set;
using std::greater;

namespace ty
{

string QueryImplement::promote() {
    set<char> cha;
    for(auto& c : _word) {
        cha.insert(c);
    }

    int standard_distance;
    if(_word.size() <= 2) {
        standard_distance = _word.size();
    }
    else {
        standard_distance = 3;
    }

    set<pair<int, string>, greater<pair<int, string>>> result_set;
    int shortest_edit_distance;
    for(auto& c : cha) {
        for(auto& word_to_compute : _p_text_query->_idx[c]) {
            shortest_edit_distance = shortestEditDistance(word_to_compute, _word);
            if(shortest_edit_distance <= standard_distance) {
                result_set.insert({shortest_edit_distance, word_to_compute});
            }
        }
    }

    Json::Value rsl;
    if(result_set.empty()) {
        rsl["answer"].append("no matching words found");
        return rsl.toStyledString();
    }

    for(int i = 0; i < 5; ++i) {
        if(result_set.empty()) break;
        rsl["answer"].append((*result_set.begin()).second);
        result_set.erase(result_set.begin());
    }
    return rsl.toStyledString();
}

int QueryImplement::shortestEditDistance(string& word1, string& word2) {
    int n = word1.length();
    int m = word2.length();

    if (n * m == 0) return n + m;
    int D[n + 1][m + 1];

    for (int i = 0; i < n + 1; i++) {
        D[i][0] = i;
    }
    for (int j = 0; j < m + 1; j++) {
        D[0][j] = j;
    }
    
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            int left = D[i - 1][j] + 1;
            int down = D[i][j - 1] + 1;
            int left_down = D[i - 1][j - 1];
            if (word1[i - 1] != word2[j - 1]) left_down += 1;
            D[i][j] = min(left, min(down, left_down));
        }
    }
    return D[n][m];
}
} // end of namespace ty