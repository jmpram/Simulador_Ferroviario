
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8080
#define SA struct sockaddr 

void escribirMensaje(int sockTren) { 
    char mensaje[MAX]; 
    int i; 
    for (;;) { 
        bzero(mensaje, sizeof(mensaje)); 
        printf(" \n Ingrese el mensaje: \n"); 
        i = 0; 
        while ((mensaje[i++] = getchar()) != '\n'); 
        
        write(sockTren, mensaje, sizeof(mensaje)); 
        bzero(mensaje, sizeof(mensaje)); 
        read(sockTren, mensaje, sizeof(mensaje)); 
        printf("Estacion envio: %s \n", mensaje); 
        if ((strncmp(mensaje, "exit", 4)) == 0) { 
            printf("El tren se desconecto...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    int sockTren; 
    struct sockaddr_in estacionAddr; 
  
    // se crea el socket
    sockTren = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockTren == -1) { 
        printf("la creacion del socket fallo...\n"); 
        exit(0); 
    } 
    else
        printf("Se creo el tren..\n"); 
    bzero(&estacionAddr, sizeof(estacionAddr)); 
  
    // se asigna la ip y el puerto a usar
    estacionAddr.sin_family = AF_INET; 
    estacionAddr.sin_addr.s_addr = INADDR_ANY; 
    estacionAddr.sin_port = htons(PORT); 
  
    // se conecta el tren con la estacion
    if (connect(sockTren, (SA*)&estacionAddr, sizeof(estacionAddr)) != 0) { 
        printf("La conexion con la estacion fallo...\n"); 
        exit(0); 
    } 
    else
        printf("Esta conectado con la estacion..\n"); 
  
    
    escribirMensaje(sockTren); 
  
    
    close(sockTren); 
} 
