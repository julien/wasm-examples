EMSDK := $(HOME)/Documents/emsdk

bin := a.out.js
src := main.c

$(bin): $(src) $(check)
	emcc -o $@ $< -lm -O3 -s WASM=1 \
		-s BINARYEN_METHOD="'interpret-binary'"

check:
	bash -c $(EMSDK)/emsdk_env.sh

clean:
	rm $(bin)

default: $(target)
.PHONY: check clean


