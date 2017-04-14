#include <stdio.h>
#include <stdlib.h>

int f=-1,r=-1,size=0,q[100];

struct process{
	int at,bt,no,ct,done,tat,wt,ts,vis,prio;
}p[100];

void nq(int x){
	q[++r]=x;
	size++;
}

void swap(struct process *a,struct process *b,int n){
	int i,j;
	struct process t;
	t=*a;
	*a=*b;
	*b=t;
}

int dq(){
	size--;
	return q[++f];
}

void dispi(int n){
	int i;
	printf("No.\tAT\tBT\tPrio\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\n",i,p[i].at,p[i].bt,p[i].prio);
	}
	printf("\n");
}

void disp(int n){
	int i,tatsum=0,wtsum=0;
	printf("No.\tAT\tBT\tPrio\tCT\tTAT\tWT\t\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,p[i].at,p[i].bt,p[i].prio,p[i].ct,p[i].tat,p[i].wt);
		tatsum+=p[i].tat;
		wtsum+=p[i].wt;
	}
	printf("\n");
	printf("Avg TAT=%f\nAvg WT=%f\n\n",(float)tatsum/(float)n,(float)wtsum/(float)n);
}

int done(int n){
	int i;
	for(i=0;i<n;i++){
		if(p[i].done==0){
			return 0;
		}
	}
	return 1;
}

int pickprio(int n){
	int i,min=999,mini;
	for(i=0;i<n;i++){
		if((p[i].prio<min) && (p[i].done==0) && (p[i].vis==1)){
			min=p[i].prio;
			mini=i;
		}
	}
	return mini;
}

void main(){

	int i,j,n,k,time=0,x,localsize=0;
	printf("enter no of processes\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("enter AT,BT,Priority for process %d\n",i);
		scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].prio);
		p[i].no=i;
		p[i].done=0;
		p[i].vis=0;
	}
	dispi(n);

	printf("sorted according to AT\n");
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(p[j].at>p[j+1].at){
				swap(&p[j],&p[j+1],n);
			}
		}
	}
	for(i=0;i<n;i++){
		p[i].no=i;
	}

	dispi(n);

	k=0;
	while(done(n)==0){
		while(k<n){
			if(p[k].at<=time){
				//nq(p[k].no);
				localsize++;
				p[k].vis=1;
				k++;
			}
			else{
				break;
			}
		}

		if(localsize){
			x=pickprio(n);
			//printf("x=%d\n",x);
			time+=p[x].bt;

			while(k<n){
			if(p[k].at<=time){
				//nq(p[k].no);
				localsize++;
				p[k].vis=1;
				k++;
			}
			else{
				break;
			}
		}

			p[x].ct=time;
			p[x].tat=p[x].ct-p[x].at;
			p[x].wt=p[x].tat-p[x].bt;
			p[x].done=1;
			localsize--;
		}
		else{
			time++;

			while(k<n){
			if(p[k].at<=time){
				//nq(p[k].no);
				localsize++;
				p[k].vis=1;
				k++;
			}
			else{
				break;
			}
		}

		}
	}

	disp(n);

}