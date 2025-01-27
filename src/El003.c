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
    unsigned char vet[] = {0x4E,0x8B,0x8A,0x0A,0xDE,0x0B,0x46,0x85,0xD6,0x9F,0x17,0x88,0x01};
    unsigned int len = 104;	// lunghezza (numero di bit)
    unsigned char n = 25;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori

    __asm{
        xor edi, edi                ; indice del vettore che analizzo
        xor esi, esi                ; contatore per il ciclo esterno

    _ciclo:
        xor edx, edx                ; registro che conterrà i miei elementi
        xor ecx, ecx
        mov cl, n
        mov edi, esi
        shr edi, 3                  ; edi = esi / 8 indice del vettore che contiene il bit di parità
        mov ebx, 1                  ; maschera di bit
        xor eax, eax                ; contenitore per la somma di uni
        mov dh, vet[edi+3]
        mov dl, vet[edi+2]
        shl edx, 16
        mov dh, vet[edi+1]
        mov dl, vet[edi]
        mov edi, esi
        and edi, 7                  ; edi = resto della divisione per 8 equivale alla posizione del bit di parità
        
    _shift_mask:                    ; aggiorna la maschera in funzione della posizione del bit di parità
        cmp edi, 0
        jle _fine_shift
        shl ebx, 1
        dec edi
        jmp _shift_mask
    _fine_shift:

    _inner_loop:
        dec cl                      ; indice del cilto interno, esegue n confronti
        test edx, ebx               ; controlla il bit del vettore in corrispondenza della maschera
        jz _not_inc
        inc eax                     ; incrementa la somma di uni
    _not_inc:
        shl ebx, 1                   ; sposta la maschera a sinistra
        cmp cl, 0
        jne _inner_loop

    _shift_loop:                    ; posiziona il bit di parità nel bit meno significativo del byte
        shr edx, 1
        shr ebx, 1
        cmp ebx, 1
        jg _shift_loop

        ; ora basta controllare che il bit meno significativo di eax corrisponda al successivo bit della sequenza
        and ax, 1
        and dl, 1
        cmp al, dl                  ; esegue il confronto tra il bit di parità e il bit meno significativo di ax
        jne _errore
        
        mov cl, n                  ; ripristino ecx = n
        inc cl
        add esi, ecx                ; continua a processare i successvi n (ecx) bit
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