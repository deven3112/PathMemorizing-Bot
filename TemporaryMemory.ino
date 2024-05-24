#define yAxis_pin A1  // Joysticks Y-axis
#define xAxis_pin A2  // Joysticks X-axis

int ENA = 8;
int LM_IN1 = 9;
int LM_IN2 = 10;

int ENB = 11;
int RM_IN3 = 12;
int RM_IN4 = 13;
int sw = A3;
int del = 6;

int fwd_Counter = -1;
int lft_Counter = -1;
int rgt_Counter = -1;
int bwd_Counter = -1;
int stp_Counter = -1;

unsigned long int current_Time0 = 0;  // for FWD movement
unsigned long int current_Time1 = 0;  // for LEFT movement
unsigned long int current_Time2 = 0;  // for RIGHT movement
unsigned long int current_Time3 = 0;  // for BWD movement
unsigned long int current_Time4 = 0;  // for STOP

unsigned long int total_Fwd_Time[10];
unsigned long int total_Lft_Time[10];
unsigned long int total_Rgt_Time[10];
unsigned long int total_Bwd_Time[10];
unsigned long int total_Stp_Time[10];

byte seq = 0;
byte seq_Array[50];

void setup() {
  Serial.begin(9600);
  pinMode(xAxis_pin, INPUT);
  pinMode(yAxis_pin, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(LM_IN1, OUTPUT);
  pinMode(LM_IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(RM_IN3, OUTPUT);
  pinMode(RM_IN4, OUTPUT);
  pinMode(sw, INPUT);
  digitalWrite(sw, LOW); // Enable internal pull-up resistor
  pinMode(del, INPUT);

  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, LOW);

  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, LOW);
}

void loop() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  char value = valu();
  check_Inst(value);
  delay(100);
}

void check_Inst(char value) {
  switch (value) {
    case 'F':
      go_Forward();
      break;
    case 'L':
      go_Left();
      break;
    case 'R':
      go_Right();
      break;
    case 'B':
      go_Backward();
      break;
    case 'S':
      go_Stop();
      break;
    case 'G':
      go_In_Seq();
      break;
    case 'I':
      del_From_Local_Mem();
      break;
    default:
      // Handle default case if needed
      break;
  }
}

void go_Forward() {
  movement_Inst_Fwd();
  current_Time0 = millis();
  int i = seq_Array[(seq - 1)];
  switch (i) {
    case 2:
      total_Lft_Time[lft_Counter + 1] = (current_Time0 - current_Time1);
      lft_Counter++;
      break;
    case 3:
      total_Rgt_Time[rgt_Counter + 1] = (current_Time0 - current_Time2);
      rgt_Counter++;
      break;
    case 4:
      total_Bwd_Time[bwd_Counter + 1] = (current_Time0 - current_Time3);
      bwd_Counter++;
      break;
    case 5:
      total_Stp_Time[stp_Counter + 1] = (current_Time0 - current_Time4);
      stp_Counter++;
      break;
  }
  seq_Array[seq] = 1;
  seq++;
}

void go_Left() {
  movement_Inst_Lft();
  current_Time1 = millis();
  int i = seq_Array[(seq - 1)];
  switch (i) {
    case 1:
      total_Fwd_Time[fwd_Counter + 1] = (current_Time1 - current_Time0);
      fwd_Counter++;
      break;
    case 3:
      total_Rgt_Time[rgt_Counter + 1] = (current_Time1 - current_Time2);
      rgt_Counter++;
      break;
    case 4:
      total_Bwd_Time[bwd_Counter + 1] = (current_Time1 - current_Time3);
      bwd_Counter++;
      break;
    case 5:
      total_Stp_Time[stp_Counter + 1] = (current_Time1 - current_Time4);
      stp_Counter++;
      break;
  }
  seq_Array[seq] = 2;
  seq++;
}

void go_Right() {
  movement_Inst_Rgt();
  current_Time2 = millis();
  int i = seq_Array[(seq - 1)];
  switch (i) {
    case 1:
      total_Fwd_Time[fwd_Counter + 1] = (current_Time2 - current_Time0);
      fwd_Counter++;
      break;
    case 2:
      total_Lft_Time[lft_Counter + 1] = (current_Time2 - current_Time1);
      lft_Counter++;
      break;
    case 4:
      total_Bwd_Time[bwd_Counter + 1] = (current_Time2 - current_Time3);
      bwd_Counter++;
      break;
    case 5:
      total_Stp_Time[stp_Counter + 1] = (current_Time2 - current_Time4);
      stp_Counter++;
      break;
  }
  seq_Array[seq] = 3;
  seq++;
}

void go_Backward() {
  movement_Inst_Bwd();
  current_Time3 = millis();
  int i = seq_Array[(seq - 1)];
  switch (i) {
    case 1:
      total_Fwd_Time[fwd_Counter + 1] = (current_Time3 - current_Time0);
      fwd_Counter++;
      break;
    case 2:
      total_Lft_Time[lft_Counter + 1] = (current_Time3 - current_Time1);
      lft_Counter++;
      break;
    case 3:
      total_Rgt_Time[rgt_Counter + 1] = (current_Time3 - current_Time2);
      rgt_Counter++;
      break;
    case 5:
      total_Stp_Time[stp_Counter + 1] = (current_Time3 - current_Time4);
      stp_Counter++;
      break;
  }
  seq_Array[seq] = 4;
  seq++;
}

void go_Stop() {
  movement_Inst_Stp();
  current_Time4 = millis();
  int i = seq_Array[(seq - 1)];
  switch (i) {
    case 1:
      total_Fwd_Time[fwd_Counter + 1] = (current_Time4 - current_Time0);
      fwd_Counter++;
      break;
    case 2:
      total_Lft_Time[lft_Counter + 1] = (current_Time4 - current_Time1);
      lft_Counter++;
      break;
    case 3:
      total_Rgt_Time[rgt_Counter + 1] = (current_Time4 - current_Time2);
      rgt_Counter++;
      break;
    case 4:
      total_Bwd_Time[bwd_Counter + 1] = (current_Time4 - current_Time3);
      bwd_Counter++;
      break;
  }
  seq_Array[seq] = 5;
  seq++;
}

void go_In_Seq() {
  for (int i = 0; i < (seq + 1); i++) {
    int value1 = seq_Array[i];
    switch (value1) {
      case 1:
        go_Forward_Seq(i);
        break;
      case 2:
        go_Left_Seq(i);
        break;
      case 3:
        go_Right_Seq(i);
        break;
      case 4:
        go_Backward_Seq(i);
        break;
      case 5:
        go_Stop_Seq(i);
        break;
      default:
        break;
    }
  }
}

void del_From_Local_Mem() {
  fwd_Counter = -1;
  lft_Counter = -1;
  rgt_Counter = -1;
  bwd_Counter = -1;
  stp_Counter = -1;

  for (int i = 0; i < 10; i++) {
    total_Fwd_Time[i] = 0;
    total_Lft_Time[i] = 0;
    total_Rgt_Time[i] = 0;
    total_Bwd_Time[i] = 0;
    total_Stp_Time[i] = 0;
  }

  for (int i = 0; i < 50; i++) {
    seq_Array[i] = 0;
  }

  seq = 0;
}

void go_Forward_Seq(int j) {
  movement_Inst_Fwd();
  delay(total_Fwd_Time[j]);
}

void go_Left_Seq(int k) {
  movement_Inst_Lft();
  delay(total_Lft_Time[k]);
}

void go_Right_Seq(int l) {
  movement_Inst_Rgt();
  delay(total_Rgt_Time[l]);
}

void go_Backward_Seq(int m) {
  movement_Inst_Bwd();
  delay(total_Bwd_Time[m]);
}

void go_Stop_Seq(int n) {
  movement_Inst_Stp();
  delay(total_Stp_Time[n]);
}

void movement_Inst_Fwd() {
  Serial.println("Going_Forward");
  digitalWrite(LM_IN1, HIGH);
  digitalWrite(LM_IN2, LOW);
  digitalWrite(RM_IN3, HIGH);
  digitalWrite(RM_IN4, LOW);
}

void movement_Inst_Lft() {
  Serial.println("Going_Left");
  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, HIGH);
  digitalWrite(RM_IN3, HIGH);
  digitalWrite(RM_IN4, LOW);
}

void movement_Inst_Rgt() {
  Serial.println("Going_Right");
  digitalWrite(LM_IN1, HIGH);
  digitalWrite(LM_IN2, LOW);
  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, HIGH);
}

void movement_Inst_Bwd() {
  Serial.println("Going_Backward");
  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, HIGH);
  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, HIGH);
}

void movement_Inst_Stp() {
  Serial.println("Stop");
  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, LOW);
  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, LOW);
}

char valu() {
  int delv = digitalRead(del);
  int swv = digitalRead(sw);
  Serial.print("swv: ");
  Serial.println(swv);
  Serial.print("delv: ");
  Serial.println(delv);

  int xAxis = analogRead(xAxis_pin);
  int yAxis = analogRead(yAxis_pin);

  if (xAxis < 470)
    return 'F';  // Forward
  else if (xAxis > 550)
    return 'B';  // Backward
  else if (yAxis < 470)
    return 'R';  // Right
  else if (yAxis > 550)
    return 'L';  // Left
  else if (xAxis > 470 && xAxis < 550 && yAxis > 470 && yAxis < 550)
    return 'S';  // Stop
  else if (swv == LOW)
    return 'G';  // Repeat
  else if (delv == 1)
    return 'I';  // Delete

  return 'D';  // Default
}
