#include <iostream>
#include <graphics.h>
#include <thread>
using namespace std;

void drawBackground();
void FillButtom(int x, int y);
void StopButtom(int x, int y);
bool isInsideCircle(int x, int y, int centerX, int centerY, int radius);
void fillTank();
void DrainButtom(int x, int y);
void DrainTank();
void showWaterLevel();
//vaciado, subir potencia, bajar potencia, litraje.

//variables globales
bool fillingInProgress = false;
bool stopFilling = true;
int tankHeight = 605; 
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
        DrainButtom(x,y);
    }

    return 0;
}

void drawBackground()
{
    readimagefile("background.jpg", 0, 0, getmaxx(),getmaxy());
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

void DrainButtom(int x, int y) 
{
    int fillButtonCenterX = 1175; int fillButtonCenterY = 324; int fillButtonRadius = 59;
    // Verificar si el clic del mouse está dentro del botón circular
    if (isInsideCircle(x, y, fillButtonCenterX, fillButtonCenterY, fillButtonRadius)) 
        {
            if (!fillingInProgress) 
            { 
                fillingInProgress = true; 
                thread DrainThread(DrainTank); 
                DrainThread.detach();
                stopFilling = false;
            }
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
        showWaterLevel();
    }
    fillingInProgress = false; 
}

void DrainTank() 
{
    int tankWidth = 230; 
    int tankLeft =186;
    int DrainSpeed = 4;
    
    while (!stopFilling && waterLevel < tankTop + tankHeight) 
    {
        // Restaurar el área del agua a la imagen de fondo original
        readimagefile("background.jpg", 0, 0, getmaxx(), getmaxy());
        // Restaurar el área del agua a la imagen original
        bar(tankLeft, waterLevel, tankLeft + tankWidth, tankTop + tankHeight);
        waterLevel += DrainSpeed; // Aumentar el nivel de agua
        showWaterLevel();
        
    }

    if (waterLevel >= tankTop + tankHeight)
    {
        showWaterLevel();
        drawBackground();
        
    }
    fillingInProgress = false;
}

void showWaterLevel() {
    int tankCapacity = 300; // Capacidad del tanque en litros
    double waterHeight = waterLevel - tankTop; // Altura del agua en el tanque
    double ratio = waterHeight / tankHeight; // Proporción del tanque ocupada por el agua
    double waterVolume = tankCapacity * ratio; // Volumen de agua en el tanque
    double Volume =  tankCapacity - waterVolume; // Volumen restante de agua en el tanque
    char text[10];
    if (Volume > 300) 
    {
        Volume=300;
    }
    sprintf(text, "%.0f",Volume); // Formatear el texto
    int x = 890; // Posición x del texto
    int y = 570; // Posición y del texto

    setcolor(WHITE); // Establecer el color del texto
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(x, y,text); // Dibujar el texto en la ventana gráfica
}