#include "raylib.h"
#include "DateMath.c"
#include "stdlib.h"
#include <stdatomic.h>
#include <stdio.h>
#include <string.h>

struct Moon{
  char name[70];
  char phase[70];
  int cycleDur;
  int newDur;
  int phaseDay;
  Texture2D picture;
  float x,y;
};

typedef struct{
  float x,y;
  Texture2D picture;
  Rectangle bounds;
}button;

void MoonPhase(struct Moon M[], int Day){
  int i;
  for(i=0;i<7;i++){
    M[i].phaseDay = Day%M[i].cycleDur;
    int NewStart = (M[i].cycleDur - M[i].newDur) / 2;

    if(M[i].phaseDay == 0){
      strcpy(M[i].phase,"Full Moon");
    }
    else if(M[i].phaseDay <= NewStart){
      strcpy(M[i].phase,"Last Quarter");
    }
    else if(M[i].phaseDay > NewStart && M[i].phaseDay <= NewStart + M[i].newDur){
      strcpy(M[i].phase,"New Moon");
    }
    else if(M[i].phaseDay > NewStart + M[i].newDur){
      strcpy(M[i].phase,"First Quarter");
    } 
  }
}

void ReadMoonInfo(const char* fname, struct Moon moons[], int amnt){
  FILE *file = fopen(fname, "r");
  if(file == NULL){
    printf("Failed to open file %s", fname);
    return;
  }

  char line[100];
  int i;
  for(i=0;i<amnt;i++){
    fgets(line, 100, file);  
    sscanf(line, "%69s %i %i", moons[i].name, &moons[i].cycleDur, &moons[i].newDur);
  }
  fclose(file);
}

void SpitMoonInfo(struct Moon M, Color tint){
  DrawTexture(M.picture, M.x, M.y, tint);
  float margin = M.picture.height + 10;
  DrawText(M.name, M.x, M.y + margin, 20, LIGHTGRAY);
  DrawText(M.phase, M.x, M.y + margin + 50, 20, LIGHTGRAY);
  char FunnyNumbers[50] ="\0";
  snprintf(FunnyNumbers, 50, "D: %i  NS: %i  NE: %i", M.phaseDay, (M.cycleDur - M.newDur) / 2, (M.cycleDur + M.newDur) / 2);
  DrawText(FunnyNumbers, M.x, M.y + margin + 100, 20, LIGHTGRAY);
}

int main(void){
  struct Moon Moons[7] = {0}; 
  ReadMoonInfo("MoonInfo.txt", Moons, 7); //loads info about cycle duration, new duration, and moon name


  int Year = 873, Month = 10, Day = 2, Days = 1649104, DaysAdded, DaysAddedTotal = 0; // Days to years ~= 4516 (how many days since all moons were full to date 0.0.0)
  FILE *DataS = fopen("DateSave.txt", "r");
  
  if(DataS == NULL){
    printf("error opening DateSave.txt\n");
    fclose(DataS);
  }
  else{
    fscanf(DataS, "%i", &Year);
    fscanf(DataS, "%i", &Month);
    fscanf(DataS, "%i", &Day);
    fclose(DataS);
  }

  char Data[30] = "\0";
  char inputD[9] = "\0";
  int letterCount = 0;

  DaysAdded = DateToDays(Year, Month, Day);
  MoonPhase(Moons, Days + DaysAdded);
  DaysAdded = 0;
  snprintf(Data, 30, "%i / %i / %i", Day, Month, Year);
  
  Moons[0].x = 280; Moons[0].y = 60; //declare drawing positions
  Moons[1].x = 520; Moons[1].y = 352;
  Moons[2].x = 650; Moons[2].y = 82;
  Moons[3].x = 980; Moons[3].y = 92;
  Moons[4].x = 900; Moons[4].y = 366;
  Moons[5].x = 70; Moons[5].y = 320;
  Moons[6].x = 1180; Moons[6].y = 378;
    
  const int ScreenWidth = 1440;
  const int ScreenHeight = 900;
  
  InitWindow(ScreenWidth , ScreenHeight, "Moon Stalker");
  SetTargetFPS(144);

  Moons[0].picture = LoadTexture("sprites/Alrune.png"); //load moon sprites
  Moons[1].picture = LoadTexture("sprites/Ytrys.png");
  Moons[2].picture = LoadTexture("sprites/Taurea.png");
  Moons[3].picture = LoadTexture("sprites/Lsha'un.png");
  Moons[4].picture = LoadTexture("sprites/Estaeda.png");
  Moons[5].picture = LoadTexture("sprites/Dallhunt.png");
  Moons[6].picture = LoadTexture("sprites/Chimeris.png");

  Texture2D StBackground = LoadTexture("sprites/st1.png");

  button Prev, Next, Plus, Minus, Input, Mode;

  Prev.picture = LoadTexture("sprites/Prev.png");
  Next.picture = LoadTexture("sprites/Next.png");
  Plus.picture = LoadTexture("sprites/Plus.png");
  Minus.picture = LoadTexture("sprites/Minus.png");
  Input.picture = LoadTexture("sprites/Input.png");
  Mode.picture = Input.picture;
  
  Input.x = ScreenWidth/2.0f - 100;
  Prev.x = ScreenWidth/2.0f - 300;
  Next.x = ScreenWidth/2.0f + 236;
  Plus.x = ScreenWidth/2.0f + 116;
  Minus.x = ScreenWidth/2.0f - 180;
  Mode.x = 1100;
  Prev.y = Next.y = Plus.y = Minus.y = Input.y = Mode.y= 784;
  Texture2D PrevPr = LoadTexture("sprites/PrevP.png");
  Texture2D NextPr = LoadTexture("sprites/NextP.png");
  Texture2D PlusPr = LoadTexture("sprites/PlusP.png");   
  Texture2D MinusPr = LoadTexture("sprites/MinusP.png");   

  Prev.bounds = (Rectangle){Prev.x, Prev.y, Prev.picture.width, Prev.picture.height};
  Next.bounds = (Rectangle){Next.x, Next.y, Next.picture.width, Prev.picture.height};
  Input.bounds = (Rectangle){Input.x, Input.y, Input.picture.width, Input.picture.height};
  Plus.bounds = (Rectangle){Plus.x, Plus.y, Plus.picture.width, Plus.picture.height};
  Minus.bounds = (Rectangle){Minus.x, Minus.y, Minus.picture.width, Minus.picture.height};
  Mode.bounds = (Rectangle){Mode.x, Mode.y, Mode.picture.width, Mode.picture.height};

  Vector2 MousePoint = {0.0f, 0.0f};
  bool IsPressed = false;
  int md = 0; // 0 - days, 1 - months 2 - years;
  while(!WindowShouldClose()){
    MousePoint = GetMousePosition();
    bool DateChanged = false;
    BeginDrawing();
    DrawTexture(StBackground, 0, 0, WHITE);

    SpitMoonInfo(Moons[0], WHITE);
    SpitMoonInfo(Moons[1], WHITE);     
    SpitMoonInfo(Moons[2], WHITE);     
    SpitMoonInfo(Moons[3], GOLD);     
    SpitMoonInfo(Moons[4], LIGHTGRAY);     
    SpitMoonInfo(Moons[5], MAROON);     
    SpitMoonInfo(Moons[6], LIGHTGRAY);     

    DrawTexture(Prev.picture, Prev.x, Prev.y, WHITE);   
    DrawTexture(Next.picture, Next.x, Next.y, WHITE);   

    if(CheckCollisionPointRec(MousePoint, Prev.bounds)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
          DateChanged = true;
          switch (md) {
            case 0:
              DateCycler(&Year, &Month, &Day, -1);
              break;
            case 1:
              Month -= 1;
              DateCycler(&Year, &Month, &Day, 0);
              break;
            case 2:
              Year-=1;       
              DateCycler(&Year, &Month, &Day, 0);
              break;
          } 
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
          DrawTexture(PrevPr, Prev.x, Prev.y, WHITE);
        }
    }
    else if(CheckCollisionPointRec(MousePoint, Next.bounds)){
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        DateChanged = true;
        switch (md) {
          case 0:
            DateCycler(&Year, &Month, &Day, 1);
            break;
          case 1:
            Month += 1;
            DateCycler(&Year, &Month, &Day, 0);
            break;
          case 2:
            Year += 1;       
            DateCycler(&Year, &Month, &Day, 0);
            break;
        }
      }
      if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        DrawTexture(NextPr, Next.x, Next.y, WHITE);
      }
    }
    
    DrawTexture(Input.picture, Input.x, Input.y, WHITE);
    
    if(CheckCollisionPointRec(MousePoint, Input.bounds)){
      int key = GetCharPressed();

      while (key > 0){
        if ((key >= 32) && (key <= 125) && (letterCount < 8)){
          inputD[letterCount] = (char)key;
          inputD[letterCount+1] = '\0';
          letterCount++;
        }

        key = GetCharPressed();
      }

      if (IsKeyPressed(KEY_BACKSPACE)){
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        inputD[letterCount] = '\0';
      }
    }
    
    DrawText(inputD, (int)Input.bounds.x + 8, (int)Input.bounds.y + 10, 40, BLACK);
    
    DrawTexture(Minus.picture, Minus.x, Minus.y, WHITE);
    if(CheckCollisionPointRec(MousePoint, Minus.bounds)){
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        sscanf(inputD, "%i", &DaysAdded);
        DaysAdded = -DaysAdded;
        switch (md) {
          case 0:
            DateCycler(&Year, &Month, &Day, DaysAdded);
            break;
          case 1:
            Month += DaysAdded;
            DateCycler(&Year, &Month, &Day, 0);
            break;
          case 2:
            Year += DaysAdded;
            DateCycler(&Year, &Month, &Day, 0);
            break;
         }
        DateChanged = true;
        snprintf(inputD, 9, "");
        inputD[0] = '\0';
        letterCount = 0;
        DaysAdded = 0;
      }
      if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        DrawTexture(MinusPr, Minus.x, Minus.y, WHITE);
      }
    }

    DrawTexture(Plus.picture, Plus.x, Plus.y, WHITE);
    if(CheckCollisionPointRec(MousePoint, Plus.bounds)){
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        sscanf(inputD, "%i", &DaysAdded);
        switch (md) {
          case 0:
            DateCycler(&Year, &Month, &Day, DaysAdded);
            break;
          case 1:
            Month += DaysAdded;
            DateCycler(&Year, &Month, &Day, 0);
            break;
          case 2:
            Year += DaysAdded;
            DateCycler(&Year, &Month, &Day, 0);
            break;
         } 
        DateChanged = true;
        snprintf(inputD, 9, "");
        inputD[0] = '\0';
        letterCount = 0;
        DaysAdded = 0;
      }
      if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        DrawTexture(PlusPr, Plus.x, Plus.y, WHITE);
      }
    }
    
    DrawTexture(Mode.picture, Mode.x, Mode.y, WHITE);
    switch(md){
      case 0:
        DrawText("Days", Mode.x+8, Mode.y+10, 40, BLACK);
        break;
      case 1: 
        DrawText("Months", Mode.x+8, Mode.y+10, 40, BLACK); 
        break;
      case 2: 
        DrawText("Years", Mode.x+8, Mode.y+10, 40, BLACK); 
        break;
    }
    if(CheckCollisionPointRec(MousePoint, Mode.bounds)){
      if(IsKeyPressed(KEY_RIGHT)){
        md += 1;
        md = md%3;
      }
      if(IsKeyPressed(KEY_LEFT)){
        md -= 1;
        if(md == -1) md = 2;
      }
    }
    if(DateChanged){
      snprintf(Data, 30, "%i / %i / %i", Day, Month, Year);
      DaysAddedTotal = DateToDays(Year, Month, Day);
      MoonPhase(Moons, Days + DaysAddedTotal);
      
    }
    DrawText(Data, ScreenWidth/2.0 - 163, 710, 50, GOLD);
    EndDrawing();
  }

  UnloadTexture(Prev.picture);
  UnloadTexture(Next.picture);
  UnloadTexture(PrevPr);
  UnloadTexture(NextPr);
  UnloadTexture(Input.picture);

  UnloadTexture(Plus.picture);
  UnloadTexture(PlusPr);
  UnloadTexture(Minus.picture);
  UnloadTexture(MinusPr);

  UnloadTexture(Moons[0].picture);
  UnloadTexture(Moons[1].picture);
  UnloadTexture(Moons[2].picture);
  UnloadTexture(Moons[3].picture);
  UnloadTexture(Moons[4].picture);
  UnloadTexture(Moons[5].picture);
  UnloadTexture(Moons[6].picture);
  CloseWindow();

  FILE *Save = fopen("DateSave.txt", "w");
  fprintf(Save, "%i\n", Year);
  fprintf(Save, "%i\n", Month);
  fprintf(Save, "%i\n", Day);
  fclose(Save);
}
