# Makefile for single batch

OUT=out
PROBLEMS=../problems
GRAPHICS=graphics# graphics for the batch (series)
PGRAPHICS=$(PROBLEMS)/graphics# graphics for problems

.SUFFIXES:
.PHONY: all clean cleanall vedouci vydavac zadavac opravujici registrace


# == Main targets ==
all: vedouci vydavac zadavac opravujici registrace
vedouci:    $(OUT)/vedouci.pdf
vydavac:    $(OUT)/vydavac.pdf
zadavac:    $(OUT)/zadavac.pdf
opravujici: $(OUT)/opravujici.pdf
registrace: $(OUT)/registrace.pdf
GRAPHDEP=


XELATEX_M=xelatex -output-directory $(@D) -jobname '$(basename $(@F))' $<

$(OUT)/%.pdf: %.tex 
	$(XELATEX_M)
	$(XELATEX_M)

clean:
	find $(OUT) -type f -not \( -name "*.pdf" -o -name ".*" \) | xargs rm

cleanall:
	rm -f $(OUT)/*
#	ls $(GRAPHICS) $(PGRAPHICS) | grep -v '\(mp\|plt\|eps\|jpg\|png\)$$' | xargs rm

# == XML for web transport ==


