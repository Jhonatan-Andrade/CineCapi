# 🎬 CineCapi — Sistema de Venda de Ingressos

> Trabalho prático da disciplina de **Estruturas de Dados** (2026/1)  
> Universidade Tuiuti do Paraná — Prof. Baroni

---

## 📌 Sobre o projeto

O **CineCapi** é um sistema de gerenciamento de venda de ingressos de cinema implementado em **C**, usando as estruturas de dados de **pilha** e **fila** implementadas com vetores estáticos.

A ideia foi modelar o fluxo real de uma bilheteria:

```
Cliente chega → entra na fila → escolhe o filme → escolhe o assento
→ recebe o ingresso → vai para a fila de exibição da sala
```

---

## 🧠 Estruturas de Dados utilizadas

| Estrutura | Tipo | Para que serve |
|-----------|------|----------------|
| `MoviesStack` | Pilha (vetor) | Armazena os filmes disponíveis |
| `CustomerQueue` | Fila (vetor) | Fila de clientes esperando atendimento |
| `TicketStack` | Pilha (vetor) | Guarda os ingressos vendidos |
| `MovieTheater` | Matriz 2D | Mapa de assentos de cada sala |

---

## ⚙️ Funcionalidades

- [x] Preencher automaticamente a fila de clientes e a pilha de filmes
- [x] Vender ingresso: remove cliente da fila, reserva assento e gera ticket
- [x] Mapa visual de assentos por sala (livres e ocupados)
- [x] Listar todos os tickets vendidos
- [x] Listar clientes na fila de espera
- [x] Interface de texto interativa no terminal

---

## 🚀 Como compilar e executar

**Pré-requisito:** GCC instalado.

```bash
# Compilar
gcc main.c -o app

# Executar
./app
```

Ou em uma linha só:

```bash
gcc main.c -o app && ./app
```

---

## 🎯 Conceitos praticados

- **Pilha (Stack):** operações de `push` e `pop` com controle de `topo`
- **Fila (Queue):** operações de `enqueue` e `dequeue` com controle de `inicio` e `fim`
- **Matrizes 2D:** representação e manipulação do mapa de assentos
- **Structs em C:** organização de dados complexos (filme, cliente, ingresso, sala)
- **Modularização:** separação entre lógica de dados e funções de interface

---

## 📚 Contexto acadêmico

**Disciplina:** Estruturas de Dados  
**Período:** 2026/1  
**Instituição:** Universidade Tuiuti do Paraná  
**Professor:** Baroni