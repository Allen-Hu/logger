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

string FD(int f)
{
	char fdpath[256];
	char buf[256];
	sprintf(fdpath, "/proc/self/fd/%d", f);
	ssize_t r = readlink(fdpath, buf, 256);
	if(r < 0) 
	{
		printf("ERROR: %d\n", errno);
		exit(1);
	}
	buf[r] = 0;
	return BRAC(string(buf));
}

string FD(FILE* f)
{
	char fdpath[256];
	char buf[256];
	int fno = fileno(f);
	sprintf(fdpath, "/proc/self/fd/%d", fno);
	ssize_t r = readlink(fdpath, buf, 256);
	if(r < 0)
	{
		printf("ERROR: %d\n", errno);
		exit(1);
	}
	buf[r] = 0;
	return BRAC(string(buf));
}

string MODE(int f)
{
	stringstream ss;
	ss << oct << f;
	return ss.str();
}

string INT(int n)
{
	return to_string(n);
}

template<typename T>
string BUF(T* b)
{
	char* bx = (char*)b;
	char buf[33];
	int len = min((int)strlen(bx), 32);
	for(int i = 0; i < len; i++)
	{
		if(isprint(bx[i]))
			sprintf(buf, "%c", bx[i]);
		else
			sprintf(buf, ".");
	}
	buf[32] = 0;
	return BRAC(buf);	
}

template<typename T>
string POINT(T* p)
{
	char buf[256];
	sprintf(buf, "%p", p);
	return string(buf);
}

void log(string name, vector<string> args, string ret)
{
	fprintf(stderr, "[logger] %s(", name.c_str());
    for(auto &arg: args)
    {
        if((&arg - &args[0]) != 0)
			fprintf(stderr, ", ");
		fprintf(stderr, "%s", arg.c_str());
    }
	fprintf(stderr, ") = %s\n", ret.c_str());
}

int chmod(const char *path, mode_t mode)
{
    typedef int (*fp)(const char*, mode_t);
    fp func = (fp)dlsym(RTLD_NEXT,"chmod");
    int ret = func(path, mode);
    log("chmod", {PATH(path), MODE(mode)}, INT(ret));
	return ret;
}

int chown(const char *path, uid_t owner, gid_t group)
{
    typedef int (*fp)(const char*, uid_t, gid_t);
    fp func = (fp)dlsym(RTLD_NEXT,"chown");
	int ret = func(path, owner, group);
	log("chown", {PATH(path), INT(owner), INT(group)}, INT(ret));
	return ret;
}

int close(int fildes)
{
	string sfd = FD(fildes);
    typedef int (*fp)(int);
    fp func = (fp)dlsym(RTLD_NEXT,"close");
	int ret = func(fildes);
	log("close", {sfd}, INT(ret));
	return ret;
}

int creat(const char *path, mode_t mode)
{
    typedef int (*fp)(const char*, mode_t);
    fp func = (fp)dlsym(RTLD_NEXT,"creat");
	int ret = func(path, mode);
	log("creat", {PATH(path), MODE(mode)}, INT(ret));
	return ret;
}

int fclose(FILE *stream)
{
	string sfd = FD(stream);
    typedef int (*fp)(FILE*);
    fp func = (fp)dlsym(RTLD_NEXT,"fclose");
	int ret = func(stream);
	log("fclose", {sfd}, INT(ret));
	return ret;
}

FILE *fopen(const char *path, const char *mode)
{
	return NULL;
    typedef FILE* (*fp)(const char*, const char*);
    fp func = (fp)dlsym(RTLD_NEXT,"fopen");
	FILE* ret = func(path, mode);
	log("fopen", {PATH(path), BRAC(mode)}, POINT(ret));
	return ret;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	string sfd = FD(stream);
    typedef size_t (*fp)(void*, size_t, size_t, FILE*);
    fp func = (fp)dlsym(RTLD_NEXT,"fread");
	size_t ret = func(ptr, size, nmemb, stream);
	log("fread", {BUF(ptr), INT(size), INT(nmemb), sfd}, INT(ret));
	return ret;
}
