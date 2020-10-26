#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct nd{									//В этой структуре хранятся сами числа и их делители
	int x;
	int *px;
};

int length(int *p){								//Вычисляем длину числовой последовательности
	if(p==NULL)return 0;
	int length=0;
	while(*(p+length)!=0)length++;
	return length;
}
		

int* add(int *p, int N){
	if(!p){
		p=malloc(sizeof(int));
		*p=0;
	}
	p=realloc(p,sizeof(int)*(length(p)+2));
	*(p+length(p)+1)=0;
	*(p+length(p))=N;
	return p;
}
	

int* delet(int x){
	int *p=NULL;
	char flag=0;								//flag=0-не простое
	do{
		flag=0;
		for(int i=2; i<=sqrt(x); i++){
			if(!(x % i)){
				x/=i;
				p=add(p, i);	
				flag=1;
				break;
			}
		}
	}while(flag==1);
	if(x!=1)p=add(p, x);
	return p;
}	
			
int NOD(int a, int b){
	int NOD=1,la=0,lb=0;
	struct nd A,B;
	A.x=a;
	B.x=b;
	A.px=delet(A.x);
	B.px=delet(B.x);
	for(int i=0; i<length(A.px); i++)printf("a[%d]=%d\n", i, *(A.px+i));
	for(int j=0; j<length(B.px); j++)printf("b[%d]=%d\n", j, *(B.px+j));
	la=length(A.px);
	lb=length(B.px);
	for(int i=0; i<la; i++)
		for(int j=0; j<lb; j++){
			if(((*(A.px+i))==(*(B.px+j)))&&((*(A.px+i)))){
				NOD*=(*(A.px+i));
				*(A.px+i)=0;
				*(B.px+j)=0;
			}
	}
	return NOD;
}
		
 

int main(){
	int a=0, b=0;
	printf("Введите 2 числа: \n");
	scanf("%d%d", &a, &b);							// Вводим числа
	if(a>b){a+=b; b=a-b; a=a-b;}
	printf("НОД(%d, %d)=%d\n", a, b, NOD(a,b)); 
return 0;
}
