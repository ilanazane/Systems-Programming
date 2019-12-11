#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

int hello(int, struct sockaddr_in*, int);

int errNum = 0;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        // invoked with host name and port number
        fprintf(stderr, "Argument Error: Incorrect arg count\n");
        exit(EXIT_FAILURE);
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "Socket Error: Cannot create socket\n");
        exit(EXIT_FAILURE);
    }

    sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);

    struct sockaddr_in serverAddr;
    socklen_t addrSize;
    struct hostent* host = gethostbyname(argv[1]);

    serverAddr.sin_addr.s_addr = inet_addr(host->h_addr_list[0]);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    addrSize = sizeof(serverAddr);

    int i; int success = 0;
    for (i = 0; i < 3; i++) {
        //Attempt E.0 HELLO 3 times
        if (hello(sockfd, &serverAddr, addrSize)) {
            success = 1;
            break;
        }
        
    }
    if (success == 0) {
        fprintf(stderr, "Connect Error: No server response\n");
    }

    char input[100];
    
    while (1) {
        printf("> ");
        fgets(input);
        switch (input) {
            case "help":
                printf("quit\ncreate\ndelete\nopen\nclose\nnext\nput\n");
                break;
            case "quit":
                if (goodbye(sockfd, &serverAddr, addrSize)) {
                    printf("Goodbye!\n");
                    return 0;
                } else {

                }
                break;
            case "create":
                char nameInput[100];
                printf("Okay, what should the new message box be named?\ncreate:> ");
                fgets(nameInput);
                if (createBox(sockfd, &serverAddr, addrSize, nameInput)) {
                    printf("Success! Message box \'%s\' is now created.\n", nameInput);
                }
                break;
            case "delete":
                char nameInput[100];
                printf("Okay, which box should be deleted?\ndelete:> ");
                fgets(nameInput);
                if (deleteBox(sockfd, &serverAddr, addrSize, nameInput)) {
                    printf("Success! Message box \'%s\' has been deleted.\n", nameInput);
                }
                break;
            case "open":
                char nameInput[100];
                printf("Okay, which box should be opened?\nopen:> ");
                fgets(nameInput);
                if (openBox(sockfd, &serverAddr, addrSize, nameInput)) {
                    printf("Success! Message box \'%s\' is now open.\n", nameInput);
                }
                break;
            case "close":
                char nameInput[100];
                printf("Okay, which box should be closed?\nclose:> ");
                fgets(nameInput);
                if (deleteBox(sockfd, &serverAddr, addrSize, nameInput)) {
                    printf("Success! Message box \'%s\' has been closed.\n", nameInput);
                }
                break;
            case "next":
                char* returnMsg = nextmsg(sockfd, &serverAddr, addrSize)
                if (returnMsg != NULL) {
                    printf("Success! Message: \'%s\'\n", nameInput);
                }
                break;
            case "put":
                char msgInput[100];
                printf("Okay, please give the message size and message contents separated by a \'!\'.\nput:> ");
                fgets(nameInput);
                if (deleteBox(sockfd, &serverAddr, addrSize, msgSize, msgInput)) {
                    printf("Success! Message box \'%s\' has been closed.\n", nameInput);
                }
                break;
            default:
                break;
        }
    }

    close(sockfd);
    return 0;
}

int hello(int sockfd, struct sockaddr_in *_serverAddr, int addrSize) {
    char* message = "HELLO ";
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    return 1;
}

int goodbye(int sockfd, struct sockaddr_in* _serverAddr, int addrSize) {
    char* message = "GDBYE ";
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 1;
    }
    return 0;
}

int createBox(int sockfd, struct sockaddr_in* _serverAddr, int addrSize, char* boxName) {
    char message[50];
    strcat(message, "CREAT ");
    strcat(message, boxName);
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    
    if (buffer == "ER:EXIST" || buffer == "ER:WHAT?")
        return 0;

    return 1;
}

int openbox(int sockfd, struct sockaddr_in* _serverAddr, int addrSize, char* boxName) {
    char message[50];
    strcat(message, "OPNBX ");
    strcat(message, boxName);
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    if (buffer == "ER:NEXST" ||buffer == "ER:OPEND"|| buffer == "ER:WHAT?")
        return 0;

    return 1;
}

int nextmsg(int sockfd, struct sockaddr_in* _serverAddr, int addrSize) {
    char message[50];
    strcat(message, "CREAT ");
    strcat(message, boxName);
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    return 1;
}

int putmsg(int sockfd, struct sockaddr_in* _serverAddr, int addrSize) {
    char message[1000];
    strcat(message, "CREAT ");
    strcat(message, boxName);
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    return 1;
}

int deletebox(int sockfd, struct sockaddr_in* _serverAddr, int addrSize, char* boxName) {
    char message[50];
    strcat(message, "DELET ");
    strcat(message, boxName);
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    return 1;
}

int closebox(int sockfd, struct sockaddr_in* _serverAddr, int addrSize) {
    char* message = "Hello";
    char buffer[1024];

    connect(sockfd, (struct sockaddr *) _serverAddr, addrSize);

    if (send(sockfd, message, strlen(message), 0) < 0) {
        // Send failed
        return 0;
    }
    if (recv(sockfd, buffer, 1024, 0) < 0) {
        // No response
        return 0;
    }
    printf(buffer);
    return 1;
}