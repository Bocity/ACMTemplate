#include<bits/stdc++.h>
using namespace std;

#define llp(i,x,y) for(int i=x;i<y;++i) // [x,y) x->y
#define rlp(i,x,y) for(int i=y-1;i>=x;--i)  // [x,y) y->x
#define mem(a,x) memset(a,x,sizeof a)

typedef long long ll;


bool eval(string s, double& num){
  if ( s=="+" || s=="-" || s=="/" || s=="*" || s=="d" || s=="("  || s==")") return false;
  else{
    stringstream ss;
    ss<<s;
    ss>>num;
    return true;
  }
}

stack<char> S;
stack<double> Snum;
map<char,int> prio;
char s[] = "()-+/*";
int pp[] = {0,0,1,1,2,2};

void calcu(char ope){
  int a,b;
  b = Snum.top();
  Snum.pop();
  a = Snum.top();
  Snum.pop();
  double ans = 0;
  switch(ope){
    case '*':
      ans = a*b;
      break;
    case '-':
      ans = a-b;
      break;
    case '+':
      ans = a+b;
      break;
    case '/':
      ans = a/b;
      break;
  }
  Snum.push(ans);
}


string str;
string elem[200];int tot;
void deal(){
  tot = 0;
  int len = str.length();
  string tmp="";
  llp(i,0,len){
    if (str[i]=='-' && (i==0 || str[i-1]=='(' || str[i-1]=='*' ||str[i-1]=='+'||str[i-1]=='-' ) ) tmp += str[i];
    else if (str[i]>='0' && str[i]<='9') tmp += str[i];
    else {
      if (tmp!="") elem[tot++] = tmp;tmp = "";
      elem[tot++] = str[i];
    }
  }
  if (tmp!="") elem[tot++] = tmp;
}

int main(){
  for (int i=0;i<6;++i) prio[s[i]] = pp[i];

  double num;
  while(cin>>str){
    deal();
    cout<<tot<<endl;
    llp(i,0,tot) cout<<elem[i]<<endl;cout<<endl;
    llp(i,0,tot){
      if (eval(elem[i],num)){
        Snum.push(num);
      }
      else{
        char elemc = elem[i][0];
        switch (elemc){
          case '(':
            S.push(elemc);
            break;
          case ')':
            while(!S.empty() && S.top()!='('){
              calcu(S.top());
              S.pop();
            }
            S.pop();
            break;
          default:
            while(!S.empty() && prio[S.top()]>=prio[elemc]){
              calcu(S.top());
              S.pop();
            }
            S.push(elemc);
            break;
        }
      }
    }

    while(!S.empty()){
      calcu(S.top());
      S.pop();
    }

    cout<<Snum.top()<<endl;
    Snum.pop();
  }
}