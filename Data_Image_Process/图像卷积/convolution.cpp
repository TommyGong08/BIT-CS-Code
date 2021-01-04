#include<iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<cmath>
using namespace std;
int photo[2000][2000];
double kernel[500][500];
int round_double(double number)
{
    return (number > 0.0) ? (number + 0.5) : (number - 0.5); 
}

int main()
{
    //freopen("1.txt","r",stdin);
    int m , n ;
    int u , v ,mid_u,mid_v;
    cin >> m >> n ;//图像长宽
    cin >> u >> v ;//卷积核长宽
    mid_u =  u/2 ;
    mid_v =  v/2 ;
    for(int i = 0; i < m ;i++)
    {
        for(int j = 0 ; j < n ;j++ )
        {
            cin >> photo[i][j];
        }
    }
    for(int i = 0; i < u; i++)
    {
        for(int j = 0 ; j < v ;j++)
        {
            cin >> kernel[i][j];
        }
    }
    double sum;
    //对每一行每一列进行卷积运算
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0;j < n;j++)
        {
            sum = 0;
            for(int k = 0;k < u; k++)
            {
                for(int l = 0;l < v;l++)
                {
                    if((i + k - mid_u) < 0 || (j + l - mid_v) < 0 ||(i + k - mid_u) > m ||(j + l - mid_v) > n) 
                    {
                        continue;
                    }
                    else
                    {
                        sum += photo[i + k - mid_u][j + l - mid_v] * kernel[k][l];
                    }
                }
            }
            cout << round_double(sum)  << " ";
        }
        cout << endl;
    }
    return 0;
}