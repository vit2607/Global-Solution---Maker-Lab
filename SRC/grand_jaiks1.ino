#include <Servo.h>



// Definição dos pinos dos Servomotores

const int PINO_SERVO_BRACO = 9;

const int PINO_SERVO_GARRA = 10;



// Configuração exata dos seus LEDs atuais

const int PINO_LED_VERMELHO = 6;  // LED Vermelho conectado ao pino 6

const int PINO_LED_VERDE = 13;    // LED Verde conectado ao pino 13



// Criação dos objetos Servo

Servo servoBraco;

Servo servoGarra;



int posBraco = 90; 

int posGarra = 10; 



void setup() {

  Serial.begin(9600);

  

  // Conecta os servos aos seus respectivos pinos

  servoBraco.attach(PINO_SERVO_BRACO);

  servoGarra.attach(PINO_SERVO_GARRA);

  

  // Configura os pinos dos LEDs como saída

  pinMode(PINO_LED_VERDE, OUTPUT);

  pinMode(PINO_LED_VERMELHO, OUTPUT);

  

  // Posiciona os servos no estado inicial

  servoBraco.write(posBraco);

  servoGarra.write(posGarra);

  

  // Estado Inicial: Garra começa aberta (Verde LIGADO, Vermelho DESLIGADO)

  digitalWrite(PINO_LED_VERDE, HIGH);

  digitalWrite(PINO_LED_VERMELHO, LOW);

  

  Serial.println("--- Sistema de Coleta Espacial Pronto ---");

  Serial.println("Comandos: U (Subir), D (Descer), O (Abrir), C (Fechar)");

}



void loop() {

  if (Serial.available() > 0) {

    char comando = Serial.read(); 

    

    switch (toupper(comando)) {

      

      case 'U': // Sobe o braço

        if (posBraco < 180) {

          posBraco += 15;

          if (posBraco > 180) posBraco = 180;

          servoBraco.write(posBraco);

          Serial.print("Braco Subindo. Angulo: ");

          Serial.println(posBraco);

        }

        break;

        

      case 'D': // Desce o braço

        if (posBraco > 0) {

          posBraco -= 15;

          if (posBraco < 0) posBraco = 0;

          servoBraco.write(posBraco);

          Serial.print("Braco Descendo. Angulo: ");

          Serial.println(posBraco);

        }

        break;

        

      case 'O': // Abrir a garra

        posGarra = 10; 

        servoGarra.write(posGarra);

        

        // Alterna os LEDs: Garra aberta = Verde ON, Vermelho OFF

        digitalWrite(PINO_LED_VERDE, HIGH);

        digitalWrite(PINO_LED_VERMELHO, LOW);

        

        Serial.println("Garra: ABERTA (LED Verde ON)");

        break;

        

      case 'C': // Fechar a garra

        posGarra = 90; 

        servoGarra.write(posGarra);

        

        // Alterna os LEDs: Garra fechada = Verde OFF, Vermelho ON

        digitalWrite(PINO_LED_VERDE, LOW);

        digitalWrite(PINO_LED_VERMELHO, HIGH);

        

        Serial.println("Garra: FECHADA (LED Vermelho ON)");

        break;

        

      case '\n':

      case '\r':

        break;

        

      default:

        break;

    }

  }

}