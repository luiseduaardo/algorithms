#include <bits/stdc++.h>
#include "../stack/stack_dll.hpp"
#include "../linked-list/linked_list.hpp"

using namespace std;

// O(n) para resolução da operação:
// os N elementos da LL são percorridos somente uma vez e as operações em si são constantes
void calcular_resultado(DoublyLinkedList<string> &n) {
    auto cur = n.get_first();

    while (cur) {
        string val = cur->value;

        if (val == "+" || val == "-" || val == "*" || val == "/" || val == "%" || val == "^") {
            auto node_op2 = cur->prev;
            auto node_op1 = node_op2->prev;

            double v1 = stod(node_op1->value);
            double v2 = stod(node_op2->value);
            double result = 0;

            if (val == "+") result = v1 + v2;
            else if (val == "-") result = v1 - v2;
            else if (val == "*") result = v1 * v2;
            else if (val == "/") result = v1 / v2;
            else if (val == "%") result = (int)v1 % (int)v2;
            else if (val == "^") result = pow(v1, v2);

            node_op1->value = std::to_string(result);
            node_op1->next = cur->next;

            if (cur->next) cur->next->prev = node_op1;
        }
        cur = cur->next;
    }
}

int main() {
    string expressao; cin >> expressao;

    Stack<char> operandos;
    DoublyLinkedList<string> notacao;

    // O(n) para transformar a expressão em notação polonesa reversa
    for (int i = 0; i < expressao.length(); i++) {
        char c = expressao[i];

        if (c >= '0' && c <= '9') {
            string s(1, c);
            notacao.insert(s);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            operandos.push(c);
        } else if (c == ')') {
            string s(1, operandos.top());
            notacao.insert(s);
            operandos.pop();
        }
    }

    notacao.print_list(); // printando a expressão antes de executar

    calcular_resultado(notacao);

    cout << notacao.get_first()->value << endl;

    return 0;
}
