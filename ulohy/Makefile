# Simple recursive makefile  + Makefile for contest

OUT=out
PROBLEMS=./problems
GRAPHICS=graphics# graphics for the batch (series)
PGRAPHICS=$(PROBLEMS)/graphics# graphics for problems
TEAMS=./teams
TEAMSFILE=./teams.csv # teams file exported from database
SIGNATURES := signatures.tex

# list of places (in one line)
PLACENOS=$(shell awk -F";" '{print $$3;}' < $(TEAMSFILE) | sort -u | sed ':a;N;$$!ba;s/\n/ /g')

.SUFFIXES:
.PHONY: all clean cleanall cleanalldep dep tasks tasksprint solutions results authors

# == Main targets ==
all: dep tasks tasksprint solutions results authors
dep:        $(PROBLEMS)/Makefile.inc Tasks.inc
tasks:      $(addsuffix  .pdf, $(addprefix $(OUT)/zadani-, $(PLACENOS)))
tasksprint: $(addsuffix p.pdf, $(addprefix $(OUT)/zadani-, $(PLACENOS)))
solutions:  $(OUT)/reseni.cs.pdf $(OUT)/reseni.sk.pdf $(OUT)/reseni-print.cs.pdf $(OUT)/reseni-print.sk.pdf $(OUT)/reseni-book.cs.pdf $(OUT)/reseni-book.sk.pdf		
results:    $(OUT)/vysledky.pdf
authors:    $(OUT)/autori.csv

include Makefile.inc

$(eval PROBS=$(addsuffix }, $(addprefix $${problem_,  $(shell seq -s" " 1 100)))) # :-)

PROBDEP= $(addprefix $(PROBLEMS)/, $(PROBS))
GRAPHDEP=fmfi.eps junior.eps mff.eps trojsten.eps vyfuk.eps
SERIEDEP=$(PROBDEP) $(addprefix $(GRAPHICS)/, $(GRAPHDEP)) common.tex $(PROBLEMS)/sort.tex uvod.tex titulky.tex zasluhy.tex $(SIGNATURES)

PLACENO=$(shell basename $(@F) | sed 's/.*-\([0-9]*\).*/\1/')
TEAMSCOUNT=$(shell cat $(TEAMS)/teams-$(PLACENO).tex | wc -l)
TEAMSCOUNT=1 # DELETE ONLY FOR PRINTING!

XELATEX_WEB     =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\UseOption{web,lngcs}\input{$<}'
XELATEX_WEBSK   =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\UseOption{web,lngsk}\input{$<}'
XELATEX_PROBS   =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\UseOption{print,lngcs,sorted}\def\placeno{$(PLACENO)}\def\teamscount{$(TEAMSCOUNT)}\input{$<}'
XELATEX_PROBSSK =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\UseOption{print,lngsk,sorted}\def\placeno{$(PLACENO)}\def\teamscount{$(TEAMSCOUNT)}\input{$<}'
XELATEX_PROBST  =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\UseOption{print,lngcs,tisk}\def\placeno{$(PLACENO)}\def\teamscount{$(TEAMSCOUNT)}\input{$<}'
XELATEX_PROBSTSK=xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\UseOption{print,lngsk,tisk}\def\placeno{$(PLACENO)}\def\teamscount{$(TEAMSCOUNT)}\input{$<}'
XELATEX_PRINT   =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\classoptions{twoside}\def\UseOption{print,lngcs}\input{$<}'
XELATEX_PRINTSK =xelatex -output-directory $(@D) -jobname $(basename $(@F)) '\def\classoptions{twoside}\def\UseOption{print,lngsk}\input{$<}'

$(PROBLEMS)/Makefile.inc: $(PROBLEMS)/problem-sort.tex
	xelatex -output-directory $(OUT) poradi_uloh.tex
	mv $(OUT)/Makefile.inc $(PROBLEMS)
	mv $(OUT)/sort.tex     $(PROBLEMS)

Tasks.inc: $(TEAMSFILE)
	./teams_task.sh $(TEAMSFILE) Tasks.inc

# targets for tasks
include Tasks.inc

$(OUT)/reseni.cs.pdf: reseni.tex $(SERIEDEP)
	$(XELATEX_WEB)
	$(XELATEX_WEB)

$(OUT)/reseni.sk.pdf: reseni.tex $(SERIEDEP)
	$(XELATEX_WEBSK)
	$(XELATEX_WEBSK)

$(OUT)/reseni-print.cs.pdf: reseni.tex $(SERIEDEP)
	$(XELATEX_PRINT)
	$(XELATEX_PRINT)

$(OUT)/reseni-print.sk.pdf: reseni.tex $(SERIEDEP)
	$(XELATEX_PRINTSK)
	$(XELATEX_PRINTSK)

$(OUT)/reseni-book.%.pdf: $(OUT)/reseni-print.%.pdf
	pdfbook --booklet true --outfile '$@' $<

$(OUT)/vysledky.pdf: vysledky.tex $(SERIEDEP)
	$(XELATEX_PRINT)

$(OUT)/autori.csv: autori.tex $(SERIEDEP)
	xelatex -output-directory $(@D) -jobname $(basename $(@F)) $<

$(TEAMS)/teams-%.tex: $(TEAMSFILE) Makefile
	sort $(TEAMSFILE) -t";" -k 4 | awk -F";" '($$3==$*) {i=i+1;print i";"$$1";"$$2;}' | sed 's/\([0-9]*\);\([0-9]*\);\(.*\)/\\newteam{\1}{\2}{\3}/g;s/&/\\&/g;s/%/\\%/g' >$@

#	cat $< | sort -t";" -k 7rn -k 1n | awk -F";" '($$5==$(PLACENO)) && ($$7!=0) {i=i+1; print i";"$$1";"$$2}' | sed 's/\([0-9]*\);\([0-9]*\);\(.*\)/\\newteam{\1}{\2}{\3}/g;s/&/\\&/g;s/%/\\%/g' >$@

clean:
	find $(OUT) -type f -not \( -name "*.pdf" -o -name ".*" \) | xargs "rm -f "

cleanall:
	rm -f $(OUT)/*
#	ls $(GRAPHICS) $(PGRAPHICS) | grep -v '\(mp\|plt\|eps\|jpg\|png\)$$' | xargs rm

cleanalldep:
	rm -f $(OUT)/* 
	rm -f $(PROBLEMS)/Makefile*
	rm -f $(PROBLEMS)/sort*
	rm -f $(TEAMS)/*
	rm -f Tasks.inc

