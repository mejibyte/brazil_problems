.PHONY: all pdf ps pics clean

all: pdf ps

pdf: problems.pdf 
ps:  problems.ps  

problemspics := $(patsubst %.mp,%.1,$(wildcard pics/[^xyz]*.mp))

problems.dvi: problems.tex olymp.sty $(problemspics) texts/[^xyz]*.tex
	latex problems.tex
	latex problems.tex

%.ps: %.dvi 
	dvips $<

%.pdf: %.dvi
	dvipdfm -p a4 $<

pics/%.1: pics/%.mp
	make -C pics $(@F)

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.dvi
	rm -f *.ps
	rm -f *.pdf
	make -C pics clean

