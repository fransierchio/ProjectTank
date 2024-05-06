#include <iostream>
#include <graphics.h>

void welcomeScreen();
bool isInsideButton(int x, int y, int buttonLeft, int buttonTop, int buttonRight, int buttonBottom);
void waitForButtonClick(int buttonLeft, int buttonTop, int buttonRight, int buttonBottom);
void drawTank();

int main() {
    //PRIMERA INTERFAZ
    // Tamaño de la pantalla
    int width = 800;
    int height = 800;
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
    drawTank();


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

void drawTank()
{
    int width = getmaxx();
    int height = getmaxy();

    //Size of 
    int tankWidth = width * 2 / 3;  // Toma dos tercios del ancho de la ventana
    int tankHeight = height * 2 / 3; // Toma dos tercios de la altura de la ventana

    // Calcular las coordenadas para posicionar la imagen en el centro horizontal y un poco arriba
    int tankLeft = (width - tankWidth) / 2;
    int tankTop = 0;

    // Cargar la imagen del tanque de agua
    readimagefile("tank.jpg", tankLeft, tankTop, tankLeft + tankWidth, tankTop + tankHeight);
}