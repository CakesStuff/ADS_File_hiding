#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Could probably be changed to ":Zone.Identifier" to hide better
#define ADS_NAME ":Data"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open %s\n", argv[1]);
        return 2;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);

    char* content = malloc(length);
    fread(content, length, 1, file);
    fclose(file);

    printf("Read file successfully...\n");

    printf("Clearing file...\n");
    fclose(fopen(argv[1], "w"));

    char* adsName = malloc(strlen(argv[1]) + 1 + strlen(ADS_NAME));
    sprintf(adsName, "%s%s", argv[1], ADS_NAME);

    printf("Got name %s for ads...\n", adsName);

    file = fopen(adsName, "w");
    if(file == NULL)
    {
        printf("Somehow opening this ads: \"%s\" failed?", adsName);
        free(content);
        free(adsName);
        return 3;
    }

    if(fwrite(content, length, 1, file) != 1)
    {
        printf("Writing this ads: \"%s\" probably failed.", adsName);
        free(content);
        fclose(file);
        remove(adsName);
        free(adsName);
        return 4;
    }

    printf("Wrote ads successfully...\n");

    fclose(file);
    free(content);
    free(adsName);

    printf("Success.\n");

    return 0;
}