EXE = json2kml.exe

all:
	g++ -std=c++11 -o $(EXE) -I. json_to_kml.cpp -fpermissive