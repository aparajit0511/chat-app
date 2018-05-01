#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>

int main(){
    
    int isexit=0;
    
    char server_message[1024] = "You have reached the server!!!!";
    
    //Create socket server
    
    long unsigned int server_socket;
    server_socket = socket(AF_INET,SOCK_STREAM,0);
    
    //Define the server Address
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
     socklen_t size;
    
    //Bind the socket to our specified IP & PORT
    
    if(bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address)) < 0){
        printf("=> Error binding connection, the socket has already been established...");
    }
    
    listen(server_socket,3);
    
    
    //Accept connection
    long unsigned int client_socket;
    client_socket = accept(server_socket,(struct sockaddr*)&server_address,&size);
    
    if(client_socket < 0){
        printf("error on accepting.... \n");
    }
    
    while(client_socket > 0){
        
        strcpy(server_message,"+> Server connected... \n");
        
        send(client_socket,&server_message,sizeof(server_message),0);
        
        printf("Enter # to Exit\n");
        
        printf("client: ");
        
        do{
            recv(client_socket,&server_message,sizeof(server_message),0);
            
            printf("%s",server_message);
            if(*server_message == '#'){
                *server_message = '*';
                isexit=1;
            }
        }while(*server_message != '*');
        
        do{
            printf("\nserver: ");
            
            do{
                scanf("%s",server_message);
                
                send(client_socket,&server_message,sizeof(server_message),0);
                
                if(*server_message == '#'){
                    send(client_socket,&server_message,sizeof(server_message),0);
                    
                    // if(*server_message == '#'){
                        
                    //      send(client_socket,&server_message,sizeof(server_message),0);
                         
                         *server_message = '*';
                         isexit=1;
                }
                }while(*server_message != '*');
                
                printf("Client: ");
                
                do{
                  recv(client_socket,&server_message,sizeof(server_message),0);
                  
                  printf("%s",server_message);
                  
                  if(*server_message == '#'){
                      *server_message = '*';
                      isexit = 1;
                  }
                }while(*server_message != '*');
            }while(!isexit);
            
            printf("GoodBye...");
            isexit=0;
            exit(1);
        }
    
    //Send the message
    
    // send(client_socket,server_message,sizeof(server_message),0);
    
    //Close the socket
    close(server_socket);
    
    return 0;
}