/**
  @description: Digital aroma display
  @date: 11/10/2022
  @author: Nikolas M. Menezes
  @version: 1.0.1 
*/

// Inclusão de Bibliotecas 
#include <SPFD5408_Adafruit_GFX.h>    
#include <SPFD5408_Adafruit_TFTLCD.h> 
#include <SPFD5408_TouchScreen.h>
#include <Servo.h> 

// Definição dos pinos do display
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Definição de cores
#define WHITE          0xFFFF
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000
#define CYAN           0x07FF

// Definindo a pressão para reconhecer o toque 
#define MINPRESSURE 10 // Pressão mínima
#define MAXPRESSURE 1000 // Pressão máxima  

// Portas de leitura das coordenadas do touch
#define YP A3 // Y+ 
#define XM A2 // X- 
#define YM 9 // Y-
#define XP 8 // X+

// Calibrando o display
#define TS_LEFT 129
#define TS_RT   924
#define TS_TOP  82
#define TS_BOT  896

// Objeto para manipulação dos toques na tela
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4); 


// Definição de variáveis
byte page;
byte atuador = 30;
byte pinServo = 32;
Servo servo1;

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
 p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
 p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  
  return p;
}

void setup() {
  
  page = 0; // Tela principal (Home Screen)
  pinMode (atuador, OUTPUT);
  servo1.attach (pinServo);
  
  uint16_t ID = tft.readID();
  Serial.begin(9600);
  
  tft.begin();
  delay (500);
  tft.reset();
  tft.begin(0x9341); 
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  // Função para a tela inicial
  IntroScreen();

  // Função para a tela principal 
  drawHomeScreen ();
}

void IntroScreen() {
  
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
  
  tft.setCursor (90,30);
  tft.setTextSize (3);
  tft.setTextColor(WHITE);
  tft.println("Projeto");

  tft.setCursor (30, 80);
  tft.setTextSize (3);
  tft.println ("Experimentador");

  tft.setCursor (70, 110);
  tft.println ("digital de" );

  tft.setCursor (108, 140);
  tft.println ("aromas" );
  
  tft.setTextSize (2);
  tft.setCursor (93, 205);  
  tft.setTextColor(CYAN);
  tft.println("TCC 3 MECA ");
  
  delay(5000);

  tft.fillScreen(BLACK);
}

void drawHomeScreen()
{

  tft.fillScreen(BLACK);
  
  //Borda da pagina inicial
  
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);  

  // Botões dos produtos
  
  tft.fillRoundRect(60, 80, 200, 40, 8, BLUE);
  tft.drawRoundRect(60, 80, 200, 40, 8, WHITE);
  
  tft.fillRoundRect(60, 130, 200, 40, 8, BLUE);  
  tft.drawRoundRect(60, 130, 200, 40, 8, WHITE);

  tft.fillRoundRect(60, 180, 200, 40, 8, BLUE);
  tft.drawRoundRect(60, 180, 200, 40, 8, WHITE); 

  tft.setCursor(30, 20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Selecione uma amostra!");
  
  tft.setCursor(90, 50);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("TCC 3 MECA");
  tft.setTextColor(WHITE);

  tft.setCursor(105, 95);
  tft.print("Produto A");

  tft.setCursor(105, 145);
  tft.print("Produto B");

  tft.setCursor(105, 195);
  tft.print("Produto C");

  delay(500);

}
 
void loop() {


  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

if (page == 0)
    {
      if (p.z > 10 && p.z < 1000) // Verifica se a pressão atual está dentro do valor que foi predeterminado
      {
        if (p.x > 403 && p.x < 525 && p.y > 271 && p.y < 725  && p.z > MINPRESSURE && p.z < MAXPRESSURE) // Primeiro botão
        {
            page=1; // Produto A
            
            tft.fillScreen (BLACK);
            tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
            
            tft.setTextSize (3);
            tft.setTextColor (WHITE);
            tft.setCursor (75, 40);
            tft.println ("Aguarde...");
            
            tft.setCursor (10, 100);
            tft.println ("sua amostra esta");

            tft.setCursor (35, 130);
            tft.println ("sendo gerada!");

            tft.setTextSize (2);
            tft.setCursor (93, 195);  
            tft.setTextColor(CYAN);
            tft.println("TCC 3 MECA ");

            digitalWrite (atuador, HIGH); 
            
            delay (4000);

            servo1.write(90);
            digitalWrite (atuador, LOW);
            
            delay (2500);

            servo1.write (0);

            
            tft.fillScreen (BLACK);
            tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
            tft.setTextColor (WHITE);
            tft.setTextSize (3);
            tft.setCursor (80, 95);
            tft.println ("Obrigado!");

            tft.setTextSize (2);
            tft.setCursor (93, 195);  
            tft.setTextColor(CYAN);
            tft.println("TCC 3 MECA ");
            
            delay (4000);
            drawHomeScreen();
            page=0;
        }
        else if (p.x > 563 && p.x < 683 && p.y > 275 && p.y < 750) // Segundo botão
        {
               
            page=2; // Produto B
            
            tft.fillScreen (BLACK);
            tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
            
            tft.setTextSize (3);
            tft.setTextColor (WHITE);
            tft.setCursor (75, 40);
            tft.println ("Aguarde...");
            
            tft.setCursor (10, 100);
            tft.println ("sua amostra esta");

            tft.setCursor (35, 130);
            tft.println ("sendo gerada!");

            tft.setTextSize (2);
            tft.setCursor (93, 195);  
            tft.setTextColor(CYAN);
            tft.println("TCC 3 MECA ");

            digitalWrite (atuador, HIGH); 
            
            delay (4000);

            servo1.write(90);
            digitalWrite (atuador, LOW);
            
            delay (2500);

            servo1.write (0);

            
            tft.fillScreen (BLACK);
            tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
            tft.setTextColor (WHITE);
            tft.setTextSize (3);
            tft.setCursor (80, 95);
            tft.println ("Obrigado!");

            tft.setTextSize (2);
            tft.setCursor (93, 195);  
            tft.setTextColor(CYAN);
            tft.println("TCC 3 MECA ");
            
            delay (4000);
            drawHomeScreen();
            page=0;
            
        }
        if (p.x > 736 && p.x < 855 && p.y > 255 && p.y < 725) // Terceiro botão
        {
          
            page=3; // Produto C
            
            tft.fillScreen (BLACK);
            tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
            
            tft.setTextSize (3);
            tft.setTextColor (WHITE);
            tft.setCursor (75, 40);
            tft.println ("Aguarde...");
            
            tft.setCursor (10, 100);
            tft.println ("sua amostra esta");

            tft.setCursor (35, 130);
            tft.println ("sendo gerada!");

            tft.setTextSize (2);
            tft.setCursor (93, 195);  
            tft.setTextColor(CYAN);
            tft.println("TCC 3 MECA ");

            digitalWrite (atuador, HIGH); 
            
            delay (4000);

            servo1.write(90);
            digitalWrite (atuador, LOW);
            
            delay (2500);

            servo1.write (0);

            
            tft.fillScreen (BLACK);
            tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);
            tft.setTextColor (WHITE);
            tft.setTextSize (3);
            tft.setCursor (80, 95);
            tft.println ("Obrigado!");

            tft.setTextSize (2);
            tft.setCursor (93, 195);  
            tft.setTextColor(CYAN);
            tft.println("TCC 3 MECA ");
            
            delay (4000);
            
            drawHomeScreen();
            page=0;
            
        }
      }
    }
}
