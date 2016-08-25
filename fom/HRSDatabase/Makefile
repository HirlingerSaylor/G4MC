make:
	g++ -c HRSDatabase.cc -o HRSDatabase.o `root-config --cflags --glibs`
	g++ -c fom.cc -o fom.o `root-config --cflags --glibs`
	g++ -c single_point.cc -o single_point.o `root-config --cflags --glibs`
	g++ -c contour.cc -o contour.o `root-config --cflags --glibs`
	g++ -c supercrextable.cc -o supercrextable.o `root-config --cflags --glibs`
	g++ fom.o HRSDatabase.o -o fom `root-config --cflags --glibs`
	g++ single_point.o HRSDatabase.o -o single_point `root-config --cflags --glibs`
	g++ contour.o HRSDatabase.o -o contour `root-config --cflags --glibs`
	g++ supercrextable.o HRSDatabase.o -o supercrextable `root-config --cflags --glibs`

clean:
	rm ./*.o
	rm ./fom
	rm ./single_point
	rm ./contour
	rm ./supercrextable
