#include <stdio.h>
#include "perfil.h"
#include <stdlib.h>


/*
 *Post:Guarda un valor entero correspondiente a un signo. Si no esta entre 1 y 12 se vuelve a pedir hasta que este dentro del rango.
 */
void preguntar_signo( int* signo ){
	printf( "\n1-¿De que signo sos? (El signo debe ser un numero del 1 al 12).\nSiendo: \n-Aries(1)\n-Tauro(2)\n-Geminis(3)\n-Cancer(4)\n-Leo(5)\n-Virgo(6)\n-Libra(7)\n-Escorpio(8)\n-Sagitario(9)\n-Capricornio(10)\n-Acuario(11)\n-Piscis(12)\n\n" );
	scanf( "%i", signo );
	system( "clear" );
	while( *signo< MENOR_SIGNO || *signo > MAYOR_SIGNO ){
		printf( "\n\tERROR. Reingrese un signo valido del 1 al 12.\n\n" );
		scanf( "%i", signo );
	}
}

/*
*Post:Guarda un caracter correspondiente a un genero de cine favorito. Si el caracter no es 'A', 'C', 'D' o 'T' se pide un caracter hasta que sea una de las opciones validas.
*/
void preguntar_genero_cine( char* genero_preferido ){
	printf( "\n2-Ingrese su genero de cine preferido.\n-Accion(A)\n-Comedia(C)\n-Drama(D)\n-Terror(T)\n\n" );	
	scanf( " %c", genero_preferido );
	system( "clear" );
	while( ( *genero_preferido != ACCION_MAYUSCULA ) && ( *genero_preferido != ACCION_MINUSCULA ) && ( *genero_preferido != COMEDIA_MAYUSCULA ) && ( *genero_preferido != COMEDIA_MINUSCULA ) && ( *genero_preferido != DRAMA_MAYUSCULA ) && ( *genero_preferido != DRAMA_MINUSCULA ) && ( *genero_preferido != TERROR_MAYUSCULA ) && ( *genero_preferido != TERROR_MINUSCULA ) ){
		printf( "\n\tERROR. Reingrese un genero valido: A,C,D o T.\n\n" );
		scanf( " %c", genero_preferido );
	}
}

/*
*Post:Guarda un valor entero correspondiente a cantidad de maldades. Si el valor no esta entre 0 y 99 se vuelve a pedir un valor hasta que este dentro del rango.
*/
void preguntar_maldades( int* cant_maldades ){
	printf( "\n3-Ingrese la cantidad de maldades que hizo el ultimo mes.\n\n" );	
	scanf( "%i", cant_maldades );
	system( "clear" );
	while( *cant_maldades < MIN_MALDADES || *cant_maldades > MAX_MALDADES ){
		printf( "\n\tERROR. Reingrese una cantidad de maldades entre 0 y 99\n\n" );
		scanf( "%i", cant_maldades );
	}
}

/*
*Post:Guarda un valor entero correspondiente a cantidad de mascotas. Si el valor no esta entre 0 y 5 se vuelve a pedir una cantidad de mascotas hasta que el valor ente dentro del rango.
*/
void preguntar_mascotas( int* cant_mascotas ){
	printf( "\n4-Ingrese la cantidad de mascotas que tiene. (Si tiene mas de 5 mascotas debe ingresar '5').\n\n" );
	scanf( "%i", cant_mascotas );
	system( "clear" );
	while( *cant_mascotas < MIN_MASCOTAS || *cant_mascotas > MAX_MASCOTAS ){
		printf( "\n\tERROR. Reingrese una cantidad entre 0 y 5 (Si tiene mas de 5 mascotas debe ingresar '5')\n\n" );
		scanf( "%i", cant_mascotas );
	}
}

/*
*Pre:Se le pasa el valor del bando asignado ( defensivo u ofensivo ) y el valor de intensidad ( un valor entero entre 1 y 10).
*Post: Imprime por pantalla un mensaje con la intensidad y bando asignados.
*/
void mostrar_perfil( int bando, int intensidad ){
	if( bando == OFENSIVO ){
		printf( "\nEres parte del bando ofensivo de Isengard, comandado por Saruman 'El Blanco' y tienes una intensidad de %i puntos.\nPelea junto a los Uruk-hai y acaba con los hombres. La era del orco ha llegado.\n\n", intensidad );
	}else{  
		printf( "\nComo parte del bando defensivo de Rohan, pelearas junto a Aragorn, Legolas y Gimli.\nTenes una intensidad de %i puntos. Demuestra que estas a su altura y defiende los muros de la ciudadela del Abismo de Helm.\n\n", intensidad );
	}
}
/*
 *Pre: Se le pasa un valor entero positivo entre 1 y 12.
 *Post: Devuelve un tipo de signo, dependiendo de que valor entero positivo se halla enviado.
 */
int tipo_sign( int *signo ){
	int tipo_signo;
	tipo_signo = (*signo) % 4;
	return tipo_signo;
}

/*
*Pre: Se pasan los 4 valores de las preguntas('tipo_signo' se deriva de 'signo' validados anteriormente. 'cant_mascotas' se pasa para poder repreguntar en caso que no se asigne un bando.)
*Post: Devuelve el bando al cual se le asignara al usuario o le pedira completar las preguntas nuevamente.
*/
int equipo( int *tipo_signo, char *genero_preferido, int *cant_maldades, int *signo, int *cant_mascotas ){
	int band;
	if( ( *tipo_signo == AIRE || *tipo_signo == FUEGO ) && ( *genero_preferido == COMEDIA_MAYUSCULA || *genero_preferido == COMEDIA_MINUSCULA || *genero_preferido == TERROR_MAYUSCULA || *genero_preferido == TERROR_MINUSCULA ) && ( *cant_maldades >= LIMITE_MALDADES ) ){
		band = OFENSIVO;
	}else if ( ( *tipo_signo == AGUA || *tipo_signo == TIERRA ) && ( *genero_preferido == ACCION_MAYUSCULA || *genero_preferido == ACCION_MINUSCULA || *genero_preferido == DRAMA_MAYUSCULA || *genero_preferido == DRAMA_MINUSCULA ) && ( *cant_maldades < LIMITE_MALDADES ) ){
		band = DEFENSIVO;
	}
	return band;
}

/*
*Pre: se le pasa un valor entre 0 y 5 que representa la cantidad de mascotas que tiene el usuario.
*Post: devuelve la cantidad de puntos de intensidad.
*/
int intensidad_mascotas( int cant_mascotas ){
	if ( cant_mascotas >= MAX_MASCOTAS ){
		return MAX_MASCOTAS;
	}
	return cant_mascotas;
}

/*
*Pre: Se le pasa un valor positivo entre 0 y 99.
*Post: Devuelvela cantidad de puntos de intensidad de las maldades realizadas en el mes.
*/
int intensidad_maldades( int cant_maldades ){
	int puntos_maldades;
	if( ( cant_maldades >= MIN_MALDADES_INFERIOR_PUNTO1 && cant_maldades <= MAX_MALDADES_INFERIOR_PUNTO1 ) || ( cant_maldades >= MIN_MALDADES_SUPERIOR_PUNTO1 && cant_maldades <= MAX_MALDADES_SUPERIOR_PUNTO1 ) ){
		puntos_maldades = 1;
	}else if( ( cant_maldades >= MIN_MALDADES_INFERIOR_PUNTO2 && cant_maldades <= MAX_MALDADES_INFERIOR_PUNTO2 ) || ( cant_maldades >= MIN_MALDADES_SUPERIOR_PUNTO2 && cant_maldades <= MAX_MALDADES_SUPERIOR_PUNTO2 ) ){
		puntos_maldades = 2;
	}else if( ( cant_maldades >= MIN_MALDADES_INFERIOR_PUNTO3 && cant_maldades <= MAX_MALDADES_INFERIOR_PUNTO3 ) || ( cant_maldades >= MIN_MALDADES_SUPERIOR_PUNTO3 && cant_maldades <= MAX_MALDADES_SUPERIOR_PUNTO3 ) ){
		puntos_maldades = 3;
	}else if( ( cant_maldades >= MIN_MALDADES_INFERIOR_PUNTO4 && cant_maldades <= MAX_MALDADES_INFERIOR_PUNTO4 ) || ( cant_maldades >= MIN_MALDADES_SUPERIOR_PUNTO4 && cant_maldades <= MAX_MALDADES_SUPERIOR_PUNTO4 ) ){
		puntos_maldades = 4;
	}else if( ( cant_maldades >= MIN_MALDADES_INFERIOR_PUNTO5 && cant_maldades <= MAX_MALDADES_INFERIOR_PUNTO5 ) || ( cant_maldades >= MIN_MALDADES_SUPERIOR_PUNTO5 && cant_maldades <= MAX_MALDADES_SUPERIOR_PUNTO5 ) ){
		puntos_maldades = 5;
	}
	return puntos_maldades;
}

/*
*Pre: Se le pasa dos valores positivos entre 0 y 5.
*Post: devuelve la suma de los puntos de intensidad de las maldades realizadas y los puntos de intensidad de las mascotas que tenga el usuario.
*/
int puntos_intensidad( int cant_maldades, int cant_mascotas ){
	int puntos_maldades = intensidad_maldades( cant_maldades );
	int puntos_mascotas = intensidad_mascotas( cant_mascotas );
	return  puntos_maldades + puntos_mascotas;
}

void perfil( char* tipo, int* intensidad ){
	int signo, cant_maldades, cant_mascotas, tipo_signo, aux;
	char genero_preferido;

	preguntar_signo( &signo );
	preguntar_genero_cine( &genero_preferido );
	preguntar_maldades( &cant_maldades );
	preguntar_mascotas( &cant_mascotas );
	tipo_signo = tipo_sign( &signo );
	aux = equipo( &tipo_signo, &genero_preferido, &cant_maldades, &signo, &cant_mascotas );
	if( aux == OFENSIVO ){
		( *tipo ) = ISENGARD; 
	}else{
		( *tipo ) = ROHAN;
	}
	( *intensidad ) = puntos_intensidad( cant_maldades, cant_mascotas );
	mostrar_perfil( aux, *intensidad );
}