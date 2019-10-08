#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "tren.h"
#define CANTTRENES 5

int dameMaximo (int *tabla, int n)
{
	int i;
	int max;

	if ((tabla == NULL) || (n<1))
		return 0;
		
	max = tabla[0];
	for (i=0; i<n; i++)
		if (tabla[i] > max)
			max = tabla[i];

	return max;
}
void nuevoCliente (int servidor, int *clientes, int *nClientes){
	/* Acepta la conexión con el cliente, guardándola en el array */
    struct sockaddr cliente;
    clientes[*nClientes] =accept(servidor,NULL,NULL);
    //clientes[*nClientes] =accept(servidor,&cliente,sizeof(cliente));
    (*nClientes)++;
    //char message [20];
    //strcpy(&message,"DiegoGATA");
    
	/* Si se ha superado el maximo de clientes, se cierra la conexión,
	 * se deja todo como estaba y se vuelve. */
	if ((*nClientes) >= CANTTRENES){
		close (clientes[(*nClientes) -1]);
		(*nClientes)--;
		return;
	}
	
	/* Envía su número de cliente al cliente */
	//Escribe_Socket (clientes[(*nClientes)-1], (char *)nClientes, sizeof(int));
       send(clientes[(*nClientes)-1],(char*)nClientes,sizeof(int),0);/* MSG_WAITALL PARA TENER EN CUENTA*/
       //send(clientes[(*nClientes)-1],"Diego reputo",sizeof(char)*12,0);/* MSG_WAITALL PARA TENER EN CUENTA*/
	
        /* Escribe en pantalla que ha aceptado al cliente y vuelve */
	printf ("Aceptado cliente %d\n", *nClientes);
	return;
}

int main(int argc, char const *argv[])
{
    char mensaje_Servidor[1000]="te has conectado a mi, al servidor.";
    fd_set idtrenes;
    int vsocketCliente[CANTTRENES];
    int numeroClientes=0;
    int maximo;
    int buffer;

    //se crea el socket
    int socketServidor; //id de servidor
    socketServidor=socket(AF_INET, SOCK_STREAM, 0);

    if(socketServidor==-1){
        printf("error al abrir el servidor Estacion");
    }// CHEQUEO SI SE ABRIO BIEN EL SERVIDOR 
    
    int option=1;
    setsockopt(socketServidor,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
    //especifica una direccion para el socket
    struct sockaddr_in  direccionDeServidor;
    direccionDeServidor.sin_family= AF_INET; //tipo de direccion, modo internet
    direccionDeServidor.sin_port= htons(5040);  //castea el numero de puerto.
    direccionDeServidor.sin_addr.s_addr=INADDR_ANY; // direccion de la ip

    //le decimos al socket servidor en que ip y puerto escuchar.
    bind(socketServidor,(struct sockaddr*) &direccionDeServidor,sizeof(direccionDeServidor));
    //se pone a la escucha
    listen(socketServidor,CANTTRENES); 

    while(1){
        FD_ZERO (&idtrenes);
        FD_SET(socketServidor,&idtrenes);
    
        for (int i=0; i<numeroClientes; i++){
            FD_SET (vsocketCliente[i], &idtrenes);
        }
    
        maximo = dameMaximo (vsocketCliente, numeroClientes);
    
        if (maximo < socketServidor){
            maximo = socketServidor;
        }
    
        select(maximo+1,&idtrenes,NULL,NULL,NULL);
        for (int i=0; i<numeroClientes; i++){
            if (FD_ISSET (vsocketCliente[i], &idtrenes)){
                /* Se lee lo enviado por el cliente y se escribe en pantalla */
                if ((recv (vsocketCliente[i], (char *)&buffer, sizeof(int),0) > 0)){
                    printf ("Cliente %d envía %d\n", i+1, buffer);
                }
                else{
                    /* Se indica que el cliente ha cerrado la conexión y se
                     * marca con -1 el descriptor para que compactaClaves() lo
                     * elimine */
                    printf ("Cliente %d ha cerrado la conexión\n", i+1);
                    vsocketCliente[i] = -1;
                }
            }
        }

		/* Se comprueba si algún cliente nuevo desea conectarse y se le
		 * admite */
	if (FD_ISSET (socketServidor, &idtrenes))
            nuevoCliente (socketServidor, vsocketCliente, &numeroClientes);
        close(socketServidor);
    
        return 0;
    }
}

