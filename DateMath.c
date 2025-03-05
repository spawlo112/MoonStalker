int DateToDays(int Year, int Month, int Day){
  int Days = 0;
  Days = (Year - 1) * 365 + (Year-1)/4;
  
  Days += (Month-1)*30;
  if(Month == 2) Days += 1;
  else if(Month == 3) Days -= 1;
  else if(Month < 9) Days += Month / 2 - 2;
  else Days += (Month + 1) / 2 - 2;
  
  if(Year%4 == 0 && Month > 2) Days+=1;
  
  Days += Day;

  return Days;
}
// 31 28/29 31 30 31 30 31 31 30 31 30 31

void DateCycler(int* Year, int* Month, int* Day, int DaysAdded){
  int DaysCap = 0;
  *Day += DaysAdded;
  if(DaysAdded>=0){
    while(*Month > 12 || *Day > DaysCap){
      switch (*Month) {
        case 1: DaysCap = 31; break;
        case 2: 
          if(*Year%4 == 0) DaysCap = 29;
          else DaysCap = 28;
          break;
        case 3: DaysCap = 31; break;
        case 4: DaysCap = 30; break;
        case 5: DaysCap = 31; break;
        case 6: DaysCap = 30; break;
        case 7: DaysCap = 31; break;
        case 8: DaysCap = 31; break;
        case 9: DaysCap = 30; break;
        case 10: DaysCap = 31; break;
        case 11: DaysCap = 30; break;
        case 12: DaysCap = 31; break;
      }
      if(*Day > DaysCap){
        *Day -= DaysCap;
        *Month += 1;
      }
      if(*Month > 12){
        *Month -= 12;
        *Year += 1;
      }
    }
  }
  else{
    while(*Month < 1 || *Day < 1){
      switch (*Month - 1) {
        case 0: DaysCap = 31;
        case 1: DaysCap = 31; break;
        case 2: 
          if(*Year%4 == 0) DaysCap = 29;
          else DaysCap = 28;
          break;
        case 3: DaysCap = 31; break;
        case 4: DaysCap = 30; break;
        case 5: DaysCap = 31; break;
        case 6: DaysCap = 30; break;
        case 7: DaysCap = 31; break;
        case 8: DaysCap = 31; break;
        case 9: DaysCap = 30; break;
        case 10: DaysCap = 31; break;
        case 11: DaysCap = 30; break;
      }
      if(*Day < 1){
        *Day = *Day + DaysCap;
        *Month -= 1;
      }
      if(*Month < 1){
        *Month += 12;
        *Year -= 1;
      }
    }  
  }
}

