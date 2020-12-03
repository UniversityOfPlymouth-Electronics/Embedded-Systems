    AREA asm_func, CODE, READONLY
; Export my_asm function location so that C compiler can find it and link
    EXPORT myasm
myasm
    
    ; Write assmebler here
    MOV R1, #0x20000000
    BX      R1              ; THIS IS BAD
    BX      LR
    
    EXPORT spinlock
spinlock
    LDREX   R1,[R0]     ;Read counter
    SUBS    R1, #1      ;Subtract 1
    ITT     PL          ;IF True True >= 0
    STREXPL R2,R1,[R0]      ;TRY UPDATE
    CMPPL   R2,#0           ;SUCCEED?
    BNE     spinlock
    BX      LR

    EXPORT spinunlock
spinunlock
    LDREX   R1,[R0]
    ADD     R1,#1
    STREX   R2,R1,[R0]
    CMP     R2,#0
    BNE     spinunlock
    BX      LR
    END