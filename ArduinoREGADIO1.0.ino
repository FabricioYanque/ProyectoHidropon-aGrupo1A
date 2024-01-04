#include <SPI.h>  
#include <Wire.h> 
#include "DHT.h" // libreria del sensor DHT11
#include <Adafruit_GFX.h> // libreria de pantalla oled
#include <Adafruit_SSD1306.h>  // libreria de pantalla Oled
#include <Servo.h> // libreria del servomotor  

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define LOGO16_GLCD_HEIGHT 128 //  tamaño de pantaña, altura 
#define LOGO16_GLCD_WIDTH  64 // ancho de pantalla 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define DHTPIN 3     // Pin donde está conectado el sensor

#define DHTTYPE DHT11 // defino el tipo de sesor



int caudal;
int valor;          // variables
int value;
int hora;
int minuto;
int hora2;
int minuto2;
int ledpin = 13;
int relay = 10;   
float millivolts;  // variable de punto flotanto 
byte t;
byte h;
byte var;
int valor2;
byte estado;
byte escoge;
byte escoge2;
byte boton;
byte a;
byte segundo;
byte minuto3;
byte hora3;
long time_on;
long time_off;
long i;
long j;
long n;
long m;
const int potenciometro = A0; // puerto de conexion de potenciometro
const int pot2 = A1;       // puerto 2 de conexion de potenciomero

double flow; //Water flow L/Min 
int flowsensor = 2; 
unsigned long currentTime;
unsigned long lastTime;
unsigned long pulse_freq;

Servo servoMotor;
DHT dht(DHTPIN, DHTTYPE);

void pulse () // Interrupt function

{
   pulse_freq++;
 }

void setup() {

  //int sensorPin = A0;

  Serial.begin(9600);   //declarando la comunicacion con el puerto serial 
  dht.begin();     // decalrando sensor de hmedad
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000); //(tiempo 1 s)
  display.clearDisplay(); // limpiaro borrar la pantalla 

  // Clear the buffer.
  display.clearDisplay();
  a = 0;

  pinMode(12, INPUT);  // entrada
  pinMode(ledpin, OUTPUT); // salida
  pinMode(relay, OUTPUT); // salida
  servoMotor.attach(9);      // conexionn con servo
  digitalWrite (relay, 0);
  display.setTextSize(3);  // estableceer el tamaño de letra
  display.setTextColor(WHITE);  // color de texto
  display.setCursor(0, 0); //  ubicacion
  display.println("CONTROL");  // colocar texto
  display.setCursor(10, 32); // ubicacion
  display.println(" TIMER"); // texto timer
  delay(1000);         // tiempo de 1 s
  display.display();   // 
  display.clearDisplay();  // limpiar pantalla
  
   attachInterrupt(0, pulse, RISING); // Setup Interrupt
   currentTime = millis();
   lastTime = currentTime;

}

void loop() {
  //-----------------------------------------------
  //digitalWrite (relay, 1);
  display.setTextSize(1); // tamaño de texto
  //display.setTextColor(WHITE);
  display.setCursor(0, 0); // ubicacion de texto en pantalla 
  display.println(boton); 
  //------------------------------------------------
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.println("MECANICA");
  display.setCursor(10, 20);
  display.println("CONFIGURA");
  display.setCursor(10, 40);
  display.println("INICIAR");

  valor2 = analogRead(A2);  // lectura del sensor a la lapata A2 del arduino
  estado = (valor2 / 1023.0) * 100 ; // formula preestablecida  
  delay(80);  // tiempo de espera
  if (estado > 90) {
    escoge = escoge + 1;
  }
  if (escoge > 1) {           // convierto la señal que emite el sensor en V y la tranformo a un valor en C°
    escoge = 0;
  }

  switch (escoge) {

    case 0:
      display.fillTriangle(0, 21, 0, 31, 4, 27, WHITE);
      estado = digitalRead(12);
      if (estado == LOW) {
        // ESPERAMOS ANTES DE COMPROBAR NUEVAMENTE
        delay(0);
        if (estado == LOW ) {
          display.display();
          display.clearDisplay();
          boton = boton + 1;
          //-----------sub pantalla de configuracion----------------------------------------------
          while (boton > 0) {
            digitalWrite (ledpin, HIGH);
            display.setCursor(60, 4);
            display.println(":");
            display.setCursor(60, 38);
            display.println(":");
            delay(30);
            digitalWrite (ledpin, LOW);  // triangulo que se vizualiza en pantalla 
            display.setCursor(60, 4);
            display.println(" ");
            //delay(200);

            valor2 = analogRead(A2);
            estado = (valor2 / 1023.0) * 100 ;

            if (estado > 90) {
              escoge2 = escoge2 + 1;
            }

            if (escoge2 > 4) {
              escoge2 = 0;
            }

            display.setTextSize(1);
            //display.setTextColor(WHITE);
            display.setCursor(0, 0);
            display.println("U");
            display.setCursor(0, 10);
            display.println("P");
            display.setCursor(0, 40);
            display.println("D");
            display.setCursor(0, 50);
            display.println("W");
            //display.println(escoge2);

            switch (escoge2) {

              case 0:
                value = analogRead(A0);
               ( millivolts = value / 1023.0) * 100;
                valor = millivolts; // 10;

                if (valor > 90) {
                  hora = hora + 1;
                }

                if (valor < 10) {
                  hora = hora - 1;
                }
                if (hora < 0) {
                  hora = 0;
                }
                if (hora > 24) {
                  hora = 0;
                }

                display.drawLine(20, 25, 50, 25, WHITE);         // linea que se vizualiza en pantalla 
                display.drawLine(20, 26, 50, 26, WHITE);
                break;

              case 1:
                value = analogRead(potenciometro);
                millivolts = (value / 1023.0) * 100;
                valor = millivolts; // 10;

                if (valor > 90) {
                  minuto = minuto + 1;
                }

                if (valor < 10) {
                  minuto = minuto - 1;
                }
                if (minuto < 0) {
                  minuto = 0;
                }
                if (minuto > 59) {
                  minuto = 0;
                }

                display.drawLine(80, 25, 110, 25, WHITE);
                display.drawLine(80, 26, 110, 26, WHITE);
                break;

              case 2:
                value = analogRead(A0);
                millivolts = (value / 1023.0) * 100;
                valor = millivolts; // 10;

                if (valor > 90) {
                  hora2 = hora2 + 1;
                }

                if (valor < 10) {
                  hora2 = hora2 - 1;
                }

                if (hora2 < 0) {
                  hora2 = 0;
                }
                if (hora2 > 24) {
                  hora2 = 0;
                }

                display.drawLine(20, 63, 50, 63, WHITE);
                display.drawLine(20, 62, 50, 62, WHITE);
                break;

              case 3:
                value = analogRead(potenciometro);
                millivolts = (value / 1023.0) * 100;
                valor = millivolts; // 10;

                if (valor > 90) {
                  minuto2 = minuto2 + 1;
                }

                if (valor < 10) {
                  minuto2 = minuto2 - 1;
                }

                if (minuto2 < 0) {
                  minuto2 = 0;
                }
                if (minuto2 > 59) {
                  minuto2 = 0;
                }

                display.drawLine(80, 63, 110, 63, WHITE);
                display.drawLine(80, 62, 110, 62, WHITE);
                break;

              case 4:
                display.fillTriangle(0, 24, 0, 32, 4, 28, WHITE);
                //---------------presionar boton para salir---------------
                estado = digitalRead(12);
                if (estado == LOW) {
                  // ESPERAMOS ANTES DE COMPROBAR NUEVAMENTE
                  delay(25);
                  if (estado == LOW ) {
                    //display.display();
                    //display.clearDisplay();
                    escoge2 = 0;
                    escoge = 0;
                    boton = 0;

                  }
                }
                //-------------------------------------------------------
                break;
            }

            display.setTextSize(3);
            display.setTextColor(WHITE);

            display.setCursor(20, 0);
            if (hora < 10) {
              display.println(0);
              display.setCursor(38, 0);
              display.println(hora);
            }
            else {
              display.println(hora);
            }

            display.setCursor(80, 0);
            if (minuto < 10) {
              display.println(0);
              display.setCursor(98, 0);
              display.println(minuto);
            }
            else {
              display.println(minuto);
            }

            display.setCursor(20, 38);
            if (hora2 < 10) {
              display.println(0);
              display.setCursor(38, 38);
              display.println(hora2);
            }
            else {
              display.println(hora2);
            }
            display.setCursor(80, 0);

            display.setCursor(80, 38);
            if (minuto2 < 10) {
              display.println(0);
              display.setCursor(98, 38);
              display.println(minuto2);
            }
            else {
              display.println(minuto2);
            }

            display.display();
            display.clearDisplay();

          }
          //-----------fin while---------------------------------------------
        }
      }
      break;

    case 1:
      display.fillTriangle(0, 42, 0, 50, 4, 46, WHITE);

      estado = digitalRead(12);
      if (estado == LOW) {
        // ESPERAMOS ANTES DE COMPROBAR NUEVAMENTE
        delay(10);
        if (estado == LOW ) {
          display.display();
          display.clearDisplay();
          boton = 2;

          time_on = ((hora * 3600) + (minuto * 60));
          time_off = ((hora2 * 3600) + (minuto2 * 60));

          while (boton == 2) {

            //-------------------ESTRUCTURA FOR ---------------
            //--------------tiempo activo -------------------
            for ( i = 0; i < time_on; i++) {
              digitalWrite (ledpin, HIGH);
              digitalWrite (relay, 1);
              display.setTextSize(2);
              segundo = segundo + 1;
              a = a + 1;

              if (segundo > 59) {
                minuto3 = minuto3 + 1;
                segundo = 0;
              }

              if (minuto3 > 59) {
                hora3 = hora3 + 1;
                minuto3 = 0;
              }

              if (a > 3) {
                h = dht.readHumidity(); //Leemos la Humedad
                t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
                a = 0;
              }

               currentTime = millis();
               // Every second, calculate and print L/Min
               if(currentTime >= (lastTime + 1000))
               {
               lastTime = currentTime; 
               // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
               flow = (pulse_freq / 7.5); 
               caudal=flow;
               pulse_freq = 0; // Reset Counter
                   
      
              }

              display.setCursor(20, 0);
              display.println("REGANDO");
              //-----------------------------------------------
              display.setTextSize(2);
              display.setCursor(0, 20);
              display.println(hora3);
              display.setCursor(38, 20);
              display.println(":");
              display.setCursor(48, 20);
              display.println(minuto3);
              display.setCursor(78, 20);
              display.println(":");
              display.setCursor(88, 20);
              display.println(segundo);
              display.setTextSize(1);
              display.setCursor(0, 40);
              display.println("H:");
              display.setCursor(10, 40);
              display.println(h);
              display.setCursor(30, 40);
              display.println("T:");
              display.setCursor(40, 40);
              display.println(t);
              display.setCursor(60, 40);
              display.println("V:");
              display.setCursor(70, 40);
              display.println(caudal);
              var= map(t, 12, 30, 10, 180);

              //----------------------------------------
              //---------------presionar boton para salir---------------
              estado = digitalRead(12);
              if (estado == LOW) {
                // ESPERAMOS ANTES DE COMPROBAR NUEVAMENTE
                delay(10);
                if (estado == LOW ) {
                  i = time_on;
                  j = time_off;
                  boton = 0;
                  segundo = 0;
                  minuto3 = 0;
                  hora3 = 0;
                  digitalWrite (ledpin, LOW);
                  digitalWrite (relay, 0);
                  servoMotor.write(var);
                }
              }

              delay (700);
              display.display();
              display.clearDisplay();

            }
            // -------------------fin tiempo encendido ------------------
            hora3 = 0;
            minuto3 = 0;

            //--------------tiempo apagado -------------------
            if (boton == 2) {
              for ( j = 0; j < time_off; j++) {
                digitalWrite (ledpin, LOW);
                digitalWrite (relay, 0);
                display.setTextSize(2);
                segundo = segundo + 1;
                a = a + 1;

                if (segundo > 59) {
                  minuto3 = minuto3 + 1;
                  segundo = 0;
                }

                if (minuto3 > 59) {
                  hora3 = hora3 + 1;
                  minuto3 = 0;
                }

                if (a > 3) {
                  h = dht.readHumidity(); //Leemos la Humedad
                  t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
                  a = 0;
                }

                currentTime = millis();
               // Every second, calculate and print L/Min
               if(currentTime >= (lastTime + 1000))
               {
               lastTime = currentTime; 
               // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
               flow = (pulse_freq / 7.5); 
               caudal=flow;
               pulse_freq = 0; //
               }

                display.setCursor(10, 0);
                display.println("ESPERANDO");
                //-----------------------------------------------
                display.setTextSize(2);
                display.setCursor(0, 20);
                display.println(hora3);
                display.setCursor(38, 20);
                display.println(":");
                display.setCursor(48, 20);
                display.println(minuto3);
                display.setCursor(78, 20);
                display.println(":");
                display.setCursor(88, 20);
                display.println(segundo);
                display.setTextSize(1);
                display.setCursor(0, 40);
                display.println("H:");
                display.setCursor(10, 40);
                display.println(h);
                display.setCursor(30, 40);
                display.println("T:");
                display.setCursor(40, 40);
                display.println(t);
                display.setCursor(60, 40);
                display.println("V:");
                display.setCursor(70, 40);
                display.println(caudal);

                delay (700);
                display.display();
                display.clearDisplay();
                //----------------------------------------
                //---------------presionar boton para salir---------------
                estado = digitalRead(12);
                if (estado == LOW) {
                  // ESPERAMOS ANTES DE COMPROBAR NUEVAMENTE
                  delay(10);
                  if (estado == LOW ) {
                    j = time_off;
                    i = time_on;
                    boton = 0;
                    segundo = 0;
                    minuto3 = 0;
                    hora3 = 0;
                    digitalWrite (ledpin, LOW);
                    digitalWrite (relay, 0);
                  }
                }
                // --------------fin presion boton para salir -----------------
              }
            }
            // -------------------fin tiempo apagado ------------------
            hora3 = 0;
            minuto3 = 0;
            // -------------------fin tiempo apagado ------------------
          }
          // -------------------fin while------------------

        }
      }

      break;

  }

  display.display();
  display.clearDisplay();
  // put your main code here, to run repeatedly:
}
