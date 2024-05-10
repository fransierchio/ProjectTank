#include <iostream>
#include <graphics.h>
#include <thread>
using namespace std;

void drawBackground();
void FillButtom(int x, int y);
void StopButtom(int x, int y);
bool isInsideCircle(int x, int y, int centerX, int centerY, int radius);
void fillTank();

bool fillingInProgress = false;
bool stopFilling = true;
int tankHeight = 610; 
int tankTop = 185;
int waterLevel = tankTop + tankHeight;


int main() {
    //PRIMERA INTERFAZ
    // Tamaño de la pantalla
    int width = 1300;
    int height = 900;
    initwindow(width, height, "Control Panel");

    //IMAGEN DEL TANQUE DE AGUA
    drawBackground();
    while (!kbhit()) 
    {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                FillButtom(x, y);
                StopButtom(x, y);
            }
    }

    // Esperar a que el usuario presione una tecla antes de cerrar la ventana
    getch();

    return 0;
}

void drawBackground()
{
    int width = getmaxx();
    int height = getmaxy();

    //Size of 
    int bgWidth = width;  
    int bgHeight = height;

    readimagefile("background.jpg", 0, 0, bgWidth,bgHeight);
}

void FillButtom(int x, int y) 
{
    
    int fillButtonCenterX = 760; 
    int fillButtonCenterY = 326; 
    int fillButtonRadius = 56;
    setcolor(RED);
    circle(fillButtonCenterX, fillButtonCenterY, fillButtonRadius);

        // Verificar si el clic del mouse está dentro del botón circular
        if (isInsideCircle(x, y, fillButtonCenterX, fillButtonCenterY, fillButtonRadius)) 
            {
                thread fillThread;
                if (!fillThread.joinable()) { // Verificar si el hilo ya se ha unido o está en ejecución
                fillThread = thread(fillTank); // Iniciar un nuevo hilo solo si no hay ninguno en ejecución
                fillThread.detach();
                stopFilling = false;
                }
                
            }
}

void StopButtom(int x, int y) 
{
    
    int StopButtonCenterX = 964; 
    int StopButtonCenterY = 320; 
    int StopButtonRadius = 56;
    setcolor(RED);
    circle(StopButtonCenterX, StopButtonCenterY, StopButtonRadius);

        // Verificar si el clic del mouse está dentro del botón circular
        if (isInsideCircle(x, y, StopButtonCenterX, StopButtonCenterY, StopButtonRadius)) 
            {
                cout << "Botón de detención presionado" << endl;
                stopFilling = true;
            }
}

bool isInsideCircle(int x, int y, int centerX, int centerY, int radius) {
    int dx = x - centerX;
    int dy = y - centerY;
    return dx * dx + dy * dy <= radius * radius;
}

void fillTank() {
    int tankWidth = 230; 
    int tankLeft =186;
    int fillSpeed = 4; // Velocidad de llenado
    int maxWaterLevel = tankTop; // Nivel máximo de agua en el tanque

    setcolor(LIGHTCYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    
    // Llenar el tanque mientras stopFilling sea falso y el nivel de agua sea mayor que el nivel máximo
    while (!stopFilling && waterLevel > maxWaterLevel) { 
        bar(tankLeft, waterLevel - fillSpeed, tankLeft + tankWidth, waterLevel);
        waterLevel -= fillSpeed; // Disminuir el nivel de agua
        delay(50);
    }
}