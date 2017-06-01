bin := loading.wasm
src := loading.c

$(bin): $(src)
	emcc -o $@ $< -lm -O3 -s WASM=1 \
		-s SIDE_MODULE=1

clean:
	@if [ -a $(bin) ]; then rm $(bin); fi;

default: $(bin)
.PHONY: clean
