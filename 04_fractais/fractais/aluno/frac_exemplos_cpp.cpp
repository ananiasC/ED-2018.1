#include <iostream>
#include <lib/pen.h>

void trigo (Pen &p, int lado){
    if(lado < 1)
        return;

    p.setColor(232,181,85);

    int angulo = 40;

    for (int i = 0; i < 4; i++) {
        p.walk(lado);
        p.right(angulo);
        trigo(p,lado/3);
        p.left(2 * angulo);
        trigo(p,lado/3);
        p.right(angulo);
    }

    p.walk(-lado*4);

}


void triangulo (Pen &p, int lado){
    if(lado < 4)
        return;
    int angulo = 120;

    p.setColor(0,0,250);

    for(int i=0; i < 3;i++){
        p.walk(lado);
        p.right(angulo);

        triangulo(p,(lado/2));
    }

    lado -= 50;
}

void arvore (Pen &p, int lado){
    if(lado < 1)
        return;
    int ang = 30;

    p.walk(lado);
    p.right(ang);
    arvore(p, lado/1.26);
    p.left(ang*2);
    arvore(p, lado/1.26);
    p.right(ang);

    p.walk(-lado);
}

void gelo(Pen &p, int lado){
    if(lado < 1)
        return;
    int ang = 72;

    for (int i = 0; i < 5; i++) {
        p.walk(lado);
        if(lado/3 < 1)
            p.setThickness(30);
        gelo(p,lado/3);
        if(lado/3 > 1)
           p.setThickness(1);
        p.walk(-lado);
        p.right(ang);

    }
}


void circulos(Pen &p, int lado){
    if(lado < 2){
        return;
    }
    for(int i = 0; i < 6; i++){
        p.right(60);
        p.circle(lado);
        p.up();
        p.walk(lado);
        p.down();
        circulos(p,lado/3);
        p.up();
        p.walk(-lado);
        p.down();

    }

}

void fractal(){
    int escolha;
    std::cout << "Digite o numero correspondente ao que deseja ver" << std::endl;
    std::cout << "1 - Arvore" << std::endl;
    std::cout << "2 - Triangulo" << std::endl;
    std::cout << "3 - Trigo" << std::endl;
    std::cout << "4 - Gelo" << std::endl;
    std::cout << "5 - Circulos" << std::endl;

    std::cout << "Digite o numero:";
    std::cin >> escolha;

    Pen p(1366, 738);


    //p.setThickness(0);

    p.setSpeed(150);

    switch (escolha) {
    case 1:
        //posição de inicio do trigo
        p.setXY(680, 500);
        p.setColor(35,142,35);
        //faz o pincel apontar pra cima
        p.setHeading(90);

        p.setThickness(2);

        arvore(p,100);

        p.wait();
    break;
    case 2:
        //coloca o pincel na posicao x 300 y 100
        p.setXY(380, 100);
        //faz o pincel apontar pra direita
        p.setHeading(0);

        triangulo(p,600);

        p.wait();
    break;
    case 3:
        //posição de inicio do trigo
        p.setXY(680, 700);

        //faz o pincel apontar pra cima
        p.setHeading(90);

        trigo(p,120);

        p.wait();
    break;
    case 4:
        //posição de inicio do fractal
        p.setXY(680, 330);
        //Cor do fractal
        p.setColor(0,250,255);
        //Posição de inicio do pincel
        p.setHeading(54);

        p.setThickness(1);
        gelo(p,230);

        p.wait();
    break;
    case 5:
        //posição de inicio do fractal
        p.setXY(680, 330);
        //Cor do fractal
        p.setColor(100,255,155);

        p.setThickness(1);

        circulos(p,250);

        p.wait();

    break;
    default:
        std::cout << "Numero não listado!" << std::endl;
    break;
    }
}

int main(){
    fractal();
    return 0;
}
