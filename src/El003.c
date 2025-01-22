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
    unsigned char vet[] = { 3,3};
    unsigned int len = 16;	// lunghezza (numero di bit)
    unsigned char n = 7;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori

    __asm
    {
        mov esi, len            ; inizializza il contatore
        xor ecx, ecx
        mov cl, n               ; ecx = n
        inc ecx
        xor edx, edx            ; inizializza il contenitore degli elem del vettore

    _loop:
        xor eax, eax            ; somma dei bit a 1
        mov ebx, 1              ; maschera iniziale per estrarre il bit meno significativo
        mov edi, esi            ; edi = esi / 8, indice del vettore che contiene il bit che voglio esaminare
        shr edi, 3
        mov dl, vet[edi-1]      ; carica il byte che voglio esaminare
        mov dh, vet[edi-2]
        mov edi, esi
        shr edi, 7              ; edi = esi % 8, posizione del byte che contiene il bit di parità

    shift_loop:
        shl ebx, 1
        dec edi
        cmp edi, 0
        jge shift_loop

    inner_loop:
        test edx, ebx            ; estrae il bit meno significativo
        jz not_inc
        inc eax
    not_inc:

        shl ebx, 1              ; sposta la maschera a sinistra
        cmp ebx, 1 << 7         ; verifica se abbiamo processato n bit {va aggiornato dinamicamente}
        jne inner_loop

        ; a questo punto eax contine il conteggio dei bit a 1
        mov edx, esi
        shr edx, 3
                                ; and al, 1 così so se la somma dei miei uni è dispari, poi faccio test con vet[edx-1] ma in posizione corretta
        and al, vet[edx-1]      ; estrae il bit di parità {considera che da per scontato che sia in posizione 8}
        cmp al, 1
        jne _error              ; se il bit di parità è deiverso dal conteggio

        ;continua a processare i successivi n bit
        sub esi, ecx
        jnz _loop

        jmp _endloop

    _error:
        mov errori, 1

    _endloop:    
    }

    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));

}