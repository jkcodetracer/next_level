/*
@Copyright:LintCode
@Author:   shizumaru0910
@Problem:  http://www.lintcode.com/problem/roman-to-integer
@Language: C++
@Datetime: 17-02-20 21:01
*/

class Solution {
public:
    /**
     * @param s Roman representation
     * @return an integer
     */
    int romanToInt(string& s) {
        // Write your code here
        int i, prev, cur;
        int sum = 0;
        
        prev = 0;
        cur = 0;
        for (i = 0; i < s.length(); i++) {
             cur = value_map(s[i]);
             sum += cur;
             if (cur > prev) {
                 sum -= 2*prev;
             }
             prev = cur;
        }
        return sum;
    }
    
    int value_map(char chr){
        char ctable[] = {'I','X','C','M','V','L','D'};
        int vtable[] = {1, 10, 100, 1000, 5, 50, 500};
        int i;
        
        for (i = 0; i < sizeof(ctable)/sizeof(char); i++){
            if (chr == ctable[i])
                break;
        }
        return vtable[i];
    }
};