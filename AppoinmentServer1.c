

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 10000

int main(){
	int sockfd, ret;
	struct sockaddr_in serverAddr;
	
	int newSocket;
	struct sockaddr_in newAddr;


	socklen_t addr_size;
	char buffer[10240];
	char press[1024];
	char w[1024];
	pid_t childpid;


	sockfd = socket(AF_INET,SOCK_STREAM,0); 
	if(sockfd < 0){

	printf("[-]Error in connection.\n");	
		exit(1);
	}	

	printf("[+]Server socket is created\n");

	memset(&serverAddr,'\0',sizeof(serverAddr)); //Use for fill the memory 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sockfd, (struct sockaddr*)&serverAddr,sizeof(serverAddr));
	if (ret < 0){


		printf("[-]Error is binding.\n");  
		exit(1);
	}

        printf("[+]bind to port %d\n",10000);

	if(listen(sockfd,10)==0){

		printf("Listing............."); 
		

		
	}
	else{
		printf("error is binding\n"); 
	}


		
	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr,&addr_size); 
		if(newSocket < 0){
			exit(1);
		}


	printf("connection accepted Ip Address %s and Port Number %d\n", inet_ntoa(newAddr.sin_addr),ntohs( newAddr.sin_port));

	if(childpid = fork()==0){

		close(sockfd);


	while(1){

		recv(newSocket,buffer,1024,0);
		

		if(strcmp(buffer, "exit") ==0){

				printf("disconnected  Ip Address  %s and Port Number%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
		break;
			}
		else{

		printf( " Client: %s\n ",buffer); 
		send(newSocket,buffer,strlen(buffer),0);
		}
		
		recv(newSocket,w,1024,0);
		

		if(strcmp(w, "exit") ==0){

				printf("disconnected  Ip Address  %s and Port Number%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
		break;
			}
		else{

		printf( " Client: %s\n ",w); 
		send(newSocket,w,strlen(w),0);
		}
		

		recv(newSocket,press,1024,0);

		if(strcmp(press, "N") ==0){

				printf("disconnected  Ip Address  %s and Port Number%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
		break;
			}
		else{

		printf( " Client: %s\n ",press); 
		send(newSocket,press,strlen(press),0);
		}

		
		if(strcmp(press, "C") ==0){
				FILE *f=fopen("User.txt","a+");
				fprintf(f,"   %s\t %d\t  %s\t\t\n", inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port ),w);
				fclose(f);
				printf("disconnected  Ip Address  %s and Port Number%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
		break;
			}
		else{

		printf( " Client: %s\n ",press); 
		send(newSocket,press,strlen(press),0);
		}
	       }
	    }
	}

   close(newSocket);

return 0;

}
























