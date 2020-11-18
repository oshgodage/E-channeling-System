
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 10000

void printAvailable(char display[])
{
	char line[301];
	char filePath[] ="doctorRef.txt";
	FILE *fp=fopen(filePath,"r");
	
	int found =0;

	if(fp==NULL)
	{
		printf("\nError file %s not found",filePath);
		return;
	}

	while(!feof(fp))
	{
		fgets(line,300,fp);

		if(strstr(line,display)!=NULL){

			printf("\n%s",line);
			found =1;		
		}
	}

	if(found==0){
	printf("Sorry.Doctor is not available Try another day\n");
	return exit(0);
	}

	fclose(fp);


}


void searchAvailable(char available[])
{	
	
	char line[301];
	char filePath[] ="doctor.txt";
	FILE *fp1=fopen(filePath,"r");
	
	
	int found =0;

	if(fp1==NULL)
	{
		printf("\nError file %s not found",filePath);
		return;
	}

	while(!feof(fp1))
	{
		fgets(line,300,fp1);

		if(strstr(line,available)!=NULL){
			printf("**************************\t\t(1)\t(2)\t(3)\n");
			printf("\n%s",line);
			found =1;		
		}
	}

	if(found==0)
	{
	
		printf("Sorry Letters are not match try again\n");
	
	}

	fclose(fp1);

}



int main(int argc, char *argv[])
{
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	char press[1024];
	char w[1024];

//create a socket
	clientSocket = socket(AF_INET,SOCK_STREAM  ,0);
	if(clientSocket < 0){

		printf("Error in connection \n");   
		exit(1);
	}

	printf("Client socket is created\n"); 

//Use for fill block of memory
	memset(&serverAddr,'\0',sizeof(serverAddr)); 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port	= htons(PORT);
	serverAddr.sin_addr.s_addr  = htonl(INADDR_ANY); 
//Establish the connection with tcp server(AppoinmentServer1)	
	ret = connect(clientSocket, (struct sockaddr*)&serverAddr,sizeof(serverAddr));
	if(ret < 0){
		printf("Error in connection");	
		exit(1);
	}

	printf("Connect to server\n");




	FILE *fPointer;
	fPointer =fopen("channelInfo.txt","r");
	char singleLine[150];

	while(!feof(fPointer)){
		fgets(singleLine,150,fPointer);
		puts(singleLine);
	}

	fclose(fPointer);




//Search the docter using printAvailable methode(doctorRef.txt)
//Search the specific doctor using doctor's ID

	 
	while(1){
		
 		printf("Enter the 4 Letters:");
		
		scanf("%s",&buffer[0]);

		send(clientSocket,buffer,strlen(buffer),0);
	/*

		if(strcmp(buffer, ":exit")==0){
			
 		close(clientSocket);
		printf("[-]Disconnected from server. \n");
			exit(1);
		}
	*/
		if(recv(clientSocket,buffer,1024,0)<0){
			printf("[-]Error in receving data. \n");
		}
		else{
			
	 	char c[200];
		int i=0;

		printAvailable(buffer);

		printf("Enter the Appoinment:\n");

		printf("Eg-:003 2\n");

		scanf("%s",&w[0]);

		send(clientSocket,w,strlen(w),0);

		searchAvailable(w);
		

		printf("Press 'C' to confirm the appoinment or press 'N' to cancle  \n");
	
		scanf("%s",&press[0]);
		
		
		send(clientSocket,press,strlen(press),0);

		
		
		
	}

	return 0;



	}



}
