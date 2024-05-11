#include <iostream>
#include <graphics.h>
#include <thread>
using namespace std;

void drawBackground();
void FillButtom(int &x, int &y);
void StopButtom(int &x, int &y);
bool isInsideCircle(int &x, int &y, int &centerX, int &centerY, int &radius);
void fillTank();
void DrainButtom(int &x, int &y);
void DrainTank();
void showWaterLevel();
void voltButtom(int &x, int &y);
void showVolt();
// subir potencia, bajar potencia, LUCES LED

//variables globales
bool fillingInProgress = false;
bool stopFilling = true;
int tankHeight = 605; 
int tankTop = 185;
int waterLevel = tankTop + tankHeight;
int DrainSpeed=4, fillSpeed=1;


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
        voltButtom(x,y);
    }

    return 0;
}

void drawBackground()
{
    readimagefile("background.jpg", 0, 0, getmaxx(),getmaxy());
}

bool isInsideCircle(int &x, int &y, int &centerX, int &centerY, int &radius) {
    int dx = x - centerX;
    int dy = y - centerY;
    return dx * dx + dy * dy <= radius * radius;
}

void FillButtom(int &x, int &y) 
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

void StopButtom(int &x, int &y) 
{
    int StopButtonCenterX = 964; int StopButtonCenterY = 320; int StopButtonRadius = 56;
        // Verificar si el clic del mouse está dentro del botón circular
        if (isInsideCircle(x, y, StopButtonCenterX, StopButtonCenterY, StopButtonRadius)) 
            {
                stopFilling = true;
            }
}

void DrainButtom(int &x, int &y) 
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
    int x = 890; 
    int y = 570; 
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(x, y,text); 
}

void voltButtom(int &x, int &y)
{
    //posiciones volt fill
    int up_voltFillx=718; int up_voltFilly=557; int up_voltFillradius = 35; 
    int down_voltFillx=800; int down_voltFilly=557; int down_voltFillradius = 36;

    //posiciones volt drain
    int up_voltDrainx=1135;int up_voltDrainy=557;int up_voltDrainradius = 35; 
    int down_voltDrainx=1217;int down_voltDrainy=557;int down_voltDrainradius = 36;

    if (isInsideCircle(x, y, up_voltFillx, up_voltFilly, up_voltFillradius) && fillSpeed <10)
    {
        fillSpeed++;
    }
    if (isInsideCircle(x, y, down_voltFillx, down_voltFilly, down_voltFillradius) && fillSpeed>1)
    {
        fillSpeed--;
    }
    if (isInsideCircle(x, y, up_voltDrainx, up_voltDrainy, up_voltDrainradius) && DrainSpeed<10)
    {
        DrainSpeed++;
    }
    if (isInsideCircle(x, y, down_voltDrainx, down_voltDrainy, down_voltDrainradius) && DrainSpeed>1)
    {
        DrainSpeed--;
    }
    
}