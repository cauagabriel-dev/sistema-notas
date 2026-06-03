#include <iostream>
#include <string>
#include <windows.h>
#include <fstream> // Serve para trabalhar com arquivos
#include <ctime>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);

    // Entrada - Declaração das Variáveis
    string nomes[20];
    int qtdAlunos = 0;
    float notas[20][5];
    float media[20];
    int qtdDisciplinas = 0;
    int opcaoInicial;

    // Variáveis para eu iniciar o switch
    int aprovados = 0, recuperacao = 0, reprovados = 0;

    // LEITURA DE ALUNOS (Commit 1)
    cout << "=== SISTEMA DE NOTAS v4.0 ===" << endl;
    cout << "1 - Novo relatório" << endl;
    cout << "2 - Ver relatório salvos" << endl;
    cout << "3 - Sobre o sistema" << endl;
    cout << "4 - Sair" << endl;
    cout << "Escolha uma opção: ";
    cin >> opcaoInicial;

    // Processamento
    switch (opcaoInicial)
    {
    case 1:
        do
        {
            cout << "\nQuantidade de alunos (1 a 20): ";
            cin >> qtdAlunos;
        } while (qtdAlunos < 1 || qtdAlunos > 20);

        cin.ignore();

        for (int i = 0; i < qtdAlunos; i++)
        {
            cout << "Nome do aluno " << i + 1 << ": ";
            getline(cin, nomes[i]);
        }

        // NOTAS E MÉDIAS (Commit 2)
        do
        {
            cout << "\nQuantidade de disciplinas (1 a 5): ";
            cin >> qtdDisciplinas;
        } while (qtdDisciplinas < 1 || qtdDisciplinas > 5);

        for (int i = 0; i < qtdAlunos; i++)
        {
            cout << "\nNotas de " << nomes[i] << ": " << endl;
            float soma = 0;
            for (int j = 0; j < qtdDisciplinas; j++)
            {
                do
                {
                    cout << "Disciplina " << j + 1 << " (Nota de 0 a 10): ";
                    cin >> notas[i][j];
                } while (notas[i][j] < 0 || notas[i][j] > 10);
                soma += notas[i][j];
            }
            media[i] = soma / qtdDisciplinas;
        }

        // CLASSIFICAÇÃO E RELATÓRIO (Commit 3)
        cout << "\n=== RELATÓRIO ===" << endl;
        aprovados = 0;
        recuperacao = 0;
        reprovados = 0;

        for (int i = 0; i < qtdAlunos; i++)
        {
            cout << nomes[i] << " - Media: " << media[i] << " - ";
            if (media[i] >= 7)
            {
                cout << "Aprovado" << endl;
                aprovados++;
            }
            else if (media[i] >= 5)
            {
                cout << "Recuperação" << endl;
                recuperacao++;
            }
            else
            {
                cout << "Reprovado" << endl;
                reprovados++;
            }
        }
        cout << "\nResumo: " << aprovados << " aprovados, " << recuperacao << " em recuperação, " << reprovados << " reprovados." << endl;

        // SALVAR EM ARQUIVO (Commit 4)
        {
            ofstream arquivo("relatorio.txt");
            if (arquivo.is_open())
            {
                arquivo << "==== RELATÓRIO ====" << endl;
                
                time_t agora = time(0);
                char *dataHora = ctime(&agora);
                arquivo << "Data do relatorio: " << dataHora << endl;

                for (int i = 0; i < qtdAlunos; i++)
                {
                    arquivo << nomes[i] << " - Média: " << media[i] << " - ";
                    if (media[i] >= 7)
                        arquivo << "Aprovado" << endl;
                    else if (media[i] >= 5)
                        arquivo << "Recuperação" << endl;
                    else
                        arquivo << "Reprovado" << endl;
                }
                arquivo << "\nResumo: " << aprovados << " aprovados, " << recuperacao << " em recuperação, " << reprovados << " reprovados." << endl;
                arquivo.close();
                cout << "\nRelatório salvo com sucesso em relatorio.txt!" << endl;
            }
            else
            {
                cout << "Erro ao criar arquivo." << endl;
            }
        }
        break;

    case 2:
        // LEITURA E ARQUIVO (Commit 5)
        {
            ifstream leitura("relatorio.txt");
            if (leitura.is_open())
            {
                string linha;
                cout << "\n=== LENDO RELATÓRIO SALVO ===" << endl;
                while (getline(leitura, linha))
                {
                    cout << linha << endl;
                }
                leitura.close();
            }
            else
            {
                cout << "\nNenhum relatório encontrado. Crie um novo primeiro (Opção 1)." << endl;
            }
        }
        break;

    case 3:
        // SOBRE O SISTEMA (Commit 6)
        cout << "\n=== SOBRE ===" << endl;
        cout << "Sistema de Notas v4.1" << endl;
        cout << "Desenvolvido por: Cauã Gabriel" << endl;
        cout << "Turma: LOPAL 2026 - SENAI-SP" << endl;
        break;

    case 4:
        cout << "\nSaindo... Até logo!" << endl;
        break;

    default:
        cout << "\nOpção inválida!" << endl;
        break;
    }

    return 0;
}