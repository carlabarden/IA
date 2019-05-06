/**
 * O cubo e o algoritmo formam um conjunto de estados, que são
 * inicializados, percorridos e utilizados nesta classe.
 */

#pragma once
#include "coordenadas.h"
#include <vector>
#include <list>
#include <iterator>

//para listas (aberta e fechada)
typedef struct {
    Coordenadas c;
    float f, g, h;
}Nodo;


///para ordenar lista aberta
bool ordena_F(const Nodo& a, const Nodo& b);

class Estados {

private:

    int perc_bloq;
    int dim_cubo;
    bool ***cubo; //recebe false se não houver bloqueio, true se houver

    //estado inicial
    Coordenadas inicio;
    //estado final
    Coordenadas final;

    //alocação de memória do array tridimensional
    bool*** alocar();
    void bloquear();    //bloquear coordenadas aleatorias

    //para a*
    std::list<Nodo> lista_aberta;
    std::list<Nodo> lista_fechada;

    Nodo gera_nodo(Coordenadas c);

    void calc_custo_h(Nodo* atual);
    void calc_custo_g(Nodo* pai, Nodo* atual);
    void calc_custo_f(Nodo* atual);

    //verifica se alguma coordenada já está na lista (true) ou não (false)
    void verifica_lista(std::vector<Coordenadas>* coord, std::list<Nodo>* lista);

public:

    //salvar distância real encontrada;
    float dist;

    Estados();
    Estados(int dim_cubo, int perc_bloq);
    Estados(int dim_cubo, int perc_bloq, Coordenadas est_inicial, Coordenadas est_final);

    void desalocar();
    void imprimir();
    int qtd_blocks();

    //inicio e final aleatórios
    void estados_random();

    Coordenadas get_estado_inicial();
    Coordenadas get_estado_final();

     //retorna true se houver bloqueio na coordenada dada, false se não houver;
    bool esta_bloqueado(Coordenadas c);

    //Calcula os nós filhos da coordenada dada, considerando bloqueios
    std::vector<Coordenadas> estados_vizinhos (Coordenadas c);

    void pre_astar();
    bool astar ();

    //para testes
    void imprime_nodo(Nodo n);
    bool conteudo_coord(Coordenadas c);

};
