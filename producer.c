#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<sys/ipc.h>
 #include <sys/types.h>
 #include <sys/mman.h>
#include <semaphore.h>	
#include <unistd.h>
#define bsize 5
#define pshare "pshare"

struct shared{

	        int buffer[bsize],index=0;
	         sem_t mutex,full,empty;
              }*ptr;





void main()
{
	int fd,check,i;
    char ch;
  //struct shared *ptr,a;

	shm_unlink(pshare);

	fd=shm_open(pshare,O_RDWR|O_CREAT,0666);
	ftruncate(fd,sizeof(struct shared));

  ptr=mmap(NULL,sizeof(struct shared),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

  sem_init(&(*ptr).index,1,1);
  sem_init(&(*ptr).empty,1,bsize);
  sem_init(&(*ptr).full,1,0);



   printf("prodcuer starting to produce\n");
  // i=0;
   do
   {   
   	   sem_wait(&(*ptr).empty);
   	   sem_wait(&(*ptr).mutex);
       printf("enter a SINGLE character \n");
       i=ptr->index;
   	   ch=getchar();
       (*ptr).buffer[i]=ch;
       i=(i+1)%bsize;
       ptr->index=i;
       sem_post(&(*ptr).mutex);
       sem_post(&(*ptr).full);
        

        printf("press y to continue")
        scanf("%d",&ch);
    }while(ch=='y');




  sem_destroy(&(*ptr).full);
  sem_destroy(&(*ptr).mutex);
  sem_destroy(&(*ptr).empty);


	printf("hello");
   }
