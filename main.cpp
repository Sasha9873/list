#include "list.h"

/**
 * Do not forget to close all files!
 */
int main(int argc, char* argv[])
{
    List Lst = {};

    if (argc > 2){ // open for reading first
        if((Lst.logs = fopen(argv[1], "w+")) == NULL)
            return NULL_FILE;

        if((Lst.graph = fopen(argv[2], "w+")) == NULL)
            return NULL_FILE;

        printf("You have just created files: \"%s\" and \"%s\"\n", argv[1], argv[2]);
    }
    else
        return NULL_FILE;

    Lst.logs = fopen("logs.txt", "w+");

    Lst.graph = fopen("graph.txt", "w+");

    list_ctor(&Lst);

    insert_after(&Lst, 0, 10);

    insert_after(&Lst, 1, 20);
    //printf("place = %d\n", physic_to_logic_number(&Lst, 2));

    sort_list(&Lst, sort_func);

    insert_after(&Lst, 1, 6);
    //printf("place = %d\n", physic_to_logic_number(&Lst, 2));

    insert_after(&Lst, 3, 44);

    delete_this_elem(&Lst, 2);

    insert_after(&Lst, 4, 37);

    insert_after(&Lst, 1, 7);
    print_graph(&Lst);
    insert_after(&Lst, 1, 9);


    sort_list(&Lst, sort_func);
    list_dump(&Lst, ALL_OK);


    fclose(Lst.graph);
    fclose(Lst.logs);

    return 0;
}
