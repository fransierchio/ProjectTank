// Coordenadas del botón "Llenar Tanque"
        int fillButtonLeft = width / 2 - 105;
        int fillButtonTop = height - 100;
        int fillButtonRight = width / 2 + 105;
        int fillButtonBottom = height - 60;

         // Dibujar el botón "Llenar Tanque"
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        rectangle(fillButtonLeft, fillButtonTop, fillButtonRight, fillButtonBottom);
        outtextxy(fillButtonLeft + 10, fillButtonTop + 10, "Llenar Tanque");