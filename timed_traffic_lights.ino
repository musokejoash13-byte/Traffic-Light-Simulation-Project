// 7-segment pins remain the same (2-8)
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; 

// Road A Pins
const int RA_RED = 9;
const int RA_YELLOW = 10;
const int RA_GREEN = 11;

// Road B Pins
const int RB_RED = 12;
const int RB_YELLOW = 13;
const int RB_GREEN = A0; // Using analog pin as digital for more space

void setup() {
  for (int i = 0; i < 7; i++) pinMode(segmentPins[i], OUTPUT);
  pinMode(RA_RED, OUTPUT); pinMode(RA_YELLOW, OUTPUT); pinMode(RA_GREEN, OUTPUT);
  pinMode(RB_RED, OUTPUT); pinMode(RB_YELLOW, OUTPUT); pinMode(RB_GREEN, OUTPUT);
}

// Function to reset all lights to OFF
void allOff() {
  digitalWrite(RA_RED, LOW); digitalWrite(RA_YELLOW, LOW); digitalWrite(RA_GREEN, LOW);
  digitalWrite(RB_RED, LOW); digitalWrite(RB_YELLOW, LOW); digitalWrite(RB_GREEN, LOW);
}

void loop() {
  // PHASE 1: Road A is Green, Road B is Red
  allOff();
  digitalWrite(RA_GREEN, HIGH);
  digitalWrite(RB_RED, HIGH);
  runCountdown(9);

  // PHASE 2: Road A is Yellow, Road B is Red
  digitalWrite(RA_GREEN, LOW);
  digitalWrite(RA_YELLOW, HIGH);
  runCountdown(3);

  // PHASE 3: Road A is Red, Road B is Green
  allOff();
  digitalWrite(RA_RED, HIGH);
  digitalWrite(RB_GREEN, HIGH);
  runCountdown(9);

  // PHASE 4: Road A is Red, Road B is Yellow
  digitalWrite(RB_GREEN, LOW);
  digitalWrite(RB_YELLOW, HIGH);
  runCountdown(3);
}

void runCountdown(int seconds) {
  for (int i = seconds; i >= 0; i--) {
    displayDigit(i); // uses the digit logic from before
    delay(1000);
  }
}
void displayDigit(int num) {
  // mapping segments {a, b, c, d, e, f, g}
  int digits[10][7] = {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
  };

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[num][i]);
  }
}