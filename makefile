GCC = gcc

PROGRAMAS = lab01_Galindo lab02_Galindo lab04_Galindo


lab01_Galindo:
	$(GCC) $@.c -o $@

lab02_Galindo:
	$(GCC) $@.c -o $@

lab04_Galindo:
	$(GCC) $@.c -o $@

clean:
	$(RM) $(PROGRAMAS)

