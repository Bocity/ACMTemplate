/*

// BigInteger操作

输出格式：
去除后导0，并不按科学计数法：
String S = a.stripTrailingZeros().toPlainString());
去除前导0：
if (S.startsWith("0.")) S = S.substring(1, S.length());
控制精度：
a.setScale(0,BigDecimal.ROUND_DOWN));
按科学计数法输出：
？？？


构造：
B = BigDecimal(___);    //可以是double,int,long
B = BigDecimal(BigInteger val);  
B = BigDecimal(BigInteger unscaledVal, int scale);  

B = BigDecimal.valueOf(__);    //把long/double赋给B；

D.stripTrailingZeros().toPlainString(); //去除多余的0，并按文本输出
S = B.toString();  
S = toBigInteger() 
I = B.__Value()   //转换成__类型，可以是int/long/double/float 

输入输出：
n=cin.nextBigDecimal();     //输入
System.out.println(n);      //输出并换行

运算：
c = a.abs()         //abs

c=a.add(b)        //把a与b相加并赋给c

c=a.subtract(b)   //把a与b相减并赋给c

c=a.multiply(b)   //把a与b相乘并赋给c

c=a.divide(b)     //把a与b相除并赋给c

a.pow(int b)          // 相当于a^b, 注意b是int

a.compareTo(b)：      //根据该数值是小于、等于、或大于a 返回 -1、0 或 1；

a.equals(b)：    //判断两数是否相等，也可以用compareTo来代替；

a.min(b)，a.max(b)：  //取两个数的较小、大者；

precision()         //返回精度
scale()             //返回标度
setScale()          //设置标度

// 位运算
c = a.and(b)        // a&b
c = a.not()        // ~a
c = a.xor(b)        // a^b
c = a.and(b)        // a&b
c = a.andnot(b)        // a& ~b


// 保留小数位

BigDecimal.setScale(x,___)  //x表示精度，__表示取整模式（默认四舍五入）

ROUND_CEILING 向正无穷方向舍入 

ROUND_FLOOR 向负无穷方向舍入 

ROUND_DOWN  向零方向舍入 

ROUND_UP  向远离0的方向舍入


ROUND_HALF_DOWN 
向（距离）最近的一边舍入，除非两边（的距离）是相等,如果是这样，向下舍入, 例如1.55 保留一位小数结果为1.5 

ROUND_HALF_UP 
向（距离）最近的一边舍入，除非两边（的距离）是相等,如果是这样，向上舍入, 1.55保留一位小数结果为1.6 

ROUND_HALF_EVEN 
向（距离）最近的一边舍入，除非两边（的距离）是相等,如果是这样，如果保留位数是奇数，使用ROUND_HALF_UP ，如果是偶数，使用ROUND_HALF_DOWN 


ROUND_UNNECESSARY 
计算结果是精确的，不需要舍入模式 



文档：http://tool.oschina.net/apidocs/apidoc?api=jdk-zh

*/