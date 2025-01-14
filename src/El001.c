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
	char* strings[] = { "a", "ad", "ai", "alle", "altre", "botte", "che", "chioccia", "colori", "contadino", "contadino", "dallaltra", "del", "della", "dellaia", "delle", "Deluso", "di", "di", "di", "dipingerlo", "e", "e", "e", "fare", "galline", "gallo", "gran", "i", "il", "il", "il", "in", "indifferente", "lavori", "le", "le", "lo", "mette", "mezzo", "nascosto", "parte", "pavone", "per", "per", "pero", "Poi", "putiferio", "quando", "Questa", "reazioni", "resta", "riempie", "rimette", "scherzo", "si", "sottrae", "spiare", "sta", "sue", "suoi", "tornarsene", "tutti", "tutto", "Un", "un", "un", "una", "uno", "uova", "uovo", "vede", "vuol"};

	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);

	__asm
	{
			MOV ECX, num		; indice del ciclo esterno
			CMP ECX, 1
			JLE fine
			DEC ECX

		esterno:
			XOR EAX, EAX 		; indice del ciclo interno
			XOR EDX, EDX		; indice usato per accedere alla lettera della stringa
			DEC EDX

		prossimo: 
			INC EDX

		interno:
			MOV ESI, [strings + EAX*4]			; carica strings di j in ESI
			MOV EDI, [strings + ECX*4]		; carica strings di j+1 in EDI
			MOV BL, [ESI][EDX]				; carica il primo carattere della stringa 
			MOV BH, [EDI][EDX]				; carica il primo carattere della stringa
			CMP BL,0
			JE noninvertire
			CMP BH,0
			JE scambia
			CMP BL, BH
			JL noninvertire					; non esegue lo sccambio se strings di j,0 < strings di j+1,0
			JE prossimo						; confronta le seconde lettare in caso di ugualianza della prima

		scambia:
			MOV [strings + EAX*4], EDI		; scambia strings di j con strings di j+1
			MOV [strings + ECX*4], ESI	; scambia strings di j+1 con strings di j

		noninvertire:
			XOR EDX, EDX
			INC EAX					; incrementta j
			CMP EAX, ECX			; confronta j minore i
			JL interno				; rientra nel ciclo

			LOOP esterno
		fine:
	}

	// Stampa su video
	{
		int i;
		for (i = 0; i < num; i++)
			printf("%s\n", strings[i]);
		
		printf("%d\n", i);
	}
}
