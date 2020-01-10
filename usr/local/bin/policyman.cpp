#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;
extern "C" char **environ;
char * pcchr2pchr(const char *pcchr) {
	char * ret = new char[strlen(pcchr)];
	strcpy(ret, pcchr);
	return ret;
}
char * envname(const char *env) {
	string ret;
	for (int i=0;env[i]!='=';i++) {
		ret += env[i];
	}
	return pcchr2pchr(ret.c_str());
}
string int2str(const int &num, const bool &hex) {
	stringstream ss;
	if (hex) {
		ss << std::hex << num;
	} else {
		ss << num;
	}
	string ret(ss.str());
	return ret;
}
int str2int(const string &str, const bool &hex) {
	int ret;
	stringstream ss;
	ss << str;
	if (hex) {
		ss >> std::hex >> ret;
	} else {
		ss >> ret;
	}
	return ret;
}
int main(int argc, char **argv) {
	setuid(0);
	seteuid(0);
	int calleruid=getuid(), temp;
	for (char **i = environ; *i; i++) {
		temp++;
	}
	char **args = new char *[2 + argc], **envbak = new char *[temp + 1];
	args[0] = (char *) "/bin/bash";
	args[1] = (char *) "/etc/policyman.d/policyman_script";
	for (int i = 1; i < argc; i++) {
		args[i + 1] = argv[i];
	}
	for (char **i = envbak; environ[0]; i++) {
		*i = new char[strlen(environ[0]) + 7];
		strcpy(*i, strcat(pcchr2pchr("envbak_"), environ[0]));
		unsetenv(envname(environ[0]));
	}
	for (char **i = envbak; *i; i++) {
		putenv(*i);
	}
	putenv(pcchr2pchr(strcat(pcchr2pchr("calleruid="), int2str(calleruid, false).c_str())));
	execv(args[0], args);
	return 0;
}