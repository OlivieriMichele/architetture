/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 1
 Descrizione: Dato un array di puntatori a stringa (ogni cella del vettore contiene
				l'indirizzo a 32 bit del primo carattere della stringa), ordinarlo
				secondo il codice ASCII. Ogni stringa termina con il carattere nullo
				(codice ASCII 0).

 ********************************************************************************/

#include <stdio.h>

void main() {
	// Le stringhe da ordinare (array di puntatori)
	char* strings[] = { "prova","1","michele","31","bianca","ciao","pizza" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);

	__asm{
			MOV ECX, num			; ECX = i, indice del ciclo esterno
			DEC ECX

		i_loop:
			XOR EAX, EAX 			; EAX = j, indice del ciclo interno
			XOR EDX, EDX			; indice usato per accedere alla lettera della stringa

		next: 
			INC EDX

		j_loop:
			MOV ESI, [strings + EAX*4]		; carica strings[j] in ESI
			MOV EDI, [strings + EAX*4 +4]	; carica strings[j+1] in EDI
			MOV BL, [ESI][EDX]				; carica il primo carattere della stringa 
			MOV BH, [EDI][EDX]				; carica il primo carattere della stringa
			CMP BL, BH
			JL no_swap				; non esegue lo sccambio se strings[j][0] < strings[j+1][0]
			JE next					; confronta le seconde lettare in caso di ugualianza della prima

			MOV [strings + EAX*4], EDI		; scambia strings[j] con strings[j+1]
			MOV [strings + EAX*4 +4], ESI	; scambia strings[j+1] con strings[j]

		no_swap:
			XOR EDX, EDX
			INC EAX					; incrementta j
			CMP EAX, ECX			; if (j < i)
			JL j_loop				; rientra nel ciclo

			LOOP i_loop
	}

	// Stampa su video
	{
		int i;
		for (i = 0; i < num; i++)
			printf("%s\n", strings[i]);
	}
}
