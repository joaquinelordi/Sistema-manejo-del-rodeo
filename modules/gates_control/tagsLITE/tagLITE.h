
//=====[#include guards - begin]===============================================

#ifndef _TAG_LITE_H_
#define _TAG_LITE_H_

#include <string.h>

//=====[Declaration of public defines]=========================================

#define UID_MAX_SIZE 10
#define MAX_LIST_SIZE 5

//=====[Declaration of public data types]======================================

typedef enum {
    TAG_ENABLE,
    TAG_DISABLE,
    TAG_ERROR,
    TAG_NONE
} tagStatus_t;

typedef struct {
    char UID[UID_MAX_SIZE];
    size_t UID_size;
    tagStatus_t tagStatus;
} TagLITE;

typedef struct {
    TagLITE tags[MAX_LIST_SIZE]; // Suponiendo un tamaño máximo de 100 tags, ajustar según necesidades
    size_t size;
} TagListLITE;

//=====[Declarations (prototypes) of public functions]=========================

void TagLITE_init(TagLITE* tag);
void TagLITE_initWithUID(TagLITE* tag, const char* UID);
const char* TagLITE_getUID(const TagLITE* tag);
void TagLITE_clear(TagLITE* tag);

void TagListLITE_init(TagListLITE* tagList);
void TagListLITE_addTag(TagListLITE* tagList, const char* UID);
bool TagListLITE_find(const TagListLITE* tagList, const char* UID);
void TagListLITE_removeTag(TagListLITE* tagList, const char* UID);
void TagListLITE_clear(TagListLITE* tagList);
size_t TagListLITE_getSize(const TagListLITE* tagList);


#endif // _TAG_LITE_H_
