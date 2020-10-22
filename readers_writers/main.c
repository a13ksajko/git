#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	//Fork/exec сто процессов, половина - пишут, половина - читают, со случайными задержками
	for(int i=0;i<100;i++){
		int j=fork();
		//Четные пишут, нечетные читают
		if(j==0)execl(((i%2)==1)?"./reader":"./writer",NULL);
	}
	printf("Finished\n");
	return 0;
}
