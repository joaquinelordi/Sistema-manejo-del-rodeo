
//=====[#include guards - begin]===============================================

#ifndef _TAG_H_
#define _TAG_H_


//=====[Declaration of public defines]=========================================

#define UID_MAX_SIZE 10
#define MAX_LIST_SIZE 5

//=====[Declaration of public data types]======================================

typedef enum{
    TAG_ENABLE,
    TAG_DISABLE,
    TAG_ERROR,
    TAG_NONE
       
} tagStatus_t;

//=====[Declarations (prototypes) of public functions]=========================


//=====[#include guards - end]=================================================

#ifndef TAGLIST_H
#define TAGLIST_H

#include <cstring>

class Tag {
public:
    Tag();
    Tag(const char *);
    ~Tag();
    
    // Métodos publicos
    const char* getTagUID() const;
    void clear();

private:
    char _UID[UID_MAX_SIZE];
    size_t _UID_size;
    tagStatus_t _tagStatus;

};

class TagList {
public:
    TagList();
    ~TagList();
    
    void addTag(const char *);
    bool find(const char *);
    void clear();
    //const char* getTag(const char *UID);
    size_t getTagListSize();

private:
    Tag _listTags[MAX_LIST_SIZE];
    size_t _listSize;

};

#endif // TAGLIST_H


#endif // _TAG_H_

