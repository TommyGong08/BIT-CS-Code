#include<iostream>
#include<ctime>
#include<vector>
using namespace std;

int main()
{
    clock_t  start_time,end_time;
    int size = 100;
    vector<vector<int>> matrix_A;
    vector<vector<int>> matrix_B;

    for (int i = 0; i < size; i++) 
    {
        matrix_A.push_back(std::vector<int>());
        for (int j = 0; j < size; j++) 
        {
            matrix_A[i].push_back(rand() % 10);
        }
    }
    for (int i = 0; i < size; i++) 
    {
        matrix_B.push_back(std::vector<int>());
        for (int j = 0; j < size; j++) 
        {
            matrix_B[i].push_back(rand() % 10);
        }
    }
    start_time = clock();
    std::vector<std::vector<int>> result_matrix(int(matrix_A.size()), std::vector<int>(int(matrix_A[0].size()), 0));
    for (int i = 0; i < int(result_matrix.size()); i++)
    {
        for (int j = 0; j < int(result_matrix[i].size()); j++)
        {
            for (int k = 0; k < int(matrix_A[0].size()); k++)
            {
             result_matrix[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
    end_time = clock();
    double time = end_time - start_time;  
    cout << "C++ cost time : " << (time/CLOCKS_PER_SEC) * 1000 << "ms" << endl;
    return 0;
}