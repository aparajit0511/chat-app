#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>


int main(){
      int isexit=0;
     //Create Scoket
     
     int network_socket;
     network_socket = socket(AF_INET,SOCK_STREAM,0);
     
     //Specify an address for the socket
     
     struct sockaddr_in server_address;
     server_address.sin_family = AF_INET;
     server_address.sin_port = htons(9002);
     server_address.sin_addr.s_addr = INADDR_ANY;
     
     int connection_status = connect(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));
     
     //Check for error with the connection
     
     if(connection_status == -1){
         printf("There was an error making a connection to the remote socket:\n\n");
     }
     
     //Recieve data from server
     
     char server_response[1024];
     
     recv(network_socket,&server_response,sizeof(server_response),0);
     
     //Printout the server's response
     
     printf("The server sends its regards:%s \n",server_response);
     
     do{
          printf("Client: ");
          
          do{
               scanf("%s",server_response);
               
               send(network_socket,&server_response,sizeof(server_response),0);
               
               if(*server_response == '#'){
                    send(network_socket,&server_response,sizeof(server_response),0);
                    
                    *server_response = '*';
                    isexit = 1;
               }
          }while(*server_response != '*');
          
          printf("Server: ");
          do{
               recv(network_socket,&server_response,sizeof(server_response),0);
               
               printf("%s",server_response);
               
               if(*server_response == '#'){
                    *server_response = '*';
                    isexit = 1;
               }
          }while(*server_response != '*');
          
          printf("\n");
          
          
     }while(!isexit);
     
     //Close the socket
     
     close(network_socket);
      
     
    return 0;
}