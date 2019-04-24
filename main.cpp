#include <iostream>
#include <vector>
#include <ctime>
//#include <omp.h>

using namespace std;

int calculate_output_size(int input_size, int filter_size){
    return (input_size - filter_size ) + 1;
}

vector<vector<int>> solve_conv2(const vector<vector<int>>& input,
                                const vector<vector<int>> weight,
                                int num_thread){
    int input_height = input.size(), input_width = input[0].size();
    int weight_height = weight.size(), weight_width = weight[0].size();
    int output_height = calculate_output_size(input_height, input_width);
    int output_width = calculate_output_size(input_width, output_width);
    vector<vector<int>> res(output_height, vector<int>(output_width));
    
    int i, j, m, n;
    
    omp_set_dynamic(0); //关闭OpenMP动态调整线程数
    clock_t start_time, end_time;
    start_time = clock();
    //告诉OpenMP启动num_thread个线程执行下面区块中的逻辑。
    #pragma omp parallel shared(input,weight,res) private(i,j,m,n) num_threads(num_thread)
    {
        for (i = 0; i < output_height; i++){
            for (j = 0; j < output_width; j++){
                int sum = 0;
                for(m = 0; m < weight_height; m++){
                    for(n = 0; n <weight_width; n++){
                        if((i+m) >= 0 && (i+m) < input_height && (j+n) >= 0 && (j+n) <  input_width){
                            sum += weight[m][n] * input[i+m][j+n];
                        }
                    }
                }
                res[i][j] = sum;
            }
        }
    }
    end_time = clock();
    
    //TODO:使用其他代码段耗时工具类，对计算能力的提升进行统计。
    std::cout<<"paralle time: "<<end_time - start_time <<std::endl;

    return res;
}


//随机的生成矩阵,用于测试
vector<vector<int>> randomVec(int n){
    if (n <= 0){
        return {};
    }
    
    vector<vector<int>> res(n, vector<int>(n));
    //.....生成矩阵的代码
    return res;
}

int main(){
    int inputN , weightN, num_thread;
    std::cout<<"input the size of input and weight, the tread num"<<std::endl;
    
    while(scanf("%d%d%d", &inputN, &weightN, &num_thread)){
        auto input = randomVec(inputN);
        auto weight =randomVec(weightN);
        solve_conv2(input, weight, num_thread);
    }
    return 0;
}
