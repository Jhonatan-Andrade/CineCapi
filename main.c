// gcc main.c -o app && ./app
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE_MOVIES 5
#define MAX_SIZE_CLIENTS 100

#define MOVIE_THEATER_SIZE_X 5
#define MOVIE_THEATER_SIZE_Y 5

void clearScreen() {
	#if defined(_WIN32)
		system("cls");
	#elif defined(_WIN64)
		system("cls");
	#elif defined(__linux__)
		system("clear");
	#elif defined(__APPLE__) && defined(__MACH__)
		system("clear");
	#elif defined(__unix__)
		system("clear");
	#else
		system("clear");
	#endif
}
typedef struct {
    char  nomeDoFilme[30];
    int  salaDeExibição;
    char  horarioDaSessão[8];
    float precoDoIngresso;
} Movies;

typedef struct {
    int numeroDaSala;
    int mapaDeAssentos[MOVIE_THEATER_SIZE_X][MOVIE_THEATER_SIZE_Y];
} Theater;

typedef struct {
    char nome[50];
    int  idade;
} Client;

typedef struct {
    char  nome[50];
    int   idade;
    char  nomeDoFilme[30];
     int  salaDeExibição;
    char  horarioDaSessão[8];
    float precoDoIngresso;
    int   numeroDoAssento;
} Ticket;

typedef struct {
 Movies itens[MAX_SIZE_MOVIES];
 int topo;
} MoviesStack;

typedef struct {
  Theater itens[MAX_SIZE_MOVIES];
} MovieTheater;

typedef struct {
 Client itens[MAX_SIZE_CLIENTS];
 int inicio;
 int fim ;
} CustomerQueue;

typedef struct {
 Ticket itens[MAX_SIZE_CLIENTS];
 int topo;
} TicketStack;

//Inicialzar pilhas
void initializeMoviesStack(MoviesStack *pilha){pilha->topo = -1;};
void initializeCustomerQueue(CustomerQueue *fila){
    fila->inicio = 0;
    fila->fim = -1;
};
void initializeTicketsStack(TicketStack *pilha){pilha->topo = -1;};
void initializeMoviesTheater(MovieTheater *mapa){
    for (int i = 0; i < MAX_SIZE_MOVIES; i++) {
        mapa->itens[i].numeroDaSala = i + 1;
        for (int j = 0; j < MOVIE_THEATER_SIZE_X; j++) {
            for (int k = 0; k < MOVIE_THEATER_SIZE_Y; k++) {
                mapa->itens[i].mapaDeAssentos[j][k] = 0;
            }
        }
    }
};
//Verifica se a pilha está vazia
int moviesStackIsVoid(MoviesStack *pilha){return pilha->topo == -1;};
int customerQueueIsVoid(CustomerQueue *fila){return fila->inicio > fila->fim;};
int ticketStackIsVoid(TicketStack *pilha){return pilha->topo == -1;};

//Verifica se a pilha está cheia
int moviesStackIsFull(MoviesStack *pilha){return pilha->topo == MAX_SIZE_MOVIES - 1;};
int customerQueueIsFull(CustomerQueue *fila){return fila->fim == MAX_SIZE_CLIENTS - 1;};
int ticketStackIsFull(TicketStack *pilha){return pilha->topo == MOVIE_THEATER_SIZE_X * MOVIE_THEATER_SIZE_Y -1;};

//Remover um item do topo da pilha (POP)
Movies removeMovieFromStack(MoviesStack *pilha){
    if (moviesStackIsVoid(pilha)) {
        printf("Erro: Pilha vazia\n");
        Movies filmeVazio;
        return filmeVazio; 
    }
    Movies item = pilha->itens[pilha->topo];
    pilha->topo--;
    return item;
};
Client removeCustomerFromQueue(CustomerQueue *fila){
     if (customerQueueIsVoid(fila)) {
        printf("Erro: Fila vazia\n");
        Client customerQueue;
        return customerQueue; 
     }
     Client item = fila->itens[fila->inicio];
     fila->inicio++;
    return item;
};
Ticket removeTicketFromStack(TicketStack *pilha){
    if (ticketStackIsVoid(pilha)) {
        printf("Erro: Pilha vazia\n");
        Ticket ticketVazio;
        return ticketVazio; 
    }
    Ticket item = pilha->itens[pilha->topo];
    pilha->topo--;
    return item;
};

//Adicionar um item ao topo da pilha (PUSH)
void pushMovieToStack(MoviesStack *pilha, Movies item){
    if (moviesStackIsFull(pilha)) {
        printf("Erro: Pilha Movie cheia\n");
        return;
    }
    pilha->topo++;
    pilha->itens[pilha->topo] = item;
};
void pushCustomerQueue(CustomerQueue *fila, Client item){
    if (customerQueueIsFull(fila)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    fila->fim++;
    fila->itens[fila->fim] = item;
};
void pushTicketToStack(TicketStack *pilha,Ticket item ){
    if (ticketStackIsFull(pilha)) {
        printf("Erro: Pilha Ticket cheia\n");
        return;
    }
    pilha->topo++;
    pilha->itens[pilha->topo] = item;
};

//Adicionar dados automaticamente na pilha
void addListMovieToStack(MoviesStack *pilha){
    Movies filme1 = {"O Poderoso Chefao", 1, "19:00", 15.0};
    Movies filme2 = {"Pulp Fiction", 2, "21:00", 120.0};
    Movies filme3 = {"A Origem", 3, "20:00", 10.0};
    Movies filme4 = {"Matrix", 4, "22:00", 8.0};
    Movies filme5 = {"Clube da Luta", 5, "18:00", 20.0};
    pushMovieToStack(pilha, filme1);
    pushMovieToStack(pilha, filme2);
    pushMovieToStack(pilha, filme3);
    pushMovieToStack(pilha, filme4);
    pushMovieToStack(pilha, filme5);
};
void addListCustomerQueue(CustomerQueue *fila){
    Client cliente1 = {"João", 25};
    Client cliente2 = {"Maria", 30};
    Client cliente3 = {"Pedro", 22};
    Client cliente4 = {"Ana", 28};
    Client cliente5 = {"Lucas", 35};
    pushCustomerQueue(fila, cliente1);
    pushCustomerQueue(fila, cliente2);
    pushCustomerQueue(fila, cliente3);
    pushCustomerQueue(fila, cliente4);
    pushCustomerQueue(fila, cliente5);
}
Ticket addTicketToStack(TicketStack *pilha,Client dataClient, Movies filmeEscolhido,int numeroDoAssento){
    Ticket ticket;
    strcpy(ticket.nome, dataClient.nome);
    ticket.idade = dataClient.idade;
    strcpy(ticket.nomeDoFilme, filmeEscolhido.nomeDoFilme);
    ticket.salaDeExibição = filmeEscolhido.salaDeExibição;
    strcpy(ticket.horarioDaSessão, filmeEscolhido.horarioDaSessão);
    ticket.precoDoIngresso = filmeEscolhido.precoDoIngresso;
    ticket.numeroDoAssento = numeroDoAssento;
    pushTicketToStack(pilha, ticket);
    return ticket;
}


// verificar se o assento escolhido está disponível
int verificarAssento(int mapa[MOVIE_THEATER_SIZE_X][MOVIE_THEATER_SIZE_Y], int escolha){
    if (escolha < 1 || escolha > MOVIE_THEATER_SIZE_X * MOVIE_THEATER_SIZE_Y) {
        return 0;
    } else {
        int linha = (escolha - 1) / MOVIE_THEATER_SIZE_Y;
        int coluna = (escolha - 1) % MOVIE_THEATER_SIZE_Y;
        if (mapa[linha][coluna] == 0) {
            mapa[linha][coluna] = 1;
            return 1;
        } else {
            return 0;
        }
    }
}
//Mostra dados na tela 
int stringLength(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
int screenMoviesStack(MoviesStack *pilha){
    bool validOption = true;
    int opt = 0;

    while(validOption){
        if (moviesStackIsVoid(pilha)) {
            printf("A pilha de filmes está vazia.\n");
        }
        printf("Filmes disponíveis\n\n");
        int counter = 1;
        for (int i = pilha->topo; i >= 0; i--) {

            int nomeLength = stringLength(pilha->itens[i].nomeDoFilme);
            int horarioLength = stringLength(pilha->itens[i].horarioDaSessão);
            printf("%d ", counter);
            counter++;

            printf("%s", pilha->itens[i].nomeDoFilme);
            for (int j = 0; j < 30 - nomeLength; j++) {printf(" ");}

            if(pilha->itens[i].salaDeExibição < 10){
                printf("Sala: 0%d  ", pilha->itens[i].salaDeExibição);    
            } else{
                printf("Sala: %d  ", pilha->itens[i].salaDeExibição);
            } 
            printf("%sH  ", pilha->itens[i].horarioDaSessão);

            float preco = pilha->itens[i].precoDoIngresso;
            if(preco < 10){
                printf("  %.2f R$\n", preco);    
            } else if (preco > 1 && preco < 100){
                printf(" %.2f R$\n", preco);
            }else {    
                printf("%.2f R$\n", preco);   
            }
        }
        printf("\nEscolha uma Filme com base na posição da lista:");
       
        int  isLetters = scanf("%d",&opt);

        if(opt < 1 || opt > counter - 1 || isLetters == 0 && opt != 0 ){ 
            clearScreen();
            printf("Opção inválida. Por favor, escolha um número entre 1 e %d .\n\n", counter - 1);
        }else{
            validOption = false;
        }
        while (getchar() != '\n');
    }
    return opt;
};
 
int screenMovieTheater(TicketStack *pilha, int mapa[MOVIE_THEATER_SIZE_X][MOVIE_THEATER_SIZE_Y]){
     
    int escolha, continuar = 1;
    if (ticketStackIsFull(pilha)) {
        printf("A pilha de tickets está cheia.\n");
        return -1; 
    }
    while (continuar) {
        printf("\nMapa dos assentos:\n"); 
        for (int i = 0; i < MOVIE_THEATER_SIZE_X; i++) {
            for (int j = 0; j < MOVIE_THEATER_SIZE_Y; j++) {
                if (mapa[i][j] == 0) {
                    printf("%02d ", (i * MOVIE_THEATER_SIZE_Y) + j + 1);
                } else {
                    printf("XX "); 
                }
            }
            printf("\n");
        } 
        printf("\nEscolha um assento ");
        scanf("%d", &escolha);

        if(verificarAssento(mapa, escolha)){ 
            continuar = 0; 
        }
        int assentoValido = verificarAssento(mapa, escolha);
    }
    return escolha;
}

int screenTicket(Ticket ticket){
    int nomeLength = stringLength(ticket.nome);
    int nomeDoFilmeLength = stringLength(ticket.nomeDoFilme);

    printf("========================================= \n");
    printf(" %s", ticket.nomeDoFilme);
    for (int j = 0; j < 31 - nomeDoFilmeLength; j++) {printf(" ");}

    if(ticket.salaDeExibição < 10){
        printf("Sala: 0%d  \n\n", ticket.salaDeExibição);    
    } else{
        printf("Sala: %d  \n\n", ticket.salaDeExibição);
    }
    if(ticket.numeroDoAssento < 10){
        printf(" Horario:%s   Assento:0%d  Preco:%.2f  \n\n", ticket.horarioDaSessão, ticket.numeroDoAssento, ticket.precoDoIngresso);    
    } else{
        printf(" Horario:%s   Assento:%d  Preco:%.2f  \n\n", ticket.horarioDaSessão, ticket.numeroDoAssento, ticket.precoDoIngresso);
    }
    printf(" Nome:%s", ticket.nome);
    for (int j = 0; j < 26 - nomeLength; j++) {printf(" ");}
    if(ticket.idade < 10){
        printf("Idade:0%d  \n", ticket.idade);    
    } else{ 
        printf("Idade:%d  \n", ticket.idade);
    }
    printf("========================================= \n"); 
    
}
void screenMovieTheaterMap(MovieTheater mapa){

        printf("\nMapa dos assentos:\n"); 
        for (int i = 0; i < MAX_SIZE_MOVIES; i++) {
            printf("Sala %d:\n", i + 1);
            for (int j = 0; j < MOVIE_THEATER_SIZE_X; j++) {
                for (int k = 0; k < MOVIE_THEATER_SIZE_Y; k++) {
                    if (mapa.itens[i].mapaDeAssentos[j][k] == 0) {
                        printf("%02d ", (j * MOVIE_THEATER_SIZE_Y) + k + 1);
                    } else {
                        printf("XX ");
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
}
int main (){
    MoviesStack moviesStack;
    initializeMoviesStack(&moviesStack);
    addListMovieToStack(&moviesStack);
    
    CustomerQueue customerQueue;
    initializeCustomerQueue(&customerQueue);
    addListCustomerQueue(&customerQueue);
    
    TicketStack ticketsStack;
    initializeTicketsStack(&ticketsStack);

    int movieTheater[MOVIE_THEATER_SIZE_X][MOVIE_THEATER_SIZE_Y] = {0};

    MovieTheater mapa;
    initializeMoviesTheater(&mapa);

    while(true){
        clearScreen();
        Client client = removeCustomerFromQueue(&customerQueue);
        printf("Bem-vindo  %s ao sistema de cinema!\n\n",client.nome);
      
        int opt = screenMoviesStack(&moviesStack);
        Movies filmeEscolhido = moviesStack.itens[moviesStack.topo - opt + 1];
        
        bool assentoEscolhido = false;
        while(!assentoEscolhido){
            clearScreen();
            printf("\nVocê escolheu o filme: %s\n", filmeEscolhido.nomeDoFilme);
            printf("\n%s qual assento deseja?\n", client.nome);

            int assento ;
            switch (filmeEscolhido.salaDeExibição) {
                case 1:
                    assento = screenMovieTheater(&ticketsStack, mapa.itens[0].mapaDeAssentos);
                    break;
                case 2:
                    assento = screenMovieTheater(&ticketsStack, mapa.itens[1].mapaDeAssentos);
                    break;
                case 3:
                    assento = screenMovieTheater(&ticketsStack, mapa.itens[2].mapaDeAssentos);
                    break;
                case 4:
                    assento = screenMovieTheater(&ticketsStack, mapa.itens[3].mapaDeAssentos);
                    break;
                case 5:
                    assento = screenMovieTheater(&ticketsStack, mapa.itens[4].mapaDeAssentos);
                    break;
                default:
                    printf("Sala de exibição inválida.\n");
                    continue;
            }
            if(!verificarAssento(mapa.itens[filmeEscolhido.salaDeExibição - 1].mapaDeAssentos, assento)){
                clearScreen();
                Ticket ticket = addTicketToStack(&ticketsStack,client,filmeEscolhido,assento);
                screenTicket(ticket);

                bool validOption = true;

                while(validOption){
                    printf("\n\nO que deseja fazer agora?\n");
                    printf("1 - Listar as salas de exibição e os assentos disponíveis\n");
                    printf("2 - Listar os tickets vendidos\n");
                    printf("3 - Listar os clientes na fila de espera\n");
                    printf("4 - Ir para o próximo cliente\n");
                    int opt;
                    scanf("%d", &opt);
                    switch (opt) {
                        case 1:
                            clearScreen();
                            screenMovieTheaterMap(mapa);
                            break;
                        case 2:
                            clearScreen();
                            for (int i = 0; i <= ticketsStack.topo; i++) {
                                screenTicket(ticketsStack.itens[i]);
                            }
                            break;
                        case 3:
                            clearScreen();
                            for (int i = customerQueue.inicio; i <= customerQueue.fim; i++) {
                                printf("Cliente: %s, Idade: %d\n", customerQueue.itens[i].nome, customerQueue.itens[i].idade);
                            }
                            break;
                        case 4:
                            validOption = false;
                            break;
                        default:
                            printf("\nOpção inválida.\n");
                    }
                }
                assentoEscolhido = true;
            } else{
                printf("Assento já ocupado, por favor escolha outro assento.\n");
            }
        }
  
    }
}
