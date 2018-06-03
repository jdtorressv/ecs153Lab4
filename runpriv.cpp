#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <sstream> 

using namespace std;

#define STUDENT_ID 7011745

string GetStdoutFromCommand(string cmd) {
    string data; 
    FILE* stream; 
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
	while (!feof(stream)) {
	    if (fgets(buffer, max_buffer, stream) != NULL) 
		data.append(buffer);
	}
	pclose(stream);
    }
    return data; 
}

int main() 
{
    string pass; 
    //string kInput;
    stringstream ss;
    string data;
    string notAuth = "kinit: Preauthentication failed while getting initial credentials";
  
    if (getuid() != STUDENT_ID) 
    {
	cout << "This user does not have permission to call runpriv. Access denied.";
	return 0;	
    }
    cout << "Please enter your password\n";
    cin >> pass; 
    //kInput = "echo \'" + pass + "\' | kinit"; 
    //system(kInput.c_str());
    
    ss << "echo \'" << pass << "\' | kinit";
    //system(ss.str().c_str());
    data = GetStdoutFromCommand(ss.str()); 

    if (data.find(notAuth) != string::npos) { 
	cout << "Not Authorized!" << '\n';
	return 0;
    }
    else
	cout << "Authorized!\n";

    
    return 0;
}
