//=====[#include guards - end]=================================================

#include "mbed.h"
#include "tagLITE.h"

//=====[Implementations of public functions]===================================
void TagLITE_init(TagLITE* tag)
{
    memset(tag->UID, 0, UID_MAX_SIZE);
    tag->UID_size = 0;
    tag->tagStatus = TAG_NONE;
}

void TagLITE_initWithUID(TagLITE* tag, const char* UID)
{
    strncpy(tag->UID, UID, UID_MAX_SIZE);
    tag->UID_size = strlen(UID);
    tag->tagStatus = TAG_NONE;
}

const char* TagLITE_getUID(const TagLITE* tag)
{
    return tag->UID;
}

void TagLITE_clear(TagLITE* tag)
{
    memset(tag->UID, 0, UID_MAX_SIZE);
    tag->UID_size = 0;
    tag->tagStatus = TAG_NONE;
}

void TagListLITE_init(TagListLITE* tagList)
{
    tagList->size = 0;
}

void TagListLITE_addTag(TagListLITE* tagList, const char* UID)
{
    if (tagList->size < MAX_LIST_SIZE)
    { 
        TagLITE_initWithUID(&tagList->tags[tagList->size], UID);
        tagList->size++;
    }
}

bool TagListLITE_find(const TagListLITE* tagList, const char* UID)
{
    for (size_t i = 0; i < tagList->size; ++i)
    {
        if (strcmp(tagList->tags[i].UID, UID) == 0)
        {
            printf("TagListLITE: Encontre el Tag: %s\n", UID);
            return true;
        }
    }
    return false;
}

void TagListLITE_removeTag(TagListLITE* tagList, const char* UID)
{
    for (size_t i = 0; i < tagList->size; ++i)
    {
        if (strcmp(tagList->tags[i].UID, UID) == 0)
        {
            for (size_t j = i; j < tagList->size - 1; ++j)
            {
                tagList->tags[j] = tagList->tags[j + 1];
            }
            tagList->size--;
            return;
        }
    }
}

void TagListLITE_clear(TagListLITE* tagList)
{
    tagList->size = 0;
}

size_t TagListLITE_getSize(const TagListLITE* tagList)
{
    return tagList->size;
}
