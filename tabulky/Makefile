# Makefile for survey

OUT=out
PRINT=../print
PROBLEMS=../problems
GRAPHICS=graphics# graphics for the batch (series)
PGRAPHICS=$(PROBLEMS)/graphics# graphics for problems


.SUFFIXES:
.PHONY: all clean cleanall tabulky tabulky_print tabulky_sk tabulky_sk_print

# == Main targets ==
all: tabulky tabulky_print tabulky_sk tabulky_sk_print
tabulky: $(OUT)/tabulky.pdf
tabulky_print: $(PRINT)/all_tabulky.pdf
tabulky_print: $(OUT)/tabulky_sk.pdf
tabulky_sk_print: $(OUT)/tabulky_sk-print.pdf
GRAPHDEP=

XELATEX_M=xelatex -output-directory $(@D) \
        -jobname $(basename $(@F))\
        '\def\UseOption{print}'\
        '\input{$<}'

$(OUT)/tabulky.pdf: tabulky.tex
	$(XELATEX_M) 
	$(XELATEX_M)

$(OUT)/tabulky_sk.pdf: tabulky_sk.tex
	$(XELATEX_M)
	$(XELATEX_M)

$(PRINT)/all_tabulky.pdf: $(OUT)/tabulky.pdf
	pdfnup --nup 2x1  --outfile $@ $<

$(OUT)/tabulky_sk-print.pdf: $(OUT)/tabulky_sk.pdf
	pdfnup --nup 2x1  --outfile $@ $<


clean:
	find $(OUT) -type f -not \( -name "*.pdf" -o -name ".*" \) | xargs rm

cleanall:
	rm -f $(OUT)/*
#	ls $(GRAPHICS) $(PGRAPHICS) | grep -v '\(mp\|plt\|eps\|jpg\|png\)$$' | xargs rm


#echo $(word 2,$(subst -, ,$@))
