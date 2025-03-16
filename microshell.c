#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <signal.h>
#include <pwd.h>

#define HISTORY_SIZE 10000
char* history[HISTORY_SIZE];
int history_index = 0;
void clear_history(){
    if(history_index==0){
       printf("array jest juz wyczyszczony");
    }else{
        for (int i=0;i<history_index;i++) {
            history[i] = NULL;
        }
        history_index = 0;
    }
}

void add_to_history(char* komenda, int history_index) {
    if(history_index < HISTORY_SIZE){
    history[history_index] = komenda;
    } else{
        clear_history();
        history_index =0;
        add_to_history(komenda, history_index);
    }
}

void print_history(char **history,int history_index) {
        if(history_index!=0){
        for(int i=0;i<history_index;i++){
            printf("%d %s\n",i, history[i]);
        }
        }else{
            printf("\n");
        }
}

void history_to_file(char **history,int history_index){
    FILE *fp;
    fp = fopen("history.txt", "w");
    for(int i=0;i<history_index; i++) {
        fprintf(fp, "%d %s\n", i, history[i]);
    }
    fclose(fp);
}

void history_to_file2(char **history,int history_index){
    FILE *fp;
    fp = fopen("history.txt", "a");
    for (int i=0;i<history_index;i++) {
        fprintf(fp, "%d %s\n", i, history[i]);
    }
    fclose(fp);
}
void cat(const char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("     /\\__/\\\n");
        printf("    /`    '\\\n");
        printf("  === \033[0;31;49m>  <\033[0m ===\n");
        printf("    \\  --  /\n");
        printf("   /        \\\n");
        printf("  /          \\\n");
        printf(" |            |\n");
        printf("  \\  ||  ||  /\n");
        printf("   \\_oo__oo_/#######o\n");
        perror("\033[0;31;49mError opening file\033[0m ===");
        return;
    }
    int x;
    while((x=fgetc(fp))!=EOF) {
        putchar(x);
    }
    fclose(fp);
}
void cat_A(const char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        perror("\033[0;31;49mError opening file\033[0m ===");
        return;
    }
    int x;
    while((x=fgetc(fp))!=EOF) {
        if(x=='\n'){
            putchar(x);
            putchar('$');
        }else if(x < 32 || x == 127){
            putchar('^');
            putchar(x+'@');
        }else{
            putchar(x);
        }
    }
    fclose(fp);
}
void cat_n(const char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        perror("\033[0;31;49mError opening file\033[0m ===");
        return;
    }

    int x;
    int line_number = 1;
    printf("%6d  ", line_number);
    while((x=fgetc(fp))!=EOF) {
            if(x=='\n'){
                putchar(x);
                line_number++;
                printf("%6d  ", line_number);
            }else{
                putchar(x);
            }
    }
    fclose(fp);
}


void placeholder(){
};
int main() {
signal(SIGINT, placeholder); /*linijka doradzona przez kolegę Kuroczenko, mająca na celu naprawę control c w forku*/
	while (1) {
	    
		char userin[10000];
		char* rozdzielony_userin;
		const char znaki_biale[16] = " \n\t";
		char sciezka[1000];
		setenv("OLDPWD", sciezka, 1);
		getcwd(sciezka, sizeof(sciezka));
		struct passwd *pw = getpwuid(geteuid());
        printf("\033[0;32m%s\033[0m:\033[0;34m%s\033[0m$ ", pw->pw_name, sciezka);
		fgets(userin,200,stdin);
		char *test = strdup(userin);
        test[strlen(test) - 1] = '\0';
        
        add_to_history(test, history_index);
        history_index++;
		rozdzielony_userin = strtok(userin, znaki_biale);
		int ilosc_arg = 0;
		char* polecenie_argumenty[10000];
		
		while (rozdzielony_userin != NULL) {
			polecenie_argumenty[ilosc_arg] = rozdzielony_userin;
			ilosc_arg++;
			rozdzielony_userin = strtok(NULL, znaki_biale);
		}
		if (ilosc_arg ==0){
		    continue;
		}
        		
		polecenie_argumenty[ilosc_arg] = NULL;
      
		if (strcmp(polecenie_argumenty[0], "help") == 0) {
			printf("Mikroshell autorstwa Bartosza Hornung\n");
			printf("Obsługiwane są proste, podstawowe komendy: help, cd(.., -, ~), exit, echo\n");
			printf("Polecenie: history. Zostało zaimplementowane samodzielnie z parametrami:\n");
			printf("-c czysci historie\n");
			printf("-w tworzy plik history.txt i dodaje do niego zawartość historii\n");
			printf("-a dodaje do pliku aktualną zawartość historii\n");
			printf("Polecenie: cat. Zostało zaimplementowane samodzielnie z parametrami:\n");
			printf("-A wyswietla zawartosc plinku wlacznie z znakami bialymi\n");
			printf("-n numerje linie pliku\n");
			printf("Pozostałe komendy są wykonywane poprzez PATH\n");
		} else if(strcmp(polecenie_argumenty[0], "echo") == 0) {
			int licznik = 1;
			while (polecenie_argumenty[licznik] != NULL) {
				printf("%s ", polecenie_argumenty[licznik]);
				licznik++;
			}
			printf("\n");
			
		}
		else if(strcmp(polecenie_argumenty[0], "history") == 0) {
		    if (ilosc_arg == 1) {
                 print_history(history,history_index);
    		} else if(strcmp(polecenie_argumenty[1],"-c")==0){
    		    clear_history(history,history_index);
    		}
    		 else if(strcmp(polecenie_argumenty[1],"-a")==0){
    		    history_to_file(history,history_index);
    		}
    		else if(strcmp(polecenie_argumenty[1],"-w")==0){
    		    history_to_file2(history,history_index);
    		}
    		else if(strcmp(polecenie_argumenty[1],"-aw")==0||strcmp(polecenie_argumenty[1],"-wa")==0||strcmp(polecenie_argumenty[1],"-acw")==0||strcmp(polecenie_argumenty[1],"-caw")==0||strcmp(polecenie_argumenty[1],"-wac")==0||strcmp(polecenie_argumenty[1],"-awc")==0){
    		    printf("według specyfikacji funkcji history nie można jednocześnie uzywac parametrow 'w' oraz 'a'\n");
    		}
    		else{
    		    print_history(history,history_index);
    		}
		 
		}
		else if(strcmp(polecenie_argumenty[0], "cat") == 0) {
		      if (ilosc_arg == 1){
            	printf("     /\\__/\\\n");
                printf("    /`    '\\\n");
                printf("  === \033[0;34;49m0  0\033[0m ===\n");
                printf("    \\  --  /\n");
                printf("   /        \\\n");
                printf("  /          \\\n");
                printf(" |            |\n");
                printf("  \\  ||  ||  /\n");
                printf("   \\_oo__oo_/#######o\n");
                printf("\033[0;34;49mNie poddano żadnego argumentu\n\033[0m");
    		} else if(strcmp(polecenie_argumenty[1], "-A")==0){
    		          for (int i=2;i<ilosc_arg;i++) {
                        cat_A(polecenie_argumenty[i]);
                        }
    		          printf("\n");

    		} 
    		else if(strcmp(polecenie_argumenty[1], "-n")==0){
    		          for (int i=2;i<ilosc_arg;i++) {
                        cat_n(polecenie_argumenty[i]);
                        }                        printf("\n");

    		    
    		} else{
    		    for (int i=1;i<ilosc_arg;i++) {
                    cat(polecenie_argumenty[i]);
                    }
    		}
		    
		}else if (strcmp(polecenie_argumenty[0],"cd") == 0) {
    		if (ilosc_arg == 1) {
                char* home = getenv("HOME");
                chdir(home);
    		}
		    else if(strcmp(polecenie_argumenty[1], "~")==0){
		        if(chdir(getenv("HOME")) == -1){
                    perror("\033[0;31;49mError changing directory\033[0m");
		        } else {
		            chdir(getenv("HOME"));  
		        }
		    } else if(strcmp(polecenie_argumenty[1],"-")==0){
                    char *previous_directory = getenv("OLDPWD");
                    if(previous_directory == NULL){
                        printf("\033[0;31;49mPrevious directory not set\n\033[0m");
                    } else if(history_index==1){
                          printf("\033[0;31;49mPrevious directory not set\n\033[0m");
                    }
                    else{
                        if(chdir(previous_directory) == -1){
                            perror("\033[0;31;49mError changing directory\033[0m");
                        } else {
                            setenv("OLDPWD", sciezka, 1);
                            chdir(previous_directory);   
                        } 
                    }
                } else {
			        if(chdir(polecenie_argumenty[1]) == -1){
                        perror("\033[0;31;49mError changing directory\033[0m");
                        }
		            }
		} 
		
		else if (strcmp(polecenie_argumenty[0], "exit") == 0) {
			exit(0);
		} else {
			pid_t pid = fork();
			if (pid == 0) {
				int x = execvp(polecenie_argumenty[0], polecenie_argumenty);
				if (x == -1) {
					perror("\033[0;31;49mError executing command\033[0m");
					exit(EXIT_FAILURE);
				}
			}
			else if(pid <0)  {
			    exit(1);
            } else {
                  wait(NULL);
                }
		}
	}
	return 0;
}
