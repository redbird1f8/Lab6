#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include <pthread.h>

typedef struct FactArgs FactArgs;
struct FactArgs {
    u_int64_t begin;
    u_int64_t end;
    u_int64_t mod;
};

u_int64_t Fact(const struct FactArgs *args);

u_int64_t MultModulo(u_int64_t a, u_int64_t b, u_int64_t mod);
