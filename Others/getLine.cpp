//https://www.cnblogs.com/xkfz007/archive/2012/08/01/2618366.html
// https://www.cnblogs.com/AlvinZH/p/6798023.html

string str;
getline(cin,str,'\n') //扔掉换行.在string头文件中. 


char s[200];
cin.getline(s,100,'\n'); //扔掉换行

getchar();//gets会读上一行(scanf等)的换行，只要用一次
gets(s);//扔掉换行

scanf("%[^\n]",&s);  //忽略换行，但不扔掉，需要手动扔掉
getchar();

//将一行字符串转换为数组
// https://www.cnblogs.com/TenosDoIt/p/3724234.html


string str;
int a[100];
while(getline(cin,str,'\n')){
  istringstream iss(str);
  int num,cnt=0;
  while(iss >> num){
    a[cnt++] = num;
  }
}
