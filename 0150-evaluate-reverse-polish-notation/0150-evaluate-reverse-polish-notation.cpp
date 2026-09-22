class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for(const string& token : tokens){
            if(token=="+"||token=="-"||token=="*"||token=="/"){
                long long b = st.top();
                st.pop();
                long long a = st.top();
                st.pop();
                long long result;

                if (token == "+") result = a + b;
                else if (token == "-") result = a - b;
                else if (token == "*") result = a * b;
                else result=a/b;

                st.push(result);
                
            }else{
                st.push(stoll(token));
            }
        }
         return (int)st.top();
    }
}; 