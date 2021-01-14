
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include<iostream>
#include<cstring>
#include<map>
using namespace std; 
#define NEED_P 3            //生产者数量
#define NEED_C 4            //消费者数量
#define WORKS_P 4           //生产次数
#define WORKS_C 3           //消费次数
#define BUF_LENGTH (sizeof(struct my_buffer))
#define LETTER_NUM 4
#define SHM_MODE 0600
#define SEM_ALL_KEY 1234
#define SEM_EMPTY  0
#define SEM_FULL   1            
#define MUTEX      2
//缓冲区结构（循环队列）
struct my_buffer{     
   char buffer[LETTER_NUM];     //存放字符数组    
   int in;                      //写指针    
   int out;                     //读指针
};
struct my_buffer * shmptr;              //指向所创建的结构体的指针
int shm_id, sem_id;                     //信号量标识符
//得到3以内的一个随机数
int get_random(){    
    int t;    
    srand((unsigned)(getpid() + time(NULL)));    
    t = rand() % 3;    
    return t;
}
 
//得到A~Z的一个随机字母
char get_letter()
{    
    char a;    
    srand((unsigned)(getpid() + time(NULL)));   
    map<int,char> name_map;
    name_map[0] = 'G';
    name_map[1] = 'H';
    name_map[2] = 'L'; 
    int num = rand() % 3;
    a = name_map[num];    
    return a;
}
 
//P操作
void p(int sem_id, int sem_num)
{    
    struct sembuf xx;    
    xx.sem_num = sem_num;                    //操作信号在信号集中的编号，第一个信号的编号是0   信号量的序号      
    xx.sem_op = -1;                          //sem_op具体执行的操作（P/V    
    xx.sem_flg = 0;    
    semop(sem_id, &xx, 1);                   //通过调用semop()函数，进程对一信号量集合中的一个或多个信号量执行P/V操作
                                            //当它的值大于 0 时，表示当前可用的资源数的数量；
                                            //当它的值小于 0 时，其绝对值表示等待使用该资源的进程个数。
}                 
 
//V操作
void v(int sem_id, int sem_num)
{    
    struct sembuf xx;    
    xx.sem_num = sem_num;                       //操作信号在信号集中的编号，第一个信号的编号是0    
    xx.sem_op = 1;                              //获取资源的使用权    
    xx.sem_flg = 0;    
    semop(sem_id, &xx, 1);
}

void Creat_Share_MM(){    
    //创建共享文件区    
    shm_id = shmget(IPC_PRIVATE, BUF_LENGTH, SHM_MODE);    
    if ( shm_id < 0)    
    {        
        printf("Error on shmget.\n");              
        exit(1);    
    }    
    //把共享内存区对象映射到调用进程的地址空间    
    shmptr = (my_buffer *)shmat(shm_id, 0, 0);    //初始化共享文件区    
    shmptr->in = 0;    
    shmptr->out = 0;        
    memset(shmptr->buffer,'-',4*sizeof(char));
}

void Creat_Semaphore(){    //创建3个新信号量    
    sem_id = semget(SEM_ALL_KEY , 3 , IPC_CREAT | 0660 ); 
    if (sem_id >= 0)    
    {        
        printf("Semaphore created.\n"); 
        printf("------------ number----------work times--|--buffer content--\n");   
    }   
    //semctl用来执行在信号量集上的控制操作
    semctl(sem_id, SEM_EMPTY, SETVAL, LETTER_NUM);    
    semctl(sem_id, SEM_FULL, SETVAL, 0);    
    semctl(sem_id,MUTEX,SETVAL,1); 
}

//主函数
int main(int argc, char * argv[])
{   
    //创建共享文件区 
    Creat_Share_MM();
    //创建3个新信号量
    Creat_Semaphore();
    int num_p = 0, num_c = 0;
    pid_t pid_p, pid_c;
    int i, j;        
    char ch;                          //随机生成的字母
    while ((num_p++) < NEED_P)    
    {       
        if ((pid_p = fork()) < 0)       
         {            
             printf("Error on fork.\n");            
             exit(1);        
         }        
        //如果是子进程，开始创建生产者        
        if (pid_p == 0)        
        {            
            //shmat()将共享内存区对象映射到调用进程的地址空间            
            shmptr = (my_buffer *)shmat(shm_id, 0, 0);            
            for (i = 0; i < WORKS_P; i++)            
            {                                
                p(sem_id, SEM_EMPTY);                                       //对资源进行p操作                
                p(sem_id,MUTEX);                
                shmptr->buffer[shmptr->out] = ch = get_letter();           //随机生成一个字母放入缓冲区                
                shmptr->out = (shmptr->out + 1) % LETTER_NUM;             //指针后移                               
                //输出缓冲区字符                
                //printf("--------------------------------\n");                
                printf("[PRODUCER]Producer %d produces '%c'.  %d    |  ", num_p, ch, i);                
                printf("buffer：%c %c %c %c\n",shmptr->buffer[0],shmptr->buffer[1],shmptr->buffer[2],shmptr->buffer[3]);                
                //把缓冲区的值冲掉
                fflush(stdout);                
                v(sem_id,MUTEX);                
                v(sem_id, SEM_FULL);                                        //对资源进行v操作                           
                sleep(get_random());                                        //等待随机时间            }                 
            }
            shmdt(shmptr);//断开共享内存连接            
            exit(0);   
        }
    }
 
    //对每个消费者创建一个子进程
    while (num_c++ < NEED_C)
    {
        if ((pid_c = fork()) < 0)
        {
            printf("Error on fork.\n");
            exit(1);
        }        
        //如果是子进程，开始创建消费者       
         if (pid_c == 0)        
         {
             //shmat()将共享内存区对象映射到调用进程的地址空间           
             shmptr = (my_buffer *)shmat(shm_id, 0, 0);            
             for (i = 0; i < WORKS_C; i++)            
             {                
                p(sem_id, SEM_FULL);//对资源进行p操作                
                p(sem_id,MUTEX);                
                ch = shmptr->buffer[shmptr->in];                     //取出缓冲区第一个字符                
                shmptr->buffer[shmptr->in]='-';                      //                
                shmptr->in = (shmptr->in + 1) % LETTER_NUM;        //头指针后移                                             
                //printf("--------------------------------\n");                
                printf("[CONSUMER]Consumer %d gets     '%c'.  %d    |  ", num_c, ch, i);                
                printf("buffer：%c %c %c %c\n",shmptr->buffer[0],shmptr->buffer[1],shmptr->buffer[2],shmptr->buffer[3]);                //
                fflush(stdout);                    //清除输出缓冲区，并输出缓存区内容                
                v(sem_id,MUTEX);                
                v(sem_id, SEM_EMPTY);              //对资源进行v操作                
                sleep(get_random());                  //等待随机时间            
              }            
              shmdt(shmptr);                                //断开共享内存连接            
              exit(0);       
          }
    }
    
    //主控程序最后退出   
    while(wait(0) != -1);        //等待所有子进程结束    
    shmdt(shmptr);                 //断开共享内存连接 
    shmctl(shm_id, IPC_RMID, 0);  //对共享主存区进行控制   
    semctl(sem_id, IPC_RMID, 0);    //对同步信号量进行控制      
    fflush(stdout);          //清除输出缓冲区，并输出缓存区内容    
    printf("--------------end---------------\n");    
    exit(0);
}
