class Solution {
public:
    string expr_str;
    int pos;

    vector<string> braceExpansionII(string expression) {
        expr_str = expression;
        pos = 0;
        set<string> result = expr();
        return vector<string>(result.begin(), result.end()); // sets are already sorted
    }

private:
    // expr := term (',' term)*  -- union of terms
    set<string> expr() {
        set<string> result = term();
        while (pos < expr_str.size() && expr_str[pos] == ',') {
            pos++; // skip ','
            set<string> other = term();
            result.insert(other.begin(), other.end());
        }
        return result;
    }

    // term := factor+  -- Cartesian product (concatenation) of factors
    set<string> term() {
        set<string> result = {""};
        while (pos < expr_str.size() && expr_str[pos] != ',' && expr_str[pos] != '}') {
            set<string> cur = factor();
            set<string> product;
            for (const string& a : result) {
                for (const string& b : cur) {
                    product.insert(a + b);
                }
            }
            result = product;
        }
        return result;
    }

    // factor := letter+ | '{' expr '}'
    set<string> factor() {
        if (expr_str[pos] == '{') {
            pos++; // skip '{'
            set<string> result = expr();
            pos++; // skip '}'
            return result;
        } else {
            int start = pos;
            while (pos < expr_str.size() && islower(expr_str[pos])) {
                pos++;
            }
            return {expr_str.substr(start, pos - start)};
        }
    }
};