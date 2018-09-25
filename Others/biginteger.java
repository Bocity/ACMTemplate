// hdu 1402
import java.math.*;
import java.io.*;
import java.util.*;

// 名称最好是Main，类一定要是public
public class Main {
    
    //输入输出挂，只能一整行地读
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    // static BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String []args) throws Exception{
        String temp;
        while((temp = in.readLine()) != null) {
            BigInteger a = new BigInteger(temp);
            BigInteger b = new BigInteger(in.readLine());
            out.write(a.multiply(b).toString());
            out.newLine();
        }
        out.flush();
    }
}

public class Main {
    static Scanner cin=new Scanner (System.in);

    public static void main(String []args) throws Exception{
        String temp;
        while(cin.hasNext()) {
            BigInteger a = cin.nextBigInteger();
            BigInteger b = cin.nextBigInteger(); 
            System.out.println(a.multiply(b));
        }
    }
}

// 大数开方二分
public static BigInteger cal(BigInteger x){
    BigInteger l = BigInteger.ONE ;
    BigInteger r = maxn;
    BigInteger mid;
    while(l.compareTo(r)<=0){
        mid = l.add(r).divide(BigInteger.valueOf(2)) ;
        if (mid.multiply(mid).compareTo(x) <= 0)
          l = mid.add(BigInteger.ONE);
        else r =  mid.subtract(BigInteger.ONE);
    }
    return r;
}   


// 更强的挂（快100ms）
class InputReader{
    BufferedReader buf;
    StringTokenizer tok;
    InputReader(){
        buf = new BufferedReader(new InputStreamReader(System.in));
    }
    boolean hasNext(){
        while(tok == null || !tok.hasMoreElements()){
            try{
                tok = new StringTokenizer(buf.readLine());
            } 
            catch(Exception e){
                return false;
            }
        }
        return true;
    }
    String next()
    {
        if(hasNext()) return tok.nextToken();
        return null;
    }
    int nextInt()
    {
        return Integer.parseInt(next());
    }
    long nextLong()
    {
        return Long.parseLong(next());
    }
    double nextDouble()
    {
        return Double.parseDouble(next());
    }
    BigInteger nextBigInteger()
    {
        return new BigInteger(next());
    }
    BigDecimal nextBigDecimal()
    {
        return new BigDecimal(next());
    }
}
public class Main{
    static InputReader in = new InputReader();
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) throws Exception{
        int t = in.nextInt();
        BigInteger N = in.nextBigInteger();
        out.println("League of Legends");
        out.close();
    }
}

/*

// 读入 

Scanner cin=new Scanner (System.in）
while(cin.hasNext())   //相当于C语言中的！=EOF
n=cin.nextInt();       //输入一个int型整数
n=cin.nextBigInteger();   //输入一个大整数

System.out.print(n);      //输出n但不换行
System.out.println();     //换行
System.out.println(n);    //输出n并换行
System.out.printf(“%d\n”,n);     //类似C语言中的输出


// BigInteger操作

类型转换：
B = BigInteger.valueOf(long);    //把long赋给B；
B = BigInteger(String val,int radix);   //把字符串赋给B，底数为int（默认为10）

S = B.toString(int radix);  //转换成以radix为基数的数（默认为10）
I = B.__Value()   //转换成__类型，可以是int/long/double/float 

输入输出：
n=cin.nextBigInteger();     //输入
System.out.println(n);      //输出并换行

运算：
c = a.abs()         //abs

c=a.add(b)        //把a与b相加并赋给c

c=a.subtract(b)   //把a与b相减并赋给c

c=a.multiply(b)   //把a与b相乘并赋给c

c=a.divide(b)     //把a与b相除并赋给c

c=a.mod(b)        // 相当于a%b

a.pow(int b)          // 相当于a^b, 注意b是int

a.modPow(BigInteger b,BigInteger m)     // a^b % m

a.compareTo(b)：      //根据该数值是小于、等于、或大于a 返回 -1、0 或 1；

a.equals(b)：    //判断两数是否相等，也可以用compareTo来代替；

a.min(b)，a.max(b)：  //取两个数的较小、大者；

a.gcd(b)   //gcd

a.isProbablePrime(int certainty)  //Miller Robin判素数

a.hashcode() // hash码 int


// 位运算
c = a.and(b)        // a&b
c = a.not()        // ~a
c = a.xor(b)        // a^b
c = a.and(b)        // a&b
c = a.andnot(b)        // a& ~b


常量：
A=BigInteger.ONE;   //把1赋给A
A=BigInteger.TEN;   //把10赋给A
A=BigInteger.ZERO;   //把0赋给A


文档：http://tool.oschina.net/apidocs/apidoc?api=jdk-zh


// 范围

布尔型 boolean 1 true,false false

字节型 byte 8 -128-127 0

字符型 char 16 ‘\u000’-\uffff ‘\u0000’

短整型 short 16 -32768-32767 0

整型 int 32 -2147483648,2147483647 0

长整型 long 64 -9.22E18,9.22E18 0

浮点型 float 32 1.4E-45-3.4028E+38 0.0

双精度型 double 64 4.9E-324,1.7977E+308 0.0

BigInteger任意大的数，原则上只要你的计算机内存足够大，可以有无限位


*/

