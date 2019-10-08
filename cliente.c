#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "tren.h"

int main(int argc, char const *argv[]){
    /*int seleccion=-1;
    char comando[25];
    while(1){
        memset(comando,'\0',25);
        printf("indique 1 si desea crear un tren \n");
        printf("indique 2 si desea salir \n");
        printf("indique 3 si Diego es puto \n");
        scanf("%s\n",comando);
         
        switch(seleccion){
            case 1:    
      */          //se crea el socket
                int socketCliente;
                char buffer[200];
                //st_tren tren=crearTren();
            
                socketCliente=socket(AF_INET, SOCK_STREAM, 0);
        
                //especifica una direccion para el socket
                struct sockaddr_in  direccionDeServidor;
                direccionDeServidor.sin_family= AF_INET; //tipo de direccion
                direccionDeServidor.sin_port= htons(5040);  //castea el numero de puerto.
                direccionDeServidor.sin_addr.s_addr=INADDR_ANY;; // direccion de la ip
        
                int estado_Conexion=connect(socketCliente, (struct sockaddr *) &direccionDeServidor, sizeof(direccionDeServidor));

                if(estado_Conexion==-1){
                    printf("Hubo un error al intentar establecer la conexion\n");
                }
                
            while(1){
// se recibe los datos del servidor
                recv(socketCliente,buffer,sizeof(char)*200,0);
                printf("respuesta del servidor:%s\n",buffer);
                //close(socketCliente);
            
            //case 2:
              //  close(socketCliente);
            }
     return 0;
      
}    
       