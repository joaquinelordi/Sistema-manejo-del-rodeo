//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "tag.h"
#include <cstring>
#include "my_stdlib.h"
#include <vector>


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============


//=====[Declaration and initialization of private global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============


//=====[Implementations of public functions]===================================

Tag::Tag()
{
    memset(_UID, 0, sizeof(_UID));
    _UID_size = 0;
}

Tag::Tag(const char *UID)
{
    my_strcpy(_UID, UID);
}

Tag::~Tag()
{

}

const char* Tag::getTagUID() const
{
    return _UID;
}


TagList::TagList()
{

}

TagList::~TagList()
{

}


void TagList::addTag(const char *UID)
{
    tags.push_back(UID);
}

bool TagList::find(const char *UID)
{
    for (size_t i = 0; i < tags.size(); ++i)
    {
        if (strcmp(tags[i].getTagUID(), UID) == 0)
        {
            printf("TagList eencontre el Tag: %s", UID);
            return true;
        }
    }
    return false;
}


void TagList::removeTag(const char *UID)
{
    for (size_t i = 0; i < tags.size(); ++i) {
        if (strcmp(tags[i].getTagUID(), UID) == 0) {
            tags.erase(tags.begin() + i);
            return;
        }
    }
}

void TagList::clear() {
    tags.clear();
}

size_t TagList::getTagListSize()
{
    return tags.size();
}

//=====[Implementations of private functions]==================================
