#include "gerenciamento_biblioteca.hpp"
using namespace std;

livro solicitarInfosLivros(){
    string titulo, autor;
    int publicacao, copias;
    cout<<"Insira o titulo do livro: ";
    cin.ignore();
    getline(cin, titulo);
    cout<<"Insira o autor do livro: ";
    getline(cin, autor);
    cout<<"Insira o ano de publicacao do livro: ";
    cin>>publicacao;
    do{
        cout<<"Insira a quantidade de copias do livro: ";
        cin>>copias;
    }while(copias < 1);
    return cadastrarLivro(titulo, autor, publicacao, copias);
}

livro cadastrarLivro(string titulo, string autor, int publicacao, int copias){
    livro novoLivro;
    novoLivro.titulo = titulo;
    novoLivro.autor = autor;
    novoLivro.publicacao = publicacao;
    novoLivro.copias = copias;
    novoLivro.vzsEmprestado = 0;
    return novoLivro;
}

usuario solicitarInfosUsuarios()
{
    string nome;
    cout<<"Insira o nome do usuario: ";
    cin.ignore();
    getline(cin, nome);
    return cadastrarUsuario(nome);

}

usuario cadastrarUsuario(string nome)
{
    usuario novoUsuario;
    novoUsuario.nome = nome;
    novoUsuario.id = rand()%9000+1000;
    novoUsuario.multas = 0;
    return novoUsuario;
}

void solicitarInfosEmprestimo(vector<usuario> &usuarios, vector<livro> &biblioteca)
{
    int idUsuario;
    string tituloDoLivro;
    usuario usuarioEspecifico;
    livro livroEspecifico;
    bool idExiste = false, tituloExiste = false;
    do{
        cout<<"Insira o ID do usuario: ";
        cin>>idUsuario;
        for(int i = 0; i < usuarios.size(); i++){
            if(idUsuario == usuarios[i].id){
                idExiste = true;
                usuarioEspecifico = usuarios[i];
                break;
            }
        }
        if(!idExiste){
            cout<<"Usuario nao encontrado. Verifique se escreveu corretamente."<<endl;
        }
    }while(!idExiste);
    bool podeEmprestar;
    for(int i = 0; i < usuarioEspecifico.historico.size(); i++){
        if(usuarioEspecifico.historico[i].emprestimoAtual == true){
            podeEmprestar = false;
            break;
        }else{
            podeEmprestar = true;
        }
    }
    if(podeEmprestar){
        do{
            cout<<"Insira o titulo do livro: ";
            cin.ignore();
            getline(cin, tituloDoLivro);
            for(int i = 0; i < biblioteca.size(); i++){
                if(tituloDoLivro == biblioteca[i].titulo){
                    tituloExiste = true;
                    livroEspecifico = biblioteca[i];
                    break;
                }
            }
            if(!tituloExiste){
                cout<<"Livro nao encontrado. Verifique se escreveu corretamente."<<endl;
            }
        }while(!tituloExiste);
        emprestarLivro(usuarioEspecifico, livroEspecifico, true);
    }else{
        cout<<"O usuario ja possui um livro em sua posse, ele precisa devolver esse para poder pegar outro."<<endl;
    }
}

void emprestarLivro(usuario &usuarioEspecifico, livro &livroEspecifico, bool mensagem)
{
    emprestimo novoEmprestimo;
    novoEmprestimo.livro = livroEspecifico;
    novoEmprestimo.emprestimoAtual = true;
    novoEmprestimo.dataEmprestimo = time(NULL);
    novoEmprestimo.dataDevolucao = novoEmprestimo.dataEmprestimo + 4*24*60*60;
    tm *dataExibir = localtime(&novoEmprestimo.dataDevolucao);
    if(mensagem){
        cout<<"O livro "<<novoEmprestimo.livro.titulo<<" tem que ser devolvido no dia: "<<dataExibir->tm_mday<<"/"<<dataExibir->tm_mon+1<<"/"<<dataExibir->tm_year+1900<<endl;
        cout << "Para cada dia de atraso, sera cobrado R$20,00" << endl;
    }
    livroEspecifico.copias--;
    livroEspecifico.vzsEmprestado++;
    usuarioEspecifico.historico.push_back(novoEmprestimo);
}

void devolverLivro(vector<usuario> &usuarios, vector<livro> &biblioteca)
{
    int i;
    int idUsuario;
    usuario usuarioEspecifico;
    bool idExiste = false;
    do{
        cout<<"Insira o ID do usuario: ";
        cin>>idUsuario;
        for(i = 0; i < usuarios.size(); i++){
            if(idUsuario == usuarios[i].id){
                idExiste = true;
                break;
            }
        }
        if(!idExiste){
            cout<<"Usuario nao encontrado. Verifique se escreveu corretamente."<<endl;
        }
    }while(!idExiste);
    for(int j = 0; j < usuarios[i].historico.size(); j++){
        if(usuarios[i].historico[j].emprestimoAtual == true){
            usuarios[i].historico[j].emprestimoAtual = false;
            for(int k = 0; k < biblioteca.size(); k++){
                if(usuarios[i].historico[j].livro.titulo == biblioteca[k].titulo){
                    biblioteca[k].copias++;
                    break;
                }
            }
            if(usuarios[i].historico[j].dataDevolucao < time(NULL)){
                usuarios[i].multas += 20*(difftime(time(NULL), usuarios[i].historico[j].dataDevolucao)/86400);
                cout<< "Multa a pagar: " <<usuarios[i].multas<<endl;
                
            }
            break;
        }
    }
    cout<<"Livro devolvido!"<<endl;
}

void listarUsuarios(vector<usuario> &usuarios)
{
    for(int i = 0; i < usuarios.size(); i++){
        cout<<"ID: "<<usuarios[i].id<<endl;
        cout<<"Nome: "<<usuarios[i].nome<<endl;
    }
}

void pesquisarLivro(vector<livro> &biblioteca)
{
    int contador = 0;
    bool achou = false;
    string pesquisa;
    cout << "Insira o nome do livro, autor ou ano de publicacao para pesquisar: ";
    cin.ignore();
    getline(cin, pesquisa);
    cout << "Livro(os) encontrado(os): " << endl;
    for(int i = 0; i < biblioteca.size(); i++){
         if(pesquisa == biblioteca[i].titulo || pesquisa == biblioteca[i].autor){
            cout<<"Titulo: "<<biblioteca[i].titulo<<endl;
            cout<<"Autor: "<<biblioteca[i].autor<<endl;
            cout<<"Ano de Publicacao: "<<biblioteca[i].publicacao<<endl;
            cout<<"Copias disponiveis: "<<biblioteca[i].copias<<endl;
            contador++;
         }else{
            for(char c: pesquisa){
                if(isdigit(c)){
                    achou = true;
                    break;
                }
            }
            if(achou == true){
                if(stoi(pesquisa) == biblioteca[i].publicacao){
                cout<<"Titulo: "<<biblioteca[i].titulo<<endl;
                cout<<"Autor: "<<biblioteca[i].autor<<endl;
                cout<<"Ano de Publicacao: "<<biblioteca[i].publicacao<<endl;
                cout<<"Copias disponiveis: "<<biblioteca[i].copias<<endl;
                contador++;
                }
            }
         }
    }
    if(contador == 0){
        cout<<"Nenhum livro."<<endl;
    }
     cout<<endl;
}

void pesquisarLivroPUsuario(int id, vector<usuario> &usuarios){
    for(int i = 0; i < usuarios.size(); i++){
        if(usuarios[i].id == id){
            int contador = 0;
            cout<<"O usuario "<<usuarios[i].nome<<" tem os seguintes livros alugados: "<<endl;
            for(int j = 0; j < usuarios[i].historico.size(); j++){
                if(usuarios[i].historico[j].emprestimoAtual){
                    cout<<usuarios[i].historico[j].livro.titulo<<endl;
                    contador++;
                }
            }
            if(contador == 0){
                cout<<"Nenhum livro."<<endl;
            }
            break;
        }
    }
}

void listarLivros(vector<livro> &biblioteca)
{
    for(int i = 0; i < biblioteca.size(); i++){
        cout<<"Titulo: "<<biblioteca[i].titulo<<endl;
        cout<<"Autor: "<<biblioteca[i].autor<<endl;
        cout<<"Ano de Publicacao: "<<biblioteca[i].publicacao<<endl;
        cout<<"Quantidade de copias disponiveis: "<<biblioteca[i].copias<<endl;
    }
}

void exibirEstatisticas(vector<usuario> &usuarios, vector<livro> &biblioteca)
{
    int totalEmprestimos = 0;
    int totalEmprestimosAtivos = 0;
    int usuarioMaisAtivoValor = 0;
    string usuarioMaisAtivoNome;
    int livroPopularValor = 0;
    string livroPopularNome;
    int usuarioCaloteiroValor = 0;
    string usuarioCaloteiroNome = "Nenhum usuario";
    int qntLivrosAtrasados = 0;
    for(int i = 0; i < usuarios.size(); i++){
        for(int j = 0; j < usuarios[i].historico.size(); j++){
            if(usuarios[i].historico[j].emprestimoAtual){
                totalEmprestimosAtivos++;
                if(difftime(time(NULL), usuarios[i].historico[j].dataDevolucao)/86400 > 0){
                    qntLivrosAtrasados++;
                }
            }
        }
        totalEmprestimos+=usuarios[i].historico.size();
        if(usuarios[i].historico.size() > usuarioMaisAtivoValor){
            usuarioMaisAtivoValor = usuarios[i].historico.size();
            usuarioMaisAtivoNome = usuarios[i].nome;
        }
        if(usuarioCaloteiroValor < usuarios[i].multas && usuarios[i].multas > 0){
            usuarioCaloteiroValor = usuarios[i].multas;
            usuarioCaloteiroNome = usuarios[i].nome;
        }
    }
    for(int i = 0; i < biblioteca.size(); i++){
          if(biblioteca[i].vzsEmprestado > livroPopularValor){
            livroPopularValor = biblioteca[i].vzsEmprestado;
            livroPopularNome = biblioteca[i].titulo;
        }      
    }
    cout<<"Usuario mais ativo do sistema: "<<usuarioMaisAtivoNome<<endl;
    cout<<"Total de emprestimos: "<<totalEmprestimos<<endl;
    cout<<"Total de emprestimos ativos: "<<totalEmprestimosAtivos<<endl;
    cout<<"Livro mais popular: "<<livroPopularNome<<endl;
    cout<<"O maior caloteiro da biblioteca: "<<usuarioCaloteiroNome<<endl;
    cout<<"Quantidade de livros em atraso: "<<qntLivrosAtrasados<<endl;
}

void menu(){
    cout<<"[1] - Cadastrar Livro"<<endl;
    cout<<"[2] - Cadastrar Usuario"<<endl;
    cout<<"[3] - Emprestar Livro"<<endl;
    cout<<"[4] - Devolver Livro"<<endl;
    cout<<"[5] - Pesquisar Livro"<<endl;
    cout<<"[6] - Pesquisar Livro por Usuario"<<endl;
    cout<<"[7] - Listar Livros"<<endl;
    cout<<"[8] - Relatorio de Emprestimo"<<endl;
    cout<<"[9] - Listar usuarios"<<endl;
}

