#include <iostream>
#include <graphics.h>
#include <thread>
using namespace std;

void drawBackground();
void FillButtom(int x, int y);
void StopButtom(int x, int y);
bool isInsideCircle(int x, int y, int centerX, int centerY, int radius);
void fillTank();

//variables globales
bool fillingInProgress = false;
bool stopFilling = true;
int tankHeight = 610; 
int tankTop = 185;
int waterLevel = tankTop + tankHeight;


int main() {
    // Tamaño de la pantalla
    int width = 1300;
    int height = 900;
    initwindow(width, height, "Control Panel");

    //IMAGEN DEL TANQUE DE AGUA
    drawBackground();

    int x, y;
    while (!kbhit()) 
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        FillButtom(x, y);
        StopButtom(x, y);
    }

    return 0;
}

void drawBackground()
{
    int width = getmaxx();
    int height = getmaxy();
    readimagefile("background.jpg", 0, 0, width,height);
}

bool isInsideCircle(int x, int y, int centerX, int centerY, int radius) {
    int dx = x - centerX;
    int dy = y - centerY;
    return dx * dx + dy * dy <= radius * radius;
}

void FillButtom(int x, int y) 
{
    int fillButtonCenterX = 760; int fillButtonCenterY = 326; int fillButtonRadius = 56;
    // Verificar si el clic del mouse está dentro del botón circular
    if (isInsideCircle(x, y, fillButtonCenterX, fillButtonCenterY, fillButtonRadius)) 
        {
            if (!fillingInProgress) 
            { 
                fillingInProgress = true; 
                thread fillThread(fillTank); 
                fillThread.detach();
                stopFilling = false;
            }
        }   
}

void StopButtom(int x, int y) 
{
    int StopButtonCenterX = 964; int StopButtonCenterY = 320; int StopButtonRadius = 56;
        // Verificar si el clic del mouse está dentro del botón circular
        if (isInsideCircle(x, y, StopButtonCenterX, StopButtonCenterY, StopButtonRadius)) 
            {
                stopFilling = true;
            }
}

void fillTank() {
    int tankWidth = 230; 
    int tankLeft =186;
    int fillSpeed = 4; // Velocidad de llenado

    setcolor(LIGHTCYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    
    // Llenar el tanque mientras stopFilling sea falso y el nivel de agua sea mayor que el nivel máximo
    while (!stopFilling && waterLevel > tankTop) { 
        bar(tankLeft, waterLevel - fillSpeed, tankLeft + tankWidth, waterLevel);
        waterLevel -= fillSpeed; // Disminuir el nivel de agua
        delay(50);
    }
    fillingInProgress = false; 
}