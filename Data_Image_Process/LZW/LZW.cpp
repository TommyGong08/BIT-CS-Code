#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
using namespace std;

void compress(vector<string> raw_data,vector<int>& ans)
{
    int dict_size = 256;
    map<string,int> dictionary;
    for(int i = 0 ; i < 256 ; i++){
        dictionary[to_string(i)] = i;
        //cout << dictionary[string(1,i)] << " " ;
    }
    string p = ""; //初始化s为空
    for(int i = 0; i < raw_data.size() ;i++)
    {
        string c = raw_data[i];//获取每一个像素点的值
        string pc;
        if(p=="") pc = p + c;
        else pc = p + "-" + c;
        //如果该字符串已经在字典中存在了

        //cout << i << "    " <<  p << "    " << c << "    " << pc << "    " << dictionary.count(pc) << endl; 
        if(dictionary.count(pc))
        {
            p = pc;
        }
        //如果该字符串在字典中不存在
        else
        {
            dictionary[pc] = dict_size;
            dict_size++;
            ans.push_back(dictionary[p]);
            p = c;
        }
        //cout << i << "    " <<  p << "    " << c << "    " << pc << "    " << dictionary.count(pc) << endl; 
    }

    //输出压缩结果
    if(!p.empty())
    {
        ans.push_back(dictionary[p]);
    }
}

int main()
{
    int n,m = 0;

    //输入m行n列
    cin >> m >> n;
    vector<string> raw_data;
    int temp_int;
    string temp_string;
    //将原始数据存进raw_data数组中
    for(int i = 0 ; i < m ; i++){
        for(int j = 0; j < n ; j++ ){
            cin >> temp_int;
            temp_string = to_string(temp_int);
            raw_data.push_back(temp_string);
        }
    }

    vector<int> ans;
    compress(raw_data , ans);
    
    for(int i=0 ; i < ans.size()-1 ; i++ )
    {
        cout << ans[i] << " ";
    }
    cout << ans[ans.size()-1] << endl;
    return 0;
}