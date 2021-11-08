#include "list.h"

int main()
{
    List Lst = {};
    list_ctor(&Lst);

    insert_after(&Lst, 4, 9);
    printf("head = %d tail = %d\n", Lst.head, Lst.tail);
    int i = 0;
    for(i = 0; i < Lst.capacity; i++)
            printf("%3d ", i);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.data[i]);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.next[i]);


    insert_after(&Lst, 1, 7);
    printf("head = %d tail = %d\n", Lst.head, Lst.tail);
    for(i = 0; i < Lst.capacity; i++)
            printf("%3d ", i);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.data[i]);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.next[i]);


    insert_after(&Lst, 1, 6);
    printf("head = %d tail = %d\n", Lst.head, Lst.tail);
    for(i = 0; i < Lst.capacity; i++)
            printf("%3d ", i);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.data[i]);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.next[i]);


    insert_after(&Lst, 3, 44);
    printf("head = %d tail = %d\n", Lst.head, Lst.tail);

    for(i = 0; i < Lst.capacity; i++)
            printf("%3d ", i);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.data[i]);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.next[i]);

    list_delete(&Lst, 2);
    printf("head = %d tail = %d\n", Lst.head, Lst.tail);

    for(i = 0; i < Lst.capacity; i++)
            printf("%3d ", i);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.data[i]);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.next[i]);


    insert_after(&Lst, 4, 37);
    printf("head = %d tail = %d\n", Lst.head, Lst.tail);

    insert_after(&Lst, 1, 7);
    insert_after(&Lst, 1, 7);
    insert_after(&Lst, 1, 7);
    insert_after(&Lst, 1, 7);
    insert_after(&Lst, 1, 7);

    for(i = 0; i < Lst.capacity; i++)
            printf("%3d ", i);

    printf("\n");

    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.data[i]);

    printf("\n");


    for(i = 0; i < Lst.capacity; i++)
        printf("%3d ", Lst.next[i]);

    return 0;
}

int list_ctor(List* Lst)
{
    Lst->data = (int*)calloc(Lst->capacity, sizeof(int));
    Lst->next = (int*)calloc(Lst->capacity, sizeof(int));
    memset(Lst->next, -1, Lst->capacity*sizeof(int));

    if(Lst->capacity > 0){
        (Lst->data)[0] = 0;
        (Lst->next)[0] = 0;
    }/**/

    return 0;
}

int insert_after(List* Lst, int place, int value)
{
    if(Lst->next[place] != -1)
    {
        int num = Lst->capacity - 1, cur_num = 1;
        printf("\ncapacity = %d\nnum: ", Lst->capacity);
        for(cur_num = 1; cur_num < Lst->capacity; cur_num++){
            printf("%d ", cur_num);
            if(Lst->next[cur_num] == -1){
                num = cur_num;
                break;
            }

        }
        printf("\nnum = %d next = %d\n", num, Lst->next[num]);

        int* new_data_memory = NULL;
        int* new_next_memory = NULL;


        if(num == Lst->capacity - 1 && Lst->next[num] != -1){
            new_data_memory = (int*)realloc(Lst->data, sizeof(int)*CHANGE*Lst->capacity);
            new_next_memory = (int*)realloc(Lst->next, sizeof(int)*CHANGE*Lst->capacity);

            if(new_data_memory == NULL || new_next_memory == NULL)
                return NO_MEMORY;
            else{
                Lst->capacity *= CHANGE;

                Lst->data = new_data_memory;
                Lst->next = new_next_memory;

                memset(Lst->data + num + 1, 0, (Lst->capacity - num - 1)*sizeof(int));
                memset(Lst->next + num + 1, -1, (Lst->capacity - num - 1)*sizeof(int));

                num++;
            }
        }

        Lst->data[num] = value;

        if(Lst->head == 0){
            Lst->next[num] = 0;
            Lst->head = num;
            Lst->tail = num;
        }
        else{
            Lst->next[num] = Lst->next[place];
            Lst->next[place] = num;

            if(Lst->next[num] == 0)
                Lst->tail = num;
        }

        return num;
    }
    else
        return AFTER_EMPTY_ELEM;

}

int list_delete(List* Lst, int place)
{
    int num = 1, cur_num;
    printf("\ncapacity = %d\nnum: ", Lst->capacity);
    for(cur_num = 1; cur_num < Lst->capacity; cur_num++){
        printf("%d ", cur_num);
        if(Lst->next[cur_num] == place){
            num = cur_num;
            break;
        }
    }

    printf("\nnum = %d\n", num);

    Lst->next[num] = Lst->next[place];

    if(Lst->head == place)
        Lst->head = num;

    if(Lst->tail == place)
        Lst->tail = num;

    Lst->data[place] = 0;
    Lst->next[place] = -1;
}


