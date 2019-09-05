#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	char mensaje_Servidor[1000]="te has conectado a mi, al servidor.";
//se crea el socket
int socketServidor;
socketServidor=socket(AF_INET, SOCK_STREAM, 0);

//especifica una direccion para el socket
struct sockaddr_in  direccionDeServidor;
direccionDeServidor.sin_family= AF_INET; //tipo de direccion
direccionDeServidor.sin_port= htons(5040);  //castea el numero de puerto.
direccionDeServidor.sin_addr.s_addr=INADDR_ANY; // direccion de la ip

//le decimos al socket servidor en que ip y puerto escuchar.
bind(socketServidor,(struct sockaddr*) &direccionDeServidor,sizeof(direccionDeServidor));
//se pone a la escucha
listen(socketServidor,5); 

int socketCliente; //acepta la conexion y la aloja en la variable socketcliente
socketCliente=accept(socketServidor,NULL,NULL);
//se envia el mensaje 
send(socketCliente,mensaje_Servidor,sizeof(mensaje_Servidor),0);

close(socketServidor);

return 0;
}
