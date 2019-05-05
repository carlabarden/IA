#include "estados.h"

Estados::Estados(){}

Estados::Estados(int dim_cubo, int perc_bloq){

    this->dim_cubo = dim_cubo;
    this->perc_bloq = perc_bloq;
    this->dist = 0;
    this->cubo = this->alocar();
    
    this->estados_random();
    this->bloquear();

}

Estados::Estados(int dim_cubo, int perc_bloq, Coordenadas est_inicial, Coordenadas est_final){

    this->dim_cubo = dim_cubo;
    this->perc_bloq = perc_bloq;
    this->cubo = this->alocar();
    this->inicio = est_inicial;
    this->final = est_final;
    this->dist = 0;
    this->bloquear();

}

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

void Estados::desalocar(){

    for (int i = 0; i < this->dim_cubo; i++){
        for (int j = 0; j < this->dim_cubo; j++){
            delete[] cubo[i][j];
        }
        delete[] cubo[i];
    }
    delete[] cubo;
    //printf("Desalocado!!\n");
}

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

bool Estados::esta_bloqueado(Coordenadas c){

    int x = c.get_x();
    int y = c.get_y();
    int z = c.get_z();

    if (this->cubo[x][y][z]) return true;
    else return false;
}


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

int Estados::qtd_blocks(){

    int aux = pow(this->dim_cubo,3) / 100 * this->perc_bloq;
    return aux;
}

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

Coordenadas Estados::get_estado_inicial(){
    
    Coordenadas aux = this->inicio;
    return aux;
}

Coordenadas Estados::get_estado_final(){
    Coordenadas aux = this->final;
    return aux;
}


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
    
    //valida estados
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

    for (unsigned i = 0; i < ev.size(); i++){
        if (ev.at(i).coord_iguais(ev.at(i),neg)) continue;
        else ev2.push_back(ev.at(i));
    }

    return ev2;
}

bool Estados::conteudo_coord(Coordenadas c){
    bool aux = this->cubo[c.get_x()][c.get_y()][c.get_z()];
    return aux;
}

/****************************** A* *****************************************/

void Estados::calc_custo_h(Nodo* atual){
    float h = 0.0;
    Coordenadas est_atual = atual->c;
    
    h = sqrt(pow((est_atual.get_x() - this->final.get_x()),2) +
             pow((est_atual.get_y() - this->final.get_y()),2) +
             pow((est_atual.get_z() - this->final.get_z()),2) 
        );
    atual->h = h;
}

void Estados::calc_custo_g(Nodo* pai, Nodo* atual){
    float g = 0.0;
    g = pai->g + 1;
    atual->g = g;
}

void Estados::calc_custo_f(Nodo* atual){
    atual->f = atual->g + atual->h;
}

Nodo Estados::gera_nodo(Coordenadas c){
    
    Nodo aux;
    aux.c.set_coord(c);
    aux.f = 0;
    aux.g = 0;
    aux.h = 0;

    return aux;
}

void Estados::pre_astar(){
    this->lista_aberta.clear();
    this->lista_fechada.clear();
    this->dist = 0.0;
}

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
        //fechando o último nó aberto
        this->lista_fechada.push_back(lista_aberta.front());
        this->lista_aberta.pop_front();
        
        if (this->lista_aberta.empty()){
            fim = true;
        }
        
    }while(!fim);
    
    return false;
}

///para ordenar lista aberta
bool ordena_F(const Nodo& a, const Nodo& b){
    return a.f < b.f;
}

void Estados::imprime_nodo(Nodo n){
    //printf("Coordenadas:  ");
    n.c.imprimir();
    printf(" ; ");
    printf("f = %.3f ; g = %.3f ; h = %.3f ; \n" , n.f, n.g, n.h);
}

void Estados::verifica_lista(std::vector<Coordenadas>* coord, std::list<Nodo>* lista){

    for (std::list<Nodo>::iterator it = lista->begin(); it != lista->end(); it++){
        Coordenadas aux_l((*it).c.get_coord());
        
        for (unsigned j = 0; j < coord->size(); j++){
           Coordenadas aux_v(coord->at(j).get_coord());
           
            if(aux_l.coord_iguais(aux_l, aux_v)){
                coord->at(j).set_coord(-1,-1,-1);
            }
        }
    }
    
    std::vector<Coordenadas> aux;
    
    for (unsigned a = 0; a < coord->size(); a++){
        Coordenadas c(coord->at(a).get_coord());
        Coordenadas neg(-1,-1,-1);
        
        if (!c.coord_iguais(c, neg)){
            aux.push_back(c);
        }
    }
    
    coord->clear();
    
    for (unsigned a = 0; a < aux.size(); a++){
        coord->push_back(aux.at(a));
    }
}



