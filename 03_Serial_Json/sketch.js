let mSerial;

let connectButton;

let readyToReceive;
let cBackgroundColor;

function receiveSerial() {
  let mLine = mSerial.readUntil("\n");
  trim(mLine);
  if (!mLine) return;

  if (mLine.charAt(0) != "{") {
    print("error: ", mLine);
    readyToReceive = true;
    return;
  }

  let data = JSON.parse(mLine).data;
  print(mLine, data);

  let a0 = data.A0;
  cBackgroundColor = map(a0.value, a0.min, a0.max, 0, 255);
  readyToReceive = true;
}

function connectToSerial() {
  if (!mSerial.opened()) {
    mSerial.open(9600);
    connectButton.hide();
    readyToReceive = true;
  }
}

function setup() {
  createCanvas(windowWidth, windowHeight);

  mSerial = createSerial();

  connectButton = createButton("Connect To Serial");
  connectButton.position(width / 2, height / 2);
  connectButton.mousePressed(connectToSerial);

  cBackgroundColor = 0;

  readyToReceive = false;
}

function draw() {
  background(cBackgroundColor);

  if (mSerial.opened() && readyToReceive) {
    mSerial.clear();
    mSerial.write(0xAB);
    readyToReceive = false;
  }

  if (mSerial.availableBytes() > 0) {
    receiveSerial();
  }
}
