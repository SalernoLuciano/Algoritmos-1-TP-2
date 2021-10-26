#ifndef __BATALLA_H__
#define __BATALLA_H__
#include "perfil.h"
#include <stdbool.h>

#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define PRIMER_FILA 0
#define ULTIMA_FILA 9
#define PRIMER_COLUMNA 0
#define ULTIMA_COLUMNA 9
#define MAX_PERSONAJES 200
#define PERSONAJES_INICIALES 3

#define ENERGIA_INICIAL 5
#define ENERGIA_MAX 10
#define VIDA_HOMBRE_ORCO 100
#define VIDA_ELFO_URUK 200
#define PTS_HOMBRE_ORCO 3
#define PTS_ELFO_URUK 8
#define ATAQUE_HOMBRE_ORCO 50
#define ATAQUE_ELFO_URUK 10
#define HOMBRE 'H'
#define ORCO 'O'
#define ELFO 'E'
#define URUK 'U'
#define TERRENO_VACIO '-'
#define RANGO_PLUS 6
#define LLEGADAS_GANAR 5
#define ENERGIA_CREAR_MIN 3

typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
	// Pueden agregar los campos que deseen
	int pts_energia;
} personaje_t;

typedef struct juego {
	char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ];
	personaje_t rohan[ MAX_PERSONAJES ];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	personaje_t isengard[ MAX_PERSONAJES ];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	// Pueden agregar los campos que deseen
	personaje_t uruk;
	personaje_t elfos;
	personaje_t hombres;
	personaje_t orcos;
	jugador_t j1;
	jugador_t j2;
	bool turno_rohan;
	char rta_rohan;
	int crear_rohan;
	int fila_rohan;
	int col_rohan;
	bool turno_isengard;
	char rta_isengard;
	int crear_isengard;
	int fila_isengard;
	int col_isengard;
	int cant_jugadores;
} juego_t;

/*
 *Post:Guarda un valor valido para la creacion de personajes.
 */
void validar_respuesta_crear( char* rta );

/*
 *Pre:pasa una matriz vacia que representara al terreno.
 *Post: guarda una interfaz grafica basica para representar la matriz como un terreno por pantalla.
 */
void cargar_mapa_inicial( char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ] );

/*
 *Post: deja cargado en el terreno la posicion de cada personaje de cada bando.
 */
void cargar_personajes( juego_t* juego );

/*
 *Post: muestra por pantalla el terreno de juego actualizado.
 */
void actualizar_terreno( juego_t*juego );

/*
 *Pre: Tomo la intensidad(del 1 al 10)de un jugador.
 *Post: devuelve un plus para calcular la vida y el ataque de los personajes de cada jugador.
 */
void plus( jugador_t jugador, juego_t* juego );

/*
 *Pre: el personaje pasado debe ser Elfo o Uruk-Hai y de juego se utilizara el campo plus.
 *Post: deja inicializados correctamente los campos vida, ataque y puntos de energia que cuesta crear los personajes Elfos y Uruk-Hai.
 */
void inicializar_personajes_fijos( personaje_t* personaje, int plus );

/*
 *Pre: el personaje pasado debe ser Hombre u Orco y se utilizara de juego el campo plus
 *Post: deja inicializados correctamente los campos de los personajes Hombres y Orcos.
 */
void inicializar_personajes_movibles( personaje_t* personaje, int plus );

/*
 *Pre: se le tiene que pasar un personaje que sea Elfo(junto con el vector del bando rohan y el jugador que corresponde al bando de rohan. ademas de la amplitud, en el caso de rohan este valor sera 5) o Uruk(junto con el vector del bando rohan y el jugador que corresponde al bando de rohan. ademas de la amplitud, en el caso de rohan este valor sera 1).
 *Post: Deja cargado en el terreno un Uruk-Hai o un elfo en una posicion aleatoria valida.
 */
void posicionar_fijo_aleatorio( int* cantidad, personaje_t personaje, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], personaje_t vec_personajes[ MAX_PERSONAJES ], int amplitud );

/*
 *Pre: se le tiene que pasar un personaje que sea Hombre(junto con la Ultima fila, el vector del bando rohan y el jugador que corresponde al bando de rohan.) u Orco(junto con la primer fila, el vector del bando de isengard y el jugador que corresponde a isengard).
 *Post: Deja cargado en el terreno un hombre o un orco en una posicion aleatoria valida.
 */
void posicionar_movil_aleatorio( int* cantidad, personaje_t personaje, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], personaje_t vec_personajes[ MAX_PERSONAJES ], jugador_t* jugador, int fila );

void posicionar_moviles(char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], int fila_inicial, personaje_t vec_personajes[ MAX_PERSONAJES ], personaje_t personaje, int* cantidad_personajes, char fila[ 10 ], char bando[ 15 ] );

void posicionar_fijos( int primer_fila_campo, int ultima_fila_campo, char rango[ 15 ], char pers[ 5 ], char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], personaje_t vec_personajes[ MAX_PERSONAJES ], int* cantidad_personajes, personaje_t personaje );

void personaje_murio( personaje_t personaje[ MAX_PERSONAJES ], int i, int* cantidad );

void personaje_llego( int* cantidad, personaje_t personaje[ MAX_PERSONAJES ], int* llegadas, int i );

void eliminar_personaje( int* cantidad, personaje_t personaje[ MAX_PERSONAJES ], int* llegadas );

void movimiento_personajes( int* cantidad_personajes, personaje_t personaje[ MAX_PERSONAJES ] , char bando, int posicion_personaje, int* llegadas, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], int movimiento, int fila_llegada );

/*
 * Inicializará todos los valores del juego, dejándolo en un estado 
 * inicial válido.
 */
void inicializar_juego( juego_t* juego );

/*
 * Recibirá un personaje, con todos sus campos correctamente cargados y
 * lo dará de alta en el juego, sumándolo al vector correspondiente,
 * posicionándolo también en la matriz.
 */
void posicionar_personaje( juego_t* juego, personaje_t personaje );

void ataque_movibles( personaje_t vec_atacante[ MAX_PERSONAJES ], int cantidad_atacante, personaje_t vec_enemigos[ MAX_PERSONAJES ], int* cantidad_enemigos, char pers, char terreno[ MAX_TERRENO_FIL ][ MAX_TERRENO_COL ], int* llegadas_enemigos );

void ataque_fijos( personaje_t vec_atacante[ MAX_PERSONAJES ], int cantidad_atacante, personaje_t vec_enemigos[ MAX_PERSONAJES ], int* cantidad_enemigos, char pers, int* llegadas_enemigo );

/*
 * Realizará la jugada del personaje del bando recibido que
 * se encuentra en la posición posicion_personaje.
 * Se moverá o atacará dependiento lo que corresponda.
 * Actualizará el juego según los efectos del movimiento del
 * personaje, matar rivales, actualizar la matriz, restar vida, etc.
 */
void jugar( juego_t* juego, char bando, int posicion_personaje );

void ganar( int llegadas, bool* juego_terminado, bool* turno_actual, bool* turno_enemigo, char bando[ 10 ] );

void aumentar_energia( jugador_t* j1, jugador_t* j2 );

void turno( bool* turno_actual, char bando, juego_t* juego, char str_bando[ 10 ], int* llegadas_bando, char str_pers_movible[ 8 ], char str_pers_fijo[ 10 ], personaje_t personaje_movible, personaje_t personaje_fijo, bool* turno_enemigo, personaje_t vec_actual[ MAX_PERSONAJES ], bool* juego_terminado );

void turno_vs_cpu( bool* turno_actual, char bando, juego_t* juego, char str_bando[ 10 ], int* llegadas_bando, char str_pers_movible[ 8 ], char str_pers_fijo[ 10 ], personaje_t personaje_movible, personaje_t personaje_fijo, bool* turno_enemigo, personaje_t vec_actual[ MAX_PERSONAJES ],int* cantidad_aliado, bool* juego_terminado, int fila_inicial );
#endif /* __BATALLA_H__ */