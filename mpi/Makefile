CXXFLAGS = -qopenmp
CXX = mpiicpc

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
	echo 'cd $$PBS_O_WORKDIR ; mpirun -machinefile $$PBS_NODEFILE ./bin/transcoder ../datasets/dna_dataset.txt' | qsub -v OMP_NUM_THREADS=32 -l nodes=4:flat -N transcoder  

clean:
	rm -rf bin/ *.o *.gch transcoder outputDna.txt transcoder.*

