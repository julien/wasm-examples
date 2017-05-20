#!/bin/bash

# use path to emsdk folder, relative to this directory
if [[ :$PATH: != *:"/emsdk":* ]]
then
  BASEDIR="$HOME/Documents/emsdk"
  BASEDIRSHA="$HOME/Documents/emsdk"
  EMSDK_ENV=$(find "$BASEDIR" -type f -name "emsdk_env.sh")
  source "$EMSDK_ENV"
fi

# add exported C/C++ functions here
CPP_FUNCS="[
 '_add'
]"

echo "compiling C++ to WASM ..."
emcc -o ./hello_c.js ./hello.cpp -lm -O3 -s WASM=1 \
  -s EXPORTED_FUNCTIONS="$CPP_FUNCS" \
  -s ALLOW_MEMORY_GROWTH=1 \

sed -i'.bak' 's/else{doRun()}/&script.dispatchEvent(doneEvent);/' hello_c.js

rm *.bak
