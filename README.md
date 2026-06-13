# UniConnect - Rede Social Universitária

## Sobre o projeto

UniConnect é uma rede social simplificada para estudantes universitários, desenvolvida em linguagem C. O sistema permite:

- Gestão de contas (criar, login, editar perfil, eliminar conta);
- Sistema de amizades (pedidos, aceitar/recusar, amigos em comum);
- Recomendação de amigos com base em interesses, curso, universidade e amigos em comum;
- Sistema de mensagens privadas e chat;
- Feed com publicações, curtidas e comentários;
- Pesquisa de utilizadores por nome, universidade, curso, interesse e cidade;
- Estatísticas gerais da rede;
- Persistência de dados em ficheiros (`.dat`).

### Estruturas de dados aplicadas

| Estrutura | Uso |
|---|---|
| Grafos | Relações de amizade, amigos em comum, amigos de amigos |
| Tabelas Hash | Login e pesquisa por username - O(1) |
| Listas Ligadas | Interesses, pedidos de amizade, mensagens, publicações, comentários |
| Filas | Pedidos de amizade pendentes, notificações |
| Pilhas (opcional) | Histórico de ações / desfazer |

## Como rodar o projeto

### Pré-requisitos

- `gcc`
- `make`

### Comandos

```bash
make run     # compila e executa o programa
make         # apenas compila
make clean   # remove o executável gerado
```

## Como colaborar

1. Clona o repositório:
```bash
   git clone https://github.com/<utilizador>/ExameEDII_T1_G8.git
```
2. Cria uma branch para a tua alteração:
```bash
   git checkout -b minha-feature
```
3. Faz commit das alterações:
```bash
   git add .
   git commit -m "descrição da alteração"
```
4. Envia para o repositório remoto:
```bash
   git push origin minha-feature
```
5. Abre um Pull Request para revisão antes do merge na `main`.

## 👥 Colaboradores

Agradecemos às seguintes pessoas que contribuíram para este projeto:

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/erivaldocazinga22">
        <img src="https://github.com/erivaldomalebo.png" width="100px;" alt="Foto do Erivaldo no GitHub"/><br>
        <sub>
          <b>Erivaldo Caginga</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/IVANILDOALMEIDA">
        <img src="https://github.com/IVANILDOALMEIDA.png" width="100px;" alt="Foto do Ivanildo no GitHub"/><br>
        <sub>
          <b>Ivanildo Almeida</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Diangien">
        <img src="https://github.com/Diangien.png" width="100px;" alt="Foto do Diangien no GitHub"/><br>
        <sub>
          <b>Diangien</b>
        </sub>
      </a>
    </td>
  </tr>
</table>