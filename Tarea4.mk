all: PuntoNemo.pdf
	
PuntoNemo.pdf: Plots.py
	python $^

Plots.py: GeographicPoint.x
	./$^

GeographicPoint.x: GeographicPoint.c
	cc $^ -lm -o GeograpicPoint.x
