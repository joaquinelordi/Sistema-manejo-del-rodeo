//=====[#include guards - begin]===============================================

#ifndef _TAG_H_
#define _TAG_H_


//=====[Declaration of public defines]=========================================

#define UID_MAX_SIZE 32
#define MAX_LIST_SIZE 20

//=====[Declaration of public data types]======================================

typedef enum
{
    TAG_ENABLE,
    TAG_DISABLE,
    TAG_ERROR,
    TAG_NONE      

    } tagStatus_t;

typedef enum
{
    GROUP_DEFAULT = 0,
    GROUP_A,
    GROUP_B

    } group_t;
//=====[Declarations (prototypes) of public functions]=========================


//=====[#include guards - end]=================================================

#ifndef TAGLIST_H
#define TAGLIST_H

#include <cstring>

class Tag
{
public:
    Tag();
    Tag(const char *, group_t = GROUP_DEFAULT);
    Tag(const char *, const char *);
    ~Tag();
    

    const char* getTagUID() const;
    void clear();
    group_t getAssignedGroup();
    void setAssignedGroup(char*);

private:
    char _UID[UID_MAX_SIZE];
    size_t _UID_size;
    group_t _assignedGroup;
    tagStatus_t _tagStatus;

};

class TagList
{
public:
    TagList();
    ~TagList();
    
    void addTag(const Tag *);
    bool find(const char *);
    void clear();
    Tag* getTag(const char *);
    size_t getTagListSize();

private:
    Tag _listTags[MAX_LIST_SIZE];
    size_t _listSize;

};

#endif // TAGLIST_H


#endif // _TAG_H_

