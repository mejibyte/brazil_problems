.PHONY: all pdf ps pics clean

all: pdf ps

pdf: practice.pdf problems.pdf 
ps:  practice.ps  problems.ps  

practicepics := $(patsubst %.mp,%.1,$(wildcard pics/[xyz]*.mp))
problemspics := $(patsubst %.mp,%.1,$(wildcard pics/[^xyz]*.mp))

practice.dvi: practice.tex olymp.sty $(practicepics) texts/[xyz]*.tex
	latex practice.tex
	latex practice.tex

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

