#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct nd{									
	int x;									
	int *px;								
};

int length(int *p){								
	if(p==NULL)return 0;							
	int length=0;
	while(*(p+length))length++;						
	return length;					
}
		

int* add(int *p, int N){							
	p=realloc(p,sizeof(int)*(length(p)+2));					
	*(p+length(p)+1)=0;
	*(p+length(p))=N;
	return p;
}
	

int* delet(int x){
	int *p=NULL;
	char flag=0;								
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
	}while(flag);
	if(x!=1) p=add(p, x);
	return p;
}	
			
void NOKD(int a, int b, int flag){
	int *k=NULL, s=0;
	int NOD=1, NOK=1, la=0, lb=0;
	struct nd A, B;
	A.x=a;
	B.x=b;
	A.px=delet(A.x);
	B.px=delet(B.x);
	int s1mple=((*(A.px+length(A.px)-1))>(*(B.px+length(B.px)-1)))?(*(A.px+length(A.px)-1)):(*(B.px+length(B.px)-1));
	k=malloc(sizeof(int)*s1mple);
	for(int i=0; i<length(A.px); i++)printf("%d  ", *(A.px+i));
	printf("\n");
	for(int j=0; j<length(B.px); j++)printf("%d  ", *(B.px+j));
	printf("\n");
	la=length(A.px);
	lb=length(B.px);
	if(!flag){for(int i=0; i<la; i++)
			for(int j=0; j<lb; j++)
				if(((*(A.px+i))==(*(B.px+j)))&&((*(A.px+i)))){
					NOD*=(*(A.px+i));
					*(A.px+i)=0;
					*(B.px+j)=0;
				}
	printf("\nНОД(%d, %d)=%d\n", A.x, B.x, NOD);
	}
	if(flag){
		for(int i=2; i<=s1mple; i++){
			*(k+i)=0;
			for(int j=0; j<lb; j++) if((*(B.px+j))==(i))(*(k+i))++;
		}
		printf("--------\n");
		for(int i=2; i<=s1mple; i++){
			s=0;	
			for(int j=0; j<la; j++)
				if((*(A.px+j))==(i)) s++;
			*(k+i)=(s>(*(k+i)))?(s):(*(k+i));
			if(*(k+i)) printf("k[%d]=%d\n", i, *(k+i));
		}
		for(int i=2; i<=s1mple; i++){
			NOK*=(!(*(k+i)))?(1):((int)pow(i, (*(k+i))));
		}
	printf("\nНОК(%d, %d)=%d\n", A.x, B.x, NOK);
	}
	
}

		
int main(){
	int a=0, b=0, flag=0;
	printf("Введите 2 числа: \n");
	scanf("%d%d", &a, &b);							
	if(a>b){a+=b; b=a-b; a=a-b;}
	printf("НОД(0) или НОК(1): ");
	scanf("%d", &flag);
	NOKD(a, b, flag); 
return 0;
}
