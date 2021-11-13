#include "list.h"
#include "list.cpp"

int main()
{
    List Lst = {};

    Lst.logs = fopen("logs.txt", "w+");

    list_ctor(&Lst);

    insert_after(&Lst, 0, 10);
    printf("place = %d\n", physic_to_logic_number(&Lst, 1));


    insert_after(&Lst, 1, 20);
    printf("place = %d\n", physic_to_logic_number(&Lst, 2));

    insert_after(&Lst, 1, 6);
    printf("place = %d\n", physic_to_logic_number(&Lst, 2));


    //Sort_List_Too_slow_slow_call_only_at_night(&Lst);

    insert_after(&Lst, 3, 44);


    delete_this_elem(&Lst, 2);

    insert_after(&Lst, 4, 37);

    insert_after(&Lst, 1, 7);
    insert_after(&Lst, 1, 9);

    Sort_List_Too_slow_slow_call_only_at_night(&Lst);
    list_dump(&Lst, ALL_OK);

    return 0;
}
