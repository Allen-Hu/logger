#include <iostream>
#include <vector>
#include <map>
using namespace std;

void print_usage()
{
	cout<<"usage: ./logger [-o file] [-p sopath] [--] cmd [cmd args ...]"<<endl;
    cout<<"    -p: set the path to logger.so, default = ./logger.so"<<endl;
    cout<<"    -o: print output to file, print to \"stderr\" if no file specified"<<endl;
    cout<<"    --: separate the arguments for logger and for the command"<<endl;
}

int main(int argc, char** argv)
{
	vector<string> args;
	int sep = -1;
	for(int i = 1; i < argc; i++)
	{
		string opt = string(argv[i]);
		if(opt == "--")
			sep = i - 1;
		args.push_back(opt);
	}

	bool valid = true;
	map<string, string> opts;
	if(sep != -1)
	{
		for(int i = 0; i < sep; i+=2)
		{
			if(args[i] != "-o" && args[i] != "-p")
			{
				valid = false;
				break;
			}
			opts.insert(make_pair(args[i], args[i+1]));
		}
	}
	if(!valid)
	{
		print_usage();
		exit(0);
	}
	return 0;
}
