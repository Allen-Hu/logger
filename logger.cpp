#include <iostream>
#include <vector>
using namespace std;

void print_usage()
{
	cout << "usage: ./logger [-o file] [-p sopath] [--] cmd [cmd args ...]"          << endl;
    cout << "    -p: set the path to logger.so, default = ./logger.so"               << endl;
    cout << "    -o: print output to file, print to \"stderr\" if no file specified" << endl;
    cout << "    --: separate the arguments for logger and for the command"          << endl;
}

int main(int argc, char** argv)
{
	// args parsing
	vector<string> args;
	int i;
	string o;
	string p = "./logger.so";
	for(int i = 1; i < argc; i++)
	{
		string arg = string(argv[i]);
		args.push_back(arg);
	}
	for(i = 0; i < (int)args.size() && args[i].front() == '-'; i += 2)
	{
		if(args[i] != "-o" && args[i] != "-p" && args[i] != "--")
		{
			cout << "./logger: invalid option -- '" << args[i].substr(1) << "'" << endl;
			print_usage();
			return 0;
		}
		if(i + 1 >= (int)args.size())
		{
			print_usage();
			return 0;
		}
		if(args[i] == "-o")
			o = args[i + 1];
		else if(args[i] == "-p")
			p = args[i + 1];
		else if(args[i] == "--")
		{
			++i;
			break;
		}
	}

	if(i == (int)args.size())
	{
		print_usage();
		return 0;
	}

	string cmd = "LD_PRELOAD=" + p + " ";
	if(!o.empty())
	{
		char buf[256];
		realpath(o.c_str(), buf);
		cmd += ("LOGGER_OUT=" + o + " ");
		system((string("rm -f ") + o).c_str());
		system((string("touch ") + o).c_str());
	}

	// run command
	for(; i < (int)args.size(); i++)
		cmd += (args[i] + " ");

	system(cmd.c_str());
	return 0;
}
