bin := hello.js
src := hello.c

$(bin): $(src)
	emcc -o $@ $< -lm -O3 -s WASM=1 \
		-s EXPORTED_FUNCTIONS="['_add']" \
		-s ALLOW_MEMORY_GROWTH=1

	sed -i'.bak' -e 's/else{doRun()}/&script.dispatchEvent(doneEvent);/' $@
	rm *.bak

clean:
	@if [ -a $(bin) ]; then rm $(bin); fi;
	@if [ -a hello.wasm ]; then rm hello.wasm; fi;

default: $(bin)
.PHONY: clean
