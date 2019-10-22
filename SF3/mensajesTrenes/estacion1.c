
//Example code: A simple server side code, which echos back the received message. 
//Handle multiple socket connections with select and fd_set on Linux 
#include <stdio.h> 
#include <string.h> //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> //close 
#include <arpa/inet.h> //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include "tren.h"
    
#define TRUE 1 
#define FALSE 0 
#define PORT 8080
    
int main(int argc , char *argv[]){ 
    struct sockaddr_in estacionAddr;  
    int option = TRUE;   
    int sockEstacion, new_socket , sockTrenes[30] ,  
          max_trenes = 30 , activity, i , valread , numDescripTren;   
    int max_numDescripTren;   
    char buffer[1025];   
         
    //puntero  los descriptores de los trenes
    fd_set descriptoresTrenes;   


    char *message = (char*)malloc(sizeof(char)*100);   
    memset(message,'\0' ,100);


    //se inicilizan el array socket trenes a valores 0
    for (i = 0; i < max_trenes; i++){   
        sockTrenes[i] = 0;   
    }   
         
    //se crea el socket estacion 
    if( (sockEstacion= socket(AF_INET , SOCK_STREAM , 0)) == 0){   
        perror("creacion de estacion fallida");   
        exit(EXIT_FAILURE);   
     }   
     
    //se configura la estacion para que reciba multiples conexiones   
    if( setsockopt(sockEstacion, SOL_SOCKET, SO_REUSEADDR, (char *)&option,sizeof(option)) < 0){   
        perror("error en las opciones del socket estacion");   
        exit(EXIT_FAILURE);   
    }   
     
    //se establece el tipo de socket 
    estacionAddr.sin_family = AF_INET;   
    estacionAddr.sin_addr.s_addr = INADDR_ANY;   
    estacionAddr.sin_port = htons( PORT );   
         
    //bind the socket to localhost 
    if (bind(sockEstacion, (struct sockaddr *)&estacionAddr, sizeof(estacionAddr))<0)   
    {   
        perror("fallo en el enlace");   
        exit(EXIT_FAILURE);   
    }   
    printf("la estacion esta escuchando en el puerto: %d \n", PORT);   
         
    //try to specify maximum of 3 pending connections for the master socket  
    if (listen(sockEstacion, 5) < 0)   
    {   
        perror("estacion a la escucha");   
        exit(EXIT_FAILURE);   
    }   
         
    //accept the incoming connection  
    int addrlen = sizeof(estacionAddr);   
    puts("esperando por conexiones de trenes...");   
         
    while(TRUE)   
    {   
        //clear the socket set  
        FD_ZERO(&descriptoresTrenes);   
     
        //add master socket to set  
        FD_SET(sockEstacion, &descriptoresTrenes);   
        max_numDescripTren = sockEstacion;   
             
        //add child sockets to set  
        for ( i = 0 ; i < max_trenes ; i++)   
        {   
            //socket descriptor  
           numDescripTren = sockTrenes[i];   
                 
            //if valid socket descriptor then add to read list  
            if(numDescripTren > 0)   
                FD_SET( numDescripTren , &descriptoresTrenes);   
                 
            //highest file descriptor number, need it for the select function  
            if(numDescripTren> max_numDescripTren)   
                max_numDescripTren = numDescripTren;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
        activity = select( max_numDescripTren + 1 , &descriptoresTrenes , NULL , NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
             
        //If something happened on the master socket ,  
        //then its an incoming connection  
        if (FD_ISSET(sockEstacion, &descriptoresTrenes))   
        {   
            if ((new_socket = accept(sockEstacion,(struct sockaddr*)&estacionAddr,(socklen_t*)&addrlen))<0)   
            {   
                perror("error en el accept");   
                exit(EXIT_FAILURE);   
            }   
             
            //inform user of socket number - used in send and receive commands  
            printf("New connection , socket descriptor is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(estacionAddr.sin_addr),
                ntohs(estacionAddr.sin_port));  
                 
            //add new socket to array of sockets  
            for (i = 0; i < max_trenes; i++)   
            {   
                //if position is empty  
                if( sockTrenes[i] == 0 )   
                {   
                    sockTrenes[i] = new_socket;   
                    printf("añadiendolo a la lista de socket trenes %d\n" , i);   
                         
                    break;   
                }   
            }   
        }   
             
        //else its some IO operation on some other socket 
        for (i = 0; i < max_trenes; i++){ 

            numDescripTren = sockTrenes[i];   
                 
        if (FD_ISSET( numDescripTren , &descriptoresTrenes)){   
                //Check if it was for closing , and also read the  
                //incoming message  
              if ((valread = read( numDescripTren , buffer, 1024)) == 0){   
               //Somebody disconnected , get his details and print  
            getpeername(numDescripTren , (struct sockaddr*)&estacionAddr ,(socklen_t*)&addrlen );   
            printf("Host disconnected , ip %s , port %d \n" ,inet_ntoa(estacionAddr.sin_addr) ,ntohs(estacionAddr.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( numDescripTren );   
                    sockTrenes[i] = 0;   
                }    else {  
                    printf("mensaje del tren %d: %s",new_socket, buffer);
                     //send back the message that came in   
                    //set the string terminating NULL byte on the end  
                    //of the data read   esto era en l version anterior cuando se enviaba el buffer
                   // buffer[valread] = '\0';
                    //message[valread] = '\0';
                    gets(message);  
                    send(numDescripTren , message , strlen(message), 0 );  
                    memset(message,'\0' ,100);
                }   
            }   
        }   
    }   
         
    return 0;   
}   