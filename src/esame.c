#include <stdio.h>

void main()
{

    unsigned short int Mat = 992; //INSERIRE QUI LE 4 CIFRE MENO SIGNIFICATIVE DELLA
    unsigned char Vet [100]; // Vettore di 100 BYTE
    unsigned short Ris1,Ris2,Ris3,Ris4,Ris5; // WORD

    __asm{
        MOV AX,Mat
        ADD AX,7
        MOV BX,AX
        SHL BX,1
        XOR BX,AX
        MOV CX,BX
        XOR CX,AX
        MOV Ris1,CX
        // --------------------------------------
        MOV ECX,4
        MOV AX,Mat
        SHL EAX,16
        MOV AX,Mat
        MOV EBX,0
        L1: MOV BYTE PTR Vet[EBX],AL
        SHR EAX,8
        INC EBX
        LOOP L1
        PUSH WORD PTR Vet[1]
        POP Ris2
        // --------------------------------------
        XOR AX,AX
        MOV DX,Mat
        INC DX
        SUB AX,DX
        JS L2
        MOV AX,0FFFFh
        JMP L3
        L2: NEG AX
        XCHG AL,AH ; XCHG a,b scambia il contenuto dei registri a e b
        ROL AX,8
        ROL AL,1
        L3: MOV Ris3,AX
        // --------------------------------------
        MOV AX,Mat
        AND AL,70h
        OR AL,80h
        XOR BL,BL
        DEC BL
        IMUL BL ; Moltiplic. con segno di AL per r/m8: ris. in AX
        MOV Ris4,AX
        // --------------------------------------
        MOV AX,Mat
        SHR AX,8
        MOV BL,5
        DIV BL ; Divisione senza segno di AX per r/m8: quoziente in AL, resto in AH
        MOV Ris5,AX
    }

    printf("%x, %x, %x, %x, %x",Ris1,Ris2,Ris3,Ris4,Ris5);
}