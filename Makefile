#################
#
# Makefile
# script para automatizacion......
#
#################

GCC = gcc
FLAGS =
MODULO =

PROGRAMAS = cliente servidor

cliente:
	$(GCC) $@.c -o $@

servidor:
	$(GCC) $@.c -o $@

clean:
	$(RM) $(PROGRAMAS)
