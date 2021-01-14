#include<math.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main(int argc, char **argv){   

    //use system time       
    struct timeval start_time;      
    struct timeval end_time;  
      
    float time_use = 0;     
    pid_t pid;      
    pid = fork();       
    if (pid < 0)    //create fail      
    {               
        printf("Create Fail!");             
        exit(0);        
    }       
    else if (pid == 0)  //child process         
    {                   
        gettimeofday(&start_time,NULL);             
        cout << "child process start_time.tv_sec:" <<start_time.tv_sec << endl; 
        cout << "child process start_time.tv_usec:" <<start_time.tv_usec << endl;             
        execv(argv[1],&argv[1]);     
    }       
    else        
    {                   
        gettimeofday(&start_time,NULL);                       
        cout << "parent process start_time.tv_sec:" <<start_time.tv_sec << endl; 
        cout << "parent process start_time.tv_usec:" <<start_time.tv_usec << endl; 
        //wait for child process end 
        wait(NULL);              
        gettimeofday(&end_time,NULL); 

        cout << "child process end_time.tv_sec:" <<end_time.tv_sec << endl; 
        cout << "child process end_time.tv_usec:" <<end_time.tv_usec << endl;                 
        time_use = (end_time.tv_sec - start_time.tv_sec)*1000000 + (end_time.tv_usec - start_time.tv_usec);             
        cout << "time cost : " << time_use/1000 << "ms" <<endl;      
    }       
    return 0;
}