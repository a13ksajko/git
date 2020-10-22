#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t vilka[5];
pthread_cond_t thinking_cond[5];
pthread_mutex_t thinking_mutex[5];
void *TryToEat(void *numptr){
	int number=*(int*)numptr;
	int left=(number==0)?4:number-1;
	printf("I am philosopher number %d, have forks %d and %d availible to me\n",number+1,left+1,number+1);
	while(1){
		if(pthread_mutex_trylock(&(vilka[left]))==0){
			printf("I am philosopher number %d, took fork number %d\n",number+1,left+1);
			if(pthread_mutex_trylock(&(vilka[number]))==0){
				printf("I am philosopher number %d, took fork number %d, eating...\n",number+1,number+1);
				usleep(2000);
				printf("I am philosopher number %d, finished eating\n",number+1);
				pthread_mutex_unlock(&(vilka[number]));
				pthread_cond_signal(&(thinking_cond[(number==4)?0:number+1]));
				pthread_mutex_unlock(&(vilka[left]));
				pthread_cond_signal(&(thinking_cond[left]));
				printf("I am philosopher number %d, signalled %d and %d\n",number+1,left+1,((number==4)?0:number+1)+1);
				void *status=malloc(sizeof(int));
				*((int*)status)=0;
				pthread_exit(status);
			}	
				printf("I am philosopher number %d, putting down fork number %d, thinking... \n",number+1,left+1);
				pthread_mutex_unlock(&(vilka[left]));
				pthread_cond_signal(&(thinking_cond[left]));
				pthread_mutex_unlock(&(vilka[number]));
				pthread_cond_signal(&(thinking_cond[(number==4)?0:number+1]));
				pthread_cond_wait(&(thinking_cond[number]),&(thinking_mutex[number]));
				
		}else{
			printf("I am philosopher number %d, did not take fork number %d, entering thinking mode...\n",number+1,left+1);
			pthread_mutex_unlock(&(vilka[left]));
			pthread_cond_signal(&(thinking_cond[left]));
			pthread_mutex_unlock(&(vilka[number]));
			pthread_cond_signal(&(thinking_cond[(number==4)?0:number+1]));
			pthread_cond_wait(&(thinking_cond[number]),&(thinking_mutex[number]));
		}
	}
	return 0;
}
int main(){
	pthread_t thread[5];
	for(int i=0;i<5;i++){
		pthread_mutex_init(&(vilka[i]),NULL);
		pthread_mutex_init(&(thinking_mutex[i]),NULL);
		pthread_mutex_lock(&(thinking_mutex[i]));
		pthread_cond_init(&(thinking_cond[i]),NULL);
	}
	for(int i=0;i<5;i++){
		int *j=malloc(sizeof(int));
		*j=i;
		pthread_create(thread+i,NULL,&TryToEat,j);
	}
	for(int i=0;i<5;i++){
		void *status;
		pthread_join(thread[i],&status);
	}
	return 0;
}
