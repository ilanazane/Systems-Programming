#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>

char client_message[2000];//string 
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
  	
  // Send message to the client socket 
  pthread_mutex_lock(&lock);
  char *message = malloc(sizeof(client_message)+20);
  //HELLO 
  recv(newSocket , client_message , 2000 , 0);
  	int correct=strcmp(client_message,"HELLO"); 
	  if(correct==0){
	    strcat(client_message, " DUMBv0 ready!"); 
	    strcpy(message,client_message); 
            strcpy(buffer,message); 
   	    free(message); 
	    send(newSocket,buffer,13,0); 
	  }else{
	    close(newSocket); 
	   }
        int correct2=strcmp(client_message,"GDBYE");
	  if(correct2==0){
	    close(newSocket); 
	  }
        int i=0; 
 	int length=strlen(client_message); 
	char wordOne[4]; 
	char wordTwo[]=malloc(sizeof(char)); 
	for(i=0;i<5;i++){
	 wordOne=client_message[i];
	}
	
	//CREAT
	int correct3=strcmp(wordOne,"CREAT"); 
	if(correct3==0){
	  if(client_message[6]==" "){
	    int j=0; 
	    for(j=6;j<length;j++){
		wordTwo=client_message[j]; 
	    }
	    int length2=strlen(wordTwo); 
	    if(length2>=5 && length2<=25){
		int alpha=isalpha(wordTwo[0]); 
		if(alpha!=0){
		  strcpy(buffer, "OK!"); 
		  send(newSocket,buffer,13,0); 
		}
	    }else{
		strcpy(buffer, "ER:WHAT?");
		send(newSocket, buffer, 13,0);  
	    }
	 }else{
		strcpy(buffer, "ER:WHAT?");
		send(newSocket, buffer, 13,0); 
	 }
	}else{
		strcpy(buffer, "ER:WHAT?");
		send(newSocket, buffer, 13,0);  
       }
     
	  
         
	


  pthread_exit(NULL);
}


int main(int argc, char **argv){

  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  //Create the socket. 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  // Configure settings of the server address struct
  // Address family = Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function to use proper byte order 
  int portnum; 
  portnum=(atoi(argv[1])); 
  serverAddr.sin_port=htons(portnum); 

  //Set IP address to localhost 
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  //Set all bits of the padding field to 0 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  //Bind the address struct to the socket 
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  //Listen on the socket, with 40 max connection requests queued 
  if(listen(serverSocket,50)==0)
    printf("Listening\n");
  else
    printf("Error\n");
    pthread_t tid[60];
    int i = 0;
    while(1)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
       //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 )
           printf("Failed to create thread\n");
        if( i >= 50)
        {
          i = 0;
          while(i < 50)
          {
            pthread_join(tid[i++],NULL);
          }
          i = 0;
        }
    }
  return 0;
}
