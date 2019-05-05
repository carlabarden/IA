#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

class Coordenadas{

private:

    int x;
    int y;
    int z;
    int num_aleatorio (int a, int b);


public:

    Coordenadas();
    Coordenadas(int x, int y, int z);
    //construtor de cópias
    Coordenadas(const Coordenadas &c);
    Coordenadas get_coord();
    void set_coord(int x, int y, int z);
    void set_coord(Coordenadas c);
    
    Coordenadas coord_aleatorias(int min, int max);
    
    int get_x();
    int get_y();
    int get_z();
    void set_x(int x);
    void set_y(int y);
    void set_z(int z);
    
    bool coord_iguais(Coordenadas &c1, Coordenadas &c2);
    
    void imprimir();

};
