#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tema1_functions.h"

void call_command(char *command, Dir **curr_dir, Dir *home) {
    // Calling the wanted command

    if(strcmp(command, "touch") == 0) {
        char *filename = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        scanf("%s", filename);

        touch(*curr_dir, filename);
        free(filename);
        return;
    }

    if(strcmp(command, "mkdir") == 0) {
        char *directoryname = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        scanf("%s", directoryname);

        mkdir(*curr_dir, directoryname);
        free(directoryname);
        return;
    }

    if(strcmp(command, "ls") == 0) {
        ls(*curr_dir);
        return;
    }

    if(strcmp(command, "rm") == 0) {
        char *removefile = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        scanf("%s", removefile);

        rm(*curr_dir, removefile);
        free(removefile);
        return;
    }

    if(strcmp(command, "rmdir") == 0) {
        char *removedir = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        scanf("%s", removedir);

        rmdir(*curr_dir, removedir);
        free(removedir);
        return;
    }

    if(strcmp(command, "cd") == 0) {
        char *dirname = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        scanf("%s", dirname);

        cd(curr_dir, dirname);
        free(dirname);
        return;
    }

    if(strcmp(command, "tree") == 0) {
        tree(*curr_dir, 0);
        return;
    }

    if(strcmp(command, "pwd") == 0) {
        char *working_directory = pwd(*curr_dir);
        printf("%s\n", working_directory);

        free(working_directory);
        return;
    }

    if(strcmp(command, "stop") == 0) {
        // Frees the memory of all the directories inside the home
        // directory

        stop(home);
        return;
    }

    if(strcmp(command, "mv") == 0) {
        // Reading the two names
        char *oldname = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        char *newname = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
        scanf("%s %s", oldname, newname);

        mv(*curr_dir, oldname, newname);

        free(oldname);
        free(newname);
        return;
    }
    
}

void touch (Dir* parent, char* name) {
    // Searching for a file with this name
    File *curr_file = parent->head_children_files;
    while(curr_file != NULL) {
        if(strcmp(curr_file->name, name) == 0) {
            printf("File already exists\n");
            return;
        }
        curr_file = curr_file->next;
    }

    // Searching for the filename in the directory list
    Dir *curr_dir = parent->head_children_dirs;
    while(curr_dir != NULL) {
        if(strcmp(curr_dir->name, name) == 0) {
            printf("File already exists\n");
            return;
        }
        curr_dir = curr_dir->next;
    }

    // If the name has not been used, a new file is created
    File *new_file = malloc(sizeof(File));
    new_file->name = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);

    // Initializing the fields for a file
    strcpy(new_file->name, name);
    new_file->parent = parent;

    // Adding the file in the list

    // If we add the first file
    if(parent->head_children_files == NULL) {
        parent->head_children_files = new_file;
        new_file->next = NULL;
        return;
    }

    // If we add anywhere else in the list
    curr_file = parent->head_children_files;
    while(curr_file->next != NULL) {
        curr_file = curr_file->next;
    }
    curr_file->next = new_file;
    new_file->next = NULL;
}

void mkdir (Dir* parent, char* name) {
    // Searching if a directory with this name exists
    Dir *curr_dir = parent->head_children_dirs;
    while(curr_dir != NULL) {
        if(strcmp(curr_dir->name, name) == 0) {
            printf("Directory already exists\n");
            return;
        }
        curr_dir = curr_dir->next;
    }

    // Searching for the directory name in the file list
    File *curr_file = parent->head_children_files;
    while(curr_file != NULL) {
        if(strcmp(curr_file->name, name) == 0) {
            printf("Directory already exists\n");
            return;
        }
        curr_file = curr_file->next;
    }

    // If the name has not been used we create the directory
    Dir *new_dir = malloc(sizeof(Dir));
    new_dir->name = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);

    // Initializing all the fields for a directory
    strcpy(new_dir->name, name);
    new_dir->parent = parent;
    new_dir->head_children_files = NULL;
    new_dir->head_children_dirs = NULL;
    new_dir->next = NULL;

    // Adding the directory in the directory list

    // Adding the first directory in the list
    if(parent->head_children_dirs == NULL) {
        parent->head_children_dirs = new_dir;
        return;
    }

    // Adding the directory on the last position in the list
    curr_dir = parent->head_children_dirs;
    while(curr_dir->next != NULL) {
        curr_dir = curr_dir->next;
    }
    curr_dir->next = new_dir;
    new_dir->next = NULL;
}

void ls (Dir* parent) {
    // Printing the name of all the directories
    Dir *curr_dir = parent->head_children_dirs;
    while(curr_dir != NULL) {
        printf("%s\n", curr_dir->name);
        curr_dir = curr_dir->next;
    }

    // Printing the file names in the current directory
    File *curr_file = parent->head_children_files;
    while(curr_file != NULL) {
        printf("%s\n", curr_file->name);
        curr_file = curr_file->next;
    }
}

void rm (Dir* parent, char* name) {
    File *curr_file = parent->head_children_files;

    // Verify if the file list in the parent directory is empty
    if(curr_file == NULL) {
        printf("Could not find the file\n");
        return;
    }

    // Verify if the first file has to be removed
    if(strcmp(curr_file->name, name) == 0) {
        File *free_file = curr_file;
        parent->head_children_files = curr_file->next;

        free(free_file->name);
        free(free_file);
        return;
    }

    // Searching for the file by its name
    while(curr_file->next != NULL) {
        // If the file is found it is removed from the list
        if(strcmp(curr_file->next->name, name) == 0) {
            File *removed_file = curr_file->next;
            curr_file->next = curr_file->next->next;

            // Freeing the memory of the removed file
            free(removed_file->name);
            free(removed_file);
            return;
        }
        curr_file = curr_file->next;
    }

    // Printing the error messaje if the file doesn't exist
    printf("Could not find the file\n");

}

void remove_dir_rec(Dir **parent) {
    // Verify if the directory is null
    if(*parent == NULL) {
        return;
    }


    // Removing all the files in the directory
    File *remove_file;
    File *curr_file = (*parent)->head_children_files;

    while(curr_file != NULL) {
        remove_file = curr_file;
        curr_file = curr_file->next;

        free(remove_file->name);
        free(remove_file);
    }

    // Removing all the directories
    Dir *remove_dir;
    Dir *curr_dir = (*parent)->head_children_dirs;

    while(curr_dir != NULL) {
        remove_dir = curr_dir;
        curr_dir = curr_dir->next;

        remove_dir_rec(&remove_dir);
        free(remove_dir->name);
        free(remove_dir);
    }
}

void rmdir (Dir* parent, char* name) {
    // Searching for the directory in the parent
    Dir *curr_dir = parent->head_children_dirs;

    // Verify if the parent's head directory list is empty
    if(parent->head_children_dirs == NULL) {
        printf("Could not find the dir\n");
        return;
    }

    // Verify if the first directory has the name
    if(strcmp(curr_dir->name, name) == 0) {
        parent->head_children_dirs = curr_dir->next;

        remove_dir_rec(&curr_dir);
        free(curr_dir->name);
        free(curr_dir);
        return;
    }


    while(curr_dir->next != NULL) {
        if(strcmp(curr_dir->next->name, name) == 0) {
            Dir *free_dir = curr_dir->next;
            curr_dir->next = free_dir->next;

            remove_dir_rec(&free_dir);
            free(free_dir->name);
            free(free_dir);
            return;
        }
        curr_dir = curr_dir->next;
    }

    // If the directory doesn't exist
    printf("Could not find the dir\n");
}

void cd(Dir** target, char *name) {
    // Checking if the name of the directory is ".."
    if(strcmp(name, "..") == 0) {
        if((*target)->parent != NULL) {
            *target = (*target)->parent;
        }
        return;
    }

    // Searching for the directories name
    Dir *curr_dir = (*target)->head_children_dirs;
    while(curr_dir != NULL) {
        if(strcmp(curr_dir->name, name) == 0) {
            *target = curr_dir;
            return;
        }
        curr_dir = curr_dir->next;
    }

    // If the directory was not found
    if(curr_dir == NULL) {
        printf("No directories found!\n");
    }
}

void pwd_r(Dir *target, char *working_directory) {
    // Verifying if we are still in a directory
    if(target == NULL) {
        return;
    }

    // calling recursively the function
    pwd_r(target->parent, working_directory);

    // Remembering the name of the directory
    strcat(working_directory, "/");
    strcat(working_directory, target->name);
}

char *pwd (Dir* target) {
    // Allocating memory for the string that remembers the working directory
    char *working_directory = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
    strcpy(working_directory, "");

    // Calling a recursive function that adds to the working_directory
    // string the needed names
    pwd_r(target, working_directory);

    // Returning the wanted string. 
    return working_directory;
}

void stop (Dir* target) {
    // Deleting all the files in the home directory
    File *curr_file = target->head_children_files;
    File *free_file;

    while (curr_file != NULL) {
        free_file = curr_file;
        curr_file = curr_file->next;
        free(free_file->name);
        free(free_file);
    }

    // Deleting all the directories in the home directory
    Dir *curr_dir = target->head_children_dirs;
    Dir *free_dir;

    while(curr_dir != NULL) {
        free_dir = curr_dir;
        curr_dir = curr_dir->next;
        rmdir(target, free_dir->name);
    }
}

void tree (Dir* target, int level) {
    Dir *curr_dir = target->head_children_dirs;
    while(curr_dir != NULL) {
        for(int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("%s\n", curr_dir->name);
        tree(curr_dir, level + 1);
        curr_dir = curr_dir->next;
    }

    File *curr_file = target->head_children_files;
    while(curr_file != NULL) {
        for(int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("%s\n", curr_file->name);
        curr_file = curr_file->next;
    }
}

void mv(Dir* parent, char *oldname, char *newname) {
    // Bool variable which remembers if the newname has been used
    bool found_newname = false;

    // Searching for the name in the file list
    File *curr_file = parent->head_children_files;
    File *change_file = NULL;

    while(curr_file != NULL) {
        if(strcmp(curr_file->name, oldname) == 0) {
            change_file = curr_file;
        }
        if(strcmp(curr_file->name, newname) == 0) {
            found_newname = true;
        }

        curr_file = curr_file->next;
    }

    // Searching for the oldname in the directory list
    Dir *curr_dir = parent->head_children_dirs;
    Dir *change_dir = NULL;

    while(curr_dir != NULL) {
        if(strcmp(curr_dir->name, oldname) == 0) {
            change_dir = curr_dir;
        }
        if(strcmp(curr_dir->name, newname) == 0) {
            found_newname = true;
        }
        curr_dir = curr_dir->next;
    }

    // Error message if the newname is already used
    if(found_newname == true) {
        printf("File/Director already exists\n");

        return;
    }

    // Error message if the oldname doesn't exist
    if(change_dir == NULL && change_file == NULL) {
        printf("File/Director not found\n");

        return;
    }


    // Changing a file
    if(change_file) {
        // Removing the old file and adding a new file with the newname
        rm(parent, change_file->name);
        touch(parent, newname);

        return;
    }

    // Changing a directory
    if(change_dir) {
        // Creating a new directory
        mkdir(parent, newname);

        // Creating two pointers to point at the position
        // of the new directory prior made (which is put in the last position
        // of the list) and a pointer to the element before the oldname
        // element in the list
        Dir *last_dir;
        Dir *bef_change_dir;
        curr_dir = parent->head_children_dirs;

        while(curr_dir != NULL) {
            if(curr_dir->next == NULL) {
                last_dir = curr_dir;
            }
            if(curr_dir->next == change_dir) {
                bef_change_dir = curr_dir;
            }

            curr_dir = curr_dir->next;
        }

        // Changing the new directory's data and freeing the memory of the oldname

        // Verify if we have to change the first directory in the list
        if(change_dir == parent->head_children_dirs) {
            parent->head_children_dirs = change_dir->next;
            last_dir->head_children_dirs = change_dir->head_children_dirs;
            last_dir->head_children_files = change_dir->head_children_files;
            free(change_dir->name);
            free(change_dir);
            
            return;
        }

        // In the other cases
        last_dir->head_children_dirs = change_dir->head_children_dirs;
        last_dir->head_children_files = change_dir->head_children_files;
        bef_change_dir->next = bef_change_dir->next->next;
        free(change_dir->name);
        free(change_dir);
    

        return;
    }

}