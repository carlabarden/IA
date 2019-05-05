#include "coordenadas.h"

Coordenadas::Coordenadas(){

    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Coordenadas::Coordenadas(int x, int y, int z){

    this->x = x;
    this->y = y;
    this->z = z;
}

Coordenadas::Coordenadas(const Coordenadas &c){

    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
}

Coordenadas Coordenadas::get_coord(){

    Coordenadas aux;
    aux.set_coord(this->x, this->y, this->z);
    return aux;
}

void Coordenadas::set_coord(int x, int y, int z){

    this->x = x;
    this->y = y;
    this->z = z;
}

void Coordenadas::set_coord(Coordenadas c){

    this->set_coord(c.get_x(), c.get_y(), c.get_z());
}

Coordenadas Coordenadas::coord_aleatorias(int min, int max){

    Coordenadas aux;
    aux.set_x(this->num_aleatorio(min - 1, max));
    aux.set_y(this->num_aleatorio(min - 1, max));
    aux.set_z(this->num_aleatorio(min - 1, max));
    return aux;
}

int Coordenadas::get_x(){

    int aux = this->x;
    return aux;
}

int Coordenadas::get_y(){

    int aux = this->y;
    return aux;
}

int Coordenadas::get_z(){

    int aux = this->z;
    return aux;
}

void Coordenadas::set_x(int x){

    this->x = x;
}

void Coordenadas::set_y(int y){

    this->y = y;
}

void Coordenadas::set_z(int z){

    this->z = z;
}

bool Coordenadas::coord_iguais(Coordenadas &c1, Coordenadas &c2){

    if (c1.get_x() == c2.get_x() && 
        c1.get_y() == c2.get_y() &&
        c1.get_z() == c2.get_z()){
            
            return true;
        }
    return false;
}

/**
//gera números aleatórios
//a < b sempre
// primeiro parametro é dado por x - 1
*/
int Coordenadas::num_aleatorio(int a, int b){

    int aux = 0;
    aux = 1 + a + rand() % (b - a);

    return aux;
}

void Coordenadas::imprimir(){

    printf("(%d, %d, %d)", this->x, this->y, this->z);
}