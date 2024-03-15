section .data
    palabras_dificiles db  "palabras", "abejones", "mapaches", "deportes", "refugios", "sobrinos", "insectos", "animales"
    palabras_normales db  "palabra ", "botella ", "mapache ", "deporte ", "refugio ", "sobrino ", "insecto ", "cuchara "
    palabras_faciles db "cabeza  ", "correr  ", "saltar  ", "gritar  ", "salida  ", "hablar  ", "mesero  ", "cadena  "
    posiciones_encontradas db 0, 0, 0, 0, 0, 0, 0, 0
    posiciones_encontradas_merged db 0, 0, 0, 0, 0, 0, 0, 0
    intentos db 0
    intentos_survival db 0

section .bss
    palabra_elegida resb 8

section .text
global  devolver_palabra
devolver_palabra:
    cmp rsi, 1          ; Compara si la dificultad es facil (igual a 1)
    je easyWord
    cmp rsi, 2          ; Compara si la dificultad es normal (igual a 2)
    je normalWord
    cmp rsi, 3          ; Compara si la dificultad es dificil (igual a 3)
    je hardWord

easyWord:
    mov rax, [palabras_faciles + rdi*8]
    mov [palabra_elegida], rax
    jmp returnWord

normalWord:
    mov rax, [palabras_normales + rdi*8]
    mov [palabra_elegida], rax
    jmp returnWord

hardWord:
    mov rax, [palabras_dificiles + rdi*8]
    mov [palabra_elegida], rax
    jmp returnWord

returnWord:
    lea rax, palabra_elegida
    ret

global buscar_rellenar_letra
buscar_rellenar_letra:
    mov qword[posiciones_encontradas], 0

    mov rcx, 0

    compare:
        cmp [palabra_elegida + rcx], dil ; dil es el subregistro de 8 bits
                                         ; de rdi que alcanza para representar
                                         ; los caracteres en ascii
        je  asignar_posicion

        jmp quit_compare

        asignar_posicion:
            mov byte[posiciones_encontradas_merged + rcx], 1
            mov byte[posiciones_encontradas + rcx], 1
            jmp quit_compare

        quit_compare:
            inc rcx
            cmp rcx, 7
            jbe compare

    mov rax, posiciones_encontradas
    cmp qword[posiciones_encontradas], 0
    jne do_ret
    inc byte[intentos]
    inc byte[intentos_survival]

    do_ret:
    ret

global get_all_letras_adivinadas
get_all_letras_adivinadas:
    mov rcx, 0
    mov rdx, posiciones_encontradas_merged

    count:
        movzx rax, byte [rdx]
        add rcx, rax
        inc rdx
        cmp rdx, posiciones_encontradas_merged + 7
        jbe count
        mov rax, rcx
    ret

global get_intentos
get_intentos:
    mov rax, 0
    mov al, [intentos]
    ret

global get_intentos_survival
get_intentos_survival:
    mov rax, 0
    mov al, [intentos_survival]
    ret

global restart_section_data
restart_section_data:
    mov qword[posiciones_encontradas], 0
    mov qword[posiciones_encontradas_merged], 0
    mov qword[palabra_elegida], 0
    mov byte[intentos], 0
    mov byte[intentos_survival], 0
    ret

global restart_survival_data
restart_survival_data:
    mov qword[posiciones_encontradas], 0
    mov qword[posiciones_encontradas_merged], 0
    mov qword[palabra_elegida], 0
    mov byte[intentos_survival], 0
    ret
