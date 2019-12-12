#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>

typedef struct Node Node; 

struct Node{
 char* name; 
 struct Node *next; 

};

Node *head=NULL; 
Node *curr=NULL; 
Node *data=wordtwo;

Node *addToBox(char *name){
  Node *temp=head; 
  while(temp){
    temp=temp->next; 
  }
  Node *ptr=malloc(sizeof(Node)); 
  ptr->name=malloc(stlen(name)+1); 
  strcpy(ptr->name,name); 
  prt->next=NULL;

  if(1){
    curr->next=ptr; 
    curr=ptr; 
  }else{
    ptr->next=head; 
    head=ptr; 
  }
  return ptr; 
}

Node *check(char *name){
  Node *ptr=head; 
  while(ptr!=NULL){
   int compare=strcmp(ptr,name); 
   if(compare==0){
     return 1; //exists
   }else{
     return 0; //doesnt exist 
   }
  }
}


char client_message[2000];//string 
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
  	
  // Send message to the client socket 
  pthread_mutex_lock(&lock);
  char *message = malloc(sizeof(client_message)+35);
  int exists=0; 
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
        //CREAT
        int i=0; 
 	int length=strlen(client_message); 
	char wordOne[4]; 
	char wordtwo[]=malloc(sizeof(char)); 
	for(i=0;i<5;i++){
	 wordOne=client_message[i];
	}
	
	int correct3=strcmp(wordOne,"CREAT"); 
	if(correct3==0){
	  if(client_message[6]==" "){
	    int j=0; 
	    for(j=6;j<length;j++){
		wordtwo=client_message[j]; 
	    }
	    int length2=strlen(wordtwo); 
	    if(length2>=5 && length2<=25){
		int alpha=isalpha(wordtwo[0]); 
		if(alpha!=0){
		  addToBox(wordtwo); //add to message box 
                  exists=1; 
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
       if(exists==1){
         strcpy(buffer, "ER:EXIST");
	 send(newSocket, buffer, 13,0);
       }
       

       //OPNBX
        int m=0;
        int opened=0; 
 	int length2=strlen(client_message); 
	char wordone[4]; 
	char wordtwo[]=malloc(sizeof(char)); 
	for(m=0;m<5;m++){
	 wordone=client_message[m];
	}

       	int correct5=strcmp(wordone,"OPNBX"); 
	if(correct5==0){
	  if(client_message[6]==" "){
	   int j=0; 
	    for(j=6;j<length2;j++){
		wordtwo=client_message[j]; 
	    }
            //check if in box 
   	     exists=check(wordtwo); 
             if(exists==1){
		strcpy(buffer,"OK!");
                opened=1; 
 		send(newSocket, buffer, 13,0); 
	     }else{
               strcpy(buffer,"ER:NEXST"); 
	       send(newSocket, buffer, 13,0); 
	     }
          }else{
          strcpy(buffer,"ER:WHAT?"); 
	       send(newSocket, buffer, 13,0); 
	  }
        }else{
	   strcpy(buffer,"ER:WHAT?"); 
	   send(newSocket, buffer, 13,0); 
	}
        if(exists==1){
	  strcpy(buffer,"ER:OPEND"); 
	  send(newSocket, buffer, 13,0); 
	}

	
/*
      //NXTMG 
        int a=0;
 	int length3=strlen(client_message); 
	char Wordone[4]; 
	char wordtwo[]=malloc(sizeof(char)); 
	for(a=0;a<5;a++){
	 Wordone=client_message[a];
	}

       	int correct6=strcmp(Wordone,"NXTMG"); 
	if(correct5==0){
	 if(opened==1){
           while(temp!=NULL){
	     Node *temp=head; 
             int msgSize=0; 
	     msgSize=strlen(head->data); 
             strcat(message,"OK!"); 
  	     strcat(message,msgSize); 
             strcat(
           }//while
	 }//if
        }//if
*/
      
	  
         
	


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
