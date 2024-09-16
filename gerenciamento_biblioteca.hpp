#ifndef GERENCIAMENTO_BIBLIOTECA_HPP
#define GERENCIAMENTO_BIBLIOTECA_HPP
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <ctime>
using namespace std;

struct livro
{
    string titulo;
    string autor;
    int publicacao;
    int copias;
    int vzsEmprestado;
};

struct emprestimo
{
    livro livro;
    time_t dataEmprestimo;
    time_t dataDevolucao;
    bool emprestimoAtual;
};


struct usuario 
{
    int id;
    string nome;
    vector<emprestimo> historico;
    int multas;

};

livro solicitarInfosLivros();
livro cadastrarLivro(string titulo, string autor, int publicacao, int copias);
usuario solicitarInfosUsuarios();
usuario cadastrarUsuario(string nome);
void solicitarInfosEmprestimo(vector<usuario> &usuarios, vector<livro> &biblioteca);
void emprestarLivro(usuario &usuarioEspecifico, livro &livroEspecifico, bool mensagem);
void devolverLivro(vector<usuario> &usuarios, vector<livro> &biblioteca);
void listarUsuarios(vector<usuario> &usuarios);
void pesquisarLivro(vector<livro> &biblioteca);
void pesquisarLivroPUsuario(int id, vector<usuario> &usuarios);
void listarLivros(vector<livro> &biblioteca);
void exibirEstatisticas(vector<usuario> &usuarios, vector<livro> &biblioteca);
void menu();
#endif
