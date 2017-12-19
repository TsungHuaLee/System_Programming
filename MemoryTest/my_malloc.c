#include<stdio.h>
#include<stdlib.h>//malloc
#include<unistd.h>//getpid
#include<string.h>
#include<sys/resource.h>//getrusage
int main(int argc, char* argv[])
{
  long long int pid = getpid();
  printf("pid = %d\n",pid);

  // sizeof(int) = 4 byte, malloc 40MiB = 4 * 10 * 1024 *1024 byte;
  int *mem = (int*)malloc(sizeof(int)*10*1024*1024);
  printf("\nwatch memory after malloc 40MB\n");
  printf("press ENTER to continue\n");
  getchar();

  //set 40MiB
  memset(mem, 0, sizeof(int)* 10* 1024 * 1024);
  printf("\nwatch memory after set 40MB\n");
  printf("press ENTER to continue\n");
  getchar();
  free(mem);

}
