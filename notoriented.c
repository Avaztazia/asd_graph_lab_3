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
                                            }
                                            else {
                                                pt[1].y = ny[i] + oneLen;
                                            }
                                        }
                                        else {
                                            pt[0].x += 15;
                                            pt[2].x += 15;
                                            pt[1].x = nx[i] + oneLen;
                                            if ( ny[i] > ny[j] ) {
                                                pt[1].y = ny[i] - oneLen;
                                            }
                                            else {
                                                pt[1].y = ny[i] + oneLen;
                                            }
                                        }
                                        Polyline(hdc,pt,3);
                                        break;
                                    default:
                                        LineTo( hdc, nx[j], ny[j] );
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
                                                }
                                                else {
                                                    pt[1].x += oneLen;
                                                }
                                            }
                                            else {
                                                pt[1].y += oneLen/2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen;

                                                }
                                                else {
                                                    pt[1].x += oneLen;
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
                                                }
                                                else {
                                                    pt[1].x += oneLen*3/2;
                                                }
                                            }
                                            else {
                                                pt[1].y += oneLen/4*3;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*3/2;
                                                }
                                                else {
                                                    pt[1].x += oneLen*3/2;
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
                                                }
                                                else {
                                                    pt[1].x += oneLen*2;
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
                                                }
                                            }
                                            break;
                                        }
                                        Polyline(hdc,pt,3);
                                    }
                                    else {
                                        LineTo( hdc, nx[j], ny[j] );
                                    }

                                }
                                else {
                                    LineTo( hdc, nx[j], ny[j] );
                                    //S..t starts here:
                                }
                            }
                        }
                        else {
                            LineTo( hdc, nx[j], ny[j] );
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

//Ñîçäà¸ì ïðîòîòèï ôóíêöèè îêíà, êîòîðàÿ áóäåò îïðåäåëåíà íèæå
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//îáúÿâëÿåì ñòðîêó-èìÿ ïðîãðàììû
char ProgName[]="Lab 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //ñîçäà¸ì ýêçåìïëÿð ñòðóêòóðû WNDCLASS

    w.lpszClassName=ProgName; //èìÿ ïðîãðàììû - îáúÿâëåíî âûøå
    w.hInstance=hInstance; //èäåíòèôèêàòîð òåêóùåãî ïðèëîæåíèÿ
    w.lpfnWndProc=WndProc; //óêàçàòåëü íà ôóíêöèþ îêíà
    w.hCursor=LoadCursor(NULL, IDC_ARROW); //çàãðóæàåì êóðñîð
    w.hIcon=0; //èêîíêè ó íàñ íå áóäåò ïîêà
    w.lpszMenuName=0; //è ìåíþ ïîêà íå áóäåò
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// öâåò ôîíà îêíà
    w.style=CS_HREDRAW|CS_VREDRAW; //ñòèëü - ïåðåðèñîâûâàåìîå ïî õ è ïî ó
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Ñîçäàäèì îêíî â ïàìÿòè, çàïîëíèâ àðãóìåíòû CreateWindow
    hWnd=CreateWindow(ProgName, //Èìÿ ïðîãðàììû
        "Lab 3", //Çàãîëîâîê îêíà
        WS_OVERLAPPEDWINDOW, //Ñòèëü îêíà - ïåðåêðûâàþùååñÿ
        0, //ïîëîæåíèå îêíà íà ýêðàíå ïî õ
        0, //ïîëîæåíèå ïî ó
        1920, //øèðèíà
        1080, //âèñîòà
        (HWND)NULL, //èäåíòèôèêàòîð ðîäèòåëüñêîãî îêíà
        (HMENU)NULL, //èäåíòèôèêàòîð ìåíþ
        (HINSTANCE)hInstance, //èäåíòèôèêàòîð ýêçåìïëÿðà ïðîãðàììû
        (HINSTANCE)NULL); //îòñóòñòâèå äîïîëíèòåëüíûõ ïàðàìåòðîâ

//Âûâîäèì îêíî èç ïàìÿòè íà ýêðàí
    ShowWindow(hWnd, nCmdShow);
//Îáíîâèì ñîäåðæèìîå îêíà
 //   UpdateWindow(hWnd);

//Öèêë îäåðæàííÿ ïîâ³äîìëåíü

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Ïîëó÷àåì ñîîáùåíèå èç î÷åðåäè
            TranslateMessage(&lpMsg); //Ïðåîáðàçóåò ñîîáùåíèÿ êëàâèø â ñèìâîëû
            DispatchMessage(&lpMsg); //Ïåðåäà¸ò ñîîáùåíèå ñîîòâåòñòâóþùåé ôóíêöèè îêíà
        }
    return(lpMsg.wParam);
    }

//Ôóíêöèÿ îêíà
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc; //ñîçäà¸ì êîíòåêñò óñòðîéñòâà
    PAINTSTRUCT ps; //ñîçäà¸ì ýêçåìïëÿð ñòðóêòóðû ãðàôè÷åñêîãî âûâîäà



//Öèêë îáðàáîòêè ñîîáùåíèé
    switch(messg){
    //ñîîáùåíèå ðèñîâàíèÿ
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);
            generateMatrixes();
            drawGraph( hdc, mirror );
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
