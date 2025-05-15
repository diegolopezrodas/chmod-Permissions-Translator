#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int translatePerm(char* binaryPerm) {
    
    int permValue = 0;
    
    for(int index = 2, power = 0; index > -1; index--, power++) {
        
        if(binaryPerm[index] == '1') {
            permValue += (1 << power);
        }
    }

    return permValue;
} //End of translatePerm(char* binaryPerm)

char* getEntity(int entityID) {

    switch(entityID) {
        case 0:
            return "admin";
        case 1:
            return "user";
        default:
            return "world";
    }

} //End of getEntity(int entityID)

char* askPermissions(int entityID) {
    
    char rwx[3][8] = {"read", "write", "execute"};
    char* fullBinaryPerms = malloc(4 * sizeof(char));

    if (fullBinaryPerms == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    int  permsHolder;
    
    for(int rwxIndex = 0; rwxIndex < 3; rwxIndex++){
        printf("\nDo you wish for %s to have %s priviledges? (NO = 0, YES = 1)\n", getEntity(entityID), rwx[rwxIndex]);
        scanf("%d", &permsHolder);
        fullBinaryPerms[rwxIndex] = (char)(permsHolder + '0');
    }

    fullBinaryPerms[3] = '\0';

    return fullBinaryPerms;

} //End of askPermissions(int entityID)

void chmodValueToExecute() {

    char command[10] = "chmod ";
    char valueBuffer[4];

    for(int index = 0; index < 3; index++){
        char* perms = askPermissions(index);
        valueBuffer[index] = (char)(translatePerm(perms) + '0');
        free(perms);
    }
    
    valueBuffer[3] = '\0';

    strcat(command, valueBuffer);

    printf("\nThe command you must enter on your terminal for the given permissions is:\n%s\n", command);

} //End of chmodValueToExecute()

int main(void) {
    
    chmodValueToExecute();

    return 0;
} //End of main(void)
