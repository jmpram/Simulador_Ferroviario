#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	//se crea el socket
int socketCliente;
socketCliente=socket(AF_INET, SOCK_STREAM, 0);

//especifica una direccion para el socket
struct sockaddr_in  direccionDeServidor;
direccionDeServidor.sin_family= AF_INET; //tipo de direccion
direccionDeServidor.sin_port= htons(5040);  //castea el numero de puerto.
direccionDeServidor.sin_addr.s_addr=INADDR_ANY; // direccion de la ip

int estado_Conexion=connect(socketCliente, (struct sockaddr *) &direccionDeServidor, sizeof(direccionDeServidor));

if(estado_Conexion==-1){
	printf("Hubo un error al intentar establecer la conexion\n");
}
// se recibe los datos del servidor
char respuesta_Servidor[1000];
recv(socketCliente, &respuesta_Servidor, sizeof(respuesta_Servidor), 0);

printf("respuesta del servidor:%s\n",respuesta_Servidor);

close(socketCliente);
return 0;
}