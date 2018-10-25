FILE=pres


.PHONY: make
make:
	@pdflatex $(FILE).tex


.PHONY: travis-build
travis-build: clean-all
	pdflatex -halt-on-error $(FILE).tex


.PHONY: clean
clean:
	rm -fv *.aux *.log *.nav *.out *.snm *.toc


.PHONY: clean-all
clean-all: clean
	rm -fv $(FILE).pdf
