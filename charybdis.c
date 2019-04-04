#include <getopt.h>
#include <stdio.h>
#include <curl/curl.h>
#include "requests.h"
#include <time.h>
#include <pthread.h> 
#define MAXCHAR 10000
void *myThreadFun(void *mystr) 
{   
    printf("%s",mystr);
    req_t req;
    CURL *curl = requests_init(&req);
    char* filly[] = {"Cookie: test=test"}; 
    requests_post_headers(curl, &req, "https://qqq.requestcatcher.com/",mystr,filly,1);
    requests_close(&req);
}
int main(int argc, char *argv[]){
    int opt;
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/john/project/wordl";  
    fp = fopen(filename, "r");
    pthread_t tid;
    while (fgets(str, MAXCHAR, fp) != NULL) {
        char *mystr=str;
        sleep(1);
        pthread_create(&tid, NULL, myThreadFun, (void *)mystr); 
    }
    while((opt = getopt(argc, argv, ":i:f:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'i':  
                printf("%i", optarg);  
                break;  
            case 'f':  
                printf("%s", optarg);  
                break; 
            case ':':
                fprintf(stderr, "%s: option '-%c' requires an argument\n",argv[0], optopt);
                break;
            case '?':
                fprintf(stderr, "Invalid option\n");
                break;
        }
    }  
      
    return 0; 
}