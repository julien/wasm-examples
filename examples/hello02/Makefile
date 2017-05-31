EMSDK := $(HOME)/Documents/emsdk

dst := hello.js
src := hello.c

$(dst): $(src) $(check)
	emcc -o $@ $< -lm -O3 -s WASM=1 \
		-s EXPORTED_FUNCTIONS="['_add']" \
		-s ALLOW_MEMORY_GROWTH=1

	sed -i'.bak' -e 's/else{doRun()}/&script.dispatchEvent(doneEvent);/' $@
	rm *.bak

check:
	bash -c $(EMSDK)/emsdk_env.sh

clean:
	rm $(dst)

default: $(target)
.PHONY: check clean
