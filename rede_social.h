typedef struct Pessoa Pessoa;
typedef struct node node;
typedef struct Grafo Grafo;

typedef struct {
    int  id;
    char nome[50];
} Sessao;
int buscarIndicePorId(Grafo* grafo, int id);
node* criarNo(int valor);
Grafo* criarGrafo(int capacidadeInicial);
void crescerGrafo(Grafo* grafo);
int adicionarPessoa(Grafo* grafo, int id, char* nome, char* universidade, char* curso, char* senha, int qtd_interesses ,char (*interesses)[20]);
int buscarIndicePorId(Grafo* grafo, int id);
int arestaExiste(Grafo* grafo, int origem, int destino);
void addAmizade(Grafo* grafo, int s, int d);
void addAmizadePorId(Grafo* grafo, int id1, int id2);
void imprimirRede(Grafo* grafo);
void liberarGrafo(Grafo* grafo);

int fazerLogin(Grafo* grafo, const char* nome, const char* senha, Sessao* sessao);
void enviarPedidoAmizade(Grafo* grafo, int idRemetente, int idDestinatario);
void responderPedidoAmizade(Grafo* grafo, int idDestinatario, int idRemetente, int aceitar);
void imprimirPedidosPendentes(Grafo* grafo, int id);

