/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

typedef struct{
    int id;
    int pasajeros;
    int combustible;
    int tViaje;
    int estado;
     
}ST_TREN;

ST_TREN crearTren();
int Lee_Socket (int fd, char *Datos, int Longitud);
int Escribe_Socket (int fd, char *Datos, int Longitud);
void cargatren(ST_TREN *tren);
void pasardatosabuffer(char*linea, ST_TREN tren);
void bufferatren(const char*linea, ST_TREN*tren);



#ifndef TREN_H
#define TREN_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* TREN_H */

