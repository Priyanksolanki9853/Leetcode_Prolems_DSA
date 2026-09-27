class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        st.push(""); 

        for (char c : s) {
            if (c == '(') {
                st.push(""); 
            } else if (c == ')') {
                string top = st.top();
                st.pop();
                reverse(top.begin(), top.end());
                st.top() += top; 
            } else {
                st.top() += c;
            }
        }

        return st.top();
    }
};