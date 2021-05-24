#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

#define numb 11
#define oneLen 180

int nx[numb] = {};
int ny[numb] = {};
double** mat = NULL;
double** mirror = NULL;


double** randmm(int rows, int cols)
{
    double** matrix = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] =  2.0 / RAND_MAX * rand();
        }
    }

    return matrix;
}

double** mulmr(double num, double **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }

    return mat;
}

void drawGraph ( HDC hdc, double** matrix )
{
    void arrow(float fi, int px,int py){
            fi = 3.1416*(180.0 - fi)/180.0;
            int lx,ly,rx,ry; //px,py,
           // px=150; py=60;
            lx = px+15*cos(fi+0.3);
            rx = px+15*cos(fi-0.3);
            ly = py+15*sin(fi+0.3);
            ry = py+15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
         //  return 0;
    }
    char *nn[numb] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b"};
    int dx = 16, dy = 16, dtx = 7;
    int i;
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    SelectObject(hdc, KPen);
    for (int i = 0; i < numb; i++)
            {
                for (int j = 0; j < numb; j++)
                {
                    if ( matrix[i][j] == 1 ) {
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        if ( ( ( nx[i] == nx[j] ) && ( ( ny[i] - ny[j] == oneLen ) || ( ny[j] - ny[i] == oneLen ) ) ) != 1 && ( ( ny[i] == ny[j] ) && ( ( nx[i] - nx[j] == oneLen ) || ( nx[j] - nx[i] == oneLen ) ) ) != 1 && ( ( i == 0 && j == ( numb - 1 ) ) ||  ( j == 0 && i == ( numb - 1 ) ) ) != 1 ) {
                            if ( i == j ) {

                            }
                            else {
                                POINT pt[3];
                                pt[0].x = nx[i];
                                pt[0].y = ny[i];
                                pt[2].x = nx[j];
                                pt[2].y = ny[j];

                                if ( nx[i] == nx[j] ){

                                    switch ( i - j ) {
                                    case 2: case -2:
                                        if ( nx[i] == oneLen ) {
                                            pt[0].x -= 15;
                                            pt[2].x -= 15;
                                            pt[1].x = nx[i] - oneLen/2;
                                            if ( ny[i] > ny[j] ) {
                                                pt[1].y = ny[i] - oneLen;
                                                arrow(60, nx[j]-dx, ny[j]+dy);
                                            }
                                            else {
                                                pt[1].y = ny[i] + oneLen;
                                                arrow(-60, nx[j]-dx, ny[j]-5);
                                            }
                                        }
                                        else {
                                            pt[0].x += 15;
                                            pt[2].x += 15;
                                            pt[1].x = nx[i] + oneLen;
                                            if ( ny[i] > ny[j] ) {
                                                pt[1].y = ny[i] - oneLen;
                                                arrow(150, nx[j]+dx, ny[j]+dy);
                                            }
                                            else {
                                                pt[1].y = ny[i] + oneLen;
                                                arrow(-150, nx[j]+dx, ny[j]-5);
                                            }
                                        }
                                        Polyline(hdc,pt,3);
                                        break;
                                    default:
                                        LineTo( hdc, nx[j], ny[j] );
                                        if ( ny[i] > ny[j] ) {
                                            arrow(90,nx[j],ny[j]+dy);
                                        }
                                        else {
                                            arrow(-90,nx[j],ny[j]-dy);
                                        }
                                        break;
                                    }

                                }
                                else if ( ny[i] == ny[j] ) {

                                    if ( ny[i] == oneLen || ny[i] == oneLen*3 ) {
                                        pt[1].y = ny[i];
                                        pt[1].x = nx[i];
                                        switch ( nx[i] - nx[j] ) {
                                        case 180*2: case 180*(-2):
                                            if ( ny[i] == oneLen ) {
                                                pt[1].y -= oneLen/2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen;
                                                    arrow(35,nx[j]+15,ny[j]+6);
                                                }
                                                else {
                                                    pt[1].x += oneLen;
                                                    arrow(-35,nx[j]-15,ny[j]+6);
                                                }
                                            }
                                            else {
                                                pt[1].y += oneLen/2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen;
                                                    arrow(145,nx[j]+15,ny[j]+6);

                                                }
                                                else {
                                                    pt[1].x += oneLen;
                                                    arrow(-145,nx[j]-15,ny[j]+6);
                                                }
                                            }
                                            break;
                                        case 180*3: case 180*(-3):
                                            if ( nx[i] > nx[j] ) {
                                                pt[0].x += 15;
                                                pt[2].x -= 15;
                                            }
                                            else {
                                                pt[0].x -= 15;
                                                pt[2].x += 15;
                                            }
                                            if ( ny[i] == oneLen ){
                                                pt[1].y -= oneLen/4*2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*3/2;
                                                    arrow(-160,nx[j]+15,ny[j]-9);
                                                }
                                                else {
                                                    pt[1].x += oneLen*3/2;
                                                    arrow(160,nx[j]+15,ny[j]-9);
                                                }
                                            }
                                            else {
                                                pt[1].y += oneLen/4*3;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*3/2;
                                                    arrow(155,nx[j]+9,ny[j]+11);
                                                }
                                                else {
                                                    pt[1].x += oneLen*3/2;
                                                    arrow(-155,nx[j]+9,ny[j]+11);
                                                }
                                            }
                                            break;
                                        case 180*4: case 180*(-4):
                                            if ( nx[i] > nx[j] ) {
                                                pt[0].x += 13;
                                                pt[2].x -= 13;
                                            }
                                            else {
                                                pt[0].x -= 13;
                                                pt[2].x += 13;
                                            }
                                            if ( ny[i] == oneLen ) {
                                                pt[0].y -= 5;
                                                pt[2].y -= 5;
                                                pt[1].y -= oneLen;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*2;
                                                    arrow(-160,nx[j]+9,ny[j]-15);
                                                }
                                                else {
                                                    pt[1].x += oneLen*2;
                                                    arrow(160,nx[j]+9,ny[j]-15);
                                                }
                                            }
                                            else {
                                                pt[0].y += 5;
                                                pt[2].y += 5;
                                                pt[1].y += oneLen*5/4;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*2;

                                                }
                                                else {
                                                    pt[1].x += oneLen*2;
                                                    arrow(40,nx[j]-5,ny[j]+15);
                                                }
                                            }
                                            break;
                                        }
                                        Polyline(hdc,pt,3);
                                    }
                                    else {
                                        LineTo( hdc, nx[j], ny[j] );
                                        if ( nx[i] > nx[j] ) {
                                            arrow(180,nx[j]+dx,ny[j]);
                                        }
                                        else {
                                            arrow(0,nx[j]-dx,ny[j]);
                                        }
                                    }

                                }
                                else {
                                    //S..t starts here:
                                    if ( matrix[j][i] == 1 ) {

                                        if ( i - j < 0 ) {
                                            pt[1].x = nx[i] + 20;
                                            pt[1].y = ny[i] - oneLen;
                                            LineTo( hdc, nx[j], ny[j] );
                                            arrow(70,nx[j]-8,ny[j]+dy);
                                            Polyline(hdc,pt,3);
                                            arrow(-100,nx[i]+1,ny[i]-dy);
                                        }

                                    }
                                    else{
                                        if ( ny[i] - ny[j] == oneLen*2 ||  ny[j] - ny[i] == oneLen*2 ) {
                                            switch ( nx[i]-nx[j] ) {
                                            case oneLen:
                                                if ( ny[j] > ny[i]) arrow(70,nx[j]+9,ny[j]-dy);
                                                else arrow(-70,nx[j]+9,ny[j]+dy);
                                                break;
                                            case -oneLen:
                                                if ( ny[j] > ny[i]) arrow(-70,nx[j]-9,ny[j]-dy);
                                                else arrow(70,nx[j]-9,ny[j]+dy);
                                                break;
                                            case oneLen*2:
                                                if ( ny[j] > ny[i]) arrow(-130,nx[j]+12,ny[j]-dy+5);
                                                else arrow(130,nx[j]+12,ny[j]+dy-5);
                                                break;
                                            case -oneLen*2:
                                                if ( ny[j] > ny[i]) arrow(-50,nx[j]-12,ny[j]-dy+5);
                                                else arrow(50,nx[j]-12,ny[j]+dy-5);
                                                break;
                                            case oneLen*3:
                                                if ( ny[j] > ny[i]) arrow(-140,nx[j]+15,ny[j]-dy+7);
                                                else arrow(140,nx[j]+15,ny[j]+dy-7);
                                                break;
                                            case -oneLen*3:
                                                if ( ny[j] > ny[i]) arrow(50,nx[j]-15,ny[j]-dy+7);
                                                else arrow(-50,nx[j]-15,ny[j]+dy-7);
                                                break;
                                            case oneLen*4:
                                                if ( ny[j] > ny[i]) arrow(-150,nx[j]+11,ny[j]-dy+2);
                                                else arrow(140,nx[j]+15,ny[j]+dy-7);
                                                break;
                                            case -oneLen*4:
                                                if ( ny[j] > ny[i]) arrow(30,nx[j]-11,ny[j]-dy+2);
                                                else arrow(-40,nx[j]-15,ny[j]+dy-7);
                                                break;
                                            }
                                        }
                                        else {

                                            if ( nx[i] - nx[j] == oneLen ) {
                                                arrow(-135,nx[j]+10,ny[j]-10);
                                            }
                                            else if ( nx[j] - nx[i] == oneLen ) {
                                                arrow(45,nx[j],ny[j]-10);
                                            }
                                            else if ( nx[i] - nx[j] == oneLen*3 ){
                                                if ( ny[i] > ny[j]) arrow(165,nx[j]+14,ny[j]+5);
                                                else arrow(-165,nx[j]+14,ny[j]-5);
                                            }

                                        }
                                        LineTo( hdc, nx[j], ny[j] );
                                    }
                                }
                            }
                        }
                        else {

                            if ( matrix[j][i] == 1 ) {
                                if ( i - j > 0 ) {
                                    POINT pt[3];
                                    pt[0].x = nx[i];
                                    pt[0].y = ny[i];

                                    pt[2].x = nx[j];
                                    pt[2].y = ny[j];

                                    LineTo( hdc, nx[j], ny[j] );
                                    if ( nx[i] == nx[j] && ny[i] > ny[j] ) {
                                        arrow(90, nx[j], ny[j]+dy);
                                        pt[1].x = nx[i]-oneLen/4;
                                        pt[1].y = ny[i]-oneLen/2;
                                        arrow(60, nx[j]-7, ny[j]+dy);
                                    }
                                    else if ( nx[i] == nx[j] && ny[i] < ny[j] ) {
                                        arrow(-90, nx[j], ny[j]-dy);
                                        pt[1].x = nx[i]+oneLen/4;
                                        pt[1].y = ny[i]+oneLen/2;
                                        arrow(-60, nx[j]+7, ny[j]+dy);
                                    }
                                    else if ( nx[i] > nx[j] ) {
                                        arrow(180, nx[j]+dx, ny[j]);
                                        pt[1].x = nx[i]-oneLen/4;
                                        pt[1].y = ny[i]+oneLen/2;
                                        arrow(150, nx[j]+dx, ny[j]+7);
                                    }
                                    else {
                                        arrow(0, nx[j]-dx, ny[j]);
                                        pt[1].x = nx[i]+oneLen/4;
                                        pt[1].y = ny[i]+oneLen/2;
                                        arrow(-150, nx[j]+dx, ny[j]-7);
                                    }
                                    Polyline(hdc,pt,3);
                                }
                            }
                            else {
                                LineTo( hdc, nx[j], ny[j] );
                                if ( nx[i] == nx[j] && ny[i] > ny[j] ) {
                                    arrow(90, nx[j], ny[j]+dy);
                                }
                                else if ( nx[i] == nx[j] && ny[i] < ny[j] ) {
                                    arrow(-90, nx[j], ny[j]-dy);
                                }
                                else if ( nx[i] > nx[j] ) {
                                     arrow(180, nx[j]+dx, ny[j]);
                                }
                                else {
                                    arrow(0, nx[j]-dx, ny[j]);
                                }
                            }

                        }
                    }
                }
            }
            SelectObject(hdc, BPen);
            for ( i = 0; i <= 10; i++ ){
              Ellipse ( hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy );
              TextOut ( hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 1 );
            }
}

void printMatrix ( double** matrix, int rows, int cols ) {
    for ( int i = 0; i < rows; i++ ){
        for ( int j = 0; j < cols; j++ )
            printf("%.0f\t", matrix[i][j]);
        printf("\n");
    }
}

void generateMatrixes (  )
{
    for ( int i = 0; i < numb; i++ ) {
        if ( i == 0 ) {
            nx[i] = oneLen*3;
            ny[i] = oneLen;
        }
        else if ( i < 3) {
            nx[i] = nx[i-1] - oneLen;
            ny[i] = ny[i-1];
        }
        else if ( i < 5 ) {
            nx[i] = nx[i-1];
            ny[i] = ny[i-1] + oneLen;
        }
        else if ( i < 9 ){
            nx[i] = nx[i-1] + oneLen;
            ny[i] = ny[i-1];
        }
        else {
            nx[i] = nx[i-1];
            ny[i] = ny[i-1] - oneLen;
        }
    }
    srand(0412);
    double** T = randmm(numb, numb);
    double coef = 1.0 - 1*0.02 - 2*0.005 - 0.25;
    mat = mulmr(coef, T, numb, numb);
    mirror = randmm(numb, numb);
    printf("\nMatrix:\n");
    printMatrix ( mat, numb, numb );
    for ( int i = 0; i < numb; i++ )
        for ( int j = 0; j < numb; j++ )
            mirror[i][j] = mat[i][j];
    for ( int i = 0; i < numb; i++ )
        for ( int j = 0; j < numb; j++ )
            if ( mat[i][j] ) mirror[j][i] = 1;
    printf("\nMirror Matrix:\n");
    printMatrix ( mirror, numb, numb );
}

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//объявляем строку-имя программы
char ProgName[]="Lab 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName=ProgName; //имя программы - объявлено выше
    w.hInstance=hInstance; //идентификатор текущего приложения
    w.lpfnWndProc=WndProc; //указатель на функцию окна
    w.hCursor=LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon=0; //иконки у нас не будет пока
    w.lpszMenuName=0; //и меню пока не будет
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// цвет фона окна
    w.style=CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd=CreateWindow(ProgName, //Имя программы
        "Lab 3", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
        0, //положение окна на экране по х
        0, //положение по у
        1920, //ширина
        1080, //висота
        (HWND)NULL, //идентификатор родительского окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
    ShowWindow(hWnd, nCmdShow);
//Обновим содержимое окна
 //   UpdateWindow(hWnd);

//Цикл одержання повідомлень

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
            TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
            DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
        }
    return(lpMsg.wParam);
    }

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода



//Цикл обработки сообщений
    switch(messg){
    //сообщение рисования
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);
            generateMatrixes();
            drawGraph( hdc, mat );
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
