# Makefile for DAL design decisions document
#
# The vector graphics figure 'Reqs_DD_layers.pdf' was produced using 'dia' in .dia, exported to .svg and converted to .pdf with 'inkscape'.
# This is a pain for anyone interested to just build to read the document, and since the figure changes infrequently, put it in the repos.
LATEX           = pdflatex -halt-on-error -interaction=nonstopmode
INKSCAPE        = inkscape
SPELLCHECKER    = aspell --lang=en_US --mode=tex check
NAME            = Reqs_Design_Decisions
SRC             = $(NAME).tex


Reqs_Design_Decisions.pdf: $(SRC) Reqs_DD_layers.pdf
	$(LATEX) Reqs_Design_Decisions
	$(LATEX) Reqs_Design_Decisions

#%.pdf: %.svg	# would be too generic for my taste
Reqs_DD_layers.pdf: Reqs_DD_layers.svg
	# --export-latex would generates extra .tex to maintain fonts, etc
	$(INKSCAPE) -D -z --file=$< --export-pdf=$@

spellcheck: $(SRC)
	@for INPUT in $?; do \
		$(SPELLCHECKER) $$INPUT; \
	done

# leaves the resulting .pdf
clean:
	@rm -f $(NAME).aux $(NAME).log $(NAME).out $(NAME).toc

.PHONY: clean spellcheck

