```
@Copyright:LintCode
@Author:   shizumaru0910
@Problem:  http://www.lintcode.com/problem/roman-to-integer
@Language: Markdown
@Datetime: 17-02-20 21:01
```

核心思想： 查表
按照规则处理即可。注意这里没有列举加下划线的情况。
-- 映射表：
V = 5
X = 10
L = 50
C = 100
D = 500
M = 1000

-- 计算规则：
相同的数字连写，表示将这些数字相加。
小的数字写在大的数字右边，表示这这个数字相加。
大的数字写在小的数字右边，表示用大的数字减去小的数字。