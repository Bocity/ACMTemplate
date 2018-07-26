//随机数     
mt19937 mt_rand(time(0));
mt_rand()  随机范围 int 循环节 2^19937
//rope 不支持一切数值操作
#include <ext/rope>
using namespace __gnu_cxx;
rope<char> t;
append(string &s,int pos,int n) // 把字符串s中从下标pos开始的n个字符连接到rope的结尾，如没有参数n则把字符串s中下标pos后的所有字符连接到rope的结尾，如没有参数pos则把整个字符串s连接到rope的结尾
t.push_back(x)	//在末尾添加x
t.insert(pos,x)	//在pos插入x
t.erase(pos,x)	//从pos开始删除x个
t.replace(pos,x)	//从pos开始换成x
t.substr(pos,x)	//提取pos开始x个
t.at(x)/[x]	//访问第x个元素
//rope支持operator += -= + - < ==
//length()，size()都可以哦
//可以用<<运算符由输入输出流读入或输出。