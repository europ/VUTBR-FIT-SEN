FILE=doc

.PHONY: make
make: clean
	pdflatex -draftmode $(FILE)
	bibtex $(FILE)
	pdflatex -draftmode $(FILE)
	pdflatex $(FILE)

.PHONY: clean
clean:
	@rm -fv *.aux *.log *.dvi *.ps *.bbl *.blg *.toc *.out

.PHONY: clean-all
clean-all: clean
	@rm -fv *.pdf
