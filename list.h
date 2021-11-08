#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

    #include <cstdio>
    #include <cstring>
    #include <cstdlib>

    int CHANGE = 2;

    typedef enum errors{
        ALL_OK           =  0,
        NO_MEMORY        = -1,
        AFTER_EMPTY_ELEM = -2,
    }errors_t;

    struct List{
        int* prev;
        int* data;
        int* next;
        int capacity = 2;
        int head = 0;
        int tail = 0;
        int free = 0;
    };

    int list_ctor(List* Lst);
    int insert_before(List* Lst, int place, int value);
    int insert_after(List* Lst, int place, int value);
    int list_delete(List* Lst, int place);


#endif // LIST_H_INCLUDED
