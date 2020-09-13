// University of Missouri - Columbia
// SpiderCam Research | Cable driven robot team

// Malek Necibi - mnygp@umsystem.edu
// 09/13/2020

// global variables
const int frameSize = 72; // dimension in inches of frame cube
const int eeSize = 8; // dimension in inches of End-Effector square

const int frameOffset = frameSize - eeSize;

const int offsetFrameCoords[4][3] = {
  {0,   0, frameSize}, // corner fA (x, y, z)
  {0,  frameSize - frameOffset, frameSize}, // corner fB
  {frameSize - frameOffset,  0, frameSize}, // corner fC
  {frameSize - frameOffset, frameSize - frameOffset, frameSize}  // corner fD
};

float eeCoords[3] = {0, 0, 0}; // Coordinates of center of End-Effector
float lengths[4] = {0};
// end of variable declarations



void setup() {
  Serial.begin(9600);
  Serial.println("\nBegin");
  calcLengths(36, 36, 72);
  printLens(lengths);
  Serial.println("End");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


float* calcLengths(float xCoord, float yCoord, float zCoord) {
  float *offsetEECoord = calcOffsets(xCoord, yCoord, zCoord, eeSize);
  int (*frame)[3] = (int(*)[3]) offsetFrameCoords;  // create alias for frame
  
  for (int i = 0; i < 4; i++) {
    lengths[i] = calcLength3D(frame[i][0] - offsetEECoord[0], frame[i][1] - offsetEECoord[1], frame[i][2] - offsetEECoord[2]);
  }
  
  eeCoords[0] = xCoord;
  eeCoords[1] = yCoord;
  eeCoords[2] = zCoord;
  return lengths;
}

float* calcOffsets(float xCoord, float yCoord, float zCoord, int eeSize) {
  // frame Offset won't change during run-time, so calculated at compile-time
  
  static float offset[3];
  offset[0] = xCoord - eeSize/2;
  offset[1] = yCoord - eeSize/2;
  offset[2] = zCoord;
  
  return offset;
}

float calcLength3D (float a, float b, float c) {
  return sqrt(a*a + b*b + c*c);
}

void printLens(float lengths[4]) {
  Serial.print(lengths[1]);
  Serial.print("-------------");
  Serial.println(lengths[3]);
  for(int i = 0; i < 9; i++) {
    Serial.println("  |                 |");
  }
  Serial.print(lengths[0]);
  Serial.print("-------------");
  Serial.println(lengths[2]);
}
