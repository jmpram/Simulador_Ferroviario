#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

    struct sockaddr_in estacionCentral; //se instancia el socket
    estacionCentral.sin_family= AF_INET;
    estacionCentral.sin_port= htons(5040); //en que puerto debe escuchar hay que poner un numero
    estacionCentral.sin_addr.s_addr=INADDR_ANY; //escuchar en cualquier interfaz del SO
    
    
    int idEstacionCentral=socket(AF_INET,SOCK_STREAM,0);// la funcion pide un socket, nos devuelve un identificador del mismo.
   // ahora asociamos el socket obtenido con dirServidor
    
    int activado=1;
    setsockopt(idEstacionCentral, SOL_SOCKET, SO_REUSEADDR,&activado, sizeof(activado));
    
    
    if(bind(idEstacionCentral,(void*) &estacionCentral, sizeof(estacionCentral))!=0){ //el bild es el enlace al puerto
        perror("Fallo la conexion\n");
        return 1;
        
    }
    printf("conexion exitosa\n");
    
    listen(idEstacionCentral,2);// UNA VEZ CONECTADO (BIND) TENEMOS QUE ESCUCHAR (LISTEN)
    //--------------------------------------------------
      //    ACEPTAR CONEXIONES
    struct sockaddr_in clienteOtraEstacion;//
    unsigned int tamanoDirCliente;// INDICAN QUIEN SE CONECTO
    
    int idClienteEstacion=accept(idEstacionCentral,(void*)&clienteOtraEstacion, &tamanoDirCliente); 
    //ACEPTA LA CONEXION Y DEVUELVE EL ID DE QUIEN SE CONECTO
    printf("Se acepto que el cliente %d envie trenes.", idClienteEstacion);
    
     send(idClienteEstacion,"mensaje enviado a la estacion que se conecto",45,0);
    //PODEMOS ENVIAR LA CANT DE SENDS QUE QUERAMOS
    //------------------------------------------------
    //... CREAMOS LA SECCION PARA RECIBIR MENSAJES
    
    char* msjRecibido= malloc(45);
    while (1){
    int bytesRecibidos=recv(idClienteEstacion,msjRecibido,44,0);// en el 0 puede ir  MSG_WAITALL, hasta que no reciba lo que pidio 44 bytes
    if(bytesRecibidos<=0){
        perror("La otra estacion se desconecto");
        return 1;
        }
       
        msjRecibido[bytesRecibidos] ='\0'; // TENEMOS QUE ESCRIBIR EN LA ULTIMA POSICION ESTO SI NO ENVIE STRINGS.
        printf("%s",msjRecibido);
    }
    free(msjRecibido);
    // FIN SECCION RECIBIR MENSJES
    
   
   /* wint32_t tamanoDelTren; //paquete
    recv(clienteOtraEstacion, &tamanoDelTren,MSG_WAITALL);
    char msjRecibido=malloc(tamanoDelTren);  //RECIBIRIA UN DATO TIPO TREN
    recv(clienteOtraEstacion,msjRecibido,tamanoDelTreN,MSG_WAITALL);
    */
    return 0;
}

