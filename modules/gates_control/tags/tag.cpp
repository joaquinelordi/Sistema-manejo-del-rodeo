
//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "tag.h"
#include <cstring>
#include "my_stdlib.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============


//=====[Declaration and initialization of private global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============


//=====[Implementations of public functions]===================================

// CLASE TAG

Tag::Tag()
{
    memset(_UID, 0, sizeof(_UID));
    _UID_size = 0;
    _assignedGroup = GROUP_DEFAULT;
    _tagStatus = TAG_NONE;
}

Tag::Tag(const char *UID, group_t assignedGroup)
{
    my_strcpy(_UID, UID);
    _UID_size = sizeof(_UID);
    _tagStatus = TAG_ENABLE;
    _assignedGroup = assignedGroup;
}

Tag::Tag(const char *UID, const char *sGroup)
{
    my_strcpy(_UID, UID);
    _UID_size = sizeof(_UID);
    _tagStatus = TAG_ENABLE;

    if(*sGroup == 'A')
    {
        printf("Tag-> se asigna grupo A\n");
        _assignedGroup = GROUP_A;
    }
    else if(*sGroup == 'B')
    {
        printf("Tag-> se asigna grupo B\n");
         _assignedGroup = GROUP_B;
    }
    else
    {
        printf("Tag-> se asigna grupo por default\n");
        _assignedGroup = GROUP_DEFAULT;        
    }    
}

Tag::~Tag()
{

}

const char* Tag::getTagUID() const
{
    return _UID;
}

group_t Tag::getAssignedGroup()
{
    return _assignedGroup;
}

void Tag::setAssignedGroup(char *sGroup)
{
    if(*sGroup == 'A')
    {
        printf("Tag-> se asigna grupo A\n");
        _assignedGroup = GROUP_A;
    }
    else if(*sGroup == 'B')
    {
        printf("Tag-> se asigna grupo B\n");
         _assignedGroup = GROUP_B;
    }
    else
    {
        printf("Tag-> se asigna grupo por default\n");
        _assignedGroup = GROUP_DEFAULT;        
    }  
}

// CLASE TAG LIST

TagList::TagList()
{
    memset(_listTags, 0, sizeof(_listTags));
    _listSize = 0;
}

TagList::~TagList()
{

}

void Tag::clear()
{
     memset(_UID, 0, sizeof(_UID));
    _UID_size = 0;
    _tagStatus = TAG_DISABLE;
}

void TagList::addTag(const Tag* pTag)
{
    // _listSize -> ultimo elemento del arreglo
    if (_listSize < MAX_LIST_SIZE)
    {
        _listTags[_listSize] = *pTag;
        _listSize++;
        printf("TagList: Tag agregado: %s\n", pTag->getTagUID());
    }
    else
    {
        printf("TagList: lista llena.\n");
    }
}

bool TagList::find(const char *UID)
{
    for (size_t i = 0; i < _listSize; ++i)
    {
        if (strcmp(_listTags[i].getTagUID(), UID) == 0)
        {
            printf("TagList encontre el Tag: %s\n", UID);
            return true;
        }
    }
    return false;
}


void TagList::clear()
{
    for (size_t i = 0; i < _listSize; ++i)
    {
        _listTags[i].clear();
        _listSize = 0;
    }
}

size_t TagList::getTagListSize()
{
    return _listSize;
}

// cosas
Tag* TagList::getTag(const char *sUID)
{
    Tag* pTag = NULL;
    for (size_t i = 0; i < _listSize; ++i)
    {
        if (strcmp(_listTags[i].getTagUID(), sUID) == 0)
        {
            pTag = &_listTags[i];
        }
    }
    return pTag;
}

//=====[Implementations of private functions]==================================

