#include "hashtable.h"

int main() {
    hashtable h;

    int status;

    status = hashtable_create(&h);

    if (status != 0) {
        printf("Ошибка во время создания хеш таблицы\n");
        return 0;
    }

    for (int i = 1; i < 11; ++i) {
        hashtable_set(&h, i, i * i);
    }

    for (int i = 1; i < 11; ++i) {
        int result = -1;
        status = hashtable_search(&h, i, &result);

        printf("поиск по %d, статус %d\n", i, status);
        if (status == 0) {
            printf("%d\n", result);
        }
    }

    hashtable_free(&h);

    return 0;
}
