#include "tren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

   void createTren(ST_TREN * tren){
     
     memset(tren->idTren,'\0',8);
     memset(tren->estacionOrigen,'\0',strlen(tren->estacionOrigen));
     memset(tren->estacionDestino,'\0',strlen(tren->estacionDestino));
     tren->pasajeros=0;
     tren->combustible=0;
     tren->tViaje=0;
     strcpy(tren->estado,"estacion");//estacion,anden, transito
     memset(tren->motivo ,'\0',strlen(tren->motivo));//PASO O ANDEN
}


void cargatren(char * tren){
    FILE*archivo=fopen("config.txt","r");
    fgets(tren,20,archivo);
    
}
/*void pasardatosabuffer(char*linea, ST_TREN tren){
    strcat
    *linea =itoa(tren.idTren);
    linea=linea+1; //dejo un epacio
    *linea=' ';
    itoa (tren.pasajeros,linea,10);//cuento pos de pasajeros
    linea = linea+1 //1 para el espacio
    *linea=' ';
    itoa (tren.combustible,linea,10);
    linea=linea+1;
    *linea=' ';
    itoa(tren.tViaje,linea,10);
    linea=linea+1;
    *linea=' ';
    itoa (tren.estado,linea,10);
    *linea='\0';
}*/
/*void bufferatren(const char * linea, ST_TREN*tren){
    int cant=0;
    char* token=malloc(5);
    memset(token,'\0',5);
    token=strtok(token,' ');
    tren->id=token;
    while(token){
        cant++;
        if (cant==2)
            strcpy(tren->pasajeros,token);
        if (cant==3)
            tren->estado=atoi(token);
        if(cant==4)
            tren->combustible=atoi(token);
        token=strtok(NULL,' ');
    }
}*/
