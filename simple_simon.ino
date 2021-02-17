int LEDPins[4] = {2, 3, 4, 5};
int SwitchPins[4] = {7, 8, 9, 10};
int count;
int LEDSequence[32];



void setup()
{
  for (int i=0; i < 4; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
    pinMode(SwitchPins[i], INPUT);
  }
  Serial.begin(9600);
  count = 0;
  randomSeed(analogRead(0));
}



boolean isPressed(int switchNum)
{
  boolean pressed = false;
  if(digitalRead(SwitchPins[switchNum]) == HIGH)
  {
    delay(10);
    while(digitalRead(SwitchPins[switchNum]) == HIGH){}
    delay(10);
    pressed = true;
  }
  return pressed;
}



int buttonPressed()
{
  int buttonNum = -1;
  for (int i=0; i < 4; i++)
  {
    if (isPressed(i) == true)
    {
      buttonNum = i;
    }
  }
  return buttonNum;
}

void passLevel()
{
  delay(500);
  digitalWrite(LEDPins[0], HIGH);
  digitalWrite(LEDPins[1], HIGH);
  digitalWrite(LEDPins[2], HIGH);
  digitalWrite(LEDPins[3], HIGH);
  delay(500);
  digitalWrite(LEDPins[0], LOW);
  digitalWrite(LEDPins[1], LOW);
  digitalWrite(LEDPins[2], LOW);
  digitalWrite(LEDPins[3], LOW);
  delay(500);
}

void winGame()
{
  for(int i=0; i<=3; i++)
  {
    digitalWrite(LEDPins[0], HIGH);
    digitalWrite(LEDPins[1], HIGH);
    digitalWrite(LEDPins[2], HIGH);
    digitalWrite(LEDPins[3], HIGH);
    delay(200);
    digitalWrite(LEDPins[0], LOW);
    digitalWrite(LEDPins[1], LOW);
    digitalWrite(LEDPins[2], LOW);
    digitalWrite(LEDPins[3], LOW);
  }
}

void loseGame()
{
  for(int i=0; i<4; i++)
  {
    digitalWrite(LEDPins[i], HIGH);
    delay(150);
    digitalWrite(LEDPins[i], LOW);
    delay(150);
    LEDPins[i] + 1;
  }
}


void loop()
{
  boolean Lose=  false;
  //genereates a random sequence
  for(int i=0; i < 32; i++)
  {
    LEDSequence[i] = random(4);
  }
  
  for(int Level = 0; Level < 32; Level++)
  {
    for(int sequence=0; sequence<=Level; sequence++)
    {
      digitalWrite(LEDPins[LEDSequence[sequence]], HIGH);
      delay(500);
      digitalWrite(LEDPins[LEDSequence[sequence]], LOW);
      delay(500);
    }
    count = 0;
    Lose = false;
    while(count <= Level)
    {
     int button = -1;
     button = buttonPressed();
     if(button > -1)
     {     
      if(button == LEDSequence[count])
      {
        count++;
        digitalWrite(LEDPins[button], HIGH);
        delay(500);
        digitalWrite(LEDPins[button], LOW);
      }
      else
      {
        Lose = true;
        break;
      }
    }
    }
    
    if(Lose == true)
    {
      loseGame();
      break;
    }
    else if(Lose == false && Level < 32)
    {
      passLevel();
    }
    else
    {
      winGame();
    }
  }
   
}

