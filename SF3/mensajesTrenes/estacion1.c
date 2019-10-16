
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
  

void escribirMensaje(int trenDescriptor) 
{ 
    char mensaje[MAX]; 
    int i; 
     //bucle infinito
    for (;;) { 
        bzero(mensaje, MAX); 
  
        // se lee el mensaje del cliente y se copia 
        read(trenDescriptor, mensaje, sizeof(mensaje)); 
        // se imprime desde la estacion el mensaje que mando el tren 
        printf("Mensaje del tren a la estacion: %s\t  ", mensaje); 
        bzero(mensaje, MAX); 
        i = 0; 
        // se copia el mensaje de la estacion en el buffer
        while ((mensaje[i++] = getchar()) != '\n') 
            ; 
  
        //  se envia el mensaje al cliente
        write(trenDescriptor, mensaje, sizeof(mensaje)); 
  
        // si el mensaje tiene "exit" entonces se cierra el servidor y el chat 
        if (strncmp("exit", mensaje, 4) == 0) { 
            printf("la Estacion se desconecto...\n"); 
            break; 
        } 
    } 
} 
  

int main() 
{ 
    int sockEstacion, trenDescriptor, longitud; 
    struct sockaddr_in estacionAddr, trenCliente; 
  
    // se crea el socket estacion
    sockEstacion = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockEstacion == -1) { 
        printf("fallo la creacion del socket\n"); 
        exit(0); 
    } 
    else
        printf("Se creo el socket\n"); 
    bzero(&estacionAddr, sizeof(estacionAddr)); 
  
    estacionAddr.sin_family = AF_INET; 
    estacionAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    estacionAddr.sin_port = htons(PORT); 
  
    // se enlaza el socketEstacion  a la ip standar
    if ((bind(sockEstacion, (SA*)&estacionAddr, sizeof(estacionAddr))) != 0) { 
        printf("el enlace del socket servidor fallo\n"); 
        exit(0); 
    } 
    else
        printf("enlace exitoso del socketServidor\n"); 
  
    // se pone el socketEstacion a escuchar conexiones entrantes 
    if ((listen(sockEstacion, 10)) != 0) { 
        printf("Fallo poner a la escucha a la estacion\n"); 
        exit(0); 
    } 
    else
        printf("la estacion esta a la escucha\n"); 
    longitud = sizeof(trenCliente); 
  
    //  se acepta la conexion con un tren 
    trenDescriptor = accept(sockEstacion, (SA*)&trenCliente, &longitud); 
    if (trenDescriptor < 0) { 
        printf("Fallo la aceptacion de la conexion con el tren\n"); 
        exit(0); 
    } 
    else
        printf("La estacion acepto la conexion del tren...\n"); 
  
    // Function for chatting between client and server 
    escribirMensaje(trenDescriptor); 
  
    // After chatting close the socket 
    close(trenDescriptor); 
} 
