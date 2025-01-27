/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, sapendo che ogni n bit (di dati) vi �
                un bit di parit� (1 se il numero di bit a 1 fra i precedenti n �
                dispari), verificare se vi sono errori.

 ********************************************************************************/

#include <stdio.h>

void main()
{
    // Input
    unsigned char vet[] = {0xE3,0xA5,0x0E,0x92,0x2F,0xB2,0x00};
    unsigned int len = 50;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori

    __asm{
		xor edi, edi				; indice (byte) del vettore che voglio analizzare
		xor esi, esi				; contatore per il ciclo esterno
		xor ecx, ecx

	_ciclo: 
		xor edx, edx 				; registro contenitore del byte da analizzare
		xor ebx, ebx				; contatore dei giri interni del ciclo
		xor eax, eax				; contenitore per la somma di uni

	_reload:
		mov cx, si					; cx = bx / 8 = indice del byte che voglio esaminare
        add cx, bx
		shr cx, 3
		mov dl, vet[ecx]            ; metto in dx la word che voglio esamniare
        mov dh, vet[ecx+1]
        mov cx, si
        add cx, bx
        and cx, 7                   ; calcolo il resto della divisione per 8 = indice del bit da controllare

    _shift_mask:
        cmp cx, 0                   ; porta nel bit meno significativo il primo bit da controllare
        jle _next
        shr dx, 1
        dec cx
        jmp _shift_mask

	_next:
		test dl, 1					; controllo il bit meno significativo
		jz _not_inc
		inc eax

	_not_inc:
		shr dl, 1					; analizza il bit successivo
		inc ebx
		cmp bl, n
		jge _exit					; esce quando ha processato n bit
		mov cx, si
        add cx, bx
		and cx, 7					; controllo il resto della divisione per 8
		jz _reload					; se ho esaminato 8 bit carico il byte successivo
		jmp _next
	_exit:

		and ax, 1 					; considero solo il bit meno significativo che rappresenta la parità
		and dl, 1					; considero solo il bit meno significatico che è il bit di parità
		cmp al, dl
		jne _errore

		xor ecx, ecx
		mov cl, n
		inc cl						; esamino il successivo blocco di n+1 elementi
		add esi, ecx
		cmp esi, len
		jl _ciclo
		jmp _fine

	_errore:
		mov errori, 1
		
	_fine:
    }

    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));

}