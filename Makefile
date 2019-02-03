all :
	(cd Tigger2RISCV; make)
	(cd Eeyore2Tigger; make)
	(cd C2Eeyore; make)

clean:
	(cd Tigger2RISCV; make clean)
	(cd Eeyore2Tigger; make clean)
	(cd C2Eeyore; make clean)
