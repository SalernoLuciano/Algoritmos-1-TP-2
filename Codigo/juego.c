#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "perfil.h"
#include "batalla.h"
#include <string.h>

int main(){
	juego_t juego;
	bool juego_terminado = false;
	bool turno_rohan = true;
	bool turno_isengard = true;
	char nombre_rohan[ 20 ] = "Rohan";
	char nombre_isengard[ 20 ] = "Isengard";

	inicializar_juego( &juego );
	printf( "Jugador 1: %c\n", juego.j1.tipo );
	printf( "Jugador 2: %c\n", juego.j2.tipo );
	if( juego.cant_jugadores == 2 ){
		while( juego_terminado == false ){
			turno( &turno_rohan, ROHAN, &juego, nombre_rohan, &( juego ).llegadas_rohan, "Hombre", "Elfo", juego.hombres, juego.elfos, &turno_isengard, juego.rohan, &juego_terminado );
			turno( &turno_isengard, ISENGARD, &juego, nombre_isengard, &( juego ).llegadas_isengard, "Orco", "Uruk-Hai", juego.orcos, juego.uruk, &turno_rohan, juego.isengard, &juego_terminado );
			aumentar_energia( &( juego ).j1, &( juego ).j2 );				
		}
	}else if( juego.cant_jugadores == 1 ){
		while( juego_terminado == false ){
			turno_vs_cpu( &turno_rohan, ROHAN, &juego, nombre_rohan, &( juego ).llegadas_rohan, "Hombre", "Elfo", juego.hombres, juego.elfos, &turno_isengard, juego.rohan, &( juego ).cantidad_rohan, &juego_terminado, ULTIMA_FILA );
			turno_vs_cpu( &turno_isengard, ISENGARD, &juego, nombre_isengard, &( juego ).llegadas_isengard, "Orco", "Uruk-Hai", juego.orcos, juego.uruk, &turno_rohan, juego.isengard, &( juego ).cantidad_isengard, &juego_terminado, PRIMER_FILA );
			aumentar_energia( &( juego ).j1, &( juego ).j2 );
		}
	}
	return 0;
} 