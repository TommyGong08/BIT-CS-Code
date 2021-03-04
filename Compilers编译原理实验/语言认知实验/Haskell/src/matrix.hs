import Data.List
import System.CPUTime
import Text.Printf

multiplyMatrix :: Num x => [[x]] -> [[x]] -> [[x]]
multiplyMatrix matrix_A matrix_B = [ [ sum $ zipWith (*) matrix_A_row matrix_B_col | matrix_B_col <- (transpose matrix_B) ] | matrix_A_row <- matrix_A ]


getMatrix n =
  let rowIndex n k = [x | x <- [1,2..n]]
  in [rowIndex n k | k <- [1,2..n]]

main = do
  let size = 100::Int
  --初始化1000*1000的矩阵
  let matrix_A = getMatrix size 
  let matrix_B = getMatrix size

  start_time <- getCPUTime
  let matrix_C = multiplyMatrix matrix_A matrix_B
  print matrix_C
  end_time <- getCPUTime
  let totalTime = (fromIntegral(end_time - start_time)) / (10 ^ 9)
  printf "Haskell cost time: %f ms\n" (totalTime :: Double)
