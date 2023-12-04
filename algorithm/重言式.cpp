#include<iostream>
#include<map>
#include<vector>
#include<stack>
#include<string>
using namespace std;

int p,q,r,s,t;


inline bool in(char c,stack<int>&stk)
{
    switch(c)
    {
        case 'p':stk.push(p);break;
        case 'q':stk.push(q);break;
        case 'r':stk.push(r);break;
        case 's':stk.push(s);break;
        case 't':stk.push(t);break;
        default: return false;
    }
    return true;
}

inline void work(char c,stack<int>&stk)
{
    switch (c)
    {
    case 'K':
        {/* code */
        int a=stk.top();
        stk.pop();
        int b=stk.top();
        stk.pop();
        stk.push(a&&b);
        break;        
        }
    case 'A':
        {
            int a=stk.top();
            stk.pop();
            int b=stk.top();
            stk.pop();
            stk.push(a||b);
            break;
        }
    case 'N':
        {
            int a=stk.top();
            stk.pop();;
            stk.push(!a);
            break;
        }
    case 'C':
    {
        int a=stk.top();
            stk.pop();
            int b=stk.top();
            stk.pop();
            stk.push(!a||b);
            break;
    }

    case 'E':
    {
        int a=stk.top();
            stk.pop();
            int b=stk.top();
            stk.pop();
            stk.push(a==b);
            break;
    }

    default:
        return;
    }

}

int main(void)
{
    stack<int>stk;
    string input;
    vector<int> ans;
    while(cin>>input&&input[0]!='0')
    {
        // int flag{1};
        for(p=0;p<2;++p)
            for(q=0;q<2;++q)
                for(r=0;r<2;++r)
                    for(s=0;s<2;++s)
                        for(t=0;t<2;++t){
                            for(int i=input.size()-1;i>-1;--i)
                            {
                                if(!in(input[i],stk))
                                    work(input[i],stk);
                            }
                            if(!stk.top())
                            {
                                ans.push_back(0);
                                goto over;
                             
                            }
                            stk.pop();
                        }
            ans.push_back(1);
            over: int a=0; 
        
    }
    for(int j=0;j<ans.size();++j)
        {
            if(ans[j])
            cout<<"tautology\n";
            else
            cout<<"not\n";
        }


    return 0;
}