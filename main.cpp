#include "list.h"
#include "list.cpp"

int main() // argc argv input
{
    List Lst = {};

    Lst.logs = fopen("logs.txt", "w+"); // parametrize please

    Lst.graph = fopen("graph.txt", "w+");

    list_ctor(&Lst);

    insert_after(&Lst, 0, 10);
    printf("place = %d\n", physic_to_logic_number(&Lst, 1));


    insert_after(&Lst, 1, 20);
    printf("place = %d\n", physic_to_logic_number(&Lst, 2));

    sort_list(&Lst);

    insert_after(&Lst, 1, 6);
    printf("place = %d\n", physic_to_logic_number(&Lst, 2));

    insert_after(&Lst, 3, 44);

    delete_this_elem(&Lst, 2);

    insert_after(&Lst, 4, 37);

    insert_after(&Lst, 1, 7);
    print_graph(&Lst);
    insert_after(&Lst, 1, 9);


    sort_list(&Lst);
    list_dump(&Lst, ALL_OK);


    fclose(Lst.graph);
    fclose(Lst.logs);

    return 0;
}
