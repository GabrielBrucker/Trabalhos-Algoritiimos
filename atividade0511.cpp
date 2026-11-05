// Atividade da Aula 05/11 - Sessoes de Telefonia
// Linguagem: C++
// Objetivo: carregar, listar e pesquisar registros de telefonia.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

typedef struct {
    string numeroCelular;
    string dadosSessao;
} Telefone;

// Le a base de dados e armazena cada registro no vetor.
bool carregarBase(vector<Telefone> &listaSessoes, const string &nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return false;
    }

    listaSessoes.clear();
    string linha;

    while (getline(arquivo, linha)) {
        // Cada linha tem o formato: numeroCelular;{dados da sessao}
        size_t posicao = linha.find(';');

        if (posicao == string::npos) {
            continue; // Ignora linhas vazias ou sem o separador.
        }

        Telefone registro;
        registro.numeroCelular = linha.substr(0, posicao);
        registro.dadosSessao = linha.substr(posicao + 1);

        if (!registro.numeroCelular.empty() && !registro.dadosSessao.empty()) {
            listaSessoes.push_back(registro);
        }
    }

    arquivo.close();
    return true;
}

// Opcao 1: mostra todos os numeros e a quantidade de registros.
void listarTelefones(const vector<Telefone> &listaSessoes) {
    cout << "\n===== LISTA DE TELEFONES =====\n";
    cout << "Quantidade de registros: " << listaSessoes.size() << "\n\n";

    for (size_t i = 0; i < listaSessoes.size(); i++) {
        cout << (i + 1) << " - " << listaSessoes[i].numeroCelular << '\n';
    }

    if (listaSessoes.empty()) {
        cout << "Nenhum telefone cadastrado.\n";
    }
}

// Metodo reutilizavel para exibir os dados de um registro.
void mostrarRegistro(const Telefone &registro) {
    cout << "Numero de celular: " << registro.numeroCelular << '\n';
    cout << "Dados da sessao: " << registro.dadosSessao << "\n\n";
}

// Opcao 2: procura um numero e mostra todas as sessoes correspondentes.
void pesquisarTelefone(const vector<Telefone> &listaSessoes, const string &numero) {
    int quantidadeEncontrada = 0;

    for (size_t i = 0; i < listaSessoes.size(); i++) {
        if (listaSessoes[i].numeroCelular == numero) {
            mostrarRegistro(listaSessoes[i]);
            quantidadeEncontrada++;
        }
    }

    if (quantidadeEncontrada == 0) {
        cout << "Telefone nao encontrado na base.\n";
    } else {
        cout << "Sessoes encontradas: " << quantidadeEncontrada << '\n';
    }
}

void mostrarMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1 - Listar telefones\n";
    cout << "2 - Pesquisar telefone e dados da sessao\n";
    cout << "3 - Finalizar\n";
    cout << "Opcao: ";
}

int main(int argc, char *argv[]) {
    vector<Telefone> listaSessoes;
    string nomeArquivo = "telephony_sessions.txt";

    // Opcional: passar o caminho da base como argumento ao executar.
    if (argc > 1) {
        nomeArquivo = argv[1];
    }

    if (!carregarBase(listaSessoes, nomeArquivo)) {
        cout << "Erro: nao foi possivel abrir o arquivo " << nomeArquivo << ".\n";
        cout << "Coloque telephony_sessions.txt na mesma pasta de execucao do programa.\n";
        return 1;
    }

    cout << "Base carregada com sucesso!\n";
    cout << "Total de registros: " << listaSessoes.size() << '\n';

    int opcao;
    string numero;

    do {
        mostrarMenu();

        if (!(cin >> opcao)) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida! Digite 1, 2 ou 3.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1:
                listarTelefones(listaSessoes);
                break;

            case 2:
                cout << "Digite o numero de telefone: ";
                getline(cin, numero);
                pesquisarTelefone(listaSessoes, numero);
                break;

            case 3:
                cout << "Obrigado por usar o sistema!\n";
                break;

            default:
                cout << "Opcao invalida! Digite 1, 2 ou 3.\n";
                break;
        }
    } while (opcao != 3);

    return 0;
}
