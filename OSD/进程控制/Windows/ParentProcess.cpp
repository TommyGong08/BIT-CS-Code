#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;
SYSTEMTIME start_time, end_time;

int main(int argc, char **argv){ 

    //该结构返回有关新进程及其主线程的信息
    PROCESS_INFORMATION ProcessInfo;  
    // 用于指定新进程的主窗口特性的一个结构  
    STARTUPINFO StartupInfo;        
                                   
    int sec,ms,min;                             
    memset(&StartupInfo,0,sizeof(STARTUPINFO));    
               
    if (!CreateProcess(NULL, argv[1] ,NULL,NULL, FALSE, 0, NULL,NULL,&StartupInfo,&ProcessInfo ))
    {   
        //创建进程失败
        cout <<"Create Fork Fail!"<< endl;        
        exit(1);    
    }    
    else    
    {        
        GetSystemTime(&start_time);        
        cout << "Begin Time: " << start_time.wHour << " h " <<  start_time.wSecond << " s " << start_time.wMilliseconds << " ms "  << endl <<endl;;   
    }
    
    WaitForSingleObject(ProcessInfo.hProcess, 5000); //HANDLE hProcess 存放每个对象的与进程相关的句柄 
    GetSystemTime(&end_time);   
    cout << "End Time: " << end_time.wHour<< " h " << end_time.wSecond <<" s " << end_time.wMilliseconds << " ms " << endl << endl;;        
    
    //处理时间
    ms  = end_time.wMilliseconds - start_time.wMilliseconds;
    sec = end_time.wSecond - start_time.wSecond;      
    if(ms<0){
        sec--;
        ms+=1000;
    }   
    if(sec<0){
        min--;
        sec+=60;
    }

    cout << "the programme " << argv[1] <<" costs " << sec*1000 + ms << "ms" << endl;
    return 0;
}

/*
BOOL CreateProcess(  
　LPCTSTR lpApplicationName, // 应用程序名称  
　LPTSTR lpCommandLine, // 命令行字符串  
　LPSECURITY_ATTRIBUTES lpProcessAttributes, // 进程的安全属性  
　LPSECURITY_ATTRIBUTES lpThreadAttributes, // 线程的安全属性  
　BOOL bInheritHandles, // 是否继承父进程的属性  
　DWORD dwCreationFlags, // 创建标志  
　LPVOID lpEnvironment, // 指向新的环境块的指针  
　LPCTSTR lpCurrentDirectory, // 指向当前目录名的指针  
　LPSTARTUPINFO lpStartupInfo, // 传递给新进程的信息  
　LPPROCESS_INFORMATION lpProcessInformation // 新进程返回的信息  
);  
*/