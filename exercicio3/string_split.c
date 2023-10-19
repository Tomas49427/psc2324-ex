#include <string.h>



size_t string_split(char *text, char *separators, char *words[], size_t words_size) {
    static char *last_token = NULL;  // Para armazenar o estado entre chamadas
    char *token;
    size_t count = 0;

    // Primeira chamada ou reinicialização
    if (text != NULL)
        last_token = text;

    // Itera sobre os tokens
    while (count < words_size && (token = strsep(&last_token, separators)) != NULL) {
        if (*token != '\0') {
            // Aloca memória para a palavra e copia o token
            words[count] = strdup(token);

            if (words[count] == NULL) {
                return count;
            }

            count++;
        }
    }

    return count;
}

