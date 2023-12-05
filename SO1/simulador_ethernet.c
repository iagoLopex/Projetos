#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h> 

#define ANSI_COLOR_RED "\x1b[31m" 
#define ANSI_COLOR_GREEN "\x1b[32m" 
#define ANSI_COLOR_RESET "\x1b[0m"

int backofftime=10,waittime=10;
struct timeval lasttime;
struct timeval currenttime;
int status(3];

init()
{ 
	int i; 
	for(i=0;i<3;i++) 
		status[i]=0; 
}

void csma(void *station)
{ 
	int name,l=3,t=0,i; 
	name=atoi(station); 
	while(1){ 
		if(status[0]+status[1]+status[2]>=3) 
			exit(0);

		if (status [name]==1){
			gettimeofday(&currenttime,0);
			sleep(waittime);
		}
		else{
			
			printf("Station %d transmitting a frame\n",name);
			gettimeofday(&currenttime,0);
			printf("Station %d: last time: %d , current time:%d\n",name,lasttime.tv_sec,currenttime.tv_sec);
			usleep(waittime);
			
			if(lasttime.tv_sec+backofftime >= currenttime.tv_sec && status[name]==0){
				
				printf(ANSI_COLOR_RED "Station %d : Collision Detected :("ANSI_COLOR_RESET "\n",name);
				l--;
				
				if(l>0){
					printf("Station %d: data resending, attemptsremaining=%d\n",name,l);
					lasttime.tv_sec=currenttime.tv_sec;
					sleep(waittime);
				}
				else{
					printf("Station %d: limit expired\n",name);
				}
			}
			else{
				
				if(status[name]==0){
					lasttime.tv_sec=currenttime.tv_sec;
					printf(ANSI_COLOR_GREEN "Station %d : Data SendSuccess!!!" ANSI_COLOR_RESET "\n",name);
					status[name]=1;
				}
				lasttime.tv_sec=currenttime.tv_sec;
			}
			
			sleep(waittime);
		}
	}
	//...
	
}

/*
http://www-usr.inf.ufsm.br/~rose/Tanenbaum.pdf
pg 218

http://deptal.estgp.pt:9090/cisco/ccna1/course/module5/5.1.2.3/5.1.2.3.html

//funcionamento da decodificacao
https://joaoricardao.files.wordpress.com/2014/03/cap6.pdf
*/
	
	
	
	
