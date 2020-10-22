#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main(){
	//Инициализируем случайную последовательность
	srand(getpid());
	//Спим
	usleep((rand()%100)*10000);
	//Открываем файл через указатель на файл
	FILE *file=fopen("file.txt","r");
	char s[512];
	int j=(rand())%20;
	//Читаем случайную строку среди первых двадцати
	for(int i=0;i<j;i++)
		fgets(s,512,file);
	// Если есть что писать, пишем на экран
	if(s!=NULL)
	printf("Pid read is %s\n",s);
	
	return 0;
}
