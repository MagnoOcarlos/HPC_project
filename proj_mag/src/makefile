CC = g++
CFLAGS = 

main: main.o Geometry.o Sphere.o
	$(CC) $(CFLAGS) -o main main.o Geometry.o Sphere.o
 
main.o: main.cpp Geometry.h Sphere.h
	$(CC) $(CFLAGS) -c main.cpp
 
Sphere.o: Sphere.h
 
Geometry.o: Geometry.h Sphere.h

clean:
	rm -rf *.o *~
