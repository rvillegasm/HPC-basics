CXXFLAGS = -qopenmp
CXX = icpc

bin/transcoder: bin/main.o bin/transcoder.o
	mkdir -p bin/
	$(CXX) -o $@ $^ $(CXXFLAGS)

bin/transcoder.o: src/transcode.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

bin/main.o: src/main.cpp
	mkdir -p bin/
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

queue: bin/transcoder
	echo 'cd $$PBS_O_WORKDIR ; ./bin/transcoder ../datasets/dna_dataset.txt' | qsub -l nodes=1:flat -N transcoder  

clean:
	rm -rf bin/ *.o *.gch transcoder

