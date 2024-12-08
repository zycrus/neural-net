APPNAME = Test
EXT = .cpp
OBJECTS = objects

#output: check-dir $(OBJECTS)/test2_vectors.o
#	g++ -Wall $(OBJECTS)/test2_vectors.o -o tests/builds/test.exe


output: check-dir $(OBJECTS)/tens.o
	g++ -Wall $(OBJECTS)/tens.o -o tests/builds/tens.exe


$(OBJECTS)/tens.o: tens.cpp
	g++ -Iinclude/ -c tens.cpp -o $(OBJECTS)/tens.o

$(OBJECTS)/test2_vectors.o: test2_vectors.cpp
	g++ -Iinclude/ -c test2_vectors.cpp -o $(OBJECTS)/test2_vectors.o


$(OBJECTS)/test.o: test.cpp
	g++ -Iinclude/ -I../eigen/ -IC:/Users/zycru/OneDrive/Documents/c++/Fastor-0.6.4/Fastor -IC:/Users/zycru/OneDrive/Documents/c++/Fastor-0.6.4/ -c test.cpp -o $(OBJECTS)/test.o


$(OBJECTS)/Tensor.o: include/Tensor.cpp
	g++ -c include/Tensor.cpp -o $(OBJECTS)/Tensor.o

# run:
# 	./tests/builds/test.exe

run:
	./tests/builds/tens.exe

clean:
	del $(OBJECTS)/*.o ./tests/builds/test.exe

check-dir:
	if not exist $(OBJECTS) mkdir objects
	if not exist tests/builds mkdir tests/builds