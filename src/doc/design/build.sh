#!/bin/sh
# generates
# Reqs_Design_Decisions.aux Reqs_Design_Decisions.toc Reqs_Design_Decisions.out Reqs_Design_Decisions.log Reqs_Design_Decisions.pdf
# Convert .svg to .pdf for pdflatex using inkscape (use --export-latex to generate extra .tex to maintain fonts, etc):
#inkscape -D -z --file=Reqs_DD_layers.svg --export-pdf=Reqs_DD_layers.pdf
pdflatex Reqs_Design_Decisions && \
pdflatex Reqs_Design_Decisions

