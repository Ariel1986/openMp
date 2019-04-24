#include <iostream>
#include <omp.h>

void test(){
    for (int i=0;i<10;i++){
        std::cout<<"in test: "<< i <<std::endl;
    }
}

int main(){
    float startTime = omp_get_wtime();
//parallel for用于生成一个并行域，并将计算任务在多个线程之间分配，从而加快计算运行的速度。可以让系统默认分配线程个数，也可以使用num_threads子句指定线程个数。
// 指定3个线程
#pragma omp parallel for num_threads(3)
    for (int i=0;i<10;i++){
        test();
    }
    
    float endTime = omp_get_wtime();
    std::cout<<"run time: "<< endTime - startTime;
    return 0;
}

//section语句是用在sections语句里用来将sections语句里的代码划分成几个不同的段，每段都并行执行。
void sectionExample(){
#pragma omp parallel sections {
#pragma omp section
    std::cout<<"section 1 threadID: "<< omp_get_thread_num();
 #pragma omp section
    std::cout<<"section 2 threadID: "<< omp_get_thread_num();
#pragma omp section
    std::cout<<"section 3 threadID: "<< omp_get_thread_num();
#pragma omp section
    std::cout<<"section 4 threadID: "<< omp_get_thread_num();
    
    return ;
}
