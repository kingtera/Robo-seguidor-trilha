#include <Arduino.h>

//Alterar os pinos para os utilizados e especificar as portas da ponte H
//Definição dos pinos de controle do motor
#define M1 26 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta IN2 ponte H;
#define M2 33 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta IN4 ponte H;
#define dir1 25 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 32 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;


//Sensores funcionam da mesma forma, ao precisa alterar a conexao para receber a entrada digital D0 ao inves da medicao analógica A0
//Definição dos pinos dos sensores
#define pin_S1 13
#define pin_S2 12
int Sensor1 = 0;
int Sensor2 = 0;
//variável responsável por controlar a velocidade dos motores
int velocidade = 150;


void setup(){
//Setamos os pinos de controle dos motores como saída
//pinMode(M1, OUTPUT);
//pinMode(M2, OUTPUT);
pinMode(dir1, OUTPUT);
pinMode(dir2, OUTPUT);

ledcSetup(0, 5000, 8); // Canal 0, 5 kHz, 8 bits de resolução
ledcSetup(1, 5000, 8); // Canal 1, 5 kHz, 8 bits de resolução

ledcAttachPin(M1, 0); // Motor 1 no canal 0
ledcAttachPin(M2, 1); // Motor 2 no canal 1

//Serial.begin(115200);

//Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
digitalWrite(dir1, LOW);
digitalWrite(dir2, LOW);
//Setamos os pinos dos sensores como entrada
pinMode(pin_S1, INPUT);
pinMode(pin_S2, INPUT);
}

void loop(){
//Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
Sensor1 = digitalRead(pin_S1);
Sensor2 = digitalRead(pin_S2);
//Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
if((Sensor1 == 0) && (Sensor2 == 0)){ // Se detectar na extremidade das faixas duas cores brancas
ledcWrite(0, velocidade); // Motor 1
ledcWrite(1, velocidade); // Motor 2
}
if((Sensor1 == 1) && (Sensor2 == 0)){ // Se detectar um lado preto e o outro branco
ledcWrite(0, 0); // Motor 1
ledcWrite(1, velocidade); // Motor 2
}
if((Sensor1 == 0) && (Sensor2 == 1)){ // Se detectar um lado branco e o outro preto
ledcWrite(0, velocidade); // Motor 1
ledcWrite(1, 0); // Motor 2
}
}