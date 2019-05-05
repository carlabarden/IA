#include "estados.h"

//para armazenar resultado final de distancia e tempo de cada iteração
typedef struct {
    float distancia;
    long double tempo;
}Data;

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    
    struct timespec t_inicio;
    struct timespec t_final;
    
    std::vector<Data> dados;
    int dim_cubo = 0;
    int perc_bloq = 0;
    int num_rod = 0;

    if (argc != 4){
        printf("\nUso ./astar [tamanho do grid] [percentual de bloqueio]  [numero de rodadas]\n\n");
        exit(0);
    }

    dim_cubo = atoi(argv[1]);
    perc_bloq = atoi(argv[2]);
    num_rod = atoi(argv[3]);
    
    Estados cubo(dim_cubo, perc_bloq);
    int fim = 0;
    
    do{
        //estados iniciais e finais gerados aleatoriamente
        cubo.estados_random();
        
        //tempo de inicio
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t_inicio);
        //a*
        cubo.pre_astar();
        bool caminho = cubo.astar();
        //tempo de fim
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t_final);
        
        //salvando o tempo e a distancia
        if(caminho){
            Data aux;
            aux.distancia = cubo.dist;
            aux.tempo = t_final.tv_nsec  - t_inicio.tv_nsec;
            dados.push_back(aux);
        }
            
        fim++;
        //printf("%d\n",fim);
    }while(fim < num_rod);

    //imprimindo na tela para redirecionar para arquivo
    printf(" G (u) ; Tempo (ns) ; \n");
    for (unsigned i = 0; i < dados.size(); i++){
        printf("%.0f;    %2.Lf;\n", dados.at(i).distancia, dados.at(i).tempo);
    }

    //liberando memória
    cubo.desalocar();
    return 0;
}
