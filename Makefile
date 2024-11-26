APPNAME = Test
EXT = .cpp
OBJECTS = objects

output: check-dir $(OBJECTS)\test.o $(OBJECTS)\Matrix.o $(OBJECTS)\Except.o $(OBJECTS)\RNN.o
	g++ -Wall $(OBJECTS)\test.o $(OBJECTS)\Except.o $(OBJECTS)\Matrix.o $(OBJECTS)\RNN.o -o tests\builds\test.exe

$(OBJECTS)\test.o: tests\test.cpp
	g++ -c tests\test.cpp -o $(OBJECTS)\test.o

$(OBJECTS)\Except.o: src\Except.cpp
	g++ -c src\Except.cpp -o $(OBJECTS)\Except.o
	
$(OBJECTS)\Matrix.o: src\Matrix.cpp
	g++ -c src\Matrix.cpp -o $(OBJECTS)\Matrix.o

$(OBJECTS)\RNN.o: src\RNN.cpp
	g++ -c src\RNN.cpp -o $(OBJECTS)\RNN.o

run:
	.\tests\builds\test.exe

clean:
	del $(OBJECTS)\*.o .\tests\builds\test.exe

check-dir:
	if not exist $(OBJECTS) mkdir objects
	if not exist tests\builds mkdir tests\builds