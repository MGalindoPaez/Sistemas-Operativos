###############################################
# Makefile
# Script para automatización de compilación
# Laboratorio de Sistemas Operativos
###############################################

# Compilador a utilizar
GCC = gcc

# Opciones de compilación (por ahora vacías)
FLAGS =

# Módulo principal (no se usa, pero reservado para futuras mejoras)
MODULO =

# Programas que se van a compilar
PROGRAMAS = cliente servidor

###############################################
# Regla para compilar el programa cliente
# Usa la variable $@ que representa el nombre del target (cliente)
# y compila el archivo cliente.c generando el ejecutable 'cliente'
###############################################
cliente:
	$(GCC) $(FLAGS) $@.c -o $@

###############################################
# Regla para compilar el programa servidor
# Similar a la regla anterior pero para servidor.c
###############################################
servidor:
	$(GCC) $(FLAGS) $@.c -o $@

###############################################
# Regla para limpiar el proyecto
# Elimina los ejecutables generados
###############################################
clean:
	$(RM) $(PROGRAMAS)
