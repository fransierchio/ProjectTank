#include <iostream>
#include <graphics.h>
using namespace std;


void welcomeScreen();
bool isInsideButton(int x, int y, int buttonLeft, int buttonTop, int buttonRight, int buttonBottom);
void waitForButtonClick(int buttonLeft, int buttonTop, int buttonRight, int buttonBottom);
void drawBackground();
void FillButtom(int x, int y);
void StopButtom(int x, int y);
bool isInsideCircle(int x, int y, int centerX, int centerY, int radius);
void fillTank();

bool stopFilling = true;

int main() {
    //PRIMERA INTERFAZ
    // Tamaño de la pantalla
    int width = 1300;
    int height = 900;
    initwindow(width, height, "Control Panel");

    // Pantalla de bienvenida
    welcomeScreen();

    // Coordenadas del botón "Ingresar"
    int buttonLeft = width / 2 - 105;
    int buttonTop = height / 2 + 20;
    int buttonRight = width / 2 + 105;
    int buttonBottom = height / 2 + 60;

    // Esperar a que el usuario haga clic en el botón "Ingresar"
    waitForButtonClick(buttonLeft, buttonTop, buttonRight, buttonBottom);

    // Limpiar la pantalla
    cleardevice();
    //FIN PRIMERA INTERFAZ
    
    //Second Interface
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

        if (!stopFilling) {
            fillTank();
        }
    }

    // Esperar a que el usuario presione una tecla antes de cerrar la ventana
    getch();

    return 0;
}

void welcomeScreen() {
    // Tamaño de la ventana
    int width = getmaxx();
    int height = getmaxy();

    // Título de bienvenida
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy((width - textwidth((char*)"Panel de Control")) / 2, height / 2 - textheight((char*)"Panel de Control"), (char*)"Panel de Control");

    // Botón "Ingresar"
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    int buttonWidth = textwidth((char*)"Ingresar") + 20; // Ajustar el ancho del botón al texto más un margen
    int buttonHeight = textheight((char*)"Ingresar") + 20; // Ajustar el alto del botón al texto más un margen
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    rectangle(width / 2 - buttonWidth / 2, height / 2 + 20, width / 2 + buttonWidth / 2, height / 2 + 20 + buttonHeight);
    outtextxy(width / 2 - textwidth((char*)"Ingresar") / 2, height / 2 + 20 + (buttonHeight - textheight((char*)"Ingresar")) / 2, (char*)"Ingresar");
}

bool isInsideButton(int x, int y, int buttonLeft, int buttonTop, int buttonRight, int buttonBottom) {
    return (x >= buttonLeft && x <= buttonRight && y >= buttonTop && y <= buttonBottom);
}

void waitForButtonClick(int buttonLeft, int buttonTop, int buttonRight, int buttonBottom) {
    // Esperar a que el usuario haga clic en cualquier lugar de la ventana
    while (true) {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInsideButton(x, y, buttonLeft, buttonTop, buttonRight, buttonBottom)) {
                // Si el clic está dentro de los límites del botón "Ingresar", salir del bucle
                break;
            }
        }
        delay(100);
    }
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
                fillTank();
                stopFilling = false;
                
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
    int tankHeight = 610; 
    int tankLeft =186;
    int tankTop = 185;

    int waterLevel = tankTop + tankHeight; // Nivel inicial del agua (en la parte inferior del tanque)
    int fillSpeed = 4; // Velocidad de llenado (píxeles por iteración)
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