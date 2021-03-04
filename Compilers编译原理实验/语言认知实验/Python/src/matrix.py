import numpy as np
import time 

matrix_A = np.random.randint(10, size=(100, 100))
matrix_B = np.random.randint(10, size=(100, 100))
# print(matrix_A)
start_time = time.time()
matrix_C = np.dot(matrix_B, matrix_A)
print(matrix_C)
end_time = time.time()

cost_time = format(1000 * (end_time - start_time), '.5f')
print('Python cost time: ', cost_time, 'ms')