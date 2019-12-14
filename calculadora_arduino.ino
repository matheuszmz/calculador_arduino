static const char display7[] = {0xD7, 0x11, 0xCD, 0x5D, 0x1B}; //Array com numeros do display

#define SetBit(RES, BIT)(RES |= (1 << BIT)) // Por BIT em nível alto
#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Por BIT em nível baixo
#define TstBit(RES, BIT)(RES &  (1 << BIT)) // testar BIT, retorna 0 ou 1
#define CplBit(RES, BIT)(RES ^= (1 << BIT)) // Inverter estado do BIT

int valor1, valor2, res;
int MAX = 4;
int cont = 0;
int estado = 0;
// Estado do sistema: 0, 1, 2
// 0: entrada do primeiro valor
// 1: entrada do segundo valor
// 2: cálculo efetuado e resultado

void exibeDisplay(int hex)
{
  PORTD = hex;
  delay(200);
}

void exibeResposta(int valor)
{
  switch (valor) {
    case 8:
      ClrBit(PORTB, PB2);
      ClrBit(PORTB, PB3);
      ClrBit(PORTB, PB4);
      break;
    case 7:
      SetBit(PORTB, PB2);
      SetBit(PORTB, PB3);
      SetBit(PORTB, PB4);
      break;
    case 6:
      ClrBit(PORTB, PB2);
      SetBit(PORTB, PB3);
      SetBit(PORTB, PB4);
      break;
    case 5:
      SetBit(PORTB, PB2);
      ClrBit(PORTB, PB3);
      SetBit(PORTB, PB4);
      break;
    case 4:
      ClrBit(PORTB, PB2);
      ClrBit(PORTB, PB3);
      SetBit(PORTB, PB4);
      break;
    case 3:
      SetBit(PORTB, PB2);
      SetBit(PORTB, PB3);
      ClrBit(PORTB, PB4);
      break;
    case 2:
      ClrBit(PORTB, PB2);
      SetBit(PORTB, PB3);
      ClrBit(PORTB, PB4);
      break;
    case 1:
      SetBit(PORTB, PB2);
      ClrBit(PORTB, PB3);
      ClrBit(PORTB, PB4);
      break;
    case 0:
      ClrBit(PORTB, PB2);
      ClrBit(PORTB, PB3);
      ClrBit(PORTB, PB4);
      break;
  }
  delay(2000);
}

void setup()
{ 
  DDRD = 0xFF;
  
  ClrBit(DDRB,   PB0);
  ClrBit(DDRB,   PB1);
  SetBit(DDRB,   PB2);
  SetBit(DDRB,   PB3);
  SetBit(DDRB,   PB4);
  
  SetBit(PORTB,   PB0);
  SetBit(PORTB,   PB1);
  ClrBit(PORTB,   PB2);
  ClrBit(PORTB,   PB3);
  ClrBit(PORTB,   PB4);
  
  exibeDisplay(display7[cont]);
}

void loop()
{
  //Acrescentador dos numeros (botão 1)
  if (TstBit(PINB, PB0)) {
    delay(50);
    cont++;
    exibeDisplay(display7[cont]);
    if (cont > MAX) cont = 0;
  }
  
  //Captura valores e calcula (botão 2)
  if (TstBit(PINB, PB1) && estado == 0) {
    valor1 = cont;
    estado = 1;
    cont = 0;
    
    exibeDisplay(display7[cont]);
  }
      
  if (TstBit(PINB, PB1) && estado == 1) {
    valor2 = cont;
    estado = 2;
    cont = 0;
    
    exibeDisplay(display7[cont]);
    
    res = valor1 + valor2;
    exibeResposta(res);
  }
    
  if (estado == 2) {
    estado = 0;
    cont = 0;
    
    ClrBit(PORTB,   PB2);
    ClrBit(PORTB,   PB3);
    ClrBit(PORTB,   PB4);
    exibeDisplay(display7[cont]);
  }  
}
