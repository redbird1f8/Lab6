#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include <pthread.h>

#include "fact.h"

uint64_t k = -1;
uint64_t mod = -1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

typedef struct Server Server;
struct Server {
    char ip[256];
    int port;
};

typedef struct ThreadArg ThreadArg;
struct ThreadArg {
    Server *server;
    FactArgs *args;
    //u_int64_t res;
};

/*u_int64_t SendRec(const ThreadArg *args) {
    u_int64_t ans = 1;

    // TODO: your code here
    printf("lol\n");
    printf("connecting %s:%d\n", ((ThreadArg*)args)->server->ip, ((ThreadArg*)args)->server->port);
    char port_str[20];
    struct addrinfo *ainf = NULL;
    sprintf(port_str, "%d", ((ThreadArg*)args)->server->port);
    printf("got address %s:%d\n", ((ThreadArg*)args)->server->ip, ((ThreadArg*)args)->server->port);
    getaddrinfo(((ThreadArg*)args)->server->ip, port_str, NULL, &ainf);
    
    //struct sockaddr_in server;
    //server.sin_family = AF_INET;
    //server.sin_port = htons(((ThreadArg*)args)->server->port);
    //server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);

    //int sck = socket(AF_INET, SOCK_STREAM, 0);
    int sck = socket(ainf->ai_family, ainf->ai_socktype, ainf->ai_protocol);
    if (sck < 0) {
        fprintf(stderr, "Socket creation failed!\n");
        exit(1);
    }

    //if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0) {
    if (connect(sck, (struct sockaddr *)(ainf->ai_addr), ainf->ai_addrlen) < 0) {
        fprintf(stderr, "Connection failed\n");
        exit(1);
    }
    freeaddrinfo(ainf);
    printf("Connected!\n");

    // TODO: for one server
    // parallel between servers
    uint64_t begin = 1;
    uint64_t end = k;

    if (send(sck, ((ThreadArg*)args)->args, sizeof(FactArgs), 0) < 0) {
        fprintf(stderr, "Send failed\n");
        exit(1);
    }
    printf("Data sent!\n");
    //uint64_t *response = malloc(sizeof(uint64_t));
    u_int64_t response;// = malloc(sizeof(u_int64_t*));
    if (recv(sck, &response, sizeof(u_int64_t), 0) < 0) {
        fprintf(stderr, "Recieve failed\n");
        exit(1);
    }
    
    close(sck);
    printf("Data received!\n");

    return response;
}*/

void *ClientThread(void *args) {
    //return (void *)(u_int64_t *)SendRec(args);
    /*pthread_mutex_lock(&mut);
    struct hostent *hostname = gethostbyname(((ThreadArg*)args)->server->ip);
    pthread_mutex_unlock(&mut);
    if (hostname == NULL) {
        fprintf(stderr, "gethostbyname failed with %s\n", ((ThreadArg*)args)->server->ip);
        exit(1);
    }*/
    printf("lol\n");
    printf("connecting %s:%d\n", ((ThreadArg*)args)->server->ip, ((ThreadArg*)args)->server->port);
    char port_str[20];
    struct addrinfo *ainf = NULL;
    sprintf(port_str, "%d", ((ThreadArg*)args)->server->port);
    printf("got address %s:%d\n", ((ThreadArg*)args)->server->ip, ((ThreadArg*)args)->server->port);
    getaddrinfo(((ThreadArg*)args)->server->ip, port_str, NULL, &ainf);
    
    //struct sockaddr_in server;
    //server.sin_family = AF_INET;
    //server.sin_port = htons(((ThreadArg*)args)->server->port);
    //server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);

    //int sck = socket(AF_INET, SOCK_STREAM, 0);
    int sck = socket(ainf->ai_family, ainf->ai_socktype, ainf->ai_protocol);
    if (sck < 0) {
        fprintf(stderr, "Socket creation failed!\n");
        exit(1);
    }

    //if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0) {
    if (connect(sck, (struct sockaddr *)(ainf->ai_addr), ainf->ai_addrlen) < 0) {
        fprintf(stderr, "Connection failed\n");
        exit(1);
    }
    freeaddrinfo(ainf);
    printf("Connected!\n");

    // TODO: for one server
    // parallel between servers
    uint64_t begin = 1;
    uint64_t end = k;

    if (send(sck, ((ThreadArg*)args)->args, sizeof(FactArgs), 0) < 0) {
        fprintf(stderr, "Send failed\n");
        exit(1);
    }
    printf("Data sent!\n");
    //uint64_t *response = malloc(sizeof(uint64_t));
    u_int64_t response;// = malloc(sizeof(u_int64_t*));
    if (recv(sck, &response, sizeof(u_int64_t), 0) < 0) {
        fprintf(stderr, "Recieve failed\n");
        exit(1);
    }
    
    close(sck);
    printf("Data received!\n");
    //return (void *)response;
    return (void *)(u_int64_t *)response;
}
/*typedef struct StrList StrList;
  struct StrList{
  Server adr;
  StrList *beg;
  StrList *next;
  };

  void ListInit(StrList* sl, Server *adr)
  {
  sl = malloc(sizeof(StrList));
  memcpy(sl->adr.ip, adr->ip, sizeof(char)*256);
  sl->adr.port = adr->port;
  sl->beg = sl;
  sl->next = NULL;
  }

  void ListAdd(StrList* sl, Server *adr)
  {
  sl->next = malloc(sizeof(StrList));
  memcpy(sl->next->adr.ip, adr->ip, sizeof(char)*256);
  sl->next->beg = sl->beg;
  sl->next->next = NULL;
  }

  void ListDestroy(StrList* sl)
  {
  StrList *np;
  while(sl->next != NULL)
  {
  np = sl->next;
  free(sl);
  sl = np;
  }
  free(sl);
  }
  */



bool ConvertStringToUI64(const char *str, uint64_t *val) {
    char *end = NULL;
    unsigned long long i = strtoull(str, &end, 10);
    if (errno == ERANGE) {
        fprintf(stderr, "Out of uint64_t range: %s\n", str);
        return false;
    }

    if (errno != 0)
        return false;

    *val = i;
    return true;
}

int main(int argc, char **argv) {
    //uint64_t k = -1;
    //uint64_t mod = -1;
    char servers[256] = {'\0'}; // TODO: explain why 255

    while (true) {
        int current_optind = optind ? optind : 1;

        static struct option options[] = {{"k", required_argument, 0, 0},
            {"mod", required_argument, 0, 0},
            {"servers", required_argument, 0, 0},
            {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "", options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0: {
                        switch (option_index) {
                            case 0:
                                ConvertStringToUI64(optarg, &k);
                                if(k <= 0)
                                {
                                    return 1;
                                }
                                // TODO: your code here
                                break;
                            case 1:
                                ConvertStringToUI64(optarg, &mod);
                                // TODO: your code here
                                if(k <= 1)
                                {
                                    return 1;
                                }
                                break;
                            case 2:
                                // TODO: your code here
                                memcpy(servers, optarg, strlen(optarg));
                                break;
                            default:
                                printf("Index %d is out of options\n", option_index);
                        }
                    } break;

            case '?':
                    printf("Arguments error\n");
                    break;
            default:
                    fprintf(stderr, "getopt returned character code 0%o?\n", c);
        }
    }

    if (k == -1 || mod == -1 || !strlen(servers)) {
        fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file\n",
                argv[0]);
        return 1;
    }

    // TODO: for one server here, rewrite with servers from file
    char srv[262];
    char *stopl;
    //srv = malloc(sizeof(char)*262);
    FILE* srv_lst;
    srv_lst = fopen(servers, "r");
    //
    unsigned int servers_num = 0;
    Server *to = NULL;
    int port; 
    char *delim_pos = NULL;
    // TODO: delete this and parallel work between servers
    while(fgets(srv, 262, srv_lst) != NULL){
    //do{
   //     stopl = fgets(srv, 262, srv_lst);
        ++servers_num;
        to = realloc(to, sizeof(struct Server) * servers_num);
        delim_pos = strchr(srv, ':');
        if(delim_pos){
            port = atoi(delim_pos + 1);
        }
        else
        {
            port = 20001;
        }
        to[servers_num-1].port = port;
        memcpy(to[servers_num-1].ip, srv, abs(delim_pos - srv)); 
        to[servers_num-1].ip[255] = '\0';
    }//while(stopl != NULL);
    fclose(srv_lst);
    //printf("created %s:%d\n", to[0].ip, to[0].port);
    //printf("created %s:%d\n", to[1].ip, to[1].port);
    //Arguments are being set here.
/*    struct FactArgs *fargs = malloc(sizeof(struct FactArgs) * servers_num);
    for(int i = 0; i < servers_num; ++i)
    {
        fargs[i].mod = mod;
        fargs[i].begin = tc*i + 1;
        if(i == servers_num - 1)
        {
            fargs[i].end = tc*(i+1) + k%servers_num;
        }
        else
        {
            fargs[i].end = tc*(i+1);
        }
    }*/
    ThreadArg *targs = malloc(sizeof(ThreadArg)*servers_num);
    int tc = k/servers_num;
    for(int i = 0; i < servers_num; ++i) {
        targs[i].args->mod = mod;
        targs[i].args->begin = tc*i + 1;
        if(i == servers_num - 1)
        {
            targs[i].args->end = tc*(i+1) + k%servers_num;
        }
        else
        {
            targs[i].args->end = tc*(i+1);
        }
        targs[i].server = &(to[i]);          //TODO Make it in different way!!!1
        //printf("created %s:%d\n", targs[i].server->ip, targs[i].server->port);
        
    }
    //printf("created %s:%d\n", targs[0].server->ip, targs[0].server->port);
    printf("Total\n");
    //Threads are being set here
    pthread_t *threads = malloc(sizeof(pthread_t) * servers_num);
    for (uint32_t i = 0; i < servers_num; ++i) {
        if (pthread_create(&threads[i], NULL, ClientThread, (void *)(targs + i))) {
            printf("Error: pthread_create failed!\n");
            return 1;
        }
    }
    // TODO: work continiously, rewrite to make parallel
    uint64_t result = 1;
    for (int i = 0; i < servers_num; i++) {
        u_int64_t srf;
        //printf("Tt: %d\n", sizeof(void *));
        pthread_join(threads[i], (void *)srf);
        result = (result * srf) % mod;

        //free(srf);
    }
    free(to);
    free(targs);
    printf("Total: %llu\n", result);

    return 0;
}
