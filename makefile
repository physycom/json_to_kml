EXE = json_to_kml.exe

all: dirtree
	$(CXX) -std=c++11 -Isrc -Isrc/jsoncons/src -o bin/$(EXE) src/json_to_kml.cpp 

dirtree:
	@mkdir -p bin

clean:
	rm -f bin/$(EXE)

cleanall:
	rm -rf bin obj
