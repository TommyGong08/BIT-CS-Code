#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
    int height , width = 0;
    int height_B,width_B = 0;
    //输入图像的长宽
    cin >> height >> width;
    //输入结构化元素的长宽(只可能为奇数)
    cin >> height_B >> width_B;
    int src[100][100] = {0};
    int temp_src[100][100] = {0};
    for(int i = 0;i < height; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            cin >> src[i][j];
            temp_src[i][j] = src[i][j];
        }
    } 
    cout << width_B/2 << " " << height_B/2 << endl;
    int flag;
    for(int i = 0 ;i < height; i++)
    {
        for(int j = 0 ;j < width;j++)
        {
            flag = 1;
            for(int m = i - height_B/2 ;m < i + height_B/2 + 1 ; m++)
            {
                for(int n = j - width_B/2; n < j + width_B/2 + 1 ; n++)
                {
                    if(m < 0 || n < 0 || m >=height || n >= width) continue;
                    //自身及领域中若有一个为0
                    //则将该点设为0
                    if(temp_src[i][j] !=0 || temp_src[m][n] !=0)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0)
                {
                    break;
                }
            }
            if(flag == 0)
            {
                src[i][j] = 255;
            }
            else
            {
                src[i][j] = 0;
            }
        }
    }
    for(int i = 0;i < height; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            if(src[i][j] == 1) src[i][j] = 255;
            cout <<  src[i][j] << " ";
        }
        cout << endl;
    } 
    return 0;
}
