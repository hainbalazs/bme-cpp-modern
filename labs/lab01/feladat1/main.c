#include <stdio.h>
#include <math.h>

 int W, H;
 double d;

void clear(char page[H][W]) {
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            page[y][x] = ' ';
}

 double dsin(double x){
    return sin(d*x);
 }

void plot(char page[H][W], char c, double (*f)(double)) {
    for (int x = 0; x < W; ++x) {
        double fx = (x - W/2)/4.0;
        double fy = f(fx);
        int y = (fy * 4.0) * -1 + H/2;
        if (y >= 0 && y < H)
            page[y][x] = c;
    }
}

void print(char page[H][W]) {
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x)
            putchar(page[y][x]);
        putchar('\n');
    }
}

int main() {
    printf("Add meg a lap mereteit! [szelesseg, hosszusag]\n");
    scanf("%d", &W);
    scanf("%d", &H);
    char page[H][W];

    // tetsz�leges fv b�v�t�s�re �ltalam v�lasztott megold�s lenne:
    // VLA T�mb param�ter �tad�s, a sz�gfv tagokra, speci�lis esetekre k�l�n fv, mint a dsin-n�l
    printf("sin(d * x), d = ?\n");
    scanf("%lf", &d);

    clear(page);
    plot(page, '.', dsin);
    plot(page, '+', cos);
    print(page);
}
