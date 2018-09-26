// 默慈金数定义：
// 在一个圆上有n个不同的点，画出彼此互不相交弦的方案数（可以不画）即是第n个默慈金数。
//M(n)=((2(n−1)+3)M(n−2)+(3(n−2)+3)M(n−2))/(n+2)
// M(1)=1,M(2)=2 
// 不知道为什么，第n项的默慈金数等于以下的东西： 
// 在一个格子图中，从(0,0)出发，走n步，每次可以往右、右下或右上走，不能走到y=0以下的地方，走到(n,0)的方案数。
import java.math.*;
import java.util.*;
 
public class Main {
	
	public static final int N = 10005;
	public static final BigInteger MOD = BigInteger.valueOf(10).pow(100);
	public static BigInteger ans[] = new BigInteger[N];
	public static void Init(){
		ans[1] = BigInteger.valueOf(1);
		ans[2] = BigInteger.valueOf(2);
		for(int i = 3; i < N; i++){
			BigInteger a = ans[i - 1].multiply((BigInteger.valueOf(2).multiply(BigInteger.valueOf(i)).add(BigInteger.valueOf(1))));
			BigInteger b = ans[i - 2].multiply((BigInteger.valueOf(3).multiply(BigInteger.valueOf(i)).subtract(BigInteger.valueOf(3))));
			ans[i] = (a.add(b)).divide(BigInteger.valueOf(i).add((BigInteger.valueOf(2))));
		}
	}
	
	public static void main(String[] args){
		Init();
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			int n = cin.nextInt();
			System.out.println(ans[n].mod(MOD));
		}
	}
}
