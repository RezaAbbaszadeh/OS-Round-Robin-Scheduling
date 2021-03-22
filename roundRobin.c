#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

//process
struct proc
{
	char *name;
	int startTime;
	int burstTime;
	int mem_size;
	int mem_start;
	bool mem_aloc;
	bool blocked;
};

//memory holes
struct hole{
	int start;
	int size;
};

int n = 4 , q=50 , time , rem , holeCount=1, max_hole , blockHead = 0, blockCount=0;
struct proc pa[40];
struct hole mem[100];
struct proc *blocklist[40];

struct proc newProc(char name[],int startTime,int burstTime, int mem_size)
{
	struct proc temp;
	temp.name = (char *) malloc(strlen(name)+1);
	strcpy(temp.name, name);
	temp.startTime = startTime;
	temp.burstTime = burstTime;
	temp.mem_size = mem_size;
	temp.mem_aloc = false;
	temp.blocked = false;
	return temp;
}

struct hole newHole(int start , int size){
	struct hole temp;
	temp.size = size;
	temp.start = start;
	return temp;
}

void print(struct proc *p)
{
	printf("%s %d %d\n",p->name,p->startTime,p->burstTime);
}


void sort(struct proc procArr[])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(procArr[i].startTime<procArr[j].startTime)
			{
				struct proc temp = procArr[i];
				procArr[i] = procArr[j];
				procArr[j] = temp;
			}
		}
	}
}


void decToHex(int a, char res[]){
	 int i=0;
	 if(a==0){
	 	res[i++] = '0';
	 }
	 while (a!=0)
	 {
		int temp = a %16;
		if(temp<10){
			res[i] = temp + 48;
			i++;
		}
		else{
			res[i] = temp + 55;
			i++;
		}
		a = a/16;
	 }
	 res[i]=0;
}


void alocateMem(struct proc *p){
	//using best fit
	int best_size = max_hole, best_start=0, index;
	for(int i=0; i<holeCount; i++){
		if(mem[i].size >= p->mem_size && mem[i].size<=best_size){//finding best fit hole
			best_size = mem[i].size;
			best_start = mem[i].start;
			index  = i;
		}
	}
	p->mem_aloc=true;
	p->mem_start=best_start;
	if(p->mem_size == best_size){//proccess fills hole
		mem[index] = mem[holeCount-1];
		holeCount--;
	}
	else{
		mem[index].size = best_size - p->mem_size;
		mem[index].start = best_start + p->mem_size;
	}
	if(best_size==max_hole){//max hole sized must update
		max_hole = 0;
		for(int i=0; i<holeCount; i++){
			if(mem[i].size>max_hole){
				max_hole = mem[i].size;
			}
		}
	}
	char a[20],b[20];
	decToHex(p->mem_start,a);
	decToHex(p->mem_size,b);
	printf("\n%s   time:%d   memory_addr:0x%s   mem_length:0x%s   Memory Alocated",p->name, time, a, b);
}

void block(struct proc *p){
	p->blocked=true;
	blocklist[blockHead+blockCount] = p;
	blockCount++;
}

void releaseMem(struct proc *p){
	bool joined = false;//after release joins to adjacent hole if exists
	int releaseHole = p->mem_size;
	for(int i=0 ; i < holeCount; i++){
		if(mem[i].start + mem[i].size == p->mem_start){//joins to upper hole
			releaseHole += mem[i].size;
			mem[i].size += p->mem_size;
			joined = true;
		}
		else if(p->mem_start + p->mem_size == mem[i].start){//joins to below hole
			releaseHole += mem[i].size;
			mem[i].start -= p->mem_size;
			joined = true;
		}
	}
	if(!joined){
		mem[holeCount] = newHole(p->mem_start, p->mem_size);
		holeCount++;
	}
	if(releaseHole>max_hole){
		max_hole=releaseHole;
	}

	if(blockCount>0){
		for(int i=blockHead ; i<blockHead+blockCount ; i++){
			if(blocklist[i]->mem_size<max_hole){//can release this blocked process
				blocklist[i]->blocked = false;
				blockCount--;
				if(i==blockHead){
					blockHead++;
				}
				else{//shift next blocked processes
					for(int j=i ; i<blockHead+blockCount-1 ; j++){
						blocklist[j] = blocklist[j+1];
					}
				}
				alocateMem(blocklist[i]);
				printf(" after process '%s' released memory\n", p->name);
				if(blocklist[i]->burstTime > q){
					time+=q;
					blocklist[i]->burstTime -= q;
				}
				else{
					time+=blocklist[i]->burstTime;
					blocklist[i]->burstTime = 0;
					releaseMem(blocklist[i]);
					rem--;					
				}
			}
		}
	}

}

void roundRobin(){
	while(rem>0){//there are unfinished processes 
		for(int i=0 ; i<n; i++){
			if(time < pa[i].startTime){ //not started yet
				if(i>0&&pa[i-1].burstTime == 0)
				{
					time++;
				}		
				break;
				
			}
			if(pa[i].burstTime>0){//not finsihed yet
				if(pa[i].blocked){
					continue;
				}
				if(!pa[i].mem_aloc && !pa[i].blocked && pa[i].mem_size>max_hole ){ // not enough memory
					printf("\n%s   BLOCKED\n" , pa[i].name);
					block(&pa[i]);
					continue;
				}
				if(!pa[i].mem_aloc && !pa[i].blocked){
					printf("\n");
					alocateMem(&pa[i]);
					printf("\n");
				}
				char memoryHex[10];
				decToHex(pa[i].mem_start, memoryHex);
				printf("%s   time:%d   memory_addr:0x%s\n",pa[i].name, time, memoryHex);
				if(pa[i].burstTime > q){
					time+=q;
					pa[i].burstTime -= q;
				}
				else{
					time+=pa[i].burstTime;
					pa[i].burstTime = 0;
					releaseMem(&pa[i]);
					rem--;					
				}
			}
		}


	}
}


int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		char name[20];
		int startTime, burstTime, mem_size;
		scanf("%s %d %d %d",name,&startTime,&burstTime,&mem_size);
		pa[i] = newProc(name,startTime,burstTime,mem_size);
	}
	sort(pa);
	time = pa[0].startTime;
	rem = n;
	max_hole = 8000000;
	mem[0] = newHole(0,max_hole);

	roundRobin();
}






