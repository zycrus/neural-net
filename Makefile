APPNAME = Test
EXT = .cpp
OBJECTS = objects

output: $(OBJECTS)\test.o $(OBJECTS)\Matrix.o $(OBJECTS)\Except.o
	g++ -Wall $(OBJECTS)\test.o $(OBJECTS)\Except.o $(OBJECTS)\Matrix.o -o tests\builds\test.exe

$(OBJECTS)\test.o: tests\test.cpp
	g++ -c tests\test.cpp -o $(OBJECTS)\test.o

$(OBJECTS)\Except.o: src\Except.cpp
	g++ -c src\Except.cpp -o $(OBJECTS)\Except.o
	
$(OBJECTS)\Matrix.o: src\Matrix.cpp
	g++ -c src\Matrix.cpp -o $(OBJECTS)\Matrix.o

run:
	.\tests\builds\test.exe

clean:
	del $(OBJECTS)\*.o .\tests\builds\test.exe