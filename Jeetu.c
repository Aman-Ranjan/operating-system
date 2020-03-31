#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Process{ // c doesnt have class concept
	int Arrival,Burst,Wait,Turnaround;
	char name[4];
};
struct Process Intial_Val(int Arrival,int Burst,int name){ //Function to intialize the processes attributes, because no contructor availabe for structure
	struct Process obj;//object of Process
	obj.Burst = Burst;
	obj.Arrival = Arrival;
	sprintf(obj.name,"P%d",name+1);//using sprintf(string print)
	return obj;
}
int main(){
	FILE *f = fopen("CPU_BURST.txt","r");//opening file in Read mode
	if(!f)
		return -1*printf("FILE OPEN ERROR!\n");
    int d,i,j,Count=0;
    int *list = (int*)malloc(sizeof(int));
    while(EOF != fscanf(f,"%d ",&d ))
	{
    	list = (int*)realloc(list,(Count+1)*sizeof(int));
    	list[Count++] = d;//count=number of process
    }
    fclose(f);
	struct Process P[Count];//intializing Array of Process for storing process
	for(i=0; i<Count; i++)
		P[i] = Intial_Val(0,list[i],i);
	//sorting the process according to their burst time
	//as all arrived at same time
	for(i=1; i<Count; i++){
		for(j=0; j<Count-i; j++){
			if(P[j].Burst>P[j+1].Burst){
				struct Process temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	printf("\nOrder : ");
	int Measure=0;
	for(i=0; i<Count; i++){
		P[i].Wait = Measure;//process switch time stored
		P[i].Turnaround= P[i].Wait+P[i].Burst;//calculating turnAround time
		Measure += P[i].Burst;
		printf("%s ",P[i].name);
	}	
	printf("\n\n%7s|%8s|%6s|%5s|%s\n","process","arrival","burst","wait","turnaround");
	int ToTaL_WaitTime=0,ToTaL_TurnAroundTime=0;
	for(i=0; i<Count; i++){
		ToTaL_WaitTime+=P[i].Wait;
		ToTaL_TurnAroundTime+=P[i].Turnaround;
		printf("%7s|%8d|%6d|%5d|%9d\n",P[i].name,P[i].Arrival,P[i].Burst,P[i].Wait,P[i].Turnaround);
	}
	printf("\nAverage Waiting Time     : %.2f\n",ToTaL_WaitTime*1.0/Count);//Average waiting time
	printf("\nAverage Turn Around Time : %.2f\n",ToTaL_TurnAroundTime*1.0/Count);//TurnAround Time
	return 0;
}
