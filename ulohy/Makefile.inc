# Common makefile parts
# vim: syn=make
#
include Makefile.conf
include $(PROBLEMS)/Makefile.inc

# == Graphics part ==
# -- Plots --
# epslatex output + size for two plots vertically on page
gnuplot=gnuplot -e "set format '$$\"%g\"$$' ; set terminal epslatex monochrome size 12.7cm,7.7cm; set output '$(@F)' " $(<F)
define plot
$(gnuplot)
endef
define plot-color
$(subst output ', output 'color/, $(subst monochrome,color,$(gnuplot)))
endef

$(PGRAPHICS)/%.eps $(PGRAPHICS)/%.tex: $(PGRAPHICS)/%.plt
	cd $(<D); $(plot)
$(PGRAPHICS)/color/%.eps $(PGRAPHICS)/color/%.tex: $(PGRAPHICS)/%.plt
	cd $(<D); $(plot-color)

$(GRAPHICS)/%.eps $(GRAPHICS)/%.tex: $(GRAPHICS)/%.plt
	$(plot)
$(GRAPHICS)/color/%.eps $(GRAPHICS)/color/%.tex: $(GRAPHICS)/%.plt
	$(plot-color)

# -- Metapost figures --
define mpost-a 
cd $(@D); mpost $(<F)
endef
define mpost-b
mv $< $@
endef
$(PGRAPHICS)/%.eps : $(PGRAPHICS)/%.1
	$(mpost-b)
$(PGRAPHICS)/%.1 : $(PGRAPHICS)/%.mp
	$(mpost-a)
$(GRAPHICS)/%.eps : $(GRAPHICS)/%.1
	$(mpost-b)
$(GRAPHICS)/%.1 : $(GRAPHICS)/%.mp
	$(mpost-a)

# -- IPE figures --
$(PGRAPHICS)/%.eps : $(PGRAPHICS)/%.ipe
	- ipetoipe -eps $< $@
	ipetoipe -eps $< $@

$(GRAPHICS)/%.eps : $(GRAPHICS)/%.ipe
	- ipetoipe -eps $< $@
	ipetoipe -eps $< $@

# == Data retrieval ==
GLOB_DATA := ../data
# credentials are at least obfuscated so they aren't easily grep'able from logs
SOAP_REQUEST = $(SOAPCLIENT) $(WS_URL) $(GLOB_DATA)/$(1) $(2) $(shell echo $(WS_USERNAME) | base64) $(shell echo $(WS_PASSWORD) | base64) 

$(GLOB_DATA)/%.xml: $(GLOB_DATA)/%Request.soap
	$(call SOAP_REQUEST,$*Request.soap,$@)

$(SIGNATURES): $(GLOB_DATA)/signatures.xml $(SIGNATURES_STYLE)
	xsltproc $(XSL_SIGNATURES) $< >$@

