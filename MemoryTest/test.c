#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  int i = 0;
  struct rusage r_usage;
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld\n",r_usage.ru_maxrss);

  int *m = (int*)malloc(sizeof(int)*1000*1000);
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld\n",r_usage.ru_maxrss);
  sleep(3);
  //4MB
  memset(m,0,sizeof(int)*1000*1000);
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld\n",r_usage.ru_maxrss);
  free(m);

  sleep (3);

  printf("\nAllocated memory, sleeping ten seconds after which we will check again...\n\n");
  sleep (10);
  getrusage(RUSAGE_SELF,&r_usage);
  printf("Memory usage = %ld\n",r_usage.ru_maxrss);
  return 0;
}
