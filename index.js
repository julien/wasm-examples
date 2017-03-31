
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
    loadImage('assets/madrid.jpg'),
    loadWASM()
  ]).then(data => {

    img = data[0];
    webdsp = data[1];

    ctx.drawImage(img, 0, 0);
    const pixels = ctx.getImageData(0, 0, img.width, img.height);
    pixels.data.set(webdsp.sobelFilter(pixels.data, img.width, img.height));
    ctx.putImageData(pixels, 0, 0);
  });


}, false);
