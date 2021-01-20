#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <utime.h>
#define BUFFERSIZE 5000

void copyLink(char *Src, char *Des){
    char oldpath[BUFFERSIZE];
    //主要用来找出符号链接所指向的位置
    int rest=readlink(Src,oldpath,BUFFERSIZE);
    if (rest < 0 )
    {
        perror("readlink ");
        exit(0);
    }
    //创建一个从指定名称连接的现存目标文件开始的符号连接
    int sy = symlink(oldpath,Des);
    printf("----------------\n");
    printf("Create Link : %s\n",Des);
    printf("----------------\n");
    struct stat buf;
    stat(Src, &buf);
    struct utimbuf timebuff;
    timebuff.actime = buf.st_atime;
    timebuff.modtime = buf.st_mtime;    
    utime(Des,&timebuff);
}

void CopyFile(char* SrcFile,char* DesFile)
{
    //打开一个文件，建立一个文件描述符到文件路径的映射，建立文件标识
    int OpSrcFile = open(SrcFile,O_RDONLY);
    if(OpSrcFile == -1)
    {
        printf("[ERROR]Can't open file: %s",SrcFile);
        exit(0);
    }
    struct stat buf;
    stat(SrcFile, &buf);
    //也能打开一个文件，如果文件不存在，则创建它
    int CtDesFile = creat(DesFile, buf.st_mode);
    if (CtDesFile == -1)
    {
        printf("[ERROR]Can not create file: %s\n", DesFile);
        exit(0);
    }
    else 
    {
        printf("----------------\n");
        printf("Create File : %s\n",DesFile);
        printf("----------------\n");
    }
    int word;
    char buff[BUFFERSIZE];
    while ((word = read(OpSrcFile, buff, BUFFERSIZE)) > 0)
    {
        if (write(CtDesFile, buff, word) != word)
        {
            printf("[ERROR]Write error!");
            exit(0);
        }
    }
    struct utimbuf timebuff;
    timebuff.actime = buf.st_atime;
    timebuff.modtime = buf.st_mtime;
    utime(DesFile, &timebuff);
    close(OpSrcFile);
    close(CtDesFile);
}

void CopyDir(char* SrcDir,char* DesDir)
{
    DIR *dir = opendir(SrcDir);
    //为了获取某文件夹目录内容，所使用的结构体。
    struct dirent *dirp;
    char TempSrcDir[BUFFERSIZE] , TempDesDir[BUFFERSIZE];
    //readdir读一个目录 , 返回dirent
    while((dirp = readdir(dir))!= NULL)
    {
        if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0) continue;
        if(dirp->d_type == 4) //d_type:4 表示一个目录
        {
            strcpy(TempSrcDir, SrcDir);
            strcpy(TempDesDir, DesDir);
            strcat(TempSrcDir, "/");
            strcat(TempDesDir, "/");
            strcat(TempSrcDir, dirp->d_name);
            strcat(TempDesDir, dirp->d_name);
            struct stat buf;
            struct utimbuf timebuff;
            stat(TempSrcDir, &buf);
            //文件的类型和存取的权限
            mkdir(TempDesDir, buf.st_mode);
            timebuff.actime = buf.st_atime;///最后一次访问时间
            timebuff.modtime = buf.st_mtime;////最后一次修改时间
            //utime用来修改参数filename文件所属的inode存取时间
            utime(TempDesDir,&timebuff);
            printf("----------------\n");
            printf("Create directory : %s\n",TempDesDir);
            printf("----------------\n");
            CopyDir(TempSrcDir,TempDesDir);
        }
        else if (dirp->d_type==10)     //d_type为10表示符号连接
        {
            strcpy(TempSrcDir, SrcDir);
            strcpy(TempDesDir, DesDir);
            strcat(TempSrcDir, "/");
            strcat(TempDesDir, "/");
            strcat(TempSrcDir, dirp->d_name);
            strcat(TempDesDir, dirp->d_name);
            //将源路径和目标路径都复制到temp中
            copyLink(TempSrcDir,TempDesDir);
        }
        else//如果文件不是一个目录，是文档
        {
            strcpy(TempSrcDir, SrcDir);
            strcpy(TempDesDir, DesDir);
            strcat(TempSrcDir, "/");
            strcat(TempDesDir, "/");
            strcat(TempSrcDir, dirp->d_name);
            strcat(TempDesDir, dirp->d_name);
            CopyFile(TempSrcDir,TempDesDir);
        }
    }

}

int main(int argc , char* argv[])
{
    //如果参数数量不对
    if(argc != 3)
    {
        printf("please input correct parameters!\n");
        printf("[For example]./my.exe ./srcdir ./desdir\n");
        return 0;
    }
    DIR *dir ;//保存当前正在被读取的目录的有关信息
    //check if srcdir exist
    if((dir = opendir(argv[1])) == NULL)
    {
        printf("[ERROR]Can't find directory %s", argv[1]);
        return 0;
    }
    closedir(dir);
    //check if desdir exist
    if((dir = opendir(argv[2])) == NULL)
    {
        //保存文件信息的结构体包括:文件的类型和存取的权限,最后一次访问时间,最后一次修改时间
        struct stat buf;
        struct utimbuf timebuff;
        //用来获取linux操作系统下文件的属性, 通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
        stat(argv[1], &buf);
        //文件的类型和存取的权限
        mkdir(argv[2], buf.st_mode);
        timebuff.actime = buf.st_atime;///最后一次访问时间
        timebuff.modtime = buf.st_mtime;////最后一次修改时间
        //utime用来修改参数filename文件所属的inode存取时间
        utime(argv[2],&timebuff);
        printf("Create new directory: %s\n", argv[2]);
    }
    //调用CopyDir函数嵌套复制文件,两个参数为被复制文件夹和目标文件夹
    CopyDir(argv[1],argv[2]);
    return 0;
}