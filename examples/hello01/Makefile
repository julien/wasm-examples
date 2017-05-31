EMSDK := $(HOME)/Documents/emsdk

dst := hello.html
src := hello.c

$(dst): $(src) $(check)
	emcc -o $@ $< -lm -O3 -s WASM=1

check:
	bash -c $(EMSDK)/emsdk_env.sh

clean:
	rm $(dst) hello.js hello.wasm

default: $(target)
.PHONY: check clean
