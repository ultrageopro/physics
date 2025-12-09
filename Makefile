all: build

build:
	mkdir -p build
	cd build && cmake .. && make -j8

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build