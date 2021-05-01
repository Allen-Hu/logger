#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>

using namespace std;

string BRAC(string s)
{
	return "\"" + s + "\"";
}

string PATH(const char* s)
{
	char buf[256];
	char* result = realpath(s, buf);
	if(result)
		return BRAC(string(result));
	else
		return BRAC(string(s));
}

template<typename T>
string FD(T f)
{
	char fdpath[256];
	char buf[256];
	sprintf(fdpath, "/proc/self/fd/%d", f);
	ssize_t r = readlink(fdpath, buf, 256);
	if(r < 0) exit(1);
	buf[r] = 0;
	return BRAC(string(buf));
}

string FLAG(int f)
{
	stringstream ss;
	ss << oct << f;
	return ss.str();
}

string INT(int n)
{
	return to_string(n);
}

string BUF(const char* b)
{
	stringstream ss;
	int len = min((int)strlen(b), 32);
	for(int i = 0; i < len; i++)
	{
		if(isprint(b[i]))
			ss << b[i];
		else
			ss << '.';
	}
	return BRAC(ss.str());	
}

template<typename T>
string POINT(T* p)
{
	stringstream ss;
	ss << static_cast<void*>(p);
	return ss.str();
}

void log(string name, vector<string> args, string ret)
{
	cerr << "[logger] " << name << "(";
    for(auto &arg: args)
    {
        if((&arg - &args[0]) != 0)
			cerr << ", ";
		cerr << arg;
    }
	cerr << ") = " << ret << endl;
}

int chmod(const char *path, mode_t mode)
{
    typedef int (*fp)(const char*, mode_t);
    fp func = (fp)dlsym(RTLD_NEXT,"chmod");
    int ret = func(path, mode);
    log("chmod", {PATH(path), FLAG(mode)}, INT(ret));
	return ret;
}

// int chown(const char *path, uid_t owner, gid_t group)
// {
//     typedef int (*fp)(const char*, uid_t, gid_t);
//     fp func = (fp)dlsym(RTLD_NEXT,"chown");
// 	int ret = func(path, owner, group);
// 	log("chown", {STR(path), INT(owner), INT(group)}, INT(ret));
// 	return ret;
// }

// int close(int fildes)
// {
//     typedef int (*fp)(int);
//     fp func = (fp)dlsym(RTLD_NEXT,"close");
// 	int ret = func(fildes);
// 	log("close", {INT(fildes)}, INT(ret));
// 	return ret;
// }

// int creat(const char *path, mode_t mode)
// {
//     typedef int (*fp)(const char*, mode_t);
//     fp func = (fp)dlsym(RTLD_NEXT,"creat");
// 	int ret = func(path, mode);
// 	log("creat", {STR(path), INT(mode)}, INT(ret));
// 	return ret;
// }

// int fclose(FILE *stream)
// {
//     typedef int (*fp)(FILE);
//     fp func = (fp)dlsym(RTLD_NEXT,"close");
// 	int ret = func(stream);
// 	log("close", {INT(stream)}, INT(ret));
// 	return ret;
// }
