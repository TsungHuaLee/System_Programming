#include<stdio.h>
#include<stdlib.h>  /*malloc atoi srand*/
#include<pthread.h>
#include<string.h> /*memset*/
#include<semaphore.h>
int rand_seed, num;
int* array;
//compare function for qsort
int compare(const void *a, const void *b)
{
  return ( *(int*)a - *(int*)b );
}

int half;
//pthread function
void *thread_sort(void* arr)
{ //如果起始是[0]，負責前一半
  if(arr == array)
    qsort((int*)arr, half, sizeof(int),compare);
  else
  {//如果起始是[num/2]，負責後一半
    int temp = num - half;
    qsort((int*)arr, temp, sizeof(int),compare);
  }
}
//將兩個sort完的array合併
int* merge(int* arr)
{
  int *temp = (int*) malloc(sizeof(int)*(num + 100));
  int flag1 = 0, flag2 = half, i = 0;
  while((flag1 < half)&&(flag2 < num))
  {
    if(arr[flag1] <= arr[flag2])
    {
      temp[i++] = arr[flag1++];
    }
    else
    {
      temp[i++] = arr[flag2++];
    }
  }
  while(flag1 != half)
  {
    temp[i++] = arr[flag1++];
  }
  while(flag2 != num)
  {
    temp[i++] = arr[flag2++];
  }
  return temp;
}

sem_t semaphores;
long long int total;
void *thread_diff(void* arr)
{
  int* typecov = (int*)arr;
  long long int local = 0;
  if(typecov == &array[0])
  {
    for(int i = 1; i < half; i++)
    {
      local = local + typecov[i] - typecov[i - 1];
    }
  }
  else
  {
    int temp = num - half;
    for(int i = 0; i < temp; i++)
    {
      local = local + typecov[i] - typecov[i - 1];
    }
  }
  sem_wait(&semaphores);
  total +=local;
  sem_post(&semaphores);
}

int main(int argc, char *argv[])
{
  rand_seed = atoi(argv[1]); num = atoi(argv[2]);
  srand(rand_seed);
  array = (int*) malloc(sizeof(int)*(num + 100));
  memset(array, 0, sizeof(array)); //initial
  for(int i = 0; i < num; i++)
    array[i] = rand();
  //將array拆成兩部份，一個從[0] 一個從[num/2]
  half = num / 2;
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, thread_sort, (void*)array);
  pthread_create(&thread2, NULL, thread_sort, (void*)(array + half));
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  array = merge(array);

  total = 0;
  sem_init(&semaphores, 0, 1);
  pthread_create(&thread1, NULL, thread_diff, (void*)array);
  pthread_create(&thread2, NULL, thread_diff, (void*)(array + half));
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("total = %lld\n", total);
  free(array);
}
