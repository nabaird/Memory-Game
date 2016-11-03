
const int light1 = 2;
const int light2 = 7;
const int light3 = 9;
const int light4 = 8;

const int button1 = 3;
const int button2 = 4;
const int button3 = 12;
const int button4 = 13; 

int buttons[]={button1, button2, button3, button4}; //array holding the buttons
int buttonsLength = 4; 

bool isOn = false; //is a button being pressed?
int onButton; //the button being pressed
bool buttonReset = true; //can a button be activated? 

int possibleAnswers[] = {light1, light2, light3, light4}; 

int theGuess;//the current answer being guessed by the player
bool guessing = false; 
int answers[15]; 
int answersLength=1; 
int currentAnswer=0;

int difficulty = 1; //how challenging the game currently is
int score=0; 

bool hasFailed = false; 


void setup() 
{
  Serial.begin(9600); 
  
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);

  digitalWrite(light1,LOW);
  digitalWrite(light2,LOW);
  digitalWrite(light3,LOW);
  digitalWrite(light4,LOW);

  pinMode(button1 ,INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

}

void loop() 
{
 if(guessing == false)//the code for providing the player the information they need to remember
 {
   int theAnswer= possibleAnswers[random(0,4)]; 
   digitalWrite(theAnswer, HIGH);
   delay(500);
   digitalWrite(theAnswer,LOW);
   delay(500);
   answers[currentAnswer] = theAnswer; 
   currentAnswer++;
   if(currentAnswer == answersLength)
   {
    guessing = true;
    currentAnswer =0;

   }
 }

 if(guessing == true && hasFailed == false)//the code for when the player is entering the answers
 {
 
    bool tempIsOn = false;//a temporary 'isOn' check, so we don't turn off isOn needlesly through every pass
    for(int i = 0; i<buttonsLength; i++)//scan through the buttons and see which one is being pressed
    {
      if(digitalRead(buttons[i])==true)
      {
        tempIsOn = true; 
        onButton = buttons[i]; 
      }
    }
    isOn = tempIsOn; 

    if(isOn == false)
    {
      digitalWrite(theGuess,LOW);
      buttonReset = true; 
    }
    else if(buttonReset == true)
    {
      if(onButton == button1)
      {
        theGuess = 2;
      }
      else if(onButton == button2)
      {
        theGuess = 7;
      }
      else if(onButton == button3)
      {
        theGuess =9;
      }
      else
      {
        theGuess=8;
      }
      if(theGuess == answers[currentAnswer])
      {
        digitalWrite(theGuess, HIGH);//demonstrates to the player which button they are pressing
        score++;
        if(currentAnswer<answersLength-1)
        {
          currentAnswer++; 
        }
        else
        {
          currentAnswer = 0;
          guessing=false; 
          difficulty++;
          answersLength = difficulty; 
          digitalWrite(theGuess, LOW);
        }
      }
      else
      {
        hasFailed = true; 
        Serial.println("SCORE"); 
        Serial.println(score); 
        digitalWrite(light1, HIGH);
        digitalWrite(light2, HIGH);
        digitalWrite(light3, HIGH);
        digitalWrite(light4, HIGH);
      }

      buttonReset = false;  
      delay(200);
    }
 }

}
