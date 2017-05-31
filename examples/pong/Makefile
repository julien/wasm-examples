EMSDK := $(HOME)/Documents/emsdk

bin := pong.wasm
ast := pong.wast
src := pong.c

$(bin): $(src) $(check)
	emcc -o $@ $< -lm -O3 -s WASM=1 -s SIDE_MODULE=1

check:
	bash -c $(EMSDK)/emsdk_env.sh

clean:
	rm $(bin) $(ast)

$(ast): $(bin)
	wasm-dis $< -o $@

default: $(target)
.PHONY: check clean $(ast)
