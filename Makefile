main: main.cc gsl_mini.h function.h
	g++ -Wall main.cc gsl_mini.h function.h -o main -lgsl -lgslcblas

test: main
	./main

clean:
	rm *.o main minidata.dat fit.log
