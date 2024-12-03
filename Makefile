APPNAME = Test
EXT = .cpp
OBJECTS = objects

output: check-dir $(OBJECTS)/test.o
	g++ -Wall $(OBJECTS)/test.o -o tests/builds/test.exe

$(OBJECTS)/test.o: test.cpp
	g++ -I../eigen/ -IC:/Users/zycru/OneDrive/Documents/c++/Fastor-0.6.4/Fastor -IC:/Users/zycru/OneDrive/Documents/c++/Fastor-0.6.4/ -c test.cpp -o $(OBJECTS)/test.o

run:
	./tests/builds/test.exe

clean:
	del $(OBJECTS)/*.o ./tests/builds/test.exe

check-dir:
	if not exist $(OBJECTS) mkdir objects
	if not exist tests/builds mkdir tests/builds