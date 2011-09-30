docstrings.i:	xml/index.xml
	doxygen doxygen.conf
	python external/doxy2swig.py $^ $@

