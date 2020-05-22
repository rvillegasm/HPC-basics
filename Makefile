bin/transcoder: bin/main.o bin/transcoder.o
	mkdir -p bin/
	$(CXX) -o $@ $^

bin/transcoder.o: src/transcode.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@

bin/main.o: src/main.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@

clean:
	rm -rf bin/ *.o *.gch transcoder

