

#include "my_stdlib.h"

size_t my_strlen(const char *str, size_t acc)
{
      return *str ? my_strlen(str+1, acc + 1) : acc;
}

char * my_strcpy(char *strDest, const char *strSrc)
{
    char *temp = NULL;
    if (strDest!=NULL && strSrc!=NULL)
    {
        char *temp = strDest;
        while((*strDest++ = *strSrc++) != '\0');
    }
    return temp;
}