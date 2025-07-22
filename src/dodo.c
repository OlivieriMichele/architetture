#include <stdio.h>

void main()
{

    unsigned short int Mat = 992; //INSERIRE QUI LE 4 CIFRE MENO SIGNIFICATIVE DELLA
    unsigned char Vet [100]; // Vettore di 100 BYTE
    unsigned short Ris1,Ris2,Ris3,Ris4,Ris5; // WORD

    __asm{
        MOV CX,Mat
        MOV BX,CX
        XOR CX,0F0F0h
        XOR CX,00F0Fh
        NOT CX
        OR CX,3
        AND CX,0Fh
        ROL BX,CL
        MOV Ris1,BX
        // --------------------------------------
        MOV AX,Mat
        AND AL,00010000b
        JZ L1
        OR AH,01101010b
        JMP L2
        L1: XOR AH,01010100b
        L2: MOV Ris2,AX
        // --------------------------------------
        MOV ECX,15
        XOR EAX,EAX
        L3: ADD EAX,ECX
        MOV Vet[ECX],CL
        LOOP L3
        MOV CX,0ff3h
        OR CX,Mat
        AND CX,000fh
        MOV AH,Vet[ECX]
        MOV Ris3,AX
        // --------------------------------------
        MOV AX,Mat
        XOR AH,AH
        XOR BL,BL
        SUB BL,-128
        DIV BL ; Divis. senza segno di AX per r/m8: risultato in AL, resto in AH
        MOV Ris4,AX
        // --------------------------------------
        MOV AX,Mat
        AND AL,7Fh
        MOV BL,-2
        DEC BL
        IMUL BL ; Moltiplic. con segno di AL per r/m8: ris. in AX
        ADD AX,0Fh
        MOV Ris5,AX
    }

    printf("%x, %x, %x, %x, %x",Ris1,Ris2,Ris3,Ris4,Ris5);
}