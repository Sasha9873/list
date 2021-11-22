#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

    #include <cstdio>
    #include <cstring>
    #include <cstdlib>
    #include <utility>
    #include <cstdbool>

    #define CHECK 1

    #if CHECK >= 1
        #define IS_DUMP
    #endif // CHECK

    #define DUMP(reason)\
        fprintf(Lst->logs, "Called from %s() at %s(%d),\n", __FUNCTION__, __FILE__, __LINE__);\
        list_dump(Lst, reason);\

    int CHANGE = 2; // static, const, define

    typedef enum errors{
        ALL_OK           =  0,
        NO_MEMORY        = -1,
        AFTER_EMPTY_ELEM = -2,
        DELETE_ZERO_ELEM = -3,
        NULL_FILE        = -4,
    }errors_t;

    char *error_names[] = { // static const
        "All is ok",
        "Not enough memory",
        "Push after an empty element",
        "Pop zero element",
        "Pointer to log file is NULL",
    };

    struct List{
        int* prev;
        int* data;
        int* next;
        int capacity = 1;
        int free = 0;
        bool sorted = 0;
        FILE* logs = NULL;
        FILE* graph = NULL;
    };

    int list_ctor(List* Lst);
    int insert_before(List* Lst, int place, int value);
    int insert_after(List* Lst, int place, int value);
    int delete_this_elem(List* Lst, int place);
    int list_dump(List* Lst, errors_t reason);
    int print_graph(List* Lst);
    int sort_list(int begining, int amount_elem, List* Lst);
    int physic_to_logic_number(int place);

#endif // LIST_H_INCLUDED
