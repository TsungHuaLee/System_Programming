#include<stdio.h>
#include<stdlib.h>//malloc
#include<unistd.h>//getpid
#include<string.h>//memset
#include<sys/mman.h>
int main(int argc, char* argv[])
{
  long long int pid = getpid();
  printf("%ld\n", pid);
  int  input = atoi(argv[1]);
  char *mem = malloc(sizeof(char)* input *1024 *1024 *1024);
  printf("程式開始前,用top/free指令觀察\n");
  printf("press ENTER to continue\n");
  getchar();
  memset(mem, 0, sizeof(char)* input* 1024* 1024* 1024);
  printf("配置大量記憶體,用top/free指令觀察\n");
  printf("press ENTER to continue\n");
  getchar();
  free(mem);
}
//free -h
