#include <cstdio>
#include <dlfcn.h>
#include <sys/stat.h>

void log(char* name, int argc, char** argv, char* ret)
{
    printf("[logger] %s:(", name);
    for(int i = 0; i < argc; i++)
    {
        if(i != 0)
        {
            printf(", ");
        }
        printf("%s", argv[i]);
    }
    printf(") = %s\n", ret);
}

int chmod(const char *path, mode_t mode)
{
    typedef int (*fp)(const char*, mode_t);
    fp func = (fp)dlsym(RTLD_NEXT,"chmod");

    int ret = func(path, mode);
	return ret;
    //log("chmod", 2,)
}
