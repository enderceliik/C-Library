//https://github.com/Enderceliik
//Ender CELIK

#include <stdio.h>
#include <stdlib.h>

typedef struct ourStack{
    char data[1];
    int number_data;
    struct ourStack *next;
}os;

os *first = NULL;
char *charArray; // Our problem string  || Problemi kullanicidan aldiktan sonra tutacagimiz char pointer.
char *resultString; // Postfix string   || Postfix'e cevirdikten sonra tutacagimiz string.

os * memoryAllocater(char *data)  // Ilk islemde operatorleri saklayacagimiz yigina bellek tanimlayan fonksiyon. // Function that allocates memory to the first conversion.
{
    os *node = (os*)malloc(sizeof(os));
    strcpy(node->data, data);
    node->next = NULL;
    return node;
}

os * memoryAllocaterForProcess(int data)  // Ikinci kisimda matematiksel islemi yaparken sayilarimizi atacagimiz yigina bellek adresi tanimlayan fonksiyon. // Function that allocates memory to the second conversion.
{
    os *node = (os*)malloc(sizeof(os));
    node -> number_data = data;
    node->next = NULL;
    return node;
}

void push(char *data)  // Ilk kisim icin push fonksiyonu. // push function for first conversion.
{
    os *node = memoryAllocater(data);
    if(first == NULL)
    {
        first = node;
    }
    else
    {
        os *iter = first;
        while(iter -> next != NULL)
            iter = iter -> next;
        iter -> next = node;
    }
}

void pushForProcess(int data)  // Ikinci kisim icin push fonksiyonu // push function for second conversion.
{
    os *node = memoryAllocaterForProcess(data);
    if(first == NULL)
    {
        first = node;
    }
    else
    {
        os *iter = first;
        while(iter -> next != NULL)
            iter = iter -> next;
        iter -> next = node;
    }
}

char * pop()  // Ilk kisim icin pop fonksiyonu // pop function for first conversion.
{
    char data[1];
    os *iter = first;
    os *prev;
    if(iter == NULL)
    {
        printf("There is no node to show...\n");
    }
    else if(first -> next == NULL)
    {
        //data = first -> data;
        strcpy(data, first -> data);
        free(first);
        first = NULL;
        return *data;
    }
    else
    {
        prev = iter;
        while(iter -> next != NULL)
        {
            prev = iter;
            iter = iter -> next;
        }
        prev -> next = NULL;
        strcpy(data, iter->data);
        free(iter);
        iter = NULL;
        return *data;
    }
}
int popForProcess()  // Ikinci kisim icin pop fonksiyonu // pop function for second conversion.
{
    int number_data;
    os *iter = first;
    os *prev;
    if(iter == NULL)
    {
        printf("There is no node to show...\n");
    }
    else if(first -> next == NULL)
    {
        number_data = first -> number_data;
        free(first);
        first = NULL;
        return number_data;
    }
    else
    {
        prev = iter;
        while(iter -> next != NULL)
        {
            prev = iter;
            iter = iter -> next;
        }
        prev -> next = NULL;
        number_data = iter->number_data;
        free(iter);
        iter = NULL;
        return number_data;
    }
}
void listFunctionForProcess() // Ikinci kisim icin list fonksiyonu // list function for second conversion.
{
    if(first == NULL)
    {
        printf(" ");
        return;
    }
    os *iter = first;
    while(iter)
    {
        printf(" %d ", iter->number_data);
        iter = iter -> next;
    }
}
void listFunction()  // Ilk kisim icin list fonksiyonu. // list function for first conversion.
{
    if(first == NULL)
    {
        printf(" ");
        return;
    }
    os *iter = first;
    while(iter)
    {
        printf(" %s ", iter->data);
        iter = iter -> next;
    }
}


int control(char *data)  // Ilk islemde yigin icindeki operatorun oncelik degerine ve girmek uzre olan operatorun oncelik degerini kiyaslayan ve islem yapilacaksa 1 yapilmayacaksa 0 donduren fonk.
{						 // A function that compares the priority value of the operator in the stack and the priority value of the operator that is about to enter in the first operation, and returns 1 if the operation is to be performed, 0 if not.
    os *iter = first;

    while(iter -> next != NULL)
        iter = iter -> next;  //Son node'a kadar ilerledik ve yiginin en ustundeki node'a tanimli operatore bakacagiz. // We've made it to the last node and we'll look at the operator defined for the node at the top of the stack.

    if(strcmp(data, "+") == 0 || strcmp(data, "-") == 0)
    {
        if(strcmp(iter->data, "(") == 0 || strcmp(iter->data, ")") == 0)
            return 0;
        else
            return 1;
    }
    if(strcmp(data, "*") == 0 || strcmp(data, "/") == 0)
    {
        if(strcmp(iter->data, "*") == 0 || strcmp(iter->data, "/") == 0)
            return 1;
        else
            return 0;
    }
}

int main()
{
    char problemString[50]; // We hold the problem in this variable. || Problemi tutacagimiz degisken.
    printf("Write the problem: ");
    scanf("%s",&problemString);

    char secondStage[50] = "";  // Postfix ifadeyi karakter karakter ekleyerek tutacagimiz char pointer. // The char pointer to keep the Postfix expression by adding character by character.

    char temp[2];
    printf("\n\n| INPUT STRING  |  OPERATOR STACK -> TOP |  OUTPUT STRING |\n");
    for(int i = 0; i < strlen(problemString); i++)
    {
        //print fonsiyonları
        printf("|  ");
        for(int j = i; j < strlen(problemString); j++)
        {
            printf("%c",problemString[j]);
        }
        printf(" |        ");
        listFunction();
        printf("        |");
        printf("%s\n",secondStage);
        printf("|\n");
        // print functions step by step

        if(isdigit(problemString[i])) // Sayi geldigi ve direkt postfix'e ekledğimiz durum. // The situation where the number comes and we add it directly to the postfix.
        {
            strncat(secondStage, &problemString[i], 1);
            continue;
        }

        temp[0] = problemString[i];
        strcat(temp, "\0");
        if(first == NULL) //Yiginimiz bos ise gelen ifade direkt yigina eklenecek. // If our stack is empty, the incoming expression will be added directly to the stack.
        {
            push(temp);
            continue;
        }
        else   // Yiginin bos olmadigi durumlar: // Cases where the stack is not empty:
        {
            if(strcmp(temp,"(") == 0) // Acma geldi ise kosulsuz eklenir. // If there is an opening parenthesis, it is added unconditionally.
            {
                push(temp);
                continue;
            }
            if(strcmp(temp,")") == 0) // Kapama geldi ise acma bulunana kadar elamana cikarilir ve postfix'e eklenir. // If there is a close parenthesis, it is removed to the element until it is found and added to the postfix.
            {
                char * variable = "";
                while(strcmp(&variable, "(") != 0) // Kapama gelene kadar. // Until the close parenthesis comes.
                {
                    variable = pop();
                    if(strcmp(&variable, "(") != 0)  // Son kapa parantezi dahil etmemek icin. // To exclude the last closed parenthesis. // Maybe this procces can make with do-while loop more easily
                        strncat(secondStage, &variable, 1);
                }
                continue;
            }
            // "+ - / *"işaretleri gelirse:
            if(control(temp) == 1) // control fonksiyonu gelen işaret ve yığındaki işaretin öncelik durumlarını karşılaştıracak ve eğer
            // yıgındaki isaretin yügündaki oncelik degeri yigina girecek isaretin girerken ki oncelik degerinden yuksek veya esit ise 1 dondurecek
            // biz de yigindaki isareti yigindan cikarip postfix e ekleyecegiz. daha sonra gelen isareti yigina yukleyecegiz.
			//The control function will compare the priority status of the incoming flag and the flag in the stack, 
			// and if the priority value of the flag in the stack is higher or equal to the priority value of the flag that will enter the stack, 
			// it will return 1, so we will remove the flag from the stack and add it to the postfix. then we will load the incoming flag on the stack.
            {
                char * variable = "";
                variable = pop();
                strncat(secondStage, &variable, 1);
                push(temp);
                continue;
            }
            else
            {
                push(temp);
                continue;
            }
        }
    }

    while(first)
    {
        printf("|    NULL    |    ");
        listFunction();
        printf("               |");
        printf("%s\n", secondStage);
        char * variable = "";
        variable = pop();
        strncat(secondStage, &variable, 1);
    }
    printf("\n Final postfix: %s\n", secondStage);
    printf("------------------------------------------\n");
    printf("\nProcess part:\n");
    printf("| POSTFIX       |  NUMBER STACK -> TOP\n");
    for(int i = 0; i < strlen(secondStage); i++)
    {
        printf("| ");
        for(int j = i ; j< strlen(secondStage); j++)
        {
            printf("%c", secondStage[j]);
        }
        printf("      ||      ");
        listFunctionForProcess();
        printf("\n");
        if(isdigit(secondStage[i])) //
        {
            char temp[2];
            temp[0] = secondStage[i];
            strcat(temp,"\0");
            int data = atoi(temp);
            pushForProcess(data);
            continue;
        }
        char temp[2];
        temp[0] = secondStage[i];
        strcat(temp, "\0");
        if(!isdigit(secondStage[i]))
        {
            if(strcmp(temp, "+") == 0)
            {
                int data1 = popForProcess();
                int data2 = popForProcess();
                int result = data1 + data2;
                pushForProcess(result);
                continue;
            }
            if(strcmp(temp, "-") == 0)
            {
                int data1 = popForProcess();
                int data2 = popForProcess();
                int result = data2 - data1;
                pushForProcess(result);
                continue;
            }
            if(strcmp(temp, "*") == 0)
            {
                int data1 = popForProcess();
                int data2 = popForProcess();
                int result = data1 * data2;
                pushForProcess(result);
                continue;
            }
            if(strcmp(temp, "/") == 0)
            {
                int data1 = popForProcess();
                int data2 = popForProcess();
                int result = data2 / data1;
                pushForProcess(result);
                continue;
            }
        }
    }
    int result = popForProcess();
    printf("\n result: %d\n", result);
    return 0;
}
