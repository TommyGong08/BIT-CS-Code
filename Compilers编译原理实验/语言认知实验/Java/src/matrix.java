public class matrix{
    public static void main(String[] args) {
    // 初始化两个矩阵
    int size = 100;
    int [][] matrix_A = new int[size][size];
    int [][] matrix_B = new int[size][size];
    int [][] matrix_C = new int[size][size];
    
    //两个矩阵赋值
    for(int i = 0; i < size ; i++)
    {
        for(int j = 0;j < size; j++)
        {
            matrix_A[i][j] = (int)(Math.random()*(10));
            matrix_B[i][j] = (int)(Math.random()*(10));
            // System.out.println(matrix_A[i][j]);
        }
        System.out.println("\n");
    }
    long start_time = System.currentTimeMillis();    
    //两个矩阵相乘
    for(int i = 0; i < size ; i++)
    {
        for(int j = 0; j < size ; j++)
        {
            for(int k = 0; k < size ; k++)
            {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
    // for(int i = 0; i < size ; i++)
    // {
    //     for(int j = 0; j < size ; j++)
    //     {
    //         System.out.println(matrix_C[i][j]);
    //     }
    // }
    long end_time = System.currentTimeMillis();
    long time = end_time - start_time ;
    System.out.println("Java cost time: " + time + "ms");
    }
}
