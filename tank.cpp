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
void showVoltFill();
void showVoltDrain();
void Led ();

//variables globales
bool fillingInProgress = false;
bool stopFilling = true;
int tankHeight = 365; 
int tankTop = 151;
int waterLevel = tankTop + tankHeight;
int DrainSpeed=4, fillSpeed=1;


int main() {
    // Tamaño de la pantalla
    int width = 1300;
    int height = 700;
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
    readimagefile("background2.jpg", 0, 0, getmaxx(),getmaxy());
}

bool isInsideCircle(int &x, int &y, int &centerX, int &centerY, int &radius) {
    int dx = x - centerX;
    int dy = y - centerY;
    return dx * dx + dy * dy <= radius * radius;
}

void FillButtom(int &x, int &y) 
{
    int fillButtonCenterX = 1040; int fillButtonCenterY = 326; int fillButtonRadius = 42;
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
    int StopButtonCenterX = 1035; int StopButtonCenterY = 570; int StopButtonRadius = 42;
    
        // Verificar si el clic del mouse está dentro del botón circular
        if (isInsideCircle(x, y, StopButtonCenterX, StopButtonCenterY, StopButtonRadius)) 
            {
                stopFilling = true;
            }
        
}

void DrainButtom(int &x, int &y) 
{
    int DrainButtonCenterX = 1188; int DrainButtonCenterY = 326; int DrainButtonRadius = 42;
    // Verificar si el clic del mouse está dentro del botón circular
    if (isInsideCircle(x, y, DrainButtonCenterX, DrainButtonCenterY, DrainButtonRadius)) 
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
    int tankWidth = 256; 
    int tankLeft =519;

    
    
    // Llenar el tanque mientras stopFilling sea falso y el nivel de agua sea mayor que el nivel máximo
    while (!stopFilling && waterLevel > tankTop) { 
        setcolor(LIGHTCYAN);
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        bar(tankLeft, waterLevel - fillSpeed, tankLeft + tankWidth, waterLevel);
        waterLevel -= fillSpeed; // Disminuir el nivel de agua
        delay(50);
        showWaterLevel();
    }
    fillingInProgress = false; 
}

void DrainTank() 
{
    int tankWidth = 256; 
    int tankLeft =519;
 
    while (!stopFilling && waterLevel < tankTop + tankHeight) 
    {
        // Restaurar el área del agua a la imagen de fondo original
        readimagefile("background2.jpg", 0, 0, getmaxx(), getmaxy());
        // Restaurar el área del agua a la imagen original
        setcolor(LIGHTCYAN);
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        bar(tankLeft, waterLevel, tankLeft + tankWidth, tankTop + tankHeight);
        waterLevel += DrainSpeed; // Aumentar el nivel de agua
        showWaterLevel();
        if (waterLevel > tankTop + tankHeight)
        {
            drawBackground();
            showWaterLevel();
        }
    }


    fillingInProgress = false;
}

void showWaterLevel() {
    Led();
    int tankCapacity = 300; // Capacidad del tanque en litros
    double waterHeight = waterLevel - tankTop; // Altura del agua en el tanque
    double ratio = waterHeight / tankHeight; // Proporción del tanque ocupada por el agua
    double waterVolume = tankCapacity * ratio; // Volumen de agua en el tanque
    double Volume =  tankCapacity - waterVolume; // Volumen restante de agua en el tanque
    char text[10];
    if (Volume > 300) 
    {
        Volume=300;
    } else if (Volume < 0)
    {
        Volume=0;
    }
    
    sprintf(text, "%.0f",Volume); // Formatear el texto
    int x = 1100; 
    int y = 570; 
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(x, y,text); 
    showVoltFill();
    showVoltDrain();
    Led ();
}

void voltButtom(int &x, int &y)
{
    //posiciones volt fill
    int up_voltFillx=1014; int up_voltFilly=453; int up_voltFillradius = 23; 
    int down_voltFillx=1064; int down_voltFilly=454; int down_voltFillradius = 23;

    //posiciones volt drain
    int up_voltDrainx=1158;int up_voltDrainy=454;int up_voltDrainradius = 23;
    int down_voltDrainx=1210;int down_voltDrainy=454;int down_voltDrainradius = 23; 

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

void showVoltFill()
{
    int x = 1000;
    int y = 397; 
    char text[10];
    sprintf(text, "%d", fillSpeed); 
    outtextxy(x, y, text); 
}

void showVoltDrain()
{
    int x = 1140; 
    int y =397; 
    char text[10];
    sprintf(text, "%d", DrainSpeed); 
    outtextxy(x, y, text);
}

void Led () {
    // Si el tanque está lleno, dibujar un círculo relleno de color verde
    if (waterLevel <= tankTop) {
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        fillellipse(155, 385, 31, 31);
    }
    // Si el tanque está vacío o se está drenando, dibujar un círculo relleno de color rojo
    else if (waterLevel >= tankTop + tankHeight) {
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse(155, 542, 31, 31);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(155, 385, 31, 31);
    } else 
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(155, 542, 31, 31);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(155, 385, 31, 31);
    }
}