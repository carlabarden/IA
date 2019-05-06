#include "estados.h"

/**
 * construtor da classe
 */
Estados::Estados(){}

/**
 * construtor da classe
 * @param dim_cubo  dimensão do cubo
 * @param perc_bloq percentual de obstáculos no cubo
 */
Estados::Estados(int dim_cubo, int perc_bloq){

    this->dim_cubo = dim_cubo;
    this->perc_bloq = perc_bloq;
    this->dist = 0;
    this->cubo = this->alocar();

    this->estados_random();
    this->bloquear();

}

/**
 * Construtor da classe
 * @param dim_cubo    dimensão do cubo
 * @param perc_bloq   percentual de obstáculos
 * @param est_inicial coordenada de saída
 * @param est_final   coordenada de chegada
 */
Estados::Estados(int dim_cubo, int perc_bloq, Coordenadas est_inicial, Coordenadas est_final){

    this->dim_cubo = dim_cubo;
    this->perc_bloq = perc_bloq;
    this->cubo = this->alocar();
    this->inicio = est_inicial;
    this->final = est_final;
    this->dist = 0;
    this->bloquear();

}

/**
 * aloca e inicializa a matriz que representará o cubo
 * a matriz é do tipo bool, onde
 * false representa sem bloqueio na coordenada dada pelos índices da matriz e
 * true representa com bloqueio na coordenada dada pelos índices da matriz
 * @return um ponteiro para o endereço inicial da matriz
 */
bool*** Estados::alocar(){

    bool ***ptr = new bool**[this->dim_cubo];

    for (int i = 0; i < this->dim_cubo; i++){
        ptr[i] = new bool*[this->dim_cubo];

        for (int j = 0; j < this->dim_cubo; j++){
            ptr[i][j] = new bool[dim_cubo];
        }
    }

    //inicializando com false
    for (int i = 0; i < this->dim_cubo; i++){
        for (int j = 0; j < this->dim_cubo; j++){
            for (int k = 0; k < this->dim_cubo; k++){
                ptr[i][j][k] = false;
            }
        }
    }
    return ptr;
}

/**
 * libera a memória alocada para o cubo
 */
void Estados::desalocar(){

    for (int i = 0; i < this->dim_cubo; i++){
        for (int j = 0; j < this->dim_cubo; j++){
            delete[] cubo[i][j];
        }
        delete[] cubo[i];
    }
    delete[] cubo;
}

/**
 * imprime o cubo
 * para ler uma coordenada: (x, y, z), sendo
 * o índice i representa a coordenada x, que indica em qual das três matrizes estão as outras coordenadas
 * o índice j representa a coordenada y, que indica em qual linha está o estado
 * o índice k representa a coordenada z, que indica em qual coluna está o estado
 * o valor do estado indica se há obstáculo (1) ou não (0)
 *
 * a função comentada imprime um mapa de coordenadas
 */
void Estados::imprimir(){
    //imprime mapa de coordenadas
  /*  for (int i = 0; i < this->dim_cubo; i++){
        for (int j = 0; j < this->dim_cubo; j++){
            for (int k = 0; k < this->dim_cubo; k++) {
                printf(" [%d,%d,%d] ",i,j,k);
            }
            printf("\n");
        }
        printf("\n\n");
    } */

    for (int i = 0; i < this->dim_cubo; i++){
        for (int j = 0; j < this->dim_cubo; j++){
            for (int k = 0; k < this->dim_cubo; k++) {
                printf(" %d ", this->cubo[i][j][k]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

/**
 * verifica se o estado passado como argumento está bloqueado
 * @param  c coordenadas do estado
 * @return   true se está bloqueado, false se está livre
 */
bool Estados::esta_bloqueado(Coordenadas c){

    int x = c.get_x();
    int y = c.get_y();
    int z = c.get_z();

    if (this->cubo[x][y][z]) return true;
    else return false;
}

/**
 * bloqueia aleatoriamente posições do cubo, conforme o percentual de
 * bloqueio passado como argumento no início do programa
 */
void Estados::bloquear(){

    int qtd_block = pow(this->dim_cubo,3) / 100 * this->perc_bloq;
    int count_block = 0;

    while(count_block < qtd_block){

        Coordenadas aux;
        aux = aux.coord_aleatorias(0,(this->dim_cubo - 1));

        //se for igual às coordenadas de inicio, fim, ou algum bloqueio já existente,
        //passa para a proxima iteração
        if (aux.coord_iguais(aux, this->inicio)) continue;
        if (aux.coord_iguais(aux, this->final)) continue;
        if (this->esta_bloqueado(aux)) continue;
        else{
            this->cubo[aux.get_x()][aux.get_y()][aux.get_z()] = true;
            count_block ++;
        }
    }
}


/**
 * calcula a quantidade de estados bloqueados e retorna-a
 * @return a quantidade de estados bloqueados
 */
int Estados::qtd_blocks(){

    int aux = pow(this->dim_cubo,3) / 100 * this->perc_bloq;
    return aux;
}

/**
 * gera os estados (coordenadas) de saída e chegada (início e fim) aleatoriamente
 */
void Estados::estados_random(){

    //flag que decrementa para sinalizar quando os estados estão setados
    int flag = 2;

    do{
        Coordenadas aux;
        aux = aux.coord_aleatorias(0, (this->dim_cubo - 1));

        //se for igual às coordenadas de inicio, fim, ou algum bloqueio já existente,
        //passa para a proxima iteração
        if (aux.coord_iguais(aux, this->inicio)) continue;
        if (aux.coord_iguais(aux, this->final)) continue;
        if (this->esta_bloqueado(aux)) continue;
        else{
            if (flag == 2){
                this->inicio = aux;
                flag--;
            }
            else if (flag == 1){
                this->final = aux;
                flag --;
            }
        }

    }while(flag);
}

/**
 * obtém o estado inicial (coordenadas de saída)
 * @return as coordenadas do estado inicial
 */
Coordenadas Estados::get_estado_inicial(){

    Coordenadas aux = this->inicio;
    return aux;
}

/**
 * obtém o estado final (coordenadas de chegada)
 * @return as coordenadas do estado final
 */
Coordenadas Estados::get_estado_final(){

    Coordenadas aux = this->final;
    return aux;
}

/**
 * gera os possiveis movimentos a partir do estado dado, considerando bloqueios
 * @param  c coordenada inicial
 * @return  vetor contendo os possíveis movimentos a partir do estado dado
 */
std::vector<Coordenadas> Estados::estados_vizinhos (Coordenadas c){

    std::vector<Coordenadas> ev;
    std::vector<Coordenadas> ev2;
    Coordenadas aux;
    Coordenadas neg;
    neg.set_coord(-1, -1, -1);

    //Simplesmente somando e diminuindo um de cada coordenada
    //Para depois realizar a verificação de se o estado é válido;
    aux.set_coord(c.get_x() + 1, c.get_y(), c.get_z());
    ev.push_back(aux);
    aux.set_coord(c.get_x() - 1, c.get_y(), c.get_z());
    ev.push_back(aux);
    aux.set_coord(c.get_x(), c.get_y() + 1, c.get_z());
    ev.push_back(aux);
    aux.set_coord(c.get_x(), c.get_y() - 1, c.get_z());
    ev.push_back(aux);
    aux.set_coord(c.get_x(), c.get_y(), c.get_z() + 1);
    ev.push_back(aux);
    aux.set_coord(c.get_x(), c.get_y(), c.get_z() - 1);
    ev.push_back(aux);

    //valida estados, se forem inválidos, recebem coordenadas (-1,-1,-1)
    for (unsigned i = 0; i < ev.size(); i++){

        if (ev.at(i).get_x() < 0 || ev.at(i).get_x() > (this->dim_cubo - 1))
            ev.at(i).set_coord(neg);
        else if (ev.at(i).get_y() < 0 || ev.at(i).get_y() > (this->dim_cubo - 1))
            ev.at(i) .set_coord(neg);
        else if (ev.at(i).get_z() < 0 || ev.at(i).get_z() > (this->dim_cubo - 1))
            ev.at(i).set_coord(neg);

        if(!ev.at(i).coord_iguais(ev.at(i),neg))
            if (this->esta_bloqueado(ev.at(i).get_coord()))
                ev.at(i).set_coord(neg);
    }

    //retira do vetor de estados válidos as coordenadas negativas
    for (unsigned i = 0; i < ev.size(); i++){
        if (ev.at(i).coord_iguais(ev.at(i),neg)) continue;
        else ev2.push_back(ev.at(i));
    }

    return ev2;
}

/**
 * verifica o conteúdo da matriz a partir da coordenada dada
 * @param  c coordenada
 * @return   o conteúdo daquela posição da matriz
 */
bool Estados::conteudo_coord(Coordenadas c){
    bool aux = this->cubo[c.get_x()][c.get_y()][c.get_z()];
    return aux;
}

/****************************** A* *****************************************/

/**
 * calcula o custo h (heuristica) do estado dado até o estado final
 * @param atual estado atual
 */
void Estados::calc_custo_h(Nodo* atual){

    float h = 0.0;
    Coordenadas est_atual = atual->c;

    h = sqrt(pow((est_atual.get_x() - this->final.get_x()),2) +
             pow((est_atual.get_y() - this->final.get_y()),2) +
             pow((est_atual.get_z() - this->final.get_z()),2)
        );
    atual->h = h;
}

/**
 * calcula o custo g do estado (custo do início até o estado atual)
 * @param pai   estado pai
 * @param atual estado atual
 */
void Estados::calc_custo_g(Nodo* pai, Nodo* atual){

    float g = 0.0;
    g = pai->g + 1;
    atual->g = g;
}

/**
 * calcula o custo f do estado (custo inicial + final)
 * @param atual o estado atual
 */
void Estados::calc_custo_f(Nodo* atual){

    atual->f = atual->g + atual->h;
}

/**
 * gera o nó para as listas (tanto lista aberta quanto lista fechada)
 * e inicializa suas variáveis
 * @param  c o estado (coordenada)
 * @return   o nó da lista
 */
Nodo Estados::gera_nodo(Coordenadas c){

    Nodo aux;
    aux.c.set_coord(c);
    aux.f = 0;
    aux.g = 0;
    aux.h = 0;

    return aux;
}

/**
 * zera as listas e a distância para a próxima iteração (rodada) do A*
 */
void Estados::pre_astar(){

    this->lista_aberta.clear();
    this->lista_fechada.clear();
    this->dist = 0.0;
}

/**
 * implementação do algoritmo A*
 * @return true se encontrou o caminho, false se não encontrou
 */
bool Estados::astar(){

    bool fim = false;
    do{
        if (lista_aberta.empty()){
            //nó inicial
            Nodo ini = gera_nodo(this->inicio);
            this->calc_custo_h(&ini);
            this->calc_custo_f(&ini);
            this->lista_aberta.push_back(ini);
        }

        //ordenando
        this->lista_aberta.sort(ordena_F);

        //pegando o 1o nó e descobrindo possíveis filhos
        Coordenadas c_aux = this->lista_aberta.front().c.get_coord();
        std::vector<Coordenadas> filhos = this->estados_vizinhos(c_aux);

        //verificando se não estão na lista aberta ou fechada
        // e retirando-os caso estiverem
        this->verifica_lista(&filhos, &this->lista_aberta);
        this->verifica_lista(&filhos, &this->lista_fechada);

        if (filhos.size() > 0){
            // gerando e abrindo nós
            for (unsigned i = 0; i < filhos.size(); i++){
                Nodo aux = gera_nodo(filhos.at(i).get_coord());

                //esses nós são filhos do primeiro nó da lista
                calc_custo_g(&this->lista_aberta.front(), &aux);
                calc_custo_h(&aux);
                calc_custo_f(&aux);

                this->lista_aberta.push_back(aux);

                 //verifica se encontrou o caminho
                 Coordenadas c(filhos.at(i).get_coord());
                if (this->final.coord_iguais(this->final, c)){
                    this->dist = aux.g;
                    return true;
                }
                //imprime_nodo(aux);
            }
        }
        //fechando o último nó computado
        this->lista_fechada.push_back(lista_aberta.front());
        this->lista_aberta.pop_front();

        //termina caso já tenha visto todos os nós e não encontrado o caminho
        if (this->lista_aberta.empty()){
            fim = true;
        }

    }while(!fim);

    return false;
}

/**
 * para ordenar a lista_aberta em ordem crescente de custo f
 * @param  a 1o nó a ser comparado
 * @param  b 2o nó a ser comparado
 * @return   true se o custo f de a for menor que o de b, false caso o contrário
 */
bool ordena_F(const Nodo& a, const Nodo& b){

    return a.f < b.f;
}

/**
 * imprime um nó na tela
 * @param n nó a ser impresso
 */
void Estados::imprime_nodo(Nodo n){

    n.c.imprimir();
    printf(" ; ");
    printf("f = %.3f ; g = %.3f ; h = %.3f ; \n" , n.f, n.g, n.h);
}

/**
 * verifica se um determinado estado (coordenada) está na lista apontada por *lista
 * e evita a sua duplicação
 * @param coord estado a ser verificdo
 * @param lista lista a ser verificada
 */
void Estados::verifica_lista(std::vector<Coordenadas>* coord, std::list<Nodo>* lista){

    for (std::list<Nodo>::iterator it = lista->begin(); it != lista->end(); it++){
        Coordenadas aux_l((*it).c.get_coord());

        for (unsigned j = 0; j < coord->size(); j++){
           Coordenadas aux_v(coord->at(j).get_coord());

           //se o estado já estiver na lista, ele recebe (-1,-1,-1)
           //para ser retirado do vector de possiveis vizinhos
            if(aux_l.coord_iguais(aux_l, aux_v)){
                coord->at(j).set_coord(-1,-1,-1);
            }
        }
    }

    std::vector<Coordenadas> aux;
    //copia os estados não negativos para o vetor de vizinhos
    for (unsigned a = 0; a < coord->size(); a++){
        Coordenadas c(coord->at(a).get_coord());
        Coordenadas neg(-1,-1,-1);

        if (!c.coord_iguais(c, neg)){
            aux.push_back(c);
        }
    }

    coord->clear();

    //atualiza o vetor de vizinhos
    for (unsigned a = 0; a < aux.size(); a++){
        coord->push_back(aux.at(a));
    }
}
