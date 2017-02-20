/*
@Copyright:LintCode
@Author:   shizumaru0910
@Problem:  http://www.lintcode.com/problem/ugly-number-ii
@Language: C++
@Datetime: 17-02-18 06:14
*/

class Solution {
public:
    int ins_min(int a, int b, int c){
        int tmp = 0;
        if (a > b) {
            tmp = b;
        } else {
            tmp = a;
        }
        
        if (tmp > c) {
            tmp = c;
        }
        return tmp;
    }
    /*
     * @param n an integer
     * @return the nth prime number as description.
     */
    int nthUglyNumber(int n) {
        // write your code here
        long *slot = NULL;
        int min_v = 0;
        int next_slot = 1;
        int p1 = 0,p2 = 0, p3 = 0;
        
        slot = new long[65535];
        slot[0] = 1;
        while (next_slot < 65535) {
            min_v = ins_min(slot[p1] * 2, slot[p2] * 3, slot[p3] * 5);
            
            slot[next_slot] = min_v;
            while (slot[p1]*2 <= min_v) {
                p1 ++;
            }
            
            while (slot[p2]*3 <= min_v) {
                p2 ++;
            }
            
            while (slot[p3]*5 <= min_v) {
                p3 ++;
            }
            next_slot++;
        }
        return slot[n-1];
    }
};