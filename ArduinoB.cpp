//Arduino B
#include <LiquidCrystal.h>
#include <Keypad.h>

int buttonState = 0;
//Keypad setup
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte xPins[ROWS] = {A5, A4, A3, A2};
byte yPins[COLS] = {A1, A0, 6, 7};
Keypad keypad = Keypad(makeKeymap(keys), xPins, yPins, ROWS, COLS);
//LCD setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
uint8_t Pr[8] = {
	0b00000,
    0b00110,
    0b00110,
    0b00100,
    0b00110,
    0b00101,
    0b01010,
  	0b01001
};

uint8_t Pl[8] = {
	0b00000,
    0b01100,
    0b01100,
    0b00100,
    0b01100,
    0b10100,
    0b01010,
  	0b10010
};

uint8_t Ar[8] = {
	0b00000,
    0b01100,
    0b01101,
    0b00111,
    0b00100,
    0b00100,
    0b01010,
  	0b10010
};

uint8_t Al[8] = {
	0b00000,
    0b00110,
    0b10110,
    0b11100,
    0b00100,
    0b00100,
    0b01010,
  	0b01001
};

uint8_t Cl[8] = {
	0b00011,
    0b01101,
    0b01101,
    0b00110,
    0b00100,
    0b01100,
    0b10110,
  	0b10010
};

uint8_t Cr[8] = {
	0b11000,
    0b10110,
    0b10110,
    0b01100,
    0b00100,
    0b00110,
    0b01101,
  	0b01001
};

uint8_t Bullet[8] = {
	0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b01110,
    0b00000,
    0b00000,
  	0b00000
};

uint8_t ChangeY[8] = {
	0b00000,
    0b00000,
    0b01100,
    0b01100,
  	0b00100,
    0b01010,
    0b01010,
  	0b10110
};
// Characther Setup
int p1_x = 0, p1_y=0, p1_hp = 3, p1_pose = 0, p1_bullet_x, p1_bullet_y, p1_prev_bullet_x; // Player 1
int p2_x = 15, p2_y=1, p2_hp = 3, p2_pose = 1, p2_bullet_x, p2_bullet_y, p2_prev_bullet_x;  // Player 2

// Estados e posições das balas (independentes para cada jogador)
bool bulletActiveP1 = false;  // Verdadeiro se a bala do Jogador 1 estiver ativa
bool bulletActiveP2 = false;  // Verdadeiro se a bala do Jogador 2 estiver ativa
int bulletDirectionP1 = 0;    // Direção da bala do Jogador 1 (1 para direita, -1 para esquerda)
int bulletDirectionP2 = 0;    // Direção da bala do Jogador 2 (1 para direita, -1 para esquerda)

void setup()
{
  lcd.begin(16, 2);  
  Serial.begin(9600); // Use default Serial for UART
  pinMode(8, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.createChar(0, Pr); //Mover dir
  lcd.createChar(1, Pl); // Mover esq
  lcd.createChar(2, Ar); // Atirar dir
  lcd.createChar(3, Al); // Atirar esq
  lcd.createChar(4, Cr); // Atacar dir
  lcd.createChar(5, Cl); // Atacar esq
  lcd.createChar(6, Bullet);
  lcd.createChar(7, ChangeY);
  lcd.setCursor(0, 0);
  lcd.print("Apertem o Botao");
}

void loop()
{ 
  char p2_key = keypad.getKey();
  delay(5);
  buttonState = digitalRead(8);
  int response = Serial.parseInt();
   if (buttonState == HIGH) {
     digitalWrite(LED_BUILTIN, HIGH);
     if(response == 1){ Start();}
    }else {digitalWrite(LED_BUILTIN, LOW);}
  Serial.println(response);
  if (Serial.available()) {
  	switch (response) {
      case 2: MovePlayer(1,1); break;Serial.println("a");
      case 3: MovePlayer(1,-1); break;Serial.println("b");
      case 4: Shoot(1,1); break;
      case 5: Shoot(1,-1); break;
      case 6: Attack(1,1); break;
      case 7: Attack(1,-1); break;
      case 8: ChangY(1); break;
      default: Serial.println("No command"); break;
  	}
  }
  if (p2_key) {
    switch (p2_key) {
      case '2': ChangY(2); break;    
      case '1': Attack(2, -1);break;   
      case '3': Attack(2, 1); break; 
      case '6': MovePlayer(2, 1); break;         
      case '4': MovePlayer(2, -1); break;        
      case '7': Shoot(2, -1); break;        
      case '9': Shoot(2, 1); break;     
      default: break;
    }
  }
  delay(5);
  //Bullet Logic
  bool bulletMoved = false;
  if (bulletActiveP1) {
    p1_prev_bullet_x = p1_bullet_x;
    p1_bullet_x += bulletDirectionP1 * 2;
    if(p1_bullet_x > 15 || p1_bullet_x <0){bulletActiveP1 = false;} // Desativa a bala imediatamente após o salto
    bulletMoved = true;
  }
  if (bulletActiveP2) {
    p2_prev_bullet_x = p2_bullet_x;
    p2_bullet_x += bulletDirectionP2 * 2;
    if(p2_bullet_x > 15 || p2_bullet_x <0){bulletActiveP2 = false;} // Desativa a bala imediatamente após o salto
    bulletMoved = true;
  }
  if (bulletMoved) {Display(0,0);}
}

void Start(){
  lcd.clear();
  p1_x = 0; p1_y = 0; p1_pose=0;
  lcd.setCursor(p1_x, p1_y); 
  lcd.write(byte(p1_pose)); 
  p2_x = 15; p2_y = 1; p2_pose = 1;
  lcd.setCursor(p2_x, p2_y);
  lcd.write(byte(p2_pose));
}

void Display(int player, int action){
    if(player == 1){
    lcd.clear();
	lcd.setCursor(p1_x, p1_y);
    p1_pose = action;
  	lcd.write(byte(action)); 
    lcd.setCursor(p2_x, p2_y);
  	lcd.write(byte(p2_pose));
    };
  
    if(player == 2){
    lcd.clear();
	lcd.setCursor(p2_x, p2_y);
    p2_pose = action;
  	lcd.write(byte(action)); 
    lcd.setCursor(p1_x, p1_y);
  	lcd.write(byte(p1_pose));
    };
  
    if(player == 3){
    lcd.clear();
	lcd.setCursor(p1_x, p1_y);
    p1_pose = action;
  	lcd.write(byte(action)); 
    lcd.setCursor(p2_x, p2_y);
    p2_pose=action;
  	lcd.write(byte(action));
    };

  if (bulletActiveP1) {
    lcd.setCursor(p1_prev_bullet_x, p1_bullet_y);
    lcd.write(" ");
    lcd.setCursor(p1_bullet_x, p1_bullet_y);
    lcd.write(byte(6)); 
  } else {
    lcd.setCursor(p1_prev_bullet_x, p1_bullet_y);
    lcd.write(" ");
  }
  if (bulletActiveP2) {
    lcd.setCursor(p2_prev_bullet_x, p2_bullet_y);
    lcd.write(" ");
    lcd.setCursor(p2_bullet_x, p2_bullet_y);
    lcd.write(byte(6));
  }else {
    lcd.setCursor(p2_prev_bullet_x, p2_bullet_y);
    lcd.write(" ");
  }
}

void MovePlayer(int player, int direction) {
  
  if (player == 1) {
    p1_x += direction;
    if(direction == 1){Display(1,0);} else {Display(1,1);}
    if (p1_x < 0) {p1_x = 0;};
    if (p1_x > 15) {p1_x = 15;};
  } else {
    p2_x += direction;
    if(direction == 1){Display(2,0);} else {Display(2,1);}
    if (p2_x < 0) p2_x = 0;
    if (p2_x > 15) p2_x = 15;
  }
}
void Shoot (int player, int direction){
   if (player == 1) {
    bulletActiveP1 = true;
    bulletDirectionP1 = direction;
    p1_bullet_x = p1_x + direction;
    p1_bullet_y = p1_y;

    if (direction == 1) {
      Display(1, 2);
    } else {
      Display(1, 3);
    }
  } 
  else if (player == 2) {
    bulletActiveP2 = true;
    bulletDirectionP2 = direction;
    p2_bullet_x = p2_x + direction;
    p2_bullet_y = p2_y;

    if (direction == 1) {
      Display(2, 2);
    } else {
      Display(2, 3);
    }
  }
}
void Attack (int player, int direction){
  if (player == 1) {
    if(direction == 1){
      Display(1,4);
    }else{
      Display(1,5);
    }
  } else {
    if(direction == 1){
      Display(2,4);
    }else{
      Display(2,5);
    }
  }
 CheckAttackHit(player, direction);
}
void ChangY(int player){
  if (player == 1) {
    if(p1_y == 0){p1_y=1;Display(1,7);}
    else{p1_y=0;Display(1,7);}
  } else {
    if(p2_y == 0){p2_y=1;Display(2,7);}
    else{p2_y=0;Display(2,7);}
  }
}
void CheckAttackHit(int player, int direction) {
  int attacker_x, attacker_y;
  int target_x, target_y;

  if (player == 1) {
    attacker_x = p1_x;
    attacker_y = p1_y;
    target_x = p2_x;
    target_y = p2_y;
  } else {
    attacker_x = p2_x;
    attacker_y = p2_y;
    target_x = p1_x;
    target_y = p1_y;
  }
  bool hit_front = (attacker_y == target_y) && (attacker_x + direction == target_x);
  bool hit_below_1 = (attacker_x == target_x) && ((attacker_y == target_y + 1)||(attacker_y == target_y - 1));
  bool hit_below_2 = (attacker_x == target_x - direction) && ((attacker_y == target_y + 1)||(attacker_y == target_y - 1));
  if (hit_front || hit_below_1 || hit_below_2) {
    //hit
  }
}