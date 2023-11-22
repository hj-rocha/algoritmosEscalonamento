#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

class Processo {
private:
    int ID;
    static int sID;
    int quantum;
    int fila;

public:
    Processo() : ID(0), quantum(0), fila(0) {}
    Processo(int quantum) : quantum(quantum), fila(1) {
        ID = sID++;
    }

    int getFila() const {
        return fila;
    }

    int getId() const {
        return ID;
    }

    int getQuantum() const {
        return quantum;
    }

    void setFila(int novaFila) {
        fila = novaFila;
    }

    void setQuantum(int novoQuantum) {
        quantum = novoQuantum;
    }

    void executar(int tempo) {
        quantum -= tempo;
        if (quantum <= 0) {
            cout << "Processo " << ID << " Finalizado\n";
        } else if (fila != 3) {
            fila++;
        }
    }

    bool emEspera() const {
        return (rand() % 2 == 1 && quantum > 0);
    }
};

int Processo::sID = 0;


class Escalonador {
private:
    queue<Processo> Fila8;
    queue<Processo> Fila16;
    queue<Processo> Fila32;
    vector<Processo> ListaEspera;
    vector<Processo> ListaFinalizados;
    Processo a;

public:
    void criarProcessos(int nProcessos) {
        for (int i = 0; i < nProcessos; i++) {
            Processo p(rand() % 64 + 1);
            cout << p.getId() << ": Quantum=" << p.getQuantum() << endl;
            Fila8.push(p);
        }
    }

    void escolherFila() {
        if (!ListaEspera.empty()) {
            if (rand() % 2 == 1) {
                int escolhido = rand() % ListaEspera.size();
                a = ListaEspera[escolhido];
                ListaEspera.erase(ListaEspera.begin() + escolhido);

                if (a.getFila() == 2) {
                    Fila16.push(a);
                    cout << "Processo " << a.getId() << " saiu do estado de espera e retornou p fila de 16 Quantum." << endl;
                } else if (a.getFila() == 3) {
                    Fila32.push(a);
                    cout << "Processo " << a.getId() << " saiu do estado de espera e retornou p fila de 32 Quantum." << endl;
                }
            }
        }

        if (!Fila8.empty()) {
            a = Fila8.front();
            Fila8.pop();
            cout << "Processo " << a.getId() << " saiu da fila de 8 Quantums"  << endl;
        } else if (!Fila16.empty()) {
            a = Fila16.front();
            Fila16.pop();
            cout << "Processo " << a.getId() << " saiu da fila de 16 Quantums"  << endl;
        } else if (!Fila32.empty()) {
            a = Fila32.front();
            Fila32.pop();
            cout << "Processo " << a.getId() << " saiu da fila de 32 Quantums" << endl;
        } else if (ListaEspera.empty()) {
            cout << "Todos os processos finalizados" << endl;
        }
    }

    void executarProcesso() {
        if (a.getFila() == 1) {
            a.executar(8);
            cout << "Quantums atual: " << a.getQuantum() << endl;
        } else if (a.getFila() == 2) {
            a.executar(16);
            cout << "Quantums atual: " << a.getQuantum() << endl;
        } else if (a.getFila() == 3) {
            a.executar(32);
            cout << "Quantums atual: " << a.getQuantum() << endl;
        }

        if (a.getQuantum() <= 0) {
            ListaFinalizados.push_back(a);
        } else if (a.emEspera()) {
            cout << "Processo " << a.getId() << " entrou em estado de espera." << endl;
            ListaEspera.push_back(a);
        } else if (a.getFila() == 2) {
            Fila16.push(a);
        } else if (a.getFila() == 3) {
            Fila32.push(a);
        }
    }

    void run(int nProcessos) {
        criarProcessos(nProcessos);
        while (ListaFinalizados.size() != nProcessos) {
            escolherFila();
            executarProcesso();
        }
    }
};

int main() {
    srand(time(0));
    const int N_PROCESSOS = 5;

    Escalonador escalonador;
    escalonador.run(N_PROCESSOS);

    return 0;
}
