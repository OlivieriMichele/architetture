
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, restituire la lunghezza minima e
				massima	delle sotto-sequenze di bit a 0.

 ********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	unsigned char vet[] = { 0xBC,0xFF,0x01 };	// Sequenza di bit
	unsigned short int len = 18;				// Lunghezza (in bit) della sequenza

	// Output
	short int minLung;		// Lunghezza minima sotto-sequenza di 0
	short int maxLung;		// Lunghezza massima sotto-sequenza di 0

	__asm{
		xor eax, eax				; lunghezza corrente della sequenza di zeri
		xor ebx, ebx				; indice del byte
		xor ecx, ecx				; indicce del ciclo

	inizio_ciclo:
		cmp ecx, len
		jge fine_ciclo

		mov dl, vet[bx]				; carica il byte

		test dl, 80h				; conronto il primo bit del byte
			jz inc_current_len		; se è 0, incremento il conteggio corrente

			cmp eax, 0				; if current_len > 0, aggiorno max se necessario
			jg reset_current_len	

			cmp maxLung, eax		; if maxLung < current
			jge skip_modify
			mov maxLung, eax		; maxLung = current

		skip_modify:

		reset_current_len:
			xor eax, eax
			jmp fine_if:
			
		inc_current_len:
			inc eax

		fine_if: 
		
		
		jmp inizio_ciclo
	fine_ciclo: 

	}
	

	// Stampa su video
	printf("Lunghezza minima delle sotto-sequenze di 0: %d\n", minLung);
	printf("Lunghezza massima delle sotto-sequenze di 0: %d\n", maxLung);
}
