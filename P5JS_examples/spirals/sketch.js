var angle = 0;
  var r = 10;

var spin = 0.1;
var grow = spin * 5;

function setup() {
  createCanvas(400, 400);
  background(220);
}

function draw() {
  angle += spin;
  r = r + grow;
  //r = noise(angle) * 100;
  // Polar to Cartesian Transformation
  var x = cos(angle)*r;
  var y = sin(angle)*r;
  translate(200, 200);
  //line(0, 0, x, y);
  ellipse(x, y, 10, 10);
}
