// definování proměných
int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0; 
int mapX = 0;
int mapY = 0;

int cursorx = 0;
int cursory = 0;
int i;
int j;
int positionChange;
char player = 'x';

//definovvání konstant 
#define Board 10
#define sensitivity 150

//definování pole na piškvorky
char arr[Board][Board];//={{'x','x','x'},{'o','o','o'},{' ',' ',' '}};

// fce se zativuje pouze jednou, při kompilování 
void setup() {
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  initBoard();
  printBoard();
}

//fce tiskne plochu a zároveň tahy hráčů
void printBoard(){
    for(int q=0; q< Board; q++){ //formátování plochy
      Serial.write("+---");
    }
    Serial.write("+");
    Serial.write('\n');
  for ( i = 0; i < Board; i++ ) { //pohyb po poli arr ve vertikání ose
    for ( j = 0; j < Board; j++ ) { //pohyb po poli arr v horizontální ose
      if ((cursorx == j) && (cursory == i)){ //pokud je kruzor na poloze i j tisknu "|*" jinak "| "
        
        Serial.print("|*");
        //Serial.print("x"); 
      }
      else{
        Serial.print("| ");
      }

      Serial.write(arr[i][j]);
      if ((cursorx == j) && (cursory == i)){ //pokud je kruzor na poloze i j tisknu "*" jinak " "
        Serial.print("*");
      }
      else{
        Serial.print(' ');
      }
    }

    //formátování plochy    
    Serial.print("|");
    Serial.write('\n');
    for(int q=0; q< Board; q++)
    {
      Serial.write("+---");
    }
    Serial.write("+");
    Serial.write('\n');
  }
  Serial.write('\n');
}

// inicializace plochy a nastavení mezery v poly
//v poli arr se pohybuju nejdřív po řádku a pak přeskočím na další řádek
void initBoard(){
  for ( i = 0; i < Board; i++ ) { //pohyb po poli arr ve vertikání ose
    for ( j = 0; j < Board; j++ ) { //pohyb po poli arr v horizontální ose
      arr[i][j]=' ';
    }
  }
}


void loop() {

  //potřebný kod na fungování joystiku, čtení a pokud je potřeba mapování pozice
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  /*mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);*/
  /*Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.println(" | Button: ");*/
  //Serial.println(SW_state);


  positionChange = 0; 
  if(SW_state == 0){arr[cursory][cursorx]=player; positionChange = 1;if (player=='x')player ='o';else player ='x';} //po stisknutí tlačítka v poli arr nastaví positionChange na 1 a nastaví "x" nebo "o" místo mezery

  //kalibrace joystiku, pohyb po poli arr a nastavení positionChange na 1
  if((xPosition <(512-sensitivity)) && (cursorx > 0)){cursorx --; positionChange = 1;}
  if((xPosition >(512+sensitivity)) && (cursorx < Board-1)){cursorx ++; positionChange= 1;}
  if((yPosition <(512-sensitivity)) && (cursory > 0)){cursory --; positionChange=1;}
  if((yPosition >(512+sensitivity)) && (cursory < Board-1)){cursory ++; positionChange=1;}

  //tisknu pole pokud positionChange = 1
  if(positionChange){printBoard();}
  //Serial.print(cursorx);
  //Serial.print(' ');
  //Serial.println(cursory);
  delay(250);
}
