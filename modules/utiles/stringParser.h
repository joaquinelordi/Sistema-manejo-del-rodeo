#define MIN_LENGH 8
#define MAX_LENGH 14
#define BEGIN_DELIMITER '{'
#define END_DELIMITER   '}'
#define CHAR_DELIMIRER  '-'
#define MAX_UID_SIZE 10
#define MAX_GROUP_SIZE 1

bool isAValidTag(char* str);
char** deserializeTag(char* str);
