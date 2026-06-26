//
// Created by Diangienda on 21/06/2026.
//

#include "rede_social.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 50

struct Pessoa {
    int id;
    char nome[MAX];
    char universidade[MAX];
    char curso[MAX];
    char senha[MAX];
    char interesses[5][20];
    node* pedidosPendentes;
};

struct node {
    int vertice;
    node* prox;
};

struct Grafo {
    int numVertices;   
    int capacidade;     
    node** listaAdjacencias;
    Pessoa* pessoas;
};


int buscarIndicePorId(Grafo* grafo, int id);

node* criarNo(int valor) {
    node* novo = malloc(sizeof(node));
    if (!novo) {
        printf("Erro: sem memoria para criar no.\n");
        exit(1);
    }
    novo->vertice = valor;
    novo->prox = NULL;
    return novo;
}

Grafo* criarGrafo(int capacidadeInicial) {
    if (capacidadeInicial <= 0) {
        printf("Erro: capacidade inicial invalida.\n");
        exit(1);
    }

    Grafo* grafo = malloc(sizeof(Grafo));
    if (!grafo) {
        printf("Erro: sem memoria para criar o grafo.\n");
        exit(1);
    }

    grafo->numVertices = 0;
    grafo->capacidade = capacidadeInicial;
    grafo->listaAdjacencias = calloc(capacidadeInicial, sizeof(node*));
    grafo->pessoas = calloc(capacidadeInicial, sizeof(Pessoa)); 

    if (!grafo->listaAdjacencias || !grafo->pessoas) {
        printf("Erro: sem memoria para criar o grafo.\n");
        exit(1);
    }

    return grafo;
}


void crescerGrafo(Grafo* grafo) {
    int capacidadeAntiga = grafo->capacidade;
    int novaCapacidade = grafo->capacidade * 2;

    node** novaLista = realloc(grafo->listaAdjacencias, novaCapacidade * sizeof(node*));
    Pessoa* novasPessoas = realloc(grafo->pessoas, novaCapacidade * sizeof(Pessoa));

    if (!novaLista || !novasPessoas) {
        printf("Erro: sem memoria para crescer o grafo.\n");
        exit(1);
    }

    grafo->listaAdjacencias = novaLista;
    grafo->pessoas = novasPessoas;
    grafo->capacidade = novaCapacidade;

    for (int i = capacidadeAntiga; i < novaCapacidade; i++) {
        grafo->listaAdjacencias[i] = NULL;
        grafo->pessoas[i].pedidosPendentes = NULL; 
    }
}

int adicionarPessoa(Grafo* grafo, int id, char* nome, char* universidade, char* curso, char* senha, int qtd_interesses, char (*interesses)[20]) {
    if (buscarIndicePorId(grafo, id) != -1) {
        printf("Aviso: ja existe uma pessoa com id %d. Pessoa nao adicionada.\n", id);
        return -1;
    }

    if (grafo->numVertices == grafo->capacidade)
        crescerGrafo(grafo);

    int indice = grafo->numVertices;

    grafo->pessoas[indice].id = id;
    strncpy(grafo->pessoas[indice].nome, nome, MAX - 1);
    grafo->pessoas[indice].nome[MAX - 1] = '\0';

    strncpy(grafo->pessoas[indice].universidade, universidade, MAX - 1);
    grafo->pessoas[indice].universidade[MAX - 1] = '\0';

    strncpy(grafo->pessoas[indice].curso, curso, MAX - 1);
    grafo->pessoas[indice].curso[MAX - 1] = '\0';

    strncpy(grafo->pessoas[indice].senha, senha, MAX - 1);
    grafo->pessoas[indice].senha[MAX - 1] = '\0';

    for (int i = 0; i < qtd_interesses; i++) {
        strncpy(grafo->pessoas[indice].interesses[i], interesses[i], 19);
        grafo->pessoas[indice].interesses[i][19] = '\0';
    }

    grafo->pessoas[indice].pedidosPendentes = NULL;
    grafo->listaAdjacencias[indice] = NULL;
    grafo->numVertices++;

    return indice;
}


int buscarIndicePorId(Grafo* grafo, int id) {
    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->pessoas[i].id == id)
            return i;
    }
    return -1; 
}

int arestaExiste(Grafo* grafo, int origem, int destino) {
    node* atual = grafo->listaAdjacencias[origem];
    while (atual) {
        if (atual->vertice == destino)
            return 1;
        atual = atual->prox;
    }
    return 0;
}


void addAmizade(Grafo* grafo, int s, int d) {
    if (s < 0 || s >= grafo->numVertices || d < 0 || d >= grafo->numVertices) {
        printf("Aviso: vertice invalido. Amizade ignorada.\n");
        return;
    }
    if (arestaExiste(grafo, s, d)) {
        printf("Aviso: %s e %s ja sao amigos.\n", grafo->pessoas[s].nome, grafo->pessoas[d].nome);
        return;
    }

    node* novoNo = criarNo(d);
    novoNo->prox = grafo->listaAdjacencias[s];
    grafo->listaAdjacencias[s] = novoNo;

    novoNo = criarNo(s);
    novoNo->prox = grafo->listaAdjacencias[d];
    grafo->listaAdjacencias[d] = novoNo;
}


void addAmizadePorId(Grafo* grafo, int id1, int id2) {
    int s = buscarIndicePorId(grafo, id1);
    int d = buscarIndicePorId(grafo, id2);

    if (s == -1 || d == -1) {
        printf("Aviso: id %d ou %d nao existe. Amizade ignorada.\n", id1, id2);
        return;
    }
    addAmizade(grafo, s, d);
}

void imprimirRede(Grafo* grafo) {
    for (int v = 0; v < grafo->numVertices; v++) {
        printf("\n%s (id %d, %s) e amigo de: ",
               grafo->pessoas[v].nome, grafo->pessoas[v].id, grafo->pessoas[v].universidade);
        node* temp = grafo->listaAdjacencias[v];
        if (!temp) {
            printf("(ninguem ainda)");
        }
        while (temp) {
            printf("%s", grafo->pessoas[temp->vertice].nome);
            temp = temp->prox;
            if (temp) printf(", ");
        }
    }
    printf("\n");
}

void liberarGrafo(Grafo* grafo) {
    for (int v = 0; v < grafo->numVertices; v++) {
        
        node* atual = grafo->listaAdjacencias[v];
        while (atual) {
            node* temp = atual;
            atual = atual->prox;
            free(temp);
        }
       
        atual = grafo->pessoas[v].pedidosPendentes;
        while (atual) {
            node* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(grafo->listaAdjacencias);
    free(grafo->pessoas);
    free(grafo);
}

static int noExisteNaLista(node* cabeca, int valor) {
    while (cabeca) {
        if (cabeca->vertice == valor) return 1;
        cabeca = cabeca->prox;
    }
    return 0;
}

static node* removerDaLista(node* cabeca, int valor) {
    node* anterior = NULL;
    node* atual = cabeca;
    while (atual) {
        if (atual->vertice == valor) {
            if (anterior) anterior->prox = atual->prox;
            else cabeca = atual->prox;
            free(atual);
            return cabeca;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return cabeca; 
}

void enviarPedidoAmizade(Grafo* grafo, int idRemetente, int idDestinatario) {
    int r = buscarIndicePorId(grafo, idRemetente);
    int d = buscarIndicePorId(grafo, idDestinatario);

    if (r == -1 || d == -1) {
        printf("Aviso: id %d ou %d nao existe. Pedido ignorado.\n", idRemetente, idDestinatario);
        return;
    }
    if (r == d) {
        printf("Aviso: %s nao pode enviar pedido para si proprio.\n", grafo->pessoas[r].nome);
        return;
    }
    if (arestaExiste(grafo, r, d)) {
        printf("Aviso: %s e %s ja sao amigos.\n", grafo->pessoas[r].nome, grafo->pessoas[d].nome);
        return;
    }
    if (noExisteNaLista(grafo->pessoas[d].pedidosPendentes, r)) {
        printf("Aviso: %s ja enviou um pedido de amizade a %s.\n",
               grafo->pessoas[r].nome, grafo->pessoas[d].nome);
        return;
    }


    if (noExisteNaLista(grafo->pessoas[r].pedidosPendentes, d)) {
        printf("Info: %s ja tinha um pedido pendente de %s. Amizade confirmada automaticamente!\n",
               grafo->pessoas[r].nome, grafo->pessoas[d].nome);
        grafo->pessoas[r].pedidosPendentes =
            removerDaLista(grafo->pessoas[r].pedidosPendentes, d);
        addAmizade(grafo, r, d);
        return;
    }

 
    node* pedido = criarNo(r);
    pedido->prox = grafo->pessoas[d].pedidosPendentes;
    grafo->pessoas[d].pedidosPendentes = pedido;

    printf("Pedido de amizade enviado de %s para %s.\n",
           grafo->pessoas[r].nome, grafo->pessoas[d].nome);
}

void responderPedidoAmizade(Grafo* grafo, int idDestinatario, int idRemetente, int aceitar) {
    int d = buscarIndicePorId(grafo, idDestinatario);
    int r = buscarIndicePorId(grafo, idRemetente);

    if (d == -1 || r == -1) {
        printf("Aviso: id invalido. Resposta ignorada.\n");
        return;
    }
    if (!noExisteNaLista(grafo->pessoas[d].pedidosPendentes, r)) {
        printf("Aviso: %s nao tem nenhum pedido pendente de %s.\n",
               grafo->pessoas[d].nome, grafo->pessoas[r].nome);
        return;
    }

    grafo->pessoas[d].pedidosPendentes =
        removerDaLista(grafo->pessoas[d].pedidosPendentes, r);

    if (aceitar) {
        addAmizade(grafo, d, r);
        printf("%s aceitou o pedido de amizade de %s. Sao agora amigos!\n",
               grafo->pessoas[d].nome, grafo->pessoas[r].nome);
    } else {
        printf("%s recusou o pedido de amizade de %s.\n",
               grafo->pessoas[d].nome, grafo->pessoas[r].nome);
    }
}


void imprimirPedidosPendentes(Grafo* grafo, int id) {
    int idx = buscarIndicePorId(grafo, id);
    if (idx == -1) { printf("Aviso: id %d nao existe.\n", id); return; }

    printf("Pedidos pendentes de %s: ", grafo->pessoas[idx].nome);
    node* p = grafo->pessoas[idx].pedidosPendentes;
    if (!p) { printf("(nenhum)\n"); return; }
    while (p) {
        printf("%s", grafo->pessoas[p->vertice].nome);
        p = p->prox;
        if (p) printf(", ");
    }
    printf("\n");
}

int fazerLogin(Grafo* grafo, const char* nome, const char* senha, Sessao* sessao) {
    for (int i = 0; i < grafo->numVertices; i++) {
        if (strcmp(grafo->pessoas[i].nome,  nome)  == 0 &&
            strcmp(grafo->pessoas[i].senha, senha) == 0) {
            sessao->id = grafo->pessoas[i].id;
            strncpy(sessao->nome, grafo->pessoas[i].nome, 49);
            sessao->nome[49] = '\0';
            return 1; 
        }
    }
    return 0; 
}
