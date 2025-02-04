
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Calcolare la matrice di DWORD prodotto di due matrici di WORD.
              Le matrici sono memorizzate per righe all’interno di array
              monodimensionali. Gli elementi delle matrici sono da considerarsi
              con segno (in complemento a due).

    for(int i = 0; i < m; i++) {
        printf("\n");
        for(int j = 0; j < k; j++) {
            int temp = 0; // Inizializza il risultato a 0
            for(int t = 0; t < n; t++) {
                temp += mat1[i*n + t] * mat2[t*k + j]; // Accesso corretto alle matrici
            }
            printf("(%d,%d) = %d ,", i, j, temp);
            mat3[i*k + j] = temp; // Memorizza il risultato nel vettore mat3
        }
    }
 ********************************************************************************/

#include <stdio.h>


void main()
{
    unsigned int m = 3; // numero di righe della prima matrice
    unsigned int n = 2; // numero di colonne della prima matrice
    unsigned int k = 4; // numero di colonne della seconda matrice
    short int mat1[] = { -1,-2, 4,5, 4,-2 }; // prima matrice
    short int mat2[] = { 2,0,0,0, 0,2,0,0 }; // seconda matrice
    int mat3[1024]; // matrice risultato

    __asm
    {
            xor ecx, ecx                    ; i indice del ciclo esterno

        esterno:
            xor edx, edx                    ; j indice del ciclo interno

        interno:
            xor ebx, ebx                    ; t indice del ciclo per la somma dei prodotti
            xor eax, eax                    ; variabile temporanea per contenere la somma che si modifica nel corso del ciclo

        somma:
            mov esi, ecx                    ; esi = i
            imul esi, n                     ; esi = i * n
            add esi, ebx                    ; esi = i*n + t
            mov si, word ptr mat1[esi*2]    ; carico in si il primo elemento della moltiplicazione mat1[i][t]
            test si, 0x8000                 ; verifico sia negativo
            jz positivo
            or esi, 0xFFFF0000
        positivo:

            mov edi, ebx                    ; edi = t
            imul edi, k                     ; edi = t * k
            add edi, edx                    ; edi = t*k + j
            mov di, word ptr mat2[edi*2]    ; carico in di il secondo elemento della moltiplicazione mat2[t][j]
            test di, 0x8000                 ; verifico sia negativo
            jz positivoo
            or edi, 0xFFFF0000
        positivoo:
            
            imul esi, edi                   ; eseguo la moltiplicazione dei due elem delle due matrici
            add eax, esi                    ; aggiorno il valore che andrà in mat3 con il prodotto calcolato

            inc ebx                         ; t++
            cmp ebx, n                      ; t < n ?
            jl somma                        ; eseguo la somma per il numero di righe della prima riga (=numero di colonne della seconda)

            mov edi, ecx                    ; edi = i
            imul edi, k                     ; edi = i*k
            add edi, edx                    ; edi = i*k +j
            mov mat3[edi*4], eax            ; carico nella matrice[i][j] il valore calcolato

            inc edx                         ; j++
            cmp edx, k                      ; j < k ?
            jl interno

            inc ecx                         ; i++
            cmp ecx, m                      ; i < m ?
            jl esterno
    }

    // Stampa su video
    {	unsigned int i, j, h;
    printf("Matrice prodotto:\n");
    for (i = h = 0; i < m; i++)
    {
        for (j = 0; j < k; j++, h++)
            printf("%6d ", mat3[h]);
        printf("\n");
    }
    }
}
