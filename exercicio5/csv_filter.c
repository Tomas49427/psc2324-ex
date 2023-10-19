#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_column(FILE* input, FILE* output, int is_case_sensitive, int column, char * pattern);

int main(int argc, char **argv){
    int option;
    char * input_path = NULL;
    char * output_path = NULL;
    int case_sensitive = 0;
    int column;
    char * pattern = NULL;
    int arguments = 0;
    char * environment_path = getenv("CSV_FILTER_PATH");
    while ((option = getopt(argc, argv, "o:i:c")) != -1){
        switch (option) {
            case 'o':
                output_path = optarg;
                arguments++;
                break;
            case 'i':
                input_path = optarg;
                arguments++;
                break;
            case 'c':
                case_sensitive++;
                arguments++;
                break;
            default:
                fprintf(stderr,"Invalid Arguments");
                exit(EXIT_FAILURE);
        }
    }

    column = atoi(argv[optind]);
    pattern = argv[++optind];
    if(column == 0 || pattern == NULL){
        fprintf(stderr,"Invalid Arguments");
        exit(EXIT_FAILURE);
    }

    FILE * input_file;
    FILE * output_file;
    if(input_path == NULL){
        input_file = stdin;
    } else{
        if(environment_path != NULL){
            strcat(environment_path,"/");
            strcat(environment_path,input_path);
            input_file = fopen(environment_path,"r");
        } else{
            input_file = fopen(input_path,"r");
        }
    }
    if(output_path == NULL){
        output_file = stdout;
    } else{
        output_file = fopen(output_path,"w");
    }
    return write_column(input_file,output_file,case_sensitive,column,pattern);
}

int write_column(FILE* input, FILE* output, int is_case_sensitive, int column, char * pattern){
    char * current_line = calloc(64,sizeof(char));
    int c;
    int index = 0;
    int successful = 0;
    while((c = fgetc(input)) != EOF){
        if(c == '\n'){
            int current_column = 1;
            char * current_string = strdup(current_line);
            char * token;
            while ((token = strsep(&current_string,",")) != NULL){
                if(current_column == column){
                    if(is_case_sensitive == 0){
                        if(strcasecmp(token,pattern) == 0){
                            fputs(current_line,output);
                            fputs("\n",output);
                            successful = 1;

                        }
                    }
                    if(is_case_sensitive == 1){
                        if(strcmp(token,pattern) == 0){
                            fputs(current_line,output);
                            fputs("\n",output);
                            successful = 1;
                        }
                    }
                }
                current_column++;
            }
            free(current_line);
            current_line = calloc(64,sizeof(char));
            index = 0;
        }
        if(strlen(current_line) == 64){
            char * buffer = calloc(strlen(current_line) * 2,sizeof(char));
            strcpy(buffer,current_line);
            current_line = buffer;
        }
        if(c != '\n'){
            current_line[index] = (char) c;
            index++;
        }
    }
    if(successful == 1){
        fclose(output);
        fclose(input);
        return 0;
    }
    return 1;
}