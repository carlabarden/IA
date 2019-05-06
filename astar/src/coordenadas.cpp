#include "coordenadas.h"

/**
 * construtor de classe
 */
Coordenadas::Coordenadas(){

    this->x = 0;
    this->y = 0;
    this->z = 0;
}

/**
 * construtor de classe
 * @param x coordenada x
 * @param y coordenada y
 * @param z coordenada z
 */
Coordenadas::Coordenadas(int x, int y, int z){

    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * construtor de cópia
 * @param c Coordenada c
 */
Coordenadas::Coordenadas(const Coordenadas &c){

    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
}

/**
 * obtém a coordenada
 * @return Coordenadas
 */
Coordenadas Coordenadas::get_coord(){

    Coordenadas aux;
    aux.set_coord(this->x, this->y, this->z);
    return aux;
}

/**
 * especifica a coordenada
 * @param x  coordenada x
 * @param y  coordenada y
 * @param z  coordenada z
 */
void Coordenadas::set_coord(int x, int y, int z){

    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * especifica a coordenada
 * @param c Coordenada c
 */
void Coordenadas::set_coord(Coordenadas c){

    this->set_coord(c.get_x(), c.get_y(), c.get_z());
}

/**
 * gera coordenadas aleatorias, variando de min a max
 * @param  min valor mínimo da coordenada
 * @param  max valor máximo da coordenada
 * @return     coordenada gerada
 */
Coordenadas Coordenadas::coord_aleatorias(int min, int max){

    Coordenadas aux;
    aux.set_x(this->num_aleatorio(min - 1, max));
    aux.set_y(this->num_aleatorio(min - 1, max));
    aux.set_z(this->num_aleatorio(min - 1, max));
    return aux;
}

/**
 * obtém o valor de x da coordenada
 * @return o valor de x
 */
int Coordenadas::get_x(){

    int aux = this->x;
    return aux;
}

/**
 * obtém o valor de y da coordenada
 * @return o valor de y
 */
int Coordenadas::get_y(){

    int aux = this->y;
    return aux;
}

/**
 * obtém o valor de z da coordenada
 * @return o valor de z
 */
int Coordenadas::get_z(){

    int aux = this->z;
    return aux;
}

/**
 * atribui um valor ao x da coordenada
 * @param x valor a ser atribuido
 */
void Coordenadas::set_x(int x){

    this->x = x;
}

/**
 * atribui um valor ao y da coordenada
 * @param y valor a ser atribuído
 */
void Coordenadas::set_y(int y){

    this->y = y;
}

/**
 * atribui um valor ao z da coordenada
 * @param z valor a ser atribuído
 */
void Coordenadas::set_z(int z){

    this->z = z;
}

/**
 * verifica se as duas coordenadas passadas como argumento
 * @param  c1 coordenada 1 a ser comparada
 * @param  c2 coordenada 2 a ser comparada
 * @return    true se forem iguais, false se forem diferentes
 */
bool Coordenadas::coord_iguais(Coordenadas &c1, Coordenadas &c2){

    if (c1.get_x() == c2.get_x() &&
        c1.get_y() == c2.get_y() &&
        c1.get_z() == c2.get_z()){

            return true;
        }
    return false;
}

/**
 * gera números aleatórios; o argumento a sempre deve ser menor que b;
 * o primeiro argumento deve ser dado por a - 1
 * @param  a mínimo do intervalo
 * @param  b máximo do intervalo
 * @return   a coordenada gerada
 */
int Coordenadas::num_aleatorio(int a, int b){

    int aux = 0;
    aux = 1 + a + rand() % (b - a);

    return aux;
}

/**
 * imprime as coordenadas geradas, no formato (x, y, z)
 */
void Coordenadas::imprimir(){

    printf("(%d, %d, %d)", this->x, this->y, this->z);
}
