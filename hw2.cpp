#include <iostream>
#include <vector>
#include <dlfcn.h>

#include <sys/stat.h>
#include <unistd.h>

using namespace std;

string INT(int n)
{
	return to_string(n);
}

string STR(const char* s)
{
	return "\"" + string(s) + "\"";
}

void log(string name, vector<string> args, string ret)
{
	cerr<<"[logger] "<<name<<":(";
    for(auto &arg: args)
    {
        if((&arg - &args[0]) != 0)
			cerr<<", ";
		cerr<<arg;
    }
	cerr<<") = "<<ret<<endl;
}

int chmod(const char *path, mode_t mode)
{
    typedef int (*fp)(const char*, mode_t);
    fp func = (fp)dlsym(RTLD_NEXT,"chmod");
    int ret = func(path, mode);
    log("chmod", {STR(path), INT(mode)}, INT(ret));
	return ret;
}

int chown(const char *path, uid_t owner, gid_t group)
{
    typedef int (*fp)(const char*, uid_t, gid_t);
    fp func = (fp)dlsym(RTLD_NEXT,"chown");
	int ret = func(path, owner, group);
	log("chown", {STR(path), INT(owner), INT(group)}, INT(ret));
	return ret;
}

int close(int fildes)
{
    typedef int (*fp)(int);
    fp func = (fp)dlsym(RTLD_NEXT,"close");
	int ret = func(fildes);
	log("close", {INT(fildes)}, INT(ret));
	return ret;
}
