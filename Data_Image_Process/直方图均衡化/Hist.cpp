#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int src[100][100] = {0};
    int height,width = 0;

    int gray[256] = {0};  //记录每个灰度级别下的像素个数
    double gray_prob[256] = {0};  //记录灰度分布密度
    double gray_distribution[256] = {0};  //记录累计密度
    int gray_new[256] = {0};  //均衡化后的灰度值

    int value;
    cin >> width >> height;
    int sum = width * height;
    //统计每个灰度下的像素个数
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0;j < width ;j++)
        {
            cin >> src[i][j];
            value = src[i][j];
            gray[value]++;
        }
    }

    //统计灰度频率
    for(int i = 0;i < 256;i++)
    {
        gray_prob[i] = ((double)gray[i] / sum);
    }

    //计算累计密度
    gray_distribution[0] = gray_prob[0];
    for(int i = 1 ; i < 256; i++)
    {
        gray_distribution[i] = gray_prob[i] + gray_distribution[i-1];
    }

    //重新计算均衡化后的灰度值，四舍五入
    for(int i = 0;i < 256;i++)
    {
        gray_new[i] = round(gray_distribution[i] * 255);
    }
    for(int i = 0;i < width ;i++)
    {
        for(int j = 0;j < height ; j++)
        {
            src[i][j] = gray_new[src[i][j]];
            cout << src[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}