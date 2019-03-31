#include <Timer.h>

Timer t;

String comando = "";
int brilho = 0;
int leds = 0;

//Define estados iniciais
boolean status7 = false;
boolean status8 = false;

//Define os leds
int ledR = 9;
int ledG = 10;
int ledB = 11;
int cooler = 6;

int ledH = 2;
int buzzer = 3;

int led1 = 4;
int led2 = 5;
int led3 = 7;
int led4 = 8;
int led5 = 12;
int led6 = 13;

void setup()
{
  //Inicia a serial
  Serial.begin(115200);
  Serial1.begin(38400);

  //Inicia os leds desligados
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(cooler, OUTPUT);

  pinMode(ledH, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(cooler, LOW);

  digitalWrite(ledH, LOW);
  digitalWrite(buzzer, LOW);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

  t.oscillate(ledH, 250, LOW);

}

void loop()
{

// Controle por App

  if (Serial1.available())
  {
    while (Serial1.available())
    {
      comando += (char)Serial1.read();
      delay(1);
    }

    Serial.println(comando);

    if (comando == "red") {
      if (brilho >= 40) {
        brilho -= 40;
        analogWrite(ledR, brilho);
        analogWrite(ledG, brilho);
        analogWrite(ledB, brilho);
      }
    }

    if (comando == "ylw") {
      if (brilho < 160) {
        brilho += 40;
        analogWrite(ledR, brilho);
        analogWrite(ledG, brilho);
        analogWrite(ledB, brilho);
      }
    }

    if (comando == "grn") {
      if (leds > 0) {
        if (leds == 6) {
          digitalWrite(led6, LOW);
        }
        if (leds == 5) {
          digitalWrite(led5, LOW);
        }
        if (leds == 4) {
          digitalWrite(led4, LOW);
        }
        if (leds == 3) {
          digitalWrite(led3, LOW);
        }
        if (leds == 2) {
          digitalWrite(led2, LOW);
        }
        if (leds == 1) {
          digitalWrite(led1, LOW);
        }
        leds -= 1;
      }
    }

    if (comando == "blu") {
      if (leds < 6) {
        if (leds == 5) {
          digitalWrite(led6, HIGH);
        }
        if (leds == 4) {
          digitalWrite(led5, HIGH);
        }
        if (leds == 3) {
          digitalWrite(led4, HIGH);
        }
        if (leds == 2) {
          digitalWrite(led3, HIGH);
        }
        if (leds == 1) {
          digitalWrite(led2, HIGH);
        }
        if (leds == 0) {
          digitalWrite(led1, HIGH);
        }
        leds += 1;
      }
    }

    if (comando == "fan") {
      if (status7) {
        digitalWrite(cooler, LOW);
        status7 = false;
      } else {
        analogWrite(cooler, 125);
        status7 = true;
      }
    }

    if (comando == "hlp") {
      if (status8) {
        digitalWrite(ledH, LOW);
        status8 = false;
      } else {
        digitalWrite(ledH, HIGH);

        tone(buzzer, 2000);
        delay(150);
        tone(buzzer, 2500);
        delay(200);
        tone(buzzer, 2000);
        delay(150);
        noTone(buzzer);

        status8 = true;
      }
    }

    comando = "";

  }

// Controle por botões

  int btnPress = analogRead(0);

  if (btnPress > 0) {
    //Serial.print ( "Botao pressionado: ");
    //Serial.print ( btnPress );

    if (btnPress < 100) {
      //Serial.println (" - ");
    }

    else if (btnPress < 200) {
      Serial.println (" - OK");
      if (status7) {
        digitalWrite(cooler, LOW);
        status7 = false;
      } else {
        analogWrite(cooler, 125);
        status7 = true;
      }
      delay(500);
    }

    else if (btnPress < 400) {
      Serial.println (" - DOWN");
      if (brilho >= 40) {
        brilho -= 40;
        analogWrite(ledR, brilho);
        analogWrite(ledG, brilho);
        analogWrite(ledB, brilho);
      }
      delay(500);
    }

    else if (btnPress < 600) {
      Serial.println (" - RIGHT");
      delay(500);
    }

    else if (btnPress < 750) {
      Serial.println (" - UP");
      if (brilho < 160) {
        brilho += 40;
        analogWrite(ledR, brilho);
        analogWrite(ledG, brilho);
        analogWrite(ledB, brilho);
      }
      delay(500);
    }

    else if (btnPress < 900) {
      Serial.println (" - LEFT");
      delay(500);
    }

    else if (btnPress > 1000) {
      Serial.println (" - CANCEL");
      if (status8) {
        digitalWrite(ledH, LOW);
        status8 = false;
        delay(500);
      } else {
        digitalWrite(ledH, HIGH);

        tone(buzzer, 2000);
        delay(150);
        tone(buzzer, 2500);
        delay(200);
        tone(buzzer, 2000);
        delay(150);
        noTone(buzzer);

        status8 = true;
      }
    }

  }

  if (status8) {
    t.update();
  }

}
