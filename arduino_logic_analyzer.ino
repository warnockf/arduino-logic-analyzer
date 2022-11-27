
#define A_15 52
#define A_14 50
#define A_13 48
#define A_12 46
#define A_11 44
#define A_10 42
#define A_9 40
#define A_8 38

#define A_7 36
#define A_6 34
#define A_5 32
#define A_4 30
#define A_3 28
#define A_2 26
#define A_1 24
#define A_0 22

#define D_7 53
#define D_6 51
#define D_5 49
#define D_4 47
#define D_3 45
#define D_2 43
#define D_1 41
#define D_0 39

#define CLK 2
#define RW 3

int addressPins[] = {A_15, A_14, A_13, A_12, A_11, A_10, A_9, A_8, A_7, A_6, A_5, A_4, A_3, A_2, A_1, A_0};

int dataPins[] = {D_7, D_6, D_5, D_4, D_3, D_2, D_1, D_0};

void setup() {
  for (int i = 0; i < 16; i++) {
    pinMode(addressPins[i], INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(dataPins[i], INPUT);
  }

  pinMode(CLK, INPUT);
  pinMode(RW, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLK), onClock, RISING);

  Serial.begin(9600);
}

void onClock() {
  char output[32];

  // Print address in binary
  int address = 0;
  for (int i = 0; i < 16; i++) {
    int bit = digitalRead(addressPins[i]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit;
  }

  Serial.print("\t");

  // Print data in binary
  int data = 0;
  for (int i = 0; i < 8; i++) {
    int bit = digitalRead(dataPins[i]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  char rw = digitalRead(RW) ? 'R' : 'W';

  // Print hex data
  sprintf(output, "\t%04X\t%c\t%02X", address, rw, data);
  Serial.println(output);
}

void loop() {
}
