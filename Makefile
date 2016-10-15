# Simple recursive makefile

SUBDIRS= manualy tabulky ulohy
# anketa ulohy 

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	make all -C $@
