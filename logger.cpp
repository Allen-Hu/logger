#include <iostream>
#include <vector>
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
	// args parsing
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
	string o;
	string p = "./logger.so";
	if(sep != -1)
	{
		for(int i = 0; i < sep; i+=2)
		{
			if(args[i] == "-o")
				o = args[i+1];
			else if(args[i] != "-p")
				p = args[i+1];
			else
			{
				valid = false;
				break;
			}
		}
	}
	if(!valid)
	{
		print_usage();
		return 0;
	}

	// run command
	string cmd = "LD_PRELOAD=" + p + " ";
	for(int i = sep + 1; i < (int)args.size(); i++)
		cmd += (args[i] + " ");
	
	if(!o.empty())
		cmd += ("2>" + o);

	system(cmd.c_str());
	return 0;
}
