#include <stdio.h>
#include "batalla.h"
#include "perfil.h"
#include <time.h>
#include <stdlib.h> 
#include <ctype.h>

void validar_respuesta_crear( char* rta ){
	while( ( *rta ) != 'S' && ( *rta ) !='N' ){
		printf( "ERROR. No es una respuesta valida. Si quiere crear un personaje insgre 'S' o 's'\nEn caso contrario ingrese 'N' o 'n'.\n" );
		scanf( " %c", rta );
		*rta=toupper( *rta );
	}
}
void cargar_mapa_inicial( char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ] ){
	for( int fila = PRIMER_FILA; fila<MAX_TERRENO_FIL; fila++ ){
		for( int columna = PRIMER_COLUMNA; columna<MAX_TERRENO_COL; columna++ ){
			terreno[ fila ][ columna ] = TERRENO_VACIO;
		}
	}
}
void cargar_personajes( juego_t* juego ){
	for( int i=0; i< juego->cantidad_isengard; i++ ){
			juego->terreno[ juego->isengard[ i ].fila ][ juego->isengard[ i ].columna ]=juego->isengard[ i ].codigo;
	}
	for( int r=0; r<juego->cantidad_rohan; r++ ){
			juego->terreno[ juego->rohan[ r ].fila ][ juego->rohan[ r ].columna ]=juego->rohan[ r ].codigo;
	}
}
void actualizar_terreno( juego_t* juego ){
	for( int fila = PRIMER_FILA; fila < MAX_TERRENO_FIL; fila++ ){
		for( int col = PRIMER_COLUMNA; col<MAX_TERRENO_COL; col++ ){
			printf( " %c\t",juego->terreno[ fila ][ col ] );
		}
		printf( "\n" );
	}
	printf( "\n" );
}
void plus( jugador_t jugador, juego_t* juego ){
	if( jugador.tipo == ROHAN ){
		juego->plus_rohan = jugador.intensidad * ( rand()%RANGO_PLUS );
	}else{
		juego->plus_isengard = jugador.intensidad * ( rand()%RANGO_PLUS );
	}
}
void inicializar_personajes_fijos( personaje_t* personaje, int plus ){
		personaje->vida = VIDA_ELFO_URUK - plus;
		personaje->ataque = ATAQUE_ELFO_URUK + plus;
		personaje->pts_energia = PTS_ELFO_URUK;
}
void inicializar_personajes_movibles( personaje_t* personaje, int plus ){
		personaje->vida = VIDA_HOMBRE_ORCO - plus;
		personaje->ataque = ATAQUE_HOMBRE_ORCO + plus;
		personaje->pts_energia = PTS_HOMBRE_ORCO;
}
void posicionar_fijo_aleatorio(  int* cantidad, personaje_t personaje, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], personaje_t vec_personajes[ MAX_PERSONAJES ], int amplitud ){
	int fil_rndm;
	int col_rndm;
		for( ; ( *cantidad )<PERSONAJES_INICIALES; ( *cantidad )++ ){
			fil_rndm = ( rand()%4 )+amplitud;
			col_rndm = rand()%10;
			for( int i=0; i<( *cantidad ); i++ ){
				while( vec_personajes[ i ].fila == fil_rndm && vec_personajes[ i ].columna == col_rndm ){
					fil_rndm = ( rand()%4 )+amplitud;
					col_rndm = rand()%10;
				}
			}
			vec_personajes[ ( *cantidad ) ] = personaje;
			vec_personajes[ ( *cantidad ) ].fila = fil_rndm;
			vec_personajes[ ( *cantidad ) ].columna = col_rndm;
		}
}
void posicionar_movil_aleatorio(  int* cantidad, personaje_t personaje, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], personaje_t vec_personajes[ MAX_PERSONAJES ], jugador_t* jugador, int fila ){
	int col_rndm;
	col_rndm = rand()%10;
	while( ( terreno[ fila ][ col_rndm ] )!=TERRENO_VACIO ){
		col_rndm = rand()%10;
	}
	vec_personajes[ ( *cantidad ) ] = personaje;
	vec_personajes[ ( *cantidad ) ].fila = fila;
	vec_personajes[ ( *cantidad ) ].columna = col_rndm;
	( *cantidad )++;
	( *jugador ).energia -= personaje.pts_energia;
}
void posicionar_moviles( char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], int fila_inicial, personaje_t vec_personajes[ MAX_PERSONAJES ], personaje_t personaje, int* cantidad_personajes, char fila[ 10 ], char bando[ 15 ] ){
	int col;
	printf( "Elija una columna ( del 0 al 9 ) de la %s fila donde quiera posicionar al %s.\n", fila, bando );
	scanf( "%i", &col );
	while( ( col > ULTIMA_COLUMNA ) || col < PRIMER_COLUMNA ){
		printf( "ERROR: el numero no es valido.\nElija una columna ( del 0 al 9 ) de la %s fila donde quiera posicionar al %s.\n", fila, bando );
		scanf( "%i", &col );
	}
	while( terreno[ fila_inicial ][ col ]!= TERRENO_VACIO ){
		printf( "ERROR: Ese espacio esta ocupado.\nElija una columna ( del 0 al 9 ) de la %s fila donde quiera posicionar al %s.\n", fila, bando );
		scanf( "%i", &col );
	}
	vec_personajes[ ( *cantidad_personajes ) ] = personaje;
	vec_personajes[ ( *cantidad_personajes ) ].fila = fila_inicial;
	vec_personajes[ ( *cantidad_personajes ) ].columna = col;
	( *cantidad_personajes )++;
}
void posicionar_fijos( int primer_fila_campo, int ultima_fila_campo, char rango[ 15 ], char pers[ 5 ], char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], personaje_t vec_personajes[ MAX_PERSONAJES ], int* cantidad_personajes, personaje_t personaje ){
	int fila;
	int col;
	printf( "Elija una fila de su mitad de terreno donde quiera ubicar a su %s.\n", pers );
	scanf( "%i", &fila );
	while( ( fila < primer_fila_campo ) || ( fila > ultima_fila_campo ) ){
		printf( "ERROR: el numero no es valido.\nElija una fila %s donde quiera posicionar al %s.\n", rango, pers );
		scanf( "%i", &fila );
	}
	printf( "Elija una columna donde quiera ubicar a su %s.\n", pers );
	scanf( "%i", &col );
	while( ( col < PRIMER_COLUMNA ) || ( col ) > ULTIMA_COLUMNA ){
		printf( "ERROR: el numero no es valido.\nElija una columna ( del 0 al 9 ) donde quiera posicionar al %s.\n", pers );
		scanf( "%i", &col );
	}
	while( terreno[ fila ][ col ]!= TERRENO_VACIO ){
		printf( "ERROR: Ese espacio esta ocupado.\nElija una fila %s donde quiera posicionar al %s.\n", rango, pers );
		scanf( "%i", &fila );
		while( ( fila < primer_fila_campo ) || ( fila > ultima_fila_campo ) ){
			printf( "ERROR: el numero no es valido.\nElija una fila %s donde quiera posicionar al %s.\n", rango, pers );
			scanf( "%i", &fila );
		}
		printf( "ERROR: Ese espacio esta ocupado.\nElija una columna ( del 0 al 9 ) donde quiera posicionar al %s.\n", pers );
		scanf( "%i", &col );
		while( ( col < PRIMER_COLUMNA ) || ( col > ULTIMA_COLUMNA ) ){
			printf( "ERROR: el numero no es valido.\nElija una columna ( del 0 al 9 ) donde quiera posicionar al %s.\n", pers );
			scanf( "%i", &col );
		}
	}
	vec_personajes[ ( *cantidad_personajes ) ] = personaje;
	vec_personajes[ ( *cantidad_personajes ) ].fila = fila;
	vec_personajes[ ( *cantidad_personajes ) ].columna = col;
	( *cantidad_personajes )++;
}
void personaje_murio( personaje_t personaje[ MAX_PERSONAJES ], int i, int* cantidad ){
	if( personaje[ i ].vida == 0 ){
		for( int j=i+1; j<( *cantidad ); j++ ){
			personaje[ i ] = personaje[ j ];	
		}
		( *cantidad )--;
	}
}
void personaje_llego( int* cantidad, personaje_t personaje[ MAX_PERSONAJES ], int* llegadas, int i ){
	if( personaje[ i ].codigo == HOMBRE && personaje[ i ].fila == PRIMER_FILA && personaje[ i ].vida > 0 ){
			( *llegadas )++;
			for( int j=i+1; j<( *cantidad ); j++ ){
				personaje[ i ] = personaje[ j ];	
			}
			( *cantidad )--;
		}else if( personaje[ i ].codigo == ORCO && personaje[ i ].fila == ULTIMA_FILA && personaje[ i ].vida > 0 ){
			( *llegadas )++;
			for( int j=i+1; j<( *cantidad ); j++ ){
				personaje[ i ] = personaje[ j ];	
			}
			( *cantidad )--;
		}
}
void eliminar_personaje( int* cantidad, personaje_t personaje[ MAX_PERSONAJES ], int* llegadas ){
	for( int i=0; i<( *cantidad ); i++ ){
		personaje_murio( personaje, i, cantidad );
		personaje_llego(  cantidad, personaje, llegadas, i );
	}		
}
void movimiento_personajes( int* cantidad_personajes, personaje_t personaje[ MAX_PERSONAJES ] , char bando, int posicion_personaje, int* llegadas, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], int movimiento, int fila_llegada ){
	for( int i=0; i<( *cantidad_personajes );i++ ){
		if( personaje[ i ].codigo == HOMBRE ){	
			if( terreno[ personaje[ i ].fila+movimiento ][ personaje[ i ].columna ] == TERRENO_VACIO || terreno[ personaje[ i ].fila+movimiento ][ personaje[ i ].columna ] == ELFO ){
				personaje[ i ].fila +=movimiento;
			}
		}else if( personaje[ i ].codigo == ORCO ){	
			if( terreno[ personaje[ i ].fila+movimiento ][ personaje[ i ].columna ] == TERRENO_VACIO || terreno[ personaje[ i ].fila+movimiento ][ personaje[ i ].columna ] == URUK ){
				personaje[ i ].fila +=movimiento;
			}
		}
	}
	for( int i=0; i<( *cantidad_personajes ); i++ ){
		if( personaje[ i ].fila == fila_llegada ){
			eliminar_personaje( cantidad_personajes, personaje, llegadas );
		}
	}
}
void inicializar_juego( juego_t* juego ){
	juego->uruk.codigo = URUK;
	juego->elfos.codigo = ELFO; 
	juego->hombres.codigo = HOMBRE; 
	juego->orcos.codigo = ORCO;  
	juego->cantidad_isengard = 0;
	juego->cantidad_rohan = 0;
	juego->turno_rohan = true;
	juego->turno_isengard = true;
	juego->llegadas_rohan = 0;
	juego->llegadas_isengard = 0;
	srand( ( unsigned )time( NULL ) );
	
	cargar_mapa_inicial( juego->terreno );
	printf( "Completar Datos para el JUGADOR 1.\n" );	
	perfil( &( juego )->j1.tipo, &( juego )->j1.intensidad );
	if( juego->j1.tipo == ROHAN ){
		juego->j2.tipo = ISENGARD;
	}else{
		juego->j2.tipo = ROHAN;
	}
	juego->j2.intensidad = INTENSIDAD_MAX - juego->j1.intensidad;
	
	plus( juego->j1, juego );
	plus( juego->j2, juego );
	
	juego->j1.energia = ENERGIA_INICIAL;
	juego->j2.energia = ENERGIA_INICIAL;
	
	printf( "1-Jugador vs. CPU\n2-Jugador 1 vs. Jugador 2\n" );
	scanf( "%i",&( juego->cant_jugadores ) );
	
	system( "clear" );
	inicializar_personajes_fijos( &( juego )->elfos, juego->plus_rohan );
	inicializar_personajes_movibles( &( juego )->hombres, juego->plus_rohan );
	inicializar_personajes_fijos( &( juego )->uruk, juego->plus_isengard );
	inicializar_personajes_movibles( &( juego )->orcos, juego->plus_isengard );	
	posicionar_fijo_aleatorio( &( juego )->cantidad_isengard, juego->uruk, juego->terreno, juego->isengard, 1  );
	posicionar_fijo_aleatorio( &( juego )->cantidad_rohan, juego->elfos, juego->terreno, juego->rohan, 5 );
}
void posicionar_personaje( juego_t* juego, personaje_t personaje ){
	if( personaje.codigo == HOMBRE ){
		posicionar_moviles( ( *juego ).terreno, ULTIMA_FILA, juego->rohan, personaje, &( *juego ).cantidad_rohan, "ultima", "Hombre" );
	}
	if( personaje.codigo == ORCO ){
		posicionar_moviles( ( *juego ).terreno, PRIMER_FILA, juego->isengard, personaje, &( *juego ).cantidad_isengard, "primer", "Orco" );
	}
	if( personaje.codigo == ELFO ){
		posicionar_fijos( ( ULTIMA_FILA/2 )+1, ULTIMA_FILA-1, "( del 5 al 8 )", "Elfo", ( *juego ).terreno, ( *juego ).rohan, &( *juego ).cantidad_rohan, personaje );
	}
	if( personaje.codigo == URUK ){
		posicionar_fijos( PRIMER_FILA+1, ULTIMA_FILA/2, "( del 1 al 4 )", "Uruk-Hai", ( *juego ).terreno, ( *juego ).isengard, &( *juego ).cantidad_isengard, personaje );
	}
}
void ataque_movibles( personaje_t vec_atacante[ MAX_PERSONAJES ], int cantidad_atacante, personaje_t vec_enemigos[ MAX_PERSONAJES ], int* cantidad_enemigos, char pers, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], int* llegadas_enemigos ){
	for( int i=0; i < cantidad_atacante; i++ ){
		if( vec_atacante[ i ].codigo == pers && vec_atacante[ i ].vida > 0 ){
			for( int r=0; r < ( *cantidad_enemigos ); r++ ){
				if( ( abs( vec_atacante[ i ].fila - vec_enemigos[ r ].fila ) + abs( vec_atacante[ i ].columna - vec_enemigos[ r ].columna ) )<=1 && vec_enemigos[ r ].vida > 0 ){
					vec_enemigos[ r ].vida-=vec_atacante[ i ].ataque;
					if( vec_enemigos[ r ].vida<=0 ){
						terreno[ vec_enemigos[ r ].fila ][ vec_enemigos[ r ].columna ]=TERRENO_VACIO;
						vec_enemigos[ r ].vida = 0;
					}
				}else if( ( vec_atacante[ i ].fila )-1 == vec_enemigos[ r ].fila && ( vec_atacante[ i ].columna )-1 == vec_enemigos[ r ].columna && ( ( vec_atacante[ i ].fila )-1 >= PRIMER_FILA ) && ( ( vec_atacante[ i ].columna )-1 >= PRIMER_COLUMNA ) ){
					vec_enemigos[ r ].vida-=vec_atacante[ i ].ataque;
					if( vec_enemigos[ r ].vida<=0 ){
						terreno[ vec_enemigos[ r ].fila ][ vec_enemigos[ r ].columna ]=TERRENO_VACIO;
						vec_enemigos[ r ].vida = 0;
					}
				}else if( ( vec_atacante[ i ].fila )-1 == vec_enemigos[ r ].fila && ( vec_atacante[ i ].columna )+1 == vec_enemigos[ r ].columna && ( ( vec_atacante[ i ].fila )-1 >= PRIMER_FILA ) && ( ( vec_atacante[ i ].columna )+1 <= ULTIMA_COLUMNA ) ){
					vec_enemigos[ r ].vida-=vec_atacante[ i ].ataque;
					if( vec_enemigos[ r ].vida<=0 ){
						terreno[ vec_enemigos[ r ].fila ][ vec_enemigos[ r ].columna ]=TERRENO_VACIO;
						vec_enemigos[ r ].vida = 0;
					}
				}else if( ( vec_atacante[ i ].fila )+1 == vec_enemigos[ r ].fila && ( vec_atacante[ i ].columna )-1 == vec_enemigos[ r ].columna && ( ( vec_atacante[ i ].fila )+1 <= ULTIMA_FILA ) && ( ( vec_atacante[ i ].columna )-1 >= PRIMER_COLUMNA ) ){
					vec_enemigos[ r ].vida-=vec_atacante[ i ].ataque;
					if( vec_enemigos[ r ].vida<=0 ){
						terreno[ vec_enemigos[ r ].fila ][ vec_enemigos[ r ].columna ]=TERRENO_VACIO;
						vec_enemigos[ r ].vida = 0;
					}
				}else if( ( vec_atacante[ i ].fila )+1 == vec_enemigos[ r ].fila && ( vec_atacante[ i ].columna )+1 == vec_enemigos[ r ].columna && ( ( vec_atacante[ i ].fila )+1 <= ULTIMA_FILA ) && ( ( vec_atacante[ i ].columna )+1 <= ULTIMA_COLUMNA ) ){
					vec_enemigos[ r ].vida-=vec_atacante[ i ].ataque;
					if( vec_enemigos[ r ].vida<=0 ){
						terreno[ vec_enemigos[ r ].fila ][ vec_enemigos[ r ].columna ]=TERRENO_VACIO;
						vec_enemigos[ r ].vida = 0;
					}
				}
			}
		}	
	}

	for( int i=0; i < ( *cantidad_enemigos ); i++ ){
		if( vec_enemigos[ i ].vida == 0 ){
			eliminar_personaje( &( *cantidad_enemigos ), vec_enemigos, &( *llegadas_enemigos ) );
		}
	}
}
void ataque_fijos( personaje_t vec_atacante[ MAX_PERSONAJES ], int cantidad_atacante, personaje_t vec_enemigos[ MAX_PERSONAJES ], int* cantidad_enemigos, char pers, int* llegadas_enemigo ){
	for( int i=0; i < cantidad_atacante; i++ ){
		if( vec_atacante[ i ].codigo == pers && vec_atacante[ i ].vida > 0 ){
			for( int r=0; r < ( *cantidad_enemigos );r++ ){
				if( ( abs( vec_atacante[ i ].fila - vec_enemigos[ r ].fila )+ abs( vec_atacante[ i ].columna - vec_enemigos[ r ].columna ) )<=3 && vec_enemigos[ r ].vida > 0 ){
					vec_enemigos[ r ].vida-=vec_atacante[ i ].ataque;
					if( vec_enemigos[ r ].vida<=0 ){
						vec_enemigos[ r ].vida = 0;
					}
				}
			}
		}
	}
	eliminar_personaje( cantidad_enemigos, vec_enemigos, llegadas_enemigo );				
}
void jugar( juego_t* juego, char bando, int posicion_personaje ){
	if( bando == ISENGARD ){
		movimiento_personajes( &( juego )->cantidad_isengard, juego->isengard, ISENGARD, juego->isengard->fila, &( juego )->llegadas_isengard, juego->terreno, 1, ULTIMA_FILA );
		ataque_movibles( ( *juego ).isengard, ( *juego ).cantidad_isengard, ( *juego ).rohan, &( *juego ).cantidad_rohan, ORCO, ( *juego ).terreno, &( *juego ).llegadas_rohan );
		ataque_fijos( ( *juego ).isengard, ( *juego ).cantidad_isengard, ( *juego ).rohan, &( *juego ).cantidad_rohan, ORCO, &( *juego ).llegadas_rohan );

	}else{
		movimiento_personajes( &( juego )->cantidad_rohan, juego->rohan, ROHAN, juego->rohan->fila, &( juego )->llegadas_rohan, juego->terreno, -1, PRIMER_FILA );
		ataque_movibles( ( *juego ).rohan, ( *juego ).cantidad_rohan, ( *juego ).isengard, &( *juego ).cantidad_isengard, HOMBRE, ( *juego ).terreno, &( *juego ).llegadas_isengard );
		ataque_fijos( ( *juego ).rohan, ( *juego ).cantidad_rohan, ( *juego ).isengard, &( *juego ).cantidad_isengard, HOMBRE, &( *juego ).llegadas_isengard );
	}
}
void ganar( int llegadas, bool* juego_terminado, bool* turno_actual, bool* turno_enemigo, char bando[ 10 ] ){
	if( llegadas == LLEGADAS_GANAR ){
		( *juego_terminado ) = true;
		( *turno_actual )=false;
		( *turno_enemigo ) = false;
		system( "clear" );
		printf( "\n%s Gana!!!\n", bando );
	}
}
void aumentar_energia( jugador_t* j1, jugador_t* j2 ){
	( *j1 ).energia++;
	( *j2 ).energia++;
	if( ( *j1 ).energia > ENERGIA_MAX ){
		( *j1 ).energia = ENERGIA_MAX;
	}
	if( ( *j2 ).energia > ENERGIA_MAX ){
		( *j2 ).energia = ENERGIA_MAX;
	}
}
void turno( bool* turno_actual, char bando, juego_t* juego, char str_bando[ 10 ], int* llegadas_bando, char str_pers_movible[ 8 ], char str_pers_fijo[ 10 ], personaje_t personaje_movible, personaje_t personaje_fijo, bool* turno_enemigo, personaje_t vec_actual[ MAX_PERSONAJES ], bool* juego_terminado ){
	char rta_bando;
	int crear_pers;
	while( ( *turno_actual ) ){
		system( "clear" );
		if( juego->j1.tipo == bando ){
			cargar_mapa_inicial( juego->terreno );
			cargar_personajes( juego );
			actualizar_terreno( juego );
			printf( "Energia %s: %i\n",str_bando, juego->j1.energia );
			printf( "Llegadas %s: %i",str_bando, ( *llegadas_bando ) );
			printf( "\n\t\tTURNO %s.\nDesea crear un personaje?.( S/N ).\n", str_bando );
			scanf( " %c", &rta_bando );
			rta_bando = toupper( rta_bando );
			validar_respuesta_crear( &rta_bando );
			if( rta_bando == 'S' ){
				printf( "Que personaje desea crear?.\n1-%s.( 3pts. de energia )\n2-%s.( 8pts. de energia )\n", str_pers_movible, str_pers_fijo );
				scanf( "%i", &crear_pers );
				while( crear_pers !=1 && crear_pers !=2 ){
					printf( "ERROR. Ingrese una opcion valida.\n1-%s.( 3pts. de energia )\n2-%s.( 8pts. de energia )\n", str_pers_movible, str_pers_fijo );
					scanf( "%i", &crear_pers );
				}
				if( crear_pers == 1 ){
					if( juego->j1.energia >= personaje_movible.pts_energia ){
						posicionar_personaje( juego, personaje_movible );
						juego->j1.energia -= personaje_movible.pts_energia;
					}else{
					printf( "\nNo tiene puntos suficientes para crear a un %s.\n", str_pers_movible );
					}
				}else{
					if( juego->j1.energia >= personaje_fijo.pts_energia ){
						posicionar_personaje( juego, personaje_fijo );
						juego->j1.energia -= personaje_fijo.pts_energia;
					}else{
						printf( "\nNo tiene puntos suficientes para crear a un %s.\n", str_pers_fijo );
					}
				}
			}else{
				( *turno_actual ) = false;
				( *turno_enemigo ) = true;
			}
		}else if( juego->j2.tipo == bando ){
			cargar_mapa_inicial( juego->terreno );
			cargar_personajes( juego );
			actualizar_terreno( juego );
			printf( "Energia %s: %i\n",str_bando, juego->j2.energia );
			printf( "Llegadas %s: %i", str_bando, ( *llegadas_bando ) );
			printf( "\n\t\tTURNO %s.\nDesea crear un personaje?.( S/N ).\n", str_bando );
			scanf( " %c", &rta_bando );
			rta_bando = toupper( rta_bando );
			validar_respuesta_crear( &rta_bando );
			if( rta_bando == 'S' ){
				printf( "Que personaje desea crear?.\n1-%s.( 3pts. de energia )\n2-%s.( 8pts. de energia )\n", str_pers_movible, str_pers_fijo );
				scanf( "%i", &crear_pers );
				while( crear_pers !=1 && crear_pers !=2 ){
					printf( "ERROR. Ingrese una opcion valida.\n1-%s.( 3pts. de energia )\n2-%s.( 8pts. de energia )\n", str_pers_movible, str_pers_fijo );
					scanf( "%i", &crear_pers );
				}
				if( crear_pers == 1 ){
					if( juego->j2.energia >= personaje_movible.pts_energia ){
						posicionar_personaje( juego, personaje_movible );
						juego->j2.energia -= personaje_movible.pts_energia;
					}else{
						printf( "No tiene puntos suficientes para crear a un %s.\n", str_pers_movible );
					}
				}else{
					if( juego->j2.energia >= personaje_fijo.pts_energia ){
						posicionar_personaje( juego, personaje_fijo );
						juego->j2.energia -= personaje_fijo.pts_energia;
					}else{
						printf( "No tiene puntos suficientes para crear a un %s.\n", str_pers_fijo );
					}
				}
			}else{
				( *turno_actual ) = false;
				( *turno_enemigo ) = true;
			}
		}
	}
	jugar( juego, bando, vec_actual->fila );
	ganar( ( *llegadas_bando ), juego_terminado, &( *turno_actual ), &( *turno_enemigo ), str_bando );	
}
void turno_vs_cpu( bool* turno_actual, char bando, juego_t* juego, char str_bando[ 10 ], int* llegadas_bando, char str_pers_movible[ 8 ], char str_pers_fijo[ 10 ], personaje_t personaje_movible, personaje_t personaje_fijo, bool* turno_enemigo, personaje_t vec_actual[ MAX_PERSONAJES ],int* cantidad_aliado, bool* juego_terminado, int fila_inicial ){
	int crear_pers;
	char rta_bando;
	while( ( *turno_actual ) ){
				system( "clear" );
				if( juego->j1.tipo == bando ){
					cargar_mapa_inicial( juego->terreno );
					cargar_personajes( juego );
					actualizar_terreno( juego );
					printf( "Energia %s: %i\n",str_bando, juego->j1.energia );
					printf( "Llegadas %s: %i",str_bando, ( *llegadas_bando ) );
					printf( "\n\t\tTURNO %s.\nDesea crear un personaje?.( S/N ).\n", str_bando );
					scanf( " %c", &rta_bando );
					rta_bando = toupper( rta_bando );
					validar_respuesta_crear( &rta_bando );
					if( rta_bando == 'S' ){
						printf( "Que personaje desea crear?.\n1-%s.( 3pts. de energia )\n2-%s.( 8pts. de energia )\n", str_pers_movible, str_pers_fijo );
						scanf( "%i", &crear_pers );
						while( crear_pers !=1 && crear_pers !=2 ){
							printf( "ERROR. Ingrese una opcion valida.\n1-%s.( 3pts. de energia )\n2-%s.( 8pts. de energia )\n",str_pers_movible, str_pers_fijo );
							scanf( "%i", &crear_pers );
						}
						if( crear_pers == 1 ){
							if( juego->j1.energia >= personaje_movible.pts_energia ){
								posicionar_personaje( juego, personaje_movible );
								juego->j1.energia -= personaje_movible.pts_energia;
							}else{
							printf( "\nNo tiene puntos suficientes para crear a un %s.\n", str_pers_movible );
							}
						}else{
							if( juego->j1.energia >= personaje_fijo.pts_energia ){
								posicionar_personaje( juego, personaje_fijo );
								juego->j1.energia -= personaje_fijo.pts_energia;
							}else{
								printf( "\nNo tiene puntos suficientes para crear a un %s.\n", str_pers_fijo );
							}
						}
					}else{
						( *turno_actual ) = false;
						( *turno_enemigo ) = true;
					}
				}else if( juego->j2.tipo == bando ){
					cargar_mapa_inicial( juego->terreno );
					cargar_personajes( juego );
					actualizar_terreno( juego );
					printf( "\nEnergia %s: %i\n",str_bando, juego->j2.energia );
					printf( "\nLlegadas %s: %i\n",str_bando, juego->llegadas_rohan );
					printf( "\n\t\tTURNO %s.\n", str_bando );					
					if( juego->j2.energia >= personaje_movible.pts_energia ){
						posicionar_movil_aleatorio( cantidad_aliado, personaje_movible, juego->terreno, vec_actual, &( *juego ).j2, fila_inicial );
					}else{
						printf( "\nNo tiene puntos suficientes para crear a un %s.\n", str_pers_movible );
					}
					( *turno_actual ) = false;
					( *turno_enemigo ) = true;
				}
			}
			jugar( juego, bando, vec_actual->fila );
			ganar( ( *llegadas_bando ), juego_terminado, turno_actual, turno_enemigo, str_bando );
}