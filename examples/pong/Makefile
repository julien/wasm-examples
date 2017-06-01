EMSDK := $(HOME)/Documents/emsdk

bin := pong.wasm
ast := pong.wast
src := pong.c

$(bin): $(src) $(check)
	emcc -o $@ $< -lm -O3 -s WASM=1 -s SIDE_MODULE=1

check:
	bash -c $(EMSDK)/emsdk_env.sh

clean:
	@if [ -a $(bin) ]; then rm $(bin); fi;
	@if [ -a $(ast) ]; then rm $(ast); fi;

$(ast): $(bin)
	wasm-dis $< -o $@

default: $(target)
.PHONY: check clean $(ast)
