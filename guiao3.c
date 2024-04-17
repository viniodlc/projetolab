#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

char ultimoDigitoUTF8(wchar_t carta) {
    int mascara = 0xF;
    int ultimo_digito = carta & mascara;
    if (ultimo_digito >= 0 && ultimo_digito <= 9) {
        return '0' + ultimo_digito;
    } else if (ultimo_digito >= 0xA && ultimo_digito <= 0xE) {
        return 'A' + (ultimo_digito - 0xA);
    } else {
        return '\0';
    }
}

void ordena(wchar_t *cartas) {
    int tamanho = wcslen(cartas);
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            char ultimo_digito_i = ultimoDigitoUTF8(cartas[i]);
            char ultimo_digito_j = ultimoDigitoUTF8(cartas[j]);
            if (ultimo_digito_i > ultimo_digito_j ||
                (ultimo_digito_i == ultimo_digito_j && cartas[i] > cartas[j])) {
                wchar_t temp = cartas[i];
                cartas[i] = cartas[j];
                cartas[j] = temp;
            }
        }
    }
}

int comparar_cartas(const void *a, const void *b) {
    return wcscoll((const wchar_t *)a, (const wchar_t *)b);
}

void ordenar_mao(wchar_t mao[]) {
    int len = wcslen(mao);
    ordena(mao); // Ordena as cartas antes de imprimir
    for (int i = 0; i < len; i++) {
        if (i > 0) {
            wprintf(L" ");
        }
        wprintf(L"%lc", mao[i]);
    }
    wprintf(L"\n");
}

int jogada_valida(const wchar_t mao[], const wchar_t jogada[]) {
    int len_jogada = wcslen(jogada);
    
    for (int i = 0; i < len_jogada; i++) {
        if (wcschr(mao, jogada[i]) == NULL) {
            return 0; // Jogada inválida
        }
    }
    
    return 1; // Jogada válida
}

void realizar_jogada(wchar_t mao[], const wchar_t jogada[]) {
    for (int i = 0; jogada[i] != L'\0'; i++) {
        wchar_t *pos = wcsstr(mao, &jogada[i]);
        if (pos != NULL) {
            wcscpy(pos, pos + 1);
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");

    int T;
    if (wscanf(L"%d", &T) != 1) {
        return 1; // Entrada inválida
    }

    for (int t = 1; t <= T; t++) {
        int N;
        if (wscanf(L"%d", &N) != 1) {
            return 1; // Entrada inválida
        }

        wchar_t mao[100];
        if (wscanf(L"%ls", mao) != 1) {
            return 1; // Entrada inválida
        }

        for (int i = 0; i < N; i++) {
            wchar_t jogada[100];
            if (wscanf(L"%ls", jogada) != 1) {
                return 1; // Entrada inválida
            }
        }

        wchar_t jogada_atual[100];
        if (wscanf(L"%ls", jogada_atual) != 1) {
            return 1; // Entrada inválida
        }

        if (jogada_valida(mao, jogada_atual)) {
            realizar_jogada(mao, jogada_atual);
        }

        wprintf(L"Teste %d\n", t);
        if (wcslen(mao) == 0) {
            wprintf(L"\n");
        } else {
            ordenar_mao(mao);
        }
    }

    return 0;
}
