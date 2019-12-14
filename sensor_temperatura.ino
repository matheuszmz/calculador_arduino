#define SERVO 6

const int LM35 = A0; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida


void posicao_servo (float temperatura)
{
  int temp = (temperatura * 1.8 * 10) + 600; //usamos por base que 90 graus são 1500ms
  int movimentos = (20000 - temp) / temp; //calcula os movimentos
  
  digitalWrite(SERVO, HIGH);  //pulso do servo
  delayMicroseconds(temp);      //0.6ms
  digitalWrite(SERVO, LOW);   //completa periodo do servo
  for(int i=0; i<movimentos; i++) delayMicroseconds(temp);
}                     

void setup() {
  Serial.begin(9600);
  pinMode(SERVO, OUTPUT);
}

void loop() {
  
  temperatura = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  
  for (int i = 0; i < 100; i++) posicao_servo(100-temperatura);
}
