#include <Servo.h>

// 서보 모터와 LED 핀 설정
Servo servoBattery;       // 배터리 분류 모터
Servo servoClothesShoes;  // 옷/신발 분류 모터
Servo servoMetal;         // 금속류(캔 등) 분류 모터
Servo servoPlasticBottle; // 플라스틱 병 분류 모터

int ledPinBattery = 12;       // 배터리 LED 핀 (빨간색)
int ledPinClothesShoes = 11;  // 옷/신발 LED 핀 (노란색)
int ledPinMetal = 10;         // 금속류 LED 핀 (파란색)
int ledPinPlasticBottle = 9;  // 플라스틱 병 LED 핀 (초록색)

String inputString = "";     // 시리얼 입력 데이터 저장
bool stringComplete = false; // 시리얼 데이터 완료 플래그

void setup() {
  // LED 핀을 출력 모드로 설정
  pinMode(ledPinBattery, OUTPUT);
  pinMode(ledPinClothesShoes, OUTPUT);
  pinMode(ledPinMetal, OUTPUT);
  pinMode(ledPinPlasticBottle, OUTPUT);

  // 서보 모터 핀을 아두이노에 연결
  servoBattery.attach(3);       // 배터리 분류용 모터 핀
  servoClothesShoes.attach(4);  // 옷/신발 분류용 모터 핀
  servoMetal.attach(5);         // 금속류 분류용 모터 핀
  servoPlasticBottle.attach(6); // 플라스틱 병 분류용 모터 핀

  // 서보 모터 초기 위치 설정
  servoBattery.write(0);
  servoClothesShoes.write(0);
  servoMetal.write(0);
  servoPlasticBottle.write(0);

  // 시리얼 통신 시작
  Serial.begin(9600);
}

void loop() {
  // 시리얼 데이터가 수신되면 처리
  if (stringComplete) {
    if (inputString == "battery") {                // 배터리 분류
      digitalWrite(ledPinBattery, HIGH);           // 배터리 빨간색 LED 켜기
      servoBattery.write(120);                     // 배터리 모터 120도 회전
      delay(1000);                                 // 1초 대기
      servoBattery.write(0);                       // 모터 원위치
      digitalWrite(ledPinBattery, LOW);            // 배터리 LED 끄기
    } 
    else if (inputString == "clothes_shoes") {     // 옷/신발 분류
      digitalWrite(ledPinClothesShoes, HIGH);      // 옷/신발 노란색 LED 켜기
      servoClothesShoes.write(120);                // 옷/신발 모터 120도 회전
      delay(1000);                                 // 1초 대기
      servoClothesShoes.write(0);                  // 모터 원위치
      digitalWrite(ledPinClothesShoes, LOW);       // 옷/신발 LED 끄기
    } 
    else if (inputString == "metal") {             // 금속류(캔 등) 분류
      digitalWrite(ledPinMetal, HIGH);             // 금속류 파란색 LED 켜기
      servoMetal.write(120);                       // 금속류 모터 120도 회전
      delay(1000);                                 // 모터 원위치
      servoMetal.write(0);                         // 모터 원위치
      digitalWrite(ledPinMetal, LOW);              // 금속류 LED 끄기
    } 
    else if (inputString == "plastic_bottle") {    // 플라스틱 병 분류
      digitalWrite(ledPinPlasticBottle, HIGH);     // 플라스틱 병 초록색 LED 켜기
      servoPlasticBottle.write(120);               // 플라스틱 병 모터 120도 회전
      delay(1000);                                 // 모터 원위치
      servoPlasticBottle.write(0);                 // 모터 원위치
      digitalWrite(ledPinPlasticBottle, LOW);      // 플라스틱 병 LED 끄기
    }

    // 입력 데이터 초기화
    inputString = "";
    stringComplete = false;
  }
}

// 시리얼 이벤트 함수: 데이터 수신 처리
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();  // 시리얼 데이터 읽기
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
