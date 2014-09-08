all: small medium large


small: compile
	./sphinx small/audio.raw language_model/turtle/ 2> /dev/null

medium: compile
	./sphinx medium/audio.raw language_model/HUB4/ 2> /dev/null

large: compile
	./sphinx large/audio.raw language_model/HUB4/ 2> /dev/null

compile:
	gcc main.c includes/*.c pocketsphinx/*.c sphinxbase/fe/*.c sphinxbase/feat/*.c sphinxbase/lm/*.c sphinxbase/util/*.c -o sphinx -lm -O2

clean:
	-rm out.txt sphinx
