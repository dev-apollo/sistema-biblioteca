#include "gerenciamento_biblioteca.hpp"
using namespace std;

int main(){
    vector<livro> biblioteca;
    vector<usuario> usuarios;
    biblioteca.push_back(cadastrarLivro("O Iluminado", "Stephen King", 1977, 12));
    biblioteca.push_back(cadastrarLivro("A Hora do Lobisomem", "Stephen King", 1983, 5));
    biblioteca.push_back(cadastrarLivro("O Cemiterio", "Stephen King", 1983, 7));
    biblioteca.push_back(cadastrarLivro("O Fisico Prodigioso", "Jorge de Sena", 1977, 4));
    biblioteca.push_back(cadastrarLivro("Os Tambores Silenciosos", "Josue Guimaraes", 1977, 13));
    usuarios.push_back(cadastrarUsuario("Beatriz Pimentel"));
    usuarios.push_back(cadastrarUsuario("Felix Depa"));
    usuarios.push_back(cadastrarUsuario("Gabriel Alexandre"));
    emprestarLivro(usuarios[0], biblioteca[3], false);
    emprestarLivro(usuarios[1], biblioteca[0], false);
    emprestarLivro(usuarios[2], biblioteca[3], false);
    bool rodando = true;
    do{
        int opcao;
        menu();
        cout<<"[0] - Sair"<<endl;
        cout<<"Insira uma das opcoes acima: ";
        cin>>opcao;
        switch(opcao){
            case 0: {
                cout<<"Saindo...";
                rodando = false;
                break;
            }
            case 1: {
                biblioteca.push_back(solicitarInfosLivros());
                break;
            }
            case 2: {
                usuarios.push_back(solicitarInfosUsuarios());
                break;
            }
            case 3: {
                solicitarInfosEmprestimo(usuarios, biblioteca);
                break;
            }
            case 4: {
                devolverLivro(usuarios, biblioteca);
                break;
            }
            case 5: {
                pesquisarLivro(biblioteca);
                break;
            }
            case 6: {
                int id;
                cout<<"Insira o ID do usuario pelo qual deseja buscar os livros: ";
                cin>>id;
                pesquisarLivroPUsuario(id, usuarios);
                break;
            }
            case 7: {
                listarLivros(biblioteca);
                break;
            }
            case 8: {
                exibirEstatisticas(usuarios, biblioteca);
                break;
            }
            case 9: {
                listarUsuarios(usuarios);
                break;
            }
        }
    }while(rodando);
}