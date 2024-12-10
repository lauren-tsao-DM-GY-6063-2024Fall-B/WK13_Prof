let mSerial;

let connectButton;

let lastSend;

function sendSerial(data) {
  if (mSerial.opened()) {
    mSerial.write(JSON.stringify(data)); // turning data into a string
    mSerial.write("\n");
  }
}

function connectToSerial() {
  if (!mSerial.opened()) {
    mSerial.open(9600);
    connectButton.hide();
  }
}

function setup() {
  createCanvas(windowWidth, windowHeight);

  mSerial = createSerial();

  connectButton = createButton("Connect To Serial");
  connectButton.position(width / 2, height / 2);
  connectButton.mousePressed(connectToSerial);

  lastSend = millis(); // the last time p5.js sent info to arduino
}

function draw() {
  background(0);
  if (millis() - lastSend > 20) { // if its been 20 milliseconds since info was last sent
    sendSerial({ data: { x: mouseX, y: mouseY, w: width, h: height } });
    lastSend = millis(); // send it
  }
}
