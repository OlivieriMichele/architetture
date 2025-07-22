#include <stdio.h>

void main()
{

    unsigned short int Mat = 992; //INSERIRE QUI LE 4 CIFRE MENO SIGNIFICATIVE DELLA
    unsigned char Vet [100]; // Vettore di 100 BYTE
    unsigned short Ris1,Ris2,Ris3,Ris4,Ris5; // WORD

    __asm{
        MOV AX,Mat
        AND AX,00FFh
        NEG AX
        MOV CX,-4
        SUB AX,CX
        MOV Ris1,AX
        // --------------------------------------
        XOR EAX,EAX
        MOV DX,Mat
        MOV AX,Mat
        SHL EDX,16
        OR EDX,EAX
        BSWAP EDX ; Converte little-endian/big-endian e viceversa
        ROL EDX,6
        MOV Ris2,DX
        // --------------------------------------
        LEA ESI,Vet
        MOV AX,Mat
        MOV ECX,16
        ROL ECX,7
        L1: MOV BL,AL
        AND BL,3
        MOV BYTE PTR Vet[ECX],BL
        SHR AX,2
        LOOP L1
        MOV AX,WORD PTR Vet[14]
        MOV DX,WORD PTR Vet[12]
        SHL DX,4
        OR AX,DX
        MOV Ris3,AX
        // --------------------------------------
        MOV AX,Mat
        AND AX,5Eh
        MOV BL,0FDh
        IDIV BL ; Divis. con segno di AX per r/m8: ris. in AL, resto in AH
        MOV Ris4,AX
        // --------------------------------------
        XOR ECX,ECX
        MOV BL,3
        MOV AX,Mat
        AND AX,3
        OR AX,2
        MOV CX,AX
        L2: MUL BL ; Moltiplicazione senza segno di AL per r/m8:risultato in AX
        LOOP L2
        MOV AH,AL
        NOT AH
        MOV Ris5,AX

    }

    printf("%x, %x, %x, %x, %x",Ris1,Ris2,Ris3,Ris4,Ris5);
}