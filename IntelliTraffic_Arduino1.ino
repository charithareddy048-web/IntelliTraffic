// =====================================================
// IntelliTraffic - ARDUINO 1
// Traffic Lights + Emergency Vehicle Priority
// =====================================================

// Arduino 2 D4 -> Arduino 1 A3
#define EMERGENCY_PIN A3


// =====================================================
// TRAFFIC LIGHT PINS
// =====================================================

// Lane 1
#define R1 2
#define Y1 3
#define G1 4

// Lane 2
#define R2 5
#define Y2 6
#define G2 7

// Lane 3
#define R3 8
#define Y3 9
#define G3 10

// Lane 4
#define R4 11
#define Y4 12
#define G4 13


// =====================================================
// SETUP
// =====================================================

void setup() {

  pinMode(EMERGENCY_PIN, INPUT);

  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);

  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);

  pinMode(R3, OUTPUT);
  pinMode(Y3, OUTPUT);
  pinMode(G3, OUTPUT);

  pinMode(R4, OUTPUT);
  pinMode(Y4, OUTPUT);
  pinMode(G4, OUTPUT);

  allRed();
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // Check emergency
  if (digitalRead(EMERGENCY_PIN) == HIGH) {
    emergencyMode();
    return;
  }


  // LANE 1
  normalLight(R1, Y1, G1);

  if (digitalRead(EMERGENCY_PIN) == HIGH) {
    emergencyMode();
    return;
  }


  // LANE 2
  normalLight(R2, Y2, G2);

  if (digitalRead(EMERGENCY_PIN) == HIGH) {
    emergencyMode();
    return;
  }


  // LANE 3
  normalLight(R3, Y3, G3);

  if (digitalRead(EMERGENCY_PIN) == HIGH) {
    emergencyMode();
    return;
  }


  // LANE 4
  normalLight(R4, Y4, G4);
}


// =====================================================
// NORMAL TRAFFIC LIGHT
// =====================================================

void normalLight(int redPin, int yellowPin, int greenPin) {

  // First make every lane RED
  allRed();

  // Turn the selected lane's RED OFF
  digitalWrite(redPin, LOW);

  // Make sure yellow is OFF
  digitalWrite(yellowPin, LOW);

  // Selected lane GREEN
  digitalWrite(greenPin, HIGH);


  // GREEN = 20 seconds
  for (int i = 0; i < 200; i++) {

    if (digitalRead(EMERGENCY_PIN) == HIGH) {

      digitalWrite(greenPin, LOW);
      allRed();

      return;
    }

    delay(100);
  }


  // GREEN OFF
  digitalWrite(greenPin, LOW);


  // YELLOW
  digitalWrite(yellowPin, HIGH);


  // YELLOW = 8 seconds
  for (int i = 0; i < 80; i++) {

    if (digitalRead(EMERGENCY_PIN) == HIGH) {

      digitalWrite(yellowPin, LOW);
      allRed();

      return;
    }

    delay(100);
  }


  // YELLOW OFF
  digitalWrite(yellowPin, LOW);
}


// =====================================================
// EMERGENCY MODE
// =====================================================

void emergencyMode() {

  // ---------------------------------------
  // ALL LANES RED
  // ---------------------------------------

  allRed();

  delay(500);


  // ---------------------------------------
  // LANE 1 YELLOW
  // ---------------------------------------

  // Lane 1 RED OFF
  digitalWrite(R1, LOW);

  // Lane 1 GREEN OFF
  digitalWrite(G1, LOW);

  // Lane 1 YELLOW ON
  digitalWrite(Y1, HIGH);

  // Yellow = 8 seconds
  delay(8000);


  // Yellow OFF
  digitalWrite(Y1, LOW);


  // ---------------------------------------
  // LANE 1 GREEN
  // ---------------------------------------

  digitalWrite(R1, LOW);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, HIGH);


  // ---------------------------------------
  // EMERGENCY PRIORITY
  // ---------------------------------------

  // Lane 1 stays GREEN
  // Other lanes stay RED

  while (digitalRead(EMERGENCY_PIN) == HIGH) {

    delay(50);
  }


  // ---------------------------------------
  // EMERGENCY FINISHED
  // ---------------------------------------

  digitalWrite(G1, LOW);

  allRed();

  delay(1000);
}


// =====================================================
// ALL RED
// =====================================================

void allRed() {

  // Lane 1
  digitalWrite(R1, HIGH);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, LOW);

  // Lane 2
  digitalWrite(R2, HIGH);
  digitalWrite(Y2, LOW);
  digitalWrite(G2, LOW);

  // Lane 3
  digitalWrite(R3, HIGH);
  digitalWrite(Y3, LOW);
  digitalWrite(G3, LOW);

  // Lane 4
  digitalWrite(R4, HIGH);
  digitalWrite(Y4, LOW);
  digitalWrite(G4, LOW);
}
