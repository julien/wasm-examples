bin := hello.html
src := hello.c

$(bin): $(src)
	emcc -o $@ $< -lm -O3 -s WASM=1

clean:
	@if [ -a $(bin) ]; then rm $(bin); fi;
	@if [ -a hello.js ]; then rm hello.js; fi;
	@if [ -a hello.wasm ]; then rm hello.wasm; fi;

default: $(bin)
.PHONY: clean
