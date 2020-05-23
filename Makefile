CXXFLAGS = -fopenmp

bin/transcoder: bin/main.o bin/transcoder.o
	mkdir -p bin/
	$(CXX) -o $@ $^ $(CXXFLAGS)

bin/transcoder.o: src/transcode.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

bin/main.o: src/main.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf bin/ *.o *.gch transcoder

