#include <Servo.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>  

#define ledR 2
#define ledY 3
#define ledG 4
#define ledP 5
#define ledC 6
#define ledO 7
#define botao 8
#define servoPin 9

Servo servo1;
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;  

String status = "Ocupado";
int estadoAtual = 0;
bool botaoPressionado = false;
float leitoNum = 1.0;

void setup() {
  Serial.begin(9600);

  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledP, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledO, OUTPUT);
  pinMode(botao, INPUT_PULLUP);

  servo1.attach(servoPin);

  lcd.init();
  lcd.backlight();

  // Inicializa RTC
  if (! rtc.begin()) {
    Serial.println("RTC nao detectado!");
    while (1);
  }

  atualizarSistema();
}

void loop() {
  if (digitalRead(botao) == LOW && !botaoPressionado) {
    botaoPressionado = true;
    estadoAtual = (estadoAtual + 1) % 6;
    atualizarSistema();
  }
  if (digitalRead(botao) == HIGH) {
    botaoPressionado = false;
  }

  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c >= '0' && c <= '5') {
      estadoAtual = c - '0';
      atualizarSistema();
    }
  }

  delay(100);
}

void atualizarSistema() {
  
  digitalWrite(ledR, LOW); digitalWrite(ledY, LOW); digitalWrite(ledG, LOW);
  digitalWrite(ledP, LOW); digitalWrite(ledC, LOW); digitalWrite(ledO, LOW);

  switch (estadoAtual) {
    case 0:
      digitalWrite(ledR, HIGH);
      servo1.write(0);
      status = "Ocupado";
      break;
    case 1:
      digitalWrite(ledY, HIGH);
      servo1.write(108);
      status = "Iniciando manut.";
      break;
    case 2:
      digitalWrite(ledG, HIGH);
      servo1.write(180);
      status = "Desocupado";
      break;
    case 3:
      digitalWrite(ledC, HIGH);
      servo1.write(36);
      status = "Iniciando limpa.";
      break;
    case 4:
      digitalWrite(ledO, HIGH);
      servo1.write(72);
      status = "Finaliza limpa.";
      break;
    case 5:
      digitalWrite(ledP, HIGH);
      servo1.write(144);
      status = "Finaliza manut.";
      break;
    case 6: // Novo estado: Leito Pronto
      digitalWrite(ledG, HIGH); 
      servo1.write(180);        
      status = "Leito Pronto"; 
      break;
  }

  exibirDados(leitoNum, status);
  enviaJson(leitoNum, status);
}

void exibirDados(float leito, String stat) {
  DateTime now = rtc.now();
  char buf[17];
  snprintf(buf, sizeof(buf), "L%.1f %02d:%02d", leito, now.hour(), now.minute());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(buf);
  lcd.setCursor(0, 1);
  lcd.print(stat);
}

void enviaJson(float leito, String stat) {
  StaticJsonDocument<200> json;
  json["leito"] = leito;
  json["status"] = stat;
  DateTime now = rtc.now();
  json["hora"] = String(now.hour()) + ":" + String(now.minute());

  serializeJson(json, Serial);
  Serial.println();
}
