#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "perfil.h"
#include "batalla.h"

int main(){
	juego_t juego;
	bool juego_terminado = false;
	bool turno_rohan = true;
	bool turno_isengard = true;

	inicializar_juego(&juego);
	while(juego_terminado == false){
		while(turno_rohan){
			system("clear");
			if(juego.j1.tipo == ROHAN){
				actualizar_terreno(juego.terreno);
				printf("Energia Rohan: %i\n", juego.j1.energia);
				printf("Llegadas Rohan: %i", juego.llegadas_rohan);
				printf("\n\t\tTURNO ROHAN.\nDesea crear un personaje?.(S/N).\n");
				scanf(" %c", &(juego.rta_rohan));
				if(juego.rta_rohan == 'S' || juego.rta_rohan == 's'){
					printf("Que personaje desea crear?.\n1-Hombre.(3pts. de energia)\n2-Elfo.(8pts. de energia)\n");
					scanf("%i", &(juego.crear_rohan));
					while(juego.crear_rohan !=1 && juego.crear_rohan !=2){
						printf("ERROR. Ingrese una opcion valida.\n1-Hombre.(3pts. de energia)\n2-Elfo.(8pts. de energia)\n");
						scanf("%i", &(juego.crear_rohan));
					}
					if(juego.crear_rohan == 1){
						if(juego.j1.energia >= juego.hombres.pts_energia){
							posicionar_personaje(&juego, juego.hombres);
						}else{
							printf("No tiene puntos suficientes para crear a un Hombre.\n");
						}
					}else{
						if(juego.j1.energia >= juego.elfos.pts_energia){
							posicionar_personaje(&juego, juego.elfos);
						}else{
							printf("No tiene puntos suficientes para crear a un Elfo.\n");
						}
					}
				}else{
					turno_rohan = false;
					turno_isengard = true;
				}
			}else if(juego.j2.tipo == ROHAN){
				actualizar_terreno(juego.terreno);
				printf("Energia Rohan: %i\n", juego.j2.energia);
				printf("Llegadas Rohan: %i", juego.llegadas_rohan);
				printf("\n\t\tTURNO ROHAN.\nDesea crear un personaje?.(S/N).\n");
				scanf(" %c", &(juego.rta_rohan));
				if(juego.rta_rohan == 'S' || juego.rta_rohan == 's'){
					printf("Que personaje desea crear?.\n1-Hombre.(3pts. de energia)\n2-Elfo.(8pts. de energia)\n");
					scanf("%i", &(juego.crear_rohan));
					while(juego.crear_rohan !=1 && juego.crear_rohan !=2){
						printf("ERROR. Ingrese una opcion valida.\n1-Hombre.(3pts. de energia)\n2-Elfo.(8pts. de energia)\n");
						scanf("%i", &(juego.crear_rohan));
					}
					if(juego.crear_rohan == 1){
						if(juego.j2.energia >= juego.hombres.pts_energia){
							posicionar_personaje(&juego, juego.hombres);
						}else{
							printf("No tiene puntos suficientes para crear a un Hombre.\n");
						}
					}else{
						if(juego.j2.energia >= juego.elfos.pts_energia){
							posicionar_personaje(&juego, juego.elfos);
						}else{
							printf("No tiene puntos suficientes para crear a un Elfo.\n");
						}
					}
				}else{

					turno_rohan = false;
					turno_isengard = true;
				}
			}
			
		}
		jugar(&juego, ROHAN, juego.rohan->fila);
		if(juego.llegadas_rohan == LLEGADAS_GANAR){
				juego_terminado = true;
				turno_isengard=false;
				turno_rohan = false;
				system("clear");
				printf("Rohan Gana!!!\n");
			}
		while(turno_isengard){
			system("clear");
			if(juego.j1.tipo == ISENGARD){
				actualizar_terreno(juego.terreno);
				printf("Energia Isengard: %i\n", juego.j1.energia);
				printf("Llegadas Isengard: %i", juego.llegadas_isengard);
				printf("\n\t\tTURNO ISENGARD.\nDesea crear un personaje?.(S/N).\n");
				scanf(" %c", &(juego.rta_isengard));
				if(juego.rta_isengard == 'S' || juego.rta_isengard == 's'){
					printf("Que personaje desea crear?.\n1-Orco.(3pts. de energia)\n2-Uruk-Hai.(8pts. de energia)\n");
					scanf("%i", &(juego.crear_isengard));
					while(juego.crear_isengard !=1 && juego.crear_isengard !=2){
						printf("ERROR. Ingrese una opcion valida.\n1-Orco.(3pts. de energia)\n2-Uruk-Hai.(8pts. de energia)\n");
						scanf("%i", &(juego.crear_isengard));
					}
					if(juego.crear_isengard == 1){
						if(juego.j1.energia >= juego.orcos.pts_energia){
							posicionar_personaje(&juego, juego.orcos);
						}else{
							printf("No tiene puntos suficientes para crear a un Orco.\n");
						}
					}else{
						if(juego.j1.energia >= juego.uruk.pts_energia){
							posicionar_personaje(&juego, juego.uruk);
						}else{
							printf("No tiene puntos suficientes para crear a un Uruk-Hai.\n");
						}
					}
				}else{
					turno_isengard = false;
					turno_rohan = true;
				}
			}else if(juego.j2.tipo == ISENGARD){
				actualizar_terreno(juego.terreno);
				printf("Energia Isengard: %i\n", juego.j2.energia);
				printf("Llegadas Isengard: %i", juego.llegadas_isengard);
				printf("\n\t\tTURNO ISENGARD.\nDesea crear un personaje?.(S/N).\n");
				scanf(" %c", &(juego.rta_isengard));
				if(juego.rta_isengard == 'S' || juego.rta_isengard == 's'){
					printf("Que personaje desea crear?.\n1-Orco.(3pts. de energia)\n2-Uruk-Hai.(8pts. de energia)\n");
					scanf("%i", &(juego.crear_isengard));
					while(juego.crear_isengard !=1 && juego.crear_isengard !=2){
						printf("ERROR. Ingrese una opcion valida.\n1-Orco.(3pts. de energia)\n2-Uruk-Hai.(8pts. de energia)\n");
						scanf("%i", &(juego.crear_isengard));
					}
					if(juego.crear_isengard == 1){
						if(juego.j2.energia >= juego.orcos.pts_energia){
							posicionar_personaje(&juego, juego.orcos);
						}else{
							printf("No tiene puntos suficientes para crear a un Orco.\n");
						}
					}else{
						if(juego.j2.energia >= juego.uruk.pts_energia){
							posicionar_personaje(&juego, juego.uruk);
						}else{
							printf("No tiene puntos suficientes para crear a un Uruk-Hai.\n");
						}
					}
				}else{
					turno_isengard = false;
					turno_rohan = true;
				}		
			}
			
		}
		jugar(&juego, ISENGARD, juego.isengard->fila);
		if(juego.llegadas_isengard == LLEGADAS_GANAR){
			juego_terminado = true;
			turno_isengard=false;
			turno_rohan = false;
			system("clear");
			printf("Isengard. Gana!!!\n");
		}						
		juego.j1.energia++;
		juego.j2.energia++;
		if(juego.j1.energia > ENERGIA_MAX){
			juego.j1.energia = ENERGIA_MAX;
		}
		if(juego.j2.energia > ENERGIA_MAX){
			juego.j2.energia = ENERGIA_MAX;
		}		
	}
	return 0;
} 