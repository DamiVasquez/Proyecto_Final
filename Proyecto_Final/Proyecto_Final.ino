/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM / EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Proyecto Final
   Dev: Damasco Oxcal Vasquez
   Fecha: 27 de mayo
*/
#include <Keypad.h>; // Con esta linea llamamos a la librería Keypad para que arduino reconozca el teclado
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
//Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

const byte filas_teclado = 4; //Este código se estable para definir que nuestro teclado tiene 4 filas 
const byte columnas_teclado = 3; //Este código se estable para definir que nuestro teclado tiene 4 columnas

char hexaKeys[filas_teclado][columnas_teclado] = //En el siguiente matriz se agregan en orden las teclas que posee nuestro teclado
{
 {'1','2','3',},
 {'4','5','6',},
 {'7','8','9',},
 {'*','0','#',}
};
  
byte pines_filas[filas_teclado] = {13, 12, 11, 10}; // Estos son los pines de conexión de Arduino de las columnas
byte pines_columnas[columnas_teclado] = {9, 8, 7,}; //Estos son los pines de conexión de Arduino de las filas
  
Keypad oxcalv = Keypad(makeKeymap(hexaKeys), pines_filas, pines_columnas, filas_teclado, columnas_teclado); //En este punto el teclado se inicia y realiza el mapeo de sus teclas con respecto a la matriz colocada arriba

int aContador = 0;
int bContador = 99;
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int pin_Servo = 6;

bool conteoA = false;
bool conteoB = false;
bool fantastico = false;
bool display = false;
bool servo = false;

//Constructor
Servo Servo_Oxcal;  //mi servo

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Damasco.");
  lcd.setCursor(1,1);
  lcd.print("Proyecto Final");
  
  Serial.begin(9600);
  Serial.println("Presione la tecla '1' para iniciar el contador de 0 a 99.");
  Serial.println("Presione la tecla '2' para iniciar el contador de 99 a 0.");
  Serial.println("Presione la tecla '3' para la animacion del auto fantastico.");
  Serial.println("Presione la tecla '4' para la animacion de  0 a 9 en un display.");
  Serial.println("Presione la tecla '5' para el movimiento de 0 a 180 grados de un servomotor.");

  for(int x=14; x<=17; x++){
    pinMode(x, OUTPUT);
  }
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(pin_Servo, OUTPUT);
  Servo_Oxcal.attach(pin_Servo);
}

void loop(){
char tecla = oxcalv.getKey();
  
  if(tecla){
    if(tecla == '1' && !conteoA){
      conteoA = true;
      Serial.println("contador iniciado");
    }
  }
  if(conteoA){
    Serial.println(aContador);
    aContador++;
    if(aContador > 99){
      aContador = 0;
    }
    delay(500);
  }
  if(tecla){
    if(tecla == '2' && !conteoB){
      conteoB = true;
      Serial.println("contador iniciado");
    }
  }
  if(conteoB){
    Serial.println(bContador);
    bContador--;
    if(bContador < 0){
      bContador = 99;
    }
    delay(500);
  }
  if(tecla){
    if(tecla == '3' && !fantastico){
    fantastico = true;
    }
  }
  if(fantastico){
    for(int z=14; z<=17; z++){
      digitalWrite(z, HIGH);
      delay(200);
      digitalWrite(z, LOW);
    }
    for(int l=17; l>=14; l--){
      digitalWrite(l, OUTPUT);
      delay(200);
      digitalWrite(l, LOW);
    }
  }
  if(tecla){
    if(tecla == '4' && !display){
      display = true;
    }
  }
  if(display){
  // Mostramos los números del 0 al 9
  for (int i = 0; i <= 9; i++) {
    mostrarNumero(i);
    delay(1000); // Esperamos 1 segundo entre cada número
  }
  }
  if(tecla){
    if(tecla == '5' && !servo){
      servo = true;
    }  
  }
  if(servo){
    Servo_Oxcal.write(0);
    delay(2000);
    Servo_Oxcal.write(180);
    delay(10000);
  }
}
// Función para mostrar un número en el display de 7 segmentos
void mostrarNumero(int numero) {
  // Definimos el BCD correspondiente a cada número
  const int bcd[10] = {
    B0000, // 0
    B0001, // 1
    B0010, // 2
    B0011, // 3
    B0100, // 4
    B0101, // 5
    B0110, // 6
    B0111, // 7
    B1000, // 8
    B1001  // 9
  };
  
  // Configuramos los pines de datos según el BCD del número
  digitalWrite(a, bitRead(bcd[numero], 0)); // Configuramos a según el bit menos significativo del BCD
  digitalWrite(b, bitRead(bcd[numero], 1)); // Configuramos b según el segundo bit del BCD
  digitalWrite(c, bitRead(bcd[numero], 2)); // Configuramos c según el tercer bit del BCD
  digitalWrite(d, bitRead(bcd[numero], 3)); // Configuramos d según el bit más significativo del BCD
}
