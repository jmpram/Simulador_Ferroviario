#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //para windows es windows.h tmb se usa gotoxy
#include <pthread.h>
#include <string.h>

typedef struct{
	int combustible;
	char *cadena;
	int x;
	int y;
}st_tren;

void gotoxy(int x, int y){

	printf("\033[%d;%df",y,x );

}

void * saludo(void * args){ //recibe argumento  puntero a void
	st_tren * stTren=(st_tren*)args;
	//char *cadena=(char*)args;
	int i;
	//int x=10;
	//int y=20; cordenadas donde imprimirse
	for (int i = 0; i< strlen(stTren->cadena); ++i){
		fflush (stdout); //limpia la salida
		//gotoxy(x,y);
		gotoxy(stTren->x,stTren->y);
		stTren->x++;
		//x++; //imprime todo sobre las cordenadas dadas.
		printf("%c",stTren->cadena[i]); 
		sleep(1); //duermo el hilo por 1 segundo
	}
	printf("\n");
}		

int main(int argc,char const *argv[]){
	st_tren tren1; //instancio mi estructura tren
	tren1.cadena="hola soy"; // le asigno un saludo
	tren1.combustible=1000;// le asigno un combustible.
	tren1.x=10;
	tren1.y=20;
	st_tren tren2; 
	tren2.cadena="..un tren";
	tren2.combustible=1000;
	tren2.x=20;
	tren2.y=20;
	//char *cadena="ejecutandose el proceso saludo";
	pthread_t proceso1;//INSTANCIO UN HILO       
	pthread_t proceso2;     
	 //el parametro null puede recibir otra cadena pero recibe parametro void
	pthread_create(&proceso1,NULL,saludo,(void*)&tren1); //creo el hilo
	pthread_create(&proceso2,NULL,saludo,(void*)&tren2);
	pthread_join(proceso1,NULL);
	pthread_join(proceso2,NULL);
	return 0;
}

