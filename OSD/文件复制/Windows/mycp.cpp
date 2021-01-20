#include<windowsx.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define BUFFER_SIZE 5000

void copyFile(char* SrcFile,char* DesFile)
{
    WIN32_FIND_DATA FileData;
    HANDLE FirstFile = FindFirstFile(SrcFile,&FileData);
    //创建打开文件的句柄
    HANDLE HdSrcFile = CreateFile(SrcFile,GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ,NULL,OPEN_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,NULL);
    HANDLE HdDesFile = CreateFile(DesFile,GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ,NULL,OPEN_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,NULL);
    //低32位减去高32位得到文件大小
    LONG FileSize = FileData.nFileSizeLow - FileData.nFileSizeHigh; 
    DWORD word;
    int *buff=new int[FileSize];//用于保存读入数组的一个缓冲区
    //ReadFile从文件指针指向的位置开始将数据读出到一个文件中
    ReadFile(HdSrcFile,buff,FileSize,&word,NULL);
    //WriteFile可以将数据写入一个文件或者I/O设备
    WriteFile(HdDesFile,buff,FileSize,&word,NULL);
    SetFileTime(HdDesFile,&FileData.ftCreationTime,&FileData.ftLastAccessTime,&FileData.ftLastWriteTime);
    printf("-----------------------------------\n");
    printf("Create File:%s\n",SrcFile);
    printf("-----------------------------------\n");
    CloseHandle(FirstFile);
    CloseHandle(HdSrcFile);
    CloseHandle(HdDesFile);
}

void CopyDir(char* SrcDir , char* DesDir)
{
    WIN32_FIND_DATA FindFileData;
    char TempSrcDir[BUFFER_SIZE],TempDesDir[BUFFER_SIZE];
    memset(TempSrcDir, 0, sizeof(TempSrcDir));
    strcpy(TempSrcDir,SrcDir);//复制目录名到缓冲区
    strcat(TempSrcDir,"\\*.*");//表示该目录所有文件
    HANDLE FirstFile=FindFirstFile(TempSrcDir,&FindFileData);//查找成功则返回当前目录文件句柄
    //判断当前目录下是否有下一个目录或文件
    //FindFileData这个结构用于装载与找到的文件有关的信息。该结构可用于后续的搜索
    while(FindNextFile(FirstFile,&FindFileData) != 0)
    {
        if(FindFileData.dwFileAttributes == 16) //文件属性等于16说明这是一个目录,32是文档
        {
            //排除本级目录和上级目录
            if(strcmp(FindFileData.cFileName,".") != 0 && strcmp(FindFileData.cFileName,"..") != 0)
            {
                memset(TempSrcDir,0,sizeof(TempSrcDir));
                memset(TempDesDir,0,sizeof(TempDesDir));
                strcpy(TempSrcDir,SrcDir);
                strcpy(TempDesDir,DesDir);
                strcat(TempDesDir,"\\");
                strcat(TempSrcDir,"\\");
                strcat(TempSrcDir,FindFileData.cFileName);
                strcat(TempDesDir,FindFileData.cFileName);
                //Des赋值后创建一个目录
                int ifCreateDir = CreateDirectory(TempDesDir,NULL);
                if(ifCreateDir == 0) printf("[ERROR]Can't Create Directory!\n");
                //这里用CreateFile读取文件
                HANDLE SrcFile = CreateFile(TempSrcDir, GENERIC_READ | GENERIC_WRITE,
                                                        FILE_SHARE_READ,NULL,OPEN_EXISTING,
                                                        FILE_FLAG_BACKUP_SEMANTICS,NULL);
                HANDLE DesFile = CreateFile(TempDesDir, GENERIC_READ | GENERIC_WRITE,
                                                        FILE_SHARE_READ,NULL,OPEN_EXISTING,
                                                        FILE_FLAG_BACKUP_SEMANTICS,NULL);
                FILETIME create,access,write;
                //取得指定Src目录文件的时间信息
                GetFileTime(SrcFile,&create,&access,&write);
                //复制给Des目录
                SetFileTime(DesFile,&create,&access,&write);
                printf("-----------------------------------\n");
                printf("SrcFile:%s\nDesFile:%s\n",TempSrcDir,TempDesDir);
                printf("-----------------------------------\n");
                CopyDir(TempSrcDir,TempDesDir);
            }
        }
        //如果文件不是一个目录，是文档32
        else
        {
            memset(TempSrcDir,0,sizeof(TempSrcDir));
            memset(TempDesDir,0,sizeof(TempDesDir));
            strcpy(TempSrcDir,SrcDir);
            strcpy(TempDesDir,DesDir);
            strcat(TempDesDir,"\\");
            strcat(TempSrcDir,"\\");
            strcat(TempSrcDir,FindFileData.cFileName);
            strcat(TempDesDir,FindFileData.cFileName);
            copyFile(TempSrcDir,TempDesDir);
        }
    }
    CloseHandle(FirstFile);
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
    WIN32_FIND_DATA FindFileData;//通过FindFirstFile查找文件名时用到这个结构，含有文件标题、属性等
    if(FindFirstFile(argv[1],&FindFileData) == INVALID_HANDLE_VALUE)
    {
        printf("[ERROR]Can't find directory %s", argv[1]);
        return 0;
    }
    if(FindFirstFile(argv[2],&FindFileData) == INVALID_HANDLE_VALUE)
    {
        printf("Create new directory: %s\n", argv[2]);
        //创建一个新目录
        CreateDirectory(argv[2],NULL);
    }
    //调用CopyDir函数嵌套复制文件,两个参数为被复制文件夹和目标文件夹
    CopyDir(argv[1],argv[2]);
    return 0;
}