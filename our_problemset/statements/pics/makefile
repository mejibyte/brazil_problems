.PHONY: pics clean

psfiles := $(patsubst %.mp,%.1,$(wildcard *.mp))

pics: $(psfiles)

%.1: %.mp
	mpost $<

clean:
	rm -f *.log
	rm -f *.mpx
	# for %%a in (*.mp) do if exist %%~na.? del %%~na.?
