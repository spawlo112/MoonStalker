# MoonStalker
MoonStalker is an application designed to keep track of Date and Phases of seven fictional moons each having different orbiting cycle length. Inteded for Worldbuilding, RPG's, or writing.

## Features and Customisation
###  1. Date tracking:
Allows you to advance or rewind days, months, or years, either one by one or by entering a specific number. Upon closing program the date is saved in **DateSave.txt**.

### 2. Moon Phases:
Shows corresponding to date moonphase for each of seven moons, with additional info like what day of cycle is it, when does "New Phase" start and end (new phase is phase when moon is not visible on sky). Information regarding moons are saved in **MoonInfo.txt** in format `Moon_Name Cycle_Lenght New_Lenght`. This file can be easily modified.

## 3. GUI:
Program is provided with simple GUI written in RayLib, making provided information more user-friendly and easily readible, as well as allowing easy input.

## Provided Moons
### 1. Alrune:
- Orbital Period: 118 days
- Length of New Phase: 20 days
### 2. Ytrys:
- Orbital Period: 44 days
- Length of New Phase: 4 days
### 3. Estaeda:
- Orbital Period: 78 days
- Length of New Phase: 14 days
### 4. Lsha'un:
- Orbital Period: 21 days
- Length of New Phase: 3 days
### 5. Taurea:
- Orbital Period: 42 days
- Length of New Phase: 3 days
### 6. Dallhunt:
- Orbital Period: 98 days
- Length of New Phase: 20 days
### 7. Chimeris:
- Orbital Period: 59 days
- Length of New Phase: 5 days

## Installation and Dependencies
To download MoonStalker, you need to:
### 1. Clone git repository
Move to directory you want this application in then
```bash
git clone https://github.com/spawlo112/MoonStalker.git
```
### 2. Install Raylib
As GUI of this app is based on RayLib its essential to have it downloaded. 
example for Arch / Arch-based OS:
```bash
sudo pacman -S raylib
```
Debian / Ubuntu:
```base
sudo apt-get install libraylib-dev
```
Windows:
Download latest release of RayLib from their official site.

### 3. Compile MoonStalker
Once RayLib is downloaded and you cloned repository move to directory of installed repo and compile MoonStalker.c linking raylib and other libraries
gcc example:
```bash
gcc -o MoonStalker main.c -lraylib -lm -lpthread -ldl -lX11
```
### 4. Run the app
If everything done correctly running:
```bash
./MoonStalker
```
should open and run MoonStalker.
