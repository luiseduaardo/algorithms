#include <bits/stdc++.h>
#define endl '\n'
#define spc ' '
#define inf 2147483647
#define arr_sz 100000

using namespace std;

struct InfoProcessos {
    string id;
    int prio;
    int tempo;

    InfoProcessos() : id(""), prio(-inf), tempo(-inf) {}
    InfoProcessos(string identificador, int prioridade, int tempo_exec) : id(identificador), prio(prioridade), tempo(tempo_exec) {}

    bool operator<(const InfoProcessos& outro) const {
        if (prio != outro.prio) {
            return prio < outro.prio;
        }

        if (tempo != outro.tempo) {
            return tempo > outro.tempo;
        }

        return id > outro.id;
    }

    bool operator>(const InfoProcessos& outro) const {
        if (prio != outro.prio) {
            return prio > outro.prio;
        }

        if (tempo != outro.tempo) {
            return tempo < outro.tempo;
        }

        return id < outro.id;
    }
    
    bool operator==(const InfoProcessos& outro) const {
        return prio == outro.prio && tempo == outro.tempo && id == outro.id;
    }
};

class Heap {
private:
    InfoProcessos heap[arr_sz];
    int heap_size;

    void swap(InfoProcessos *p1, InfoProcessos *p2) {
        InfoProcessos temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

    int parent(int k) {
        return (k-1)/2;
    }

    int left_chd(int k) {
        return 2*k+1;
    }

    int right_chd(int k) {
        return 2*k+2;
    }

    void max_heapify(int idx) {
        int maior, l, r; l = left_chd(idx); r = right_chd(idx); maior = idx;

        if (l < heap_size && heap[l] > heap[maior]) {
            maior = l;
        }

        if (r < heap_size && heap[r] > heap[maior]) {
            maior = r;
        }

        if (maior != idx) {
            swap(&heap[maior], &heap[idx]);
            max_heapify(maior); // faz o max heapify no que foi trocado
        }
    }

    void increase_key(int idx, InfoProcessos val) {
        if (val < heap[idx]) return;

        heap[idx] = val;
        while (idx > 0 && heap[parent(idx)] < heap[idx]) {
            swap(&heap[parent(idx)], &heap[idx]);
            idx = parent(idx);
        }
    }

public:
    Heap() {
        heap_size = 0;
    }

    void build_max_heap() {
        for (int i = heap_size/2 - 1; i >= 0; i--) {
            max_heapify(i);
        }
    }

    void insert(InfoProcessos val) {
        heap[heap_size] = InfoProcessos();
        increase_key(heap_size, val);
        heap_size++;
    }

    InfoProcessos del_most_priority() {
        if (heap_size == 0) return InfoProcessos("IDLE", 0, 0);

        InfoProcessos todie = heap[0];
        swap(&heap[0], &heap[heap_size-1]);
        heap_size--;
        max_heapify(0);

        return todie;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Heap escalonador;
    int eventos; cin >> eventos;
    string op, id;
    int prioridade, tempo, boost;
    int global_boost = 0;

    while (eventos--) {
        cin >> op;

        if (op == "ADD") {
            cin >> id >> prioridade >> tempo;

            InfoProcessos novo = InfoProcessos(id, (prioridade - global_boost), tempo);
            escalonador.insert(novo);
        } else if (op == "RUN") {
            InfoProcessos removed = escalonador.del_most_priority();
            cout << removed.id << endl;
        } else if (op == "BOOST") {
            cin >> boost;
            global_boost += boost; // feito pro boost ocorrer em tempo constante - O(1)
        }
    }

    return 0;
}
