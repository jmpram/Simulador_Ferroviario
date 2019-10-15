#include "tren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

crearTren(){
    ST_TREN tren;
    FILE* archivo=NULL;
    archivo=fopen("trenesPares.dat","rb");
    if(archivo==NULL){
        exit(EXIT_FAILURE);
        }
    fread(&tren, sizeof(ST_TREN),1,archivo);
    
    
    return tren;
}

void cargatren(char *tren){
    FILE*archivo=fopen("config.txt","r");
    fgets(tren,20,archivo);
    return;
    //fscanf(archivo,"%d %d %d %d %d",tren->id, tren->pasajeros,tren->combustible,tren->tViaje,tren->estado);
}
void pasardatosabuffer(char*linea, ST_TREN tren){
    strcat
    *linea =itoa(tren.id);
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
}
void bufferatren(const char*linea, ST_TREN*tren){
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
}
void cargadatotren (ST_TREN)

