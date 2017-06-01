bin := pong.wasm
ast := pong.wast
src := pong.c

$(bin): $(src)
	emcc -o $@ $< -lm -O3 -s WASM=1 -s SIDE_MODULE=1

clean:
	@if [ -a $(bin) ]; then rm $(bin); fi;
	@if [ -a $(ast) ]; then rm $(ast); fi;

$(ast): $(bin)
	$(BINARYEN_ROOT)/bin/wasm-dis $< -o $@

default: $(bin)
.PHONY: clean $(ast)
