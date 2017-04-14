#include <stdio.h>
#include <stdlib.h>

int f1=-1,r1=-1,size1=0,f2=-1,r2=-1,size2=0,q1[100],q2[100];

struct process{
	int at,bt,no,ct,done,tat,wt,ts,vis;
}highp[100],lowp[100];

void nqhigh(int x){
	q1[++r1]=x;
	size1++;
}

int dqhigh(){
	size1--;
	return q1[++f1];
}

void nqlow(int x){
	q2[++r2]=x;
	size2++;
}

int dqlow(){
	size2--;
	return q2[++f2];
}

void swap(struct process *a,struct process *b,int n){
	int i,j;
	struct process t;
	t=*a;
	*a=*b;
	*b=t;
}

void dispihigh(int n){
	int i;
	printf("No.\tAT\tBT\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\n",i,highp[i].at,highp[i].bt);
	}
	printf("\n");
}

void disphigh(int n){
	int i,tatsum=0,wtsum=0;
	printf("higher priority processes\n");
	printf("No.\tAT\tBT\tCT\tTAT\tWT\t\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,highp[i].at,highp[i].bt,highp[i].ct,highp[i].tat,highp[i].wt);
		tatsum+=highp[i].tat;
		wtsum+=highp[i].wt;
	}
	printf("\n");
	printf("Avg TAT=%f\nAvg WT=%f\n\n",(float)tatsum/(float)n,(float)wtsum/(float)n);
}

void dispilow(int n){
	int i;
	printf("No.\tAT\tBT\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\n",i,lowp[i].at,lowp[i].bt);
	}
	printf("\n");
}

void displow(int n){
	int i,tatsum=0,wtsum=0;
	printf("lower priority processes\n");
	printf("No.\tAT\tBT\tCT\tTAT\tWT\t\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,lowp[i].at,lowp[i].bt,lowp[i].ct,lowp[i].tat,lowp[i].wt);
		tatsum+=lowp[i].tat;
		wtsum+=lowp[i].wt;
	}
	printf("\n");
	printf("Avg TAT=%f\nAvg WT=%f\n\n",(float)tatsum/(float)n,(float)wtsum/(float)n);
}

int donehigh(int n){
	int i;
	for(i=0;i<n;i++){
		if(highp[i].done==0){
			return 0;
		}
	}
	return 1;
}

int donelow(int n){
	int i;
	for(i=0;i<n;i++){
		if(lowp[i].done==0){
			return 0;
		}
	}
	return 1;
}


void main(){

	int i,j,n1,n2,k1,k2,time=0,x,localsizehigh=0,localsizelow=0;
	printf("enter number of higher priority processes - RR\n");
	scanf("%d",&n1);
	for(i=0;i<n1;i++){
		printf("enter AT,BT for process %d\n",i);
		scanf("%d%d",&highp[i].at,&highp[i].bt);
		highp[i].no=i;
		highp[i].done=0;
		highp[i].vis=0;
		highp[i].ts=0;
	}
	dispihigh(n1);
	printf("enter number of low priority processes - FCFS\n");
	scanf("%d",&n2);
	for(i=0;i<n2;i++){
		printf("enter AT,BT for process %d\n",i);
		scanf("%d%d",&lowp[i].at,&lowp[i].bt);
		lowp[i].no=i;
		lowp[i].done=0;
		lowp[i].vis=0;
		lowp[i].ts=0;
	}
	dispilow(n2);

	printf("enter time quantum\n");
	int tq;
	scanf("%d",&tq);

	printf("sorted according to AT\n");
	for(i=0;i<n1;i++){
		for(j=0;j<n1-i-1;j++){
			if(highp[j].at>highp[j+1].at){
				swap(&highp[j],&highp[j+1],n1);
			}
		}
	}
	for(i=0;i<n1;i++){
		highp[i].no=i;
	}
	printf("\nTQ=%d\n",tq);
	dispihigh(n1);

	printf("sorted according to AT\n");
	for(i=0;i<n2;i++){
		for(j=0;j<n2-i-1;j++){
			if(lowp[j].at>lowp[j+1].at){
				swap(&lowp[j],&lowp[j+1],n2);
			}
		}
	}
	for(i=0;i<n2;i++){
		lowp[i].no=i;
	}
	dispilow(n2);

	k1=0;
	k2=0;
	while(donehigh(n1)==0 || donelow(n2)==0){
		while(k1<n1){
			if(highp[k1].at<=time){
				nqhigh(highp[k1].no);
				localsizehigh++;
				highp[k1].vis=1;
				k1++;
			}
			else{
				break;
			}
		}
		while(k2<n2){
			if(lowp[k2].at<=time){
				nqlow(lowp[k2].no);
				localsizelow++;
				lowp[k2].vis=1;
				k2++;
			}
			else{
				break;
			}
		}

		if(localsizehigh!=0){
			x=dqhigh();
			time+=tq;
		
		while(k1<n1){
			if(highp[k1].at<=time){
				nqhigh(highp[k1].no);
				localsizehigh++;
				highp[k1].vis=1;
				k1++;
			}
			else{
				break;
			}
		}
		while(k2<n2){
			if(lowp[k2].at<=time){
				nqlow(lowp[k2].no);
				localsizelow++;
				lowp[k2].vis=1;
				k2++;
			}
			else{
				break;
			}
		}

			highp[x].ts+=tq;
			if(highp[x].ts>=highp[x].bt){
				highp[x].done=1;
				highp[x].ct=time-(highp[x].ts-highp[x].bt);
				highp[x].tat=highp[x].ct-highp[x].at;
				highp[x].wt=highp[x].tat-highp[x].bt;
				localsizehigh--;
			}
			else{
				nqhigh(x);
			}
		}
		else if(localsizelow!=0){
			if(size2!=0){
			x=dqlow();
			localsizelow--;
			time+=lowp[x].bt;

		while(k1<n1){
			if(highp[k1].at<=time){
				nqhigh(highp[k1].no);
				localsizehigh++;
				highp[k1].vis=1;
				k1++;
			}
			else{
				break;
			}
		}
		while(k2<n2){
			if(lowp[k2].at<=time){
				nqlow(lowp[k2].no);
				localsizelow++;
				lowp[k2].vis=1;
				k2++;
			}
			else{
				break;
			}
		}

			lowp[x].ct=time;
			lowp[x].tat=lowp[x].ct-lowp[x].at;
			lowp[x].wt=lowp[x].tat-lowp[x].bt;
			lowp[x].done=1;
		}
		else{
			time++;
			
			while(k2<n2){
			if(lowp[k2].at<=time){
				nqlow(lowp[k2].no);
				localsizelow++;
				lowp[k2].vis=1;
				k2++;
			}
			else{
				break;
			}
		}

		}
		}
		else{
			time++;
		}
		
	}

	disphigh(n1);
	displow(n2);

}