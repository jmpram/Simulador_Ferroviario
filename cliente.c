#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {

    struct sockaddr_in direccionEstacionCentral; //se instancia el socket
    direccionEstacionCentral.sin_family= AF_INET;
    direccionEstacionCentral.sin_port= htons(5040); //en que puerto debe escuchar hay que poner un numero
    direccionEstacionCentral.sin_addr.s_addr=inet_addr("192.168.56.1"); //escuchar en cualquier interfaz del SO
    
    int yoCliente=socket(AF_INET, SOCK_STREAM,0);
        if(0!=connect(yoCliente,(void*)&direccionEstacionCentral,sizeof(direccionEstacionCentral))){
        perror("no se pudo establecer la conexion");
        return 1;
        }
    
    while(1){
        
        char mensaje[100];
        fscanf("%s",mensaje); // LA ESTACION LEE UN ARCHIVO SETEA EL TREN Y LO ENVIA.
        
        send(yoCliente,mensaje,strlen(mensaje),0);
        
    }
    
    return (EXIT_SUCCESS);
}
    

