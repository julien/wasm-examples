const fs = require('fs');
const path = require('path');

if (typeof WebAssembly === 'undefined') {
  throw new Error('No WebAssembly support');
}

const memory = new WebAssembly.Memory({initial: 256, maximum: 256});
const env = {
  STACKTOP: 0,
  STACK_MAX: 5244960,
  abortStackOverflow: _ => {
    throw new Error('overflow');
  },
  tableBase: 0,
  memoryBase: 1024,
  table: new WebAssembly.Table({initial: 0, maximum: 0, element: 'anyfunc'}),
  memory: memory,
};

function loadWasm(url, importObj) {
  let data = new Buffer('');
  const stream = fs.createReadStream(url)
    .on('data', (chunk, encoding) => {
      data = Buffer.concat([data, chunk]);
    })
    .on('end', () => {
      WebAssembly.compile(data)
        .then(mod => {
          return WebAssembly.instantiate(mod, importObj);
        })
        .then(ins => {
          stream.emit('loaded', ins);
        })
        .catch(err => {
          stream.emit('error', err);
        });
    });
  return stream;
}


loadWasm(path.resolve(__dirname, 'loading.wasm'), {env})
  .on('loaded', ins => {
    console.log('exported functions');
    console.log(ins.exports);

    console.log('1 + 10.1\t', ins.exports._add(1, 10.1));
    console.log('10 - 9.02\t', ins.exports._sub(10, 9.02));
    console.log('3.2 * 2.6\t', ins.exports._mul(3.2, 2.6));
    console.log('4.3 / 1.5\t', ins.exports._div(4.3, 1.5));
  })
  .on('error', err => { console.error('failed loading webassembly') });
