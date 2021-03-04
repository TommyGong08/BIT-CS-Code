#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
    int height , width = 0;
    int height_B,width_B = 0;
    //����ͼ��ĳ���
    cin >> height >> width;
    //����ṹ��Ԫ�صĳ���(ֻ����Ϊ����)
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
    for(int i = height_B/2 ;i < height - height_B/2 ; i++)
    {
        for(int j = width_B/2 ;j < width - width_B/2 ;j++)
        {
            flag = 1;
            //3*3�Ľṹ
            for(int m = i - height_B/2 ;m < i + height_B/2 + 1 ; m++)
            {
                for(int n = j - width_B/2; n < j + width_B/2 + 1 ; n++)
                {
                    if(temp_src[i][j] == 0 || temp_src[m][n] == 0)
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
                src[i][j] = 0;
            }
            else
            {
                src[i][j] = 255;
            }
        }
    }
    for(int i = 0;i < height; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            if(src[i][j] == 1) src[i][j] = 0;
            cout <<  src[i][j] << " ";
        }
        cout << endl;
    } 
    return 0;
}
