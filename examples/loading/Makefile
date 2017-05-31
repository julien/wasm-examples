EMSDK := $(HOME)/Documents/emsdk

dst := loading.wasm
src := loading.c

$(dst): $(src) $(check)
	emcc -o $@ $< -lm -O3 -s WASM=1 \
		-s SIDE_MODULE=1

check:
	bash -c $(EMSDK)/emsdk_env.sh

clean:
	rm $(dst)

default: $(target)
.PHONY: check clean
