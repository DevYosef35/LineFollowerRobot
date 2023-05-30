// Motorlar için pin tanımlamaları
int enA = 6;
int in1 = 2;
int in2 = 3;
int enB = 7;
int in3 = 4;
int in4 = 5;

// 4'lü çizgi okuma sensörü için pin tanımlamaları
int lineSensor1 = A0;
int lineSensor2 = A1;
int lineSensor3 = A2;
int lineSensor4 = A3;

// Ultrasonik sensörler için pin tanımlamaları

int trigPin2 = 10;
int echoPin2 = 11;
int trigPin3 = 12;
int echoPin3 = 13;

// İlerleme hızı
int motorSpeed = 200;

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // 4'lü çizgi okuma sensörü pinlerini giriş olarak ayarla
  pinMode(lineSensor1, INPUT);
  pinMode(lineSensor2, INPUT);
  pinMode(lineSensor3, INPUT);
  pinMode(lineSensor4, INPUT);

  // Ultrasonik sensör pinlerini ayarla

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // Seri iletişim hızını başlat
  Serial.begin(9600);
}

void loop() {
  // Sensör okumaları
  int line1 = digitalRead(lineSensor1);
  int line2 = digitalRead(lineSensor2);
  int line3 = digitalRead(lineSensor3);
  int line4 = digitalRead(lineSensor4);
  
 
  int distance2 = readDistance(trigPin2, echoPin2);
  int distance3 = readDistance(trigPin3, echoPin3);

  // Seri monitöre verileri gönder
  Serial.print("Line Sensors: ");
  Serial.print(line1);
  Serial.print(" ");
  Serial.print(line2);
  Serial.print(" ");
  Serial.print(line3);
  Serial.print(" ");
  Serial.println(line4);
  
  Serial.print("Ultrasonic Distances: ");
  Serial.print(distance2);
  Serial.print(" ");
  Serial.println(distance3);

  // Sol çizgi tespit edildiyse
  if (lineDetected(line1) || lineDetected(line2)) {
    // Sol çizgi takip
    moveLeft();
    Serial.println("Turning Left");
  }
  // Sağ çizgi tespit edildiyse
  else if (lineDetected(line3) || lineDetected(line4)) {
    // Sağ çizgi takip
    moveRight();
    Serial.println("Turning Right");
  }
  // Hiçbir çizgi tespit edilmediyse
  else {
    // Düz git
    moveForward();
    Serial.println("Moving Forward");
  }
  
  // Uzaklık mesafeleri kontrolü
  if ( distance2 < 10 || distance3 < 10) {
    // Motorları durdur
    stopMotors();
    Serial.println("Obstacle Detected! Stopping Motors");
  }
}

// Çizgi tespit edildi mi?
bool lineDetected(int lineValue) {
  if (lineValue == LOW) {
    return true;
  } else {
    return false;
  }
}

// Ultrasonik mesafe ölçümü
int readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  return distance;
}

// İleri hareket fonksiyonu
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, motorSpeed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, motorSpeed);
}

// Sol çizgi takip fonksiyonu
void moveLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, motorSpeed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, motorSpeed);
}

// Sağ çizgi takip fonksiyonu
void moveRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, motorSpeed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, motorSpeed);
}

// Motorları durdurma fonksiyonu
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
