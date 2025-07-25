/********************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 2
Descrizione: Dato in input il livello massimo richiesto, restituire il rispettivo
			 triangolo di Tartaglia memorizzando consecutivamente i vari livelli
			 all'interno di un array monodimensionale.

********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	unsigned int livello = 12;		// livello massimo del triangolo di tartaglia da generare

	// Output
	unsigned int triangolo[1024];	// risultato: il vettore contiene i numeri del 
									// triangolo dal livello 0 al più alto richiesto

	unsigned int i;
	unsigned int k = 0;

	__asm
	{
		xor ecx, ecx 			; i = 0
		xor edi, edi 			; k = 0 

	inizio_ciclo_esterno:
		cmp ecx, livello
		ja fine_ciclo_esterno
		xor eax, eax 			; j = 0

	inizio_ciclo_interno:
		cmp eax, ecx
		ja fine_ciclo_interno

		cmp eax, 0				; if j == 0
		je caso_base
		cmp eax, ecx			; if j == i
		je caso_base

		mov ebx, edi
		sub ebx, ecx					; edi = k - i
		mov edx, triangolo[ebx*4 - 4]	; ebx = triangolo[k -i -1]
		add edx, triangolo[ebx*4]		; ebx = triangolo[k -i -1] + triangolo[k -i]
		mov triangolo[edi*4], edx
		jmp salta_caso_base

	caso_base:
		mov triangolo[edi*4], 1

	salta_caso_base:
		inc eax
		inc edi
		jmp inizio_ciclo_interno

	fine_ciclo_interno:
		
		inc ecx
		jmp inizio_ciclo_esterno

	fine_ciclo_esterno:
	
	}

	// Stampa su video
	printf("Triangolo di Tartaglia fino al livello %d\n", livello);
	for (i = 0; i <= livello; i++)
	{
		unsigned int j;
		for (j = 0; j <= i; j++)
			printf("%d ", triangolo[k++]);
		printf("\n");
	}
}
