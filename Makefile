all:	LDA_wrap.cc LDA.py

clean:
	rm -rf xml docstrings.i LDA_wrap.cc LDA.py

xml/index.xml:
	doxygen doxygen.conf

docstrings.i:	xml/index.xml
	python external/doxy2swig.py $^ $@

LDA_wrap.cc LDA.py:	LDA.i docstrings.i
	swig -Wall -c++ -python -o LDA_wrap.cc LDA.i
