//=====[#include guards - begin]===============================================

#ifndef _TAG_H_
#define _TAG_H_


//=====[Declaration of public defines]=========================================

#define UID_MAX_SIZE 10


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

#include <vector>
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
    tagStatus_t tagStatus;


};

class TagList {
public:
    TagList();
    ~TagList();
    
    void addTag(const char *);
    bool find(const char *);
    void removeTag(const char *);
    void clear();
    //const char* getTag(const char *UID);
    size_t getTagListSize();

private:
    std::vector<Tag> tags;


};

#endif // TAGLIST_H


#endif // _TAG_H_
