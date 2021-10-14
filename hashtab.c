#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
 
struct hashTab* Tab;
int size_glob;
int n = 0; // количество элементов контейнера
//опишем хэш-таблицу
struct hashTab{
    char information[256]; //содержание элемента
    int key; // ключ, по которому определяем индекс в хэш-таблице
};
//опишем классическую хэш-функцию
//преобразовывает ключ элемента в индекс массива
// передаем ключ и размер таблицы
int hash_fun(int key, int size_of_tab){
    return key % (size_of_tab);
}
//функция разрешения столкновений (коллизий)
//если у нас обнаружено столкновение исполльзуем ее
// передаеми нашу таблицу и ее размер
//вернет индекс свободной ячейки массива
int collusion(struct hashTab* oldTab, int size_tab){
    for (int i = 0; i < size_tab; i++){
        if (oldTab[i].key == 0){
            return(i);
        }
    }
}
//функция позволяет заполнить таблицу с клавиатуры
//принимает таблицу, размер таблицы
//Ничего не возвращает, но изменчет хэш таблицу
//Есть вложенная функция для проверки на столкновения
void fiil_tab(struct hashTab* oldTab, int size_tab){
    int size_of_string = 0;
    int tmpKey = 0, index;
    char buffer[256];
    printf("Введите строку\n");
    scanf("%s", buffer);
    //Вычисление ключа. Суммируются все коды элементов строки
    for (int i = 0; buffer[i] != '\0'; i++){
        tmpKey += (int)buffer[i];
        size_of_string = i;
    }
    size_of_string++;
    //Определяем индекс свободной ячейки с помощью хэш-функции
    index = hash_fun(tmpKey, size_tab); //получаем индекс с помощью хэш-функции
    //попытка разрешить столкновения
    if (oldTab[index].key != 0)
        index = collusion(oldTab, size_tab);
    for (int i = 0; i <= size_of_string; i++)
        oldTab[index].information[i] = buffer[i]; //заполняем поле "инфомация" строкой,введенной с клавиатуры
    oldTab[index].key = tmpKey; //перезаписываем ключ из временной переменной в структуру
    printf("Индекс элемента = \n"); printf("%d \n", index);
    printf("Ключ элемента = \n"); printf("%d \n", oldTab[index].key);
    printf("Длина строки = \n"); printf("%d \n", size_of_string);
    n += 1;
}
void filltab2(struct hashTab* oldTab, int size_tab,char* buffer){
    int size_of_string = 0;
    int tmpKey = 0, index;
    //Вычисление ключа. Суммируются все коды элементов строки
    for (int i = 0; buffer[i] != '\0'; i++){
        tmpKey += (int)buffer[i];
        size_of_string = i;
    }
    size_of_string++;
    //Определяем индекс свободной ячекйки с помощью хэш-функции
    index = hash_fun(tmpKey, size_tab); //получаем индекс с помощью хэш-функции
    //попытка разрешить столкновени¤
    if (oldTab[index].key != 0)
        index = collusion(oldTab, size_tab);
    for (int i = 0; i <= size_of_string; i++)
        oldTab[index].information[i] = buffer[i]; //заполняем поле "инфомация" строкой,введенной с клавиатуры
    oldTab[index].key = tmpKey; //перезаписываем ключ из временной переменной в структуру
    printf("Индекс элемента = \n"); printf("%d \n", index);
    printf("Ключ элемента = \n"); printf("%d \n", oldTab[index].key);
    printf("Длина строки = \n"); printf("%d \n", size_of_string);
}
void NumEl(struct hashTab* Tab, int size) {
    printf(" Кол-во элементов = ");
    printf("%d \n", n);
}
//Если контейнер создается впервые
struct hashTab* new_cont(struct hashTab* Tab, int size) {
    //объвление массива структур
    struct hashTab* newTab = (struct hashTab*)malloc(sizeof(size));
    //проинициализируем все ключи таблицы нулями
    for (int j = 0; j < size; j++){
        newTab[j].key = 0;
        newTab[j].information[0] = '\0';
    }
    return newTab;
}
 
//Добавляет ячейки контейнеру
struct hashTab* add_cont(struct hashTab* Tab, int size, int num) {
    struct hashTab* newTab = (struct hashTab*)malloc(sizeof(size+num));
    for (int i = 0; i < size; i++){
        newTab[i].key = Tab[i].key;
        for (int j = 0; j < 256; j++){
            newTab[i].information[j] = Tab[i].information[j];
            if (Tab[i].information[j] == '\0')
                break;
        }
    }
    for (int j = size; j < size+num; j++){
        newTab[j].key = 0;
        newTab[j].information[0] = '\0';
    }
    return newTab;
}
 
//Удаляет таблицу
void del_cont(struct hashTab* Tab) {
    free(Tab);
    n = 0;
    printf("Вы удалили хэш-таблицу\n");   
}
 
//Поиск
void search(struct hashTab* Tab, int size) {
    int g, count;
    char choose[256];
    printf("Поиск по значению [1] или по индексу [2]\n");
    scanf_s("%d", &g);
    switch (g){
 
    //по значению
    case 1:{
        printf("введите значение\n");
        scanf("%s", choose);
        for (int i = 0; i < size; i++){
            if (strcmp(Tab[i].information, choose) == 0){
                printf("Key[");
                printf("%d", i);
                printf("]:");
                printf("%d \n", Tab[i].key);
                printf("String[");
                printf("%d", i);
                printf("]:");
                printf("%s \n", Tab[i].information);
                printf("\n");
                break;
            }
        }
        break;
    }
    
    //по индексу
    case 2:
    {
        printf("Введите индекс\n");
        scanf("%d", &count);
        if (count > size)
            printf("Внимание! Слишком большой индекс!\n");
        else{
            printf("Key[");
            printf("%d", count);
            printf("]:");
            printf("%d \n", Tab[count].key);
            printf("String[");
            printf("%d", count);
            printf("]:");
            printf("%s \n", Tab[count].information);
            printf("\n");
        }
        break;
    }
} 
}
 
//Вывод на экран
void Print(struct hashTab* Tab, int size) {
    for (int i = 0; i < size; i++){
        printf("Key[");
        printf("%d", i);
        printf("]:");
        printf("%d \n", Tab[i].key);
        printf("String[");
        printf("%d", i);
        printf("]:");
        printf("%s \n", Tab[i].information);
        printf("\n");
    }
}
 
//Сохранение 
void SIF(struct hashTab* Tab, int size) {
    char filename[256];
    printf("Введите путь к файлу:\n");
    scanf("%s", filename);
    FILE* fout = fopen(filename, "wt");
    for (int i = 0; i < size; i++){
        fprintf(fout, "Key:", '\n');
        fprintf(fout, "%d%c", Tab[i].key, '\n');
        fprintf(fout, "Text:", '\n');
        fprintf(fout, "%s%c", Tab[i].information, '\n');
    }
    fclose(fout);
    printf("Контейнер сохранён в файле: ");
    printf(filename, '\n');
}
 
//Загрузить
void read(FILE* fin, struct hashTab* Tab){
    char str[256]; //Создаем массив для имени файла
    char filename[256];
    printf("Введите путь к файлу:\n");
    scanf("%s", filename); //Считываем имя файла
    fin = fopen(filename, "r"); //Создаем указатель типа FILE на функцию открытия файла, указанного в скобках
    while (!feof(fin)){
        char* s = (char*)malloc(sizeof(char));
        fscanf(fin, "%s", s);//выписываем следующие элементы 
        filltab2(Tab,size_glob,s);
    }
}
void main() {
    setlocale(LC_ALL, "RUSSIAN");
    int ffc = 0, w = 0, p, size, num, free_space = 0;
    char filename[256];
    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(filename, "w");
    while (w == 0) {
        size = size_glob;
        printf("\n Что вы хотите сделать? \n");
        printf("1. Создать новый контейнер \n");
        printf("2. Удалить контейнер \n");
        printf("3. Добавить элемент \n");
        printf("4. Поиск элемента \n");
        printf("5. Показать элементы \n");
        printf("6. Удалить все элементы \n");
        printf("7. Сохранить контейнер \n");
        printf("8. Загрузить контейнер \n");
        printf("9. Показать количество элементов \n");
        printf("Нажмите на любую другую кнопку для выхода \n");
        printf("\n");
        scanf_s("%d", &p);
        switch (p) {
        case 1:
        {
            if (ffc == 0) {
                printf("Введите размер контейнера \n");
                scanf_s("%d", &size);
                Tab = new_cont(Tab, size);
                ffc = 1;
            }
            else {
                printf("Сейчас вы увеличиваете размер контейнера \n");
                printf("Введите насколько вы хотите увеличить контейнер \n");
                scanf_s("%d", &num);
                Tab = add_cont(Tab, size, num);
                size += num;
            }
            break;
        }
        case 2:
        {
            if (ffc == 0){
                printf("У вас нет контейнера \n");
            }
            else {
                del_cont(Tab);
                size = 0;
                ffc = 0;
            }
            break;
        }
        case 3:
        {
            for (int i = 0; i < size; i++){
                if (Tab[i].key == 0)
                    free_space = 1;
            }
            if (free_space == 0)
                printf("Внимание! Хэш-таблица заполнена! \n");
            else{
                fiil_tab(Tab, size);
            }
            free_space = 0;
            break;
        }
        case 4:
        {    
            search(Tab, size);
            break;
        }
        case 5:
        {
            if (ffc == 0){
                printf("У вас нет контейнера \n");
            }
            else{
                Print(Tab, size);
            }
            break;
        }
        case 6:
        {
            if (ffc == 0){
                printf("У вас нет контейнера\n");
            }
            else{
                Tab = new_cont(Tab, size);
                n = 0;
                printf("Хэш-таблица теперь пустая\n");
            }
            break;
        }
        case 7:
        {
            if (ffc == 0) {
                printf("У вас нет хэш-таблицы \n");
            }
            else {
                SIF(Tab, size);
            }
            break;
        }
        case 8:
        {
            if (ffc == 0) {
                printf("У вас нет хэш-таблицы \n");
            }
            else {
                read(fin, Tab);
            }
            break;
        }
        case 9: {
            if (ffc == 0) {
                printf("У вас нет хэш-таблицы \n");
            }
            else {
                NumEl(fin, Tab);
            }
            break;
        }
        default:
        {   w = 1;
        break; }
        }
        size_glob = size;
    }
    system("pause");
}
