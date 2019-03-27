all:
	@mkdir -p build
	g++ -o build/alc src/main.cpp src/SqMatrix.cpp src/Vector.cpp -Iinclude -std=c++14 -Wall

.PHONY: clean

clean:
	rm -rf build 