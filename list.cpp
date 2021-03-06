#include "list.h"

int list_ctor(List* Lst)
{
    Lst->data = (int*)calloc(Lst->capacity, sizeof(int));
    Lst->next = (int*)calloc(Lst->capacity, sizeof(int));
    Lst->prev = (int*)calloc(Lst->capacity, sizeof(int));

    if(Lst->data == NULL || Lst->next == NULL || Lst->prev == NULL){
        Lst->capacity = 0;
        DUMP(NO_MEMORY);
        return NO_MEMORY;
    }

    memset(Lst->next, -1, Lst->capacity*sizeof(int));
    memset(Lst->prev, -1, Lst->capacity*sizeof(int));

    if(Lst->capacity > 0){
        (Lst->data)[0] = 0;
        (Lst->next)[0] = 0;
        (Lst->prev)[0] = 0;
    }

    if(Lst->capacity > 1){
        Lst->free = 1;
        for(int i = 1; i < Lst->capacity - 1; i++)
            Lst->next[i] = i + 1;
        Lst->next[Lst->capacity - 1] = 0;
    }

    #ifdef IS_DUMP
        DUMP(ALL_OK);
    #endif // IS_DUMP

    return 0;
}

int insert_after(List* Lst, int place, int value)
{
    if(Lst->next[place] != -1)
    {
        int num = 0;

        if(Lst->free == 0){             //there is no empty place left
            //printf("next1 place %d\n", Lst->next[place]);
            int* new_data_memory = (int*)realloc(Lst->data, sizeof(int)*CHANGE*Lst->capacity);
            int* new_next_memory = (int*)realloc(Lst->next, sizeof(int)*CHANGE*Lst->capacity);
            int* new_prev_memory = (int*)realloc(Lst->prev, sizeof(int)*CHANGE*Lst->capacity);
            //printf("prev = %p\n", new_prev_memory);

            if(new_data_memory == NULL || new_next_memory == NULL || new_prev_memory == NULL){
                DUMP(NO_MEMORY);
                return NO_MEMORY;
            }
            else{
                num = Lst->capacity;

                Lst->capacity *= CHANGE;

                Lst->data = new_data_memory;
                Lst->next = new_next_memory;
                Lst->prev = new_prev_memory;

                memset(Lst->data + num + 1, 0, (Lst->capacity - num - 1)*sizeof(int));
                memset(Lst->prev + num + 1, -1, (Lst->capacity - num - 1)*sizeof(int));

                if(num < Lst->capacity - 1){
                    Lst->free = num + 1;
                    for(int index = num; index < Lst->capacity - 1; index++)
                        Lst->next[index] = index + 1;
                    Lst->next[Lst->capacity - 1] = 0;
                }
                //printf("next1 place %d\n", Lst->next[place]);
                //list_print(Lst);
            }
        }
        else{
            num = Lst->free;
            Lst->free = Lst->next[Lst->free];
        }

        /*printf("\ncapacity = %d\nnum: ", Lst->capacity);
        printf("\nnum = %d next = %d\n", num, Lst->next[num]);
        printf("next place %d\n", Lst->next[place]);*/

        Lst->data[num] = value;

        Lst->next[num] = Lst->next[place];
        Lst->next[place] = num;

        Lst->prev[num] = place;
        Lst->prev[Lst->next[num]] = num;

        #ifdef IS_DUMP
            DUMP(ALL_OK);
        #endif // IS_DUMP
        return num;
    }
    else{
        DUMP(AFTER_EMPTY_ELEM);
        return AFTER_EMPTY_ELEM;
    }


}

int delete_this_elem(List* Lst, int place)  // delete elem which is at the place(physical)
{
    if(place !=0){
        int del_elem = 0;

        del_elem = Lst->data[place];

        Lst->next[Lst->prev[place]] = Lst->next[place];
        Lst->prev[Lst->next[place]] = Lst->prev[place];

        Lst->data[place] = 0;

        Lst->next[place] = Lst->free;
        Lst->free = place;

        Lst->prev[place] = -1;

        #ifdef IS_DUMP
            DUMP(ALL_OK);
        #endif // IS_DUMP

        return del_elem;

    }
    else{
        DUMP(DELETE_ZERO_ELEM);
        return DELETE_ZERO_ELEM;
    }

}

int list_dump(List* Lst, errors_t reason)
{
    if(Lst->logs == NULL)
        return NULL_FILE;

    if(reason != ALL_OK)
        fprintf(Lst->logs, "Dump was called because %s(%d)\n", error_names[abs(reason)], reason);

    fprintf(Lst->logs, "head = %d tail = %d free = %d\n", Lst->next[0], Lst->prev[0], Lst->free);

    int i = 0;

    fprintf(Lst->logs,"      ");

    for(i = 0; i < Lst->capacity; i++)
            fprintf(Lst->logs,"%3d ", i);

    fprintf(Lst->logs,"\ndata  ");

    for(i = 0; i < Lst->capacity; i++)
        fprintf(Lst->logs,"%3d ", Lst->data[i]);

    fprintf(Lst->logs,"\nnext  ");

    for(i = 0; i < Lst->capacity; i++)
        fprintf(Lst->logs,"%3d ", Lst->next[i]);
    fprintf(Lst->logs,"\nprev  ");

    for(i = 0; i < Lst->capacity; i++)
        fprintf(Lst->logs,"%3d ", Lst->prev[i]);

    fprintf(Lst->logs,"\n\n");

    return ALL_OK;
}

int print_graph(List* Lst)
{

    if(Lst->graph == NULL)
        return NULL_FILE;

    fprintf(Lst->graph, "digraph G{\n rankdir=LR;\n node[fontsize=11];\n node[margin=\"0.01\"];\n");

    fprintf(Lst->graph, " {\n    node[shape=\"plaintext\",style=\"invisible\"];\n    edge [color=\"white\"];\n    ");

    fprintf(Lst->graph, "    \"1\"");
    for(int index = 2; index < Lst->capacity + 1; index++)
        fprintf(Lst->graph, "->\"%d\"", index);
    fprintf(Lst->graph, "\n }\n");

    fprintf(Lst->graph, "edge [color=\"blue\"];");

    /*fprintf(Lst->graph, " {rank = same; \"0\";box0;}\n \"box0\"[shape=\"record\", label = \"index|data|next|prev\"];\n");*/
    for(int index = 1; index < Lst->capacity + 1; index++){
        fprintf(Lst->graph, "{rank = same; \"%d\";box%d;}\n", index, index);

        if(Lst->prev[index - 1] == -1){
            fprintf(Lst->graph, " \"box%d\"[shape=\"record\", style=\"filled\", fillcolor=\"green\", label = \"index = %d|data = %d|", index, index - 1, Lst->data[index - 1]);
        }
        else
            fprintf(Lst->graph, " \"box%d\"[shape=\"record\", style=\"filled\", fillcolor=\"white\", label = \"index = %d|data = %d|", index, index - 1, Lst->data[index - 1]);
        fprintf(Lst->graph, "<f%d>next = %d|prev = %d\"];\n\n", index, Lst->next[index - 1], Lst->prev[index - 1]);
    }

    if(Lst->next[0] != 0)
        fprintf(Lst->graph, " box1");

    int index = 0;
    while(Lst->next[index] != 0){
        fprintf(Lst->graph, "->box%d", Lst->next[index] + 1);
        index = Lst->next[index];
    }

    fprintf(Lst->graph, "\n");


    fprintf(Lst->graph, "edge [color=\"red\"];");

    index = Lst->free;
    if(index != 0 && Lst->next[index] != 0)
        fprintf(Lst->graph, " box%d", index + 1);
    while(Lst->next[index] != 0){
        fprintf(Lst->graph, "->box%d", Lst->next[index] + 1);
        index = Lst->next[index];
    }

    fprintf(Lst->graph, "}");

    return ALL_OK;

}

int sort_list(List* Lst, int (*sort_func)(List* Lst))
{
    return sort_func(Lst);
}

int sort_func(List* Lst)
{
    int current = Lst->next[0];
    int exchange = 0;
    int val = 0;
    int num = 1;
    int next = 0;

    while(current != 0){

        if(current != num){
            val = Lst->data[current];      //change data
            Lst->data[current] = Lst->data[num];
            Lst->data[num] = val;

            if(Lst->next[current] == num){

                Lst->prev[current] = num;
                Lst->prev[Lst->next[num]] = current;

                Lst->next[current] = Lst->next[num];
                Lst->next[num] = current;

                Lst->prev[num] = num - 1;
                Lst->next[num - 1] = num;
            }
            else{
                exchange = Lst->next[current];      //change next
                Lst->next[current] = Lst->next[num];
                Lst->next[num] = exchange;

                exchange = Lst->prev[current];      //change prev
                Lst->prev[current] = Lst->prev[num];
                Lst->prev[num] = exchange;
                Lst->prev[Lst->next[num]] = num;
                Lst->prev[Lst->next[current]] = current;

                Lst->next[Lst->prev[num]] = num;
                Lst->next[Lst->prev[current]] = current;
                Lst->next[num - 1] = num;
            }

        }
        #ifdef IS_DUMP
            DUMP(ALL_OK);
        #endif // IS_DUMP
        current = Lst->next[num];
        num++;
    }

    return num;
}


int physic_to_logic_number(List* Lst, int place)
{
    if(Lst->sorted)
        return place;

    int logic = 0;

    if(place != 0){
        while(Lst->prev[place] != 0){
            place = Lst->prev[place];
            logic++;
        }
        return logic + 1;
    }
    else
        return 0;
}

