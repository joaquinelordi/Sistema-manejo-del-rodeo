#include "mbed.h"
#include "stringParser.h"
#include <cstring>
#include <stdlib.h>
#include "my_stdlib.h"
#include "ctype.h"

// funcion que decide si el string pasado como argumento tiene el formato arbitrario para utilizado para recibir tags serializados
// formato elegido: en regexp: ^{[A-F0-9]{4,10}-[A-Z]}$ EJ: "{8CA7B544-A}"
// donde lo que esta a la izquierda del guion es el UID y lo que esta a la derecha es el corral asignado
bool isAValidTag(char* str)
{
    bool containsNL = false;

    if (str == NULL)
        return false;

    size_t l = my_strlen(str);
    printf("isAValidTag-> [%s, %d] \n", str, l);
    
    if (str[l -1] == '\n')
        containsNL = true;
      
    //verifico que empiece con '{' y termine con '}'
    if (str[0] != BEGIN_DELIMITER)
        return false;
      
    if (str[l - 1] != END_DELIMITER)
        return false;

    //verifico longitud minima y maxima del string
    if (l < MIN_LENGH || l > MAX_LENGH)
        return false;

    //busco el separador  
    char* delPos = my_strchr(str, CHAR_DELIMIRER);
    if (delPos == NULL)
        return false;

    //evaluo la parte del UID, me fijo si es un numero en hexaecimal valido
    size_t end_UID = (delPos - str);
    for (int i = 1; i < end_UID; i++)
    {
        if (!isxdigit(str[i]))
            return false;
    }
    // veo si es una letra el ultimo caracter usado para asignar el corral y que despues esta el '}'
    if (!isupper(*(delPos+1)))
        return false;

    // el caracter que le sigue al de asignar corral es el '}' y ademas es el ultimo
    if (*(delPos+2) != END_DELIMITER && *(delPos+3) != '\0')
        return false;
        
    return true;
}

// este metodo se usa despues de preguntar si es un tag valido, no tiene sentido usarlo sin validar
// devuelve un arreglo de dos strings, el UID y el corral, en ese orden.
char** deserializeTag(char * str)
{
    if (str == NULL)
        return NULL;

    //inicializo el arreglo de strings a devolver
    //dos puntero a char* primero
    char** vStrings =(char**) malloc(2 * sizeof(char*));

    if(vStrings == NULL)
    {
        printf("deserializeTag -> falla por memoria\n");
        return NULL;
    }

    vStrings[0] = (char*) malloc(MAX_UID_SIZE +1);
    vStrings[1] = (char*) malloc(MAX_GROUP_SIZE +1);

    //busco el separador  
    char* delPos = my_strchr(str, CHAR_DELIMIRER);
    //reemplazo caracteres \0
    *delPos = '\0';
    //copio las dos cadenas
    my_strcpy(vStrings[0], str+1);
    strncpy(vStrings[1], delPos+1, MAX_GROUP_SIZE);
    vStrings[1][MAX_GROUP_SIZE] = '\0';

    return vStrings;

}