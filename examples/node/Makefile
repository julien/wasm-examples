bin := a.out.js
src := main.c

$(bin): $(src)
	emcc -o $@ $< -lm -O3 -s WASM=1 \
		-s BINARYEN_METHOD="'interpret-binary'"

clean:
	@if [ -a $(bin) ]; then rm $(bin); fi;
	@if [ -a hello.wasm ]; then rm hello.wasm; fi;

default: $(bin)
.PHONY: clean


