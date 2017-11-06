#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdio.h>
#include<errno.h>
int main()
{
    //int shmget(key_t key, size_t size, int shmflg)
    int segment_id;
    struct shmid_ds shmbuffer;
    //create a new share menory object
    segment_id = shmget(IPC_PRIVATE, 128, IPC_CREAT|IPC_EXCL|0600);

    if(segment_id == -1)
    {
      perror("shmget error!");
      return -1;
    }
    //int shmctl(int shmid, int cmd, struct shmid_ds *buf)
    int ctl_id;
    ctl_id = shmctl(segment_id, IPC_STAT, &shmbuffer);

    if(ctl_id == -1)
    {
      perror("shmctl error!");
      return -1;
    }

    printf("segment ID: %d\n", segment_id);
    printf("Key: %d\n", (int)shmbuffer.shm_perm.__key);
    printf("Mode: %d\n", (int)shmbuffer.shm_perm.mode);
    printf("Onwer UID: %d\n", (int)shmbuffer.shm_perm.uid);
    printf("Size: %d\n", (int)shmbuffer.shm_segsz);
    printf("Number of atthchment: %d\n", (int)shmbuffer.shm_nattch);
}
