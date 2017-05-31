
window.addEventListener('load', () => {

  const canvas = document.getElementById('c');
  canvas.width = innerWidth;
  canvas.height = innerHeight;

  const ctx = canvas.getContext('2d');

  let webdsp = {};
  let img = null;

  const loadImage = src => new Promise((resolve, reject) => {
      const img = new Image();
      img.onload = () => resolve(img);
      img.onerror = e => reject(e);
      img.src = src;
    });

  Promise.all([
    loadImage('./assets/madrid.jpg'),
    loadWASM()
  ]).then(data => {

    img = data[0];
    webdsp = data[1];

    const x = (canvas.width - img.width) / 2;
    const y = (canvas.height - img.height) / 2;
    const w = img.width;
    const h = img.height;

    ctx.drawImage(img, x, y, w, h);
    const pixels = ctx.getImageData(x, y, img.width, img.height);

    pixels.data.set(webdsp.sobelFilter(pixels.data, img.width, img.height, true));
    // pixels.data.set(webdsp.acid(pixels.data, img.width, img.height));
    // pixels.data.set(webdsp.hulk(pixels.data, img.width));

    ctx.putImageData(pixels, x, y);
  });


});
