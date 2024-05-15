global f1
global f2
global f3
global main

section .data
    z dq 3.0
    zz dq 2.5
    zzz dq 5.0
    x dq 0.5
    xx dq 1.0
    xxx dq 9.5
    y dq 9.0
section .text
f4:
    push ebp
    mov ebp, esp
    finit
    fld qword[xx]
    fld dword[ebp + 8]
    fadd st0, st1
    fld qword[x]
    fdivr 
    fld qword[xx]
    fadd st0, st1  
    fld qword[z]
    fmulp
    leave
    ret
    
f5:
    push ebp
    mov ebp, esp
    finit
    fld qword[xxx]
    fld qword[zz]
    fld qword[ebp + 8]
    fmul 
    fsubp 
    leave
    ret
    
    
f6:
    push ebp
    mov ebp, esp
    finit
    fld qword[zzz]
    fld qword[ebp + 8]
    fdivp 
    leave
    ret

f4:
    push ebp
    mov ebp, esp
    finit
    fld qword[z]
    fld qword[ebp + 8]
    fsub st0, st1
    fmul st0, st0
    fld qword[y]
    fsubp
    leave
    ret

f5:
    push ebp
    mov ebp, esp
    finit
    fld qword[z]
    fld qword[ebp + 8]
    fsubrp
    leave
    ret
    
f6:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp + 8]
    fld qword[z]
    fsubrp
    leave
    ret    
    