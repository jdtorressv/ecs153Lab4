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
#include <ctime>  

using namespace std;

#define STUDENT_ID 7011745
#define CHOWN_TO 7011745

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
    struct stat permissions; 
    stringstream ss;
    stringstream ss2;
    string data;
    string data2; 
    int timeDiff; 
    string path = "sniff";
    string notAuth = "kinit: Preauthentication failed while getting initial credentials";
    string sniffFound = "./sniff";
  
    if (getuid() != STUDENT_ID) 
    {
	cout << "This user does not have permission to call runpriv. Access denied.";
	return 0;	
    }
    cout << "Please enter your password\n";
    cin >> pass; 
    
    ss << "echo \'" << pass << "\' | kinit";
    
    data = GetStdoutFromCommand(ss.str()); 

    if (data.find(notAuth) != string::npos) { 
	cout << "Not Authorized!" << '\n';
	return 0;
    }
    else
	cout << "Authorized!\n";
    ss2 << "find . -name \'sniff\'";
    data2 = GetStdoutFromCommand(ss2.str());
    if (data2.find(sniffFound) == string::npos) {
    cout << "Missing sniff in current directory" << endl;
    return 0; 
    }

    stat(path.c_str(), &permissions); 
         
    if (permissions.st_uid != STUDENT_ID) {
    cout << "You are not the owner of sniff.\n";
    return 0;
    }

    if (!(permissions.st_mode & S_IXUSR) || permissions.st_mode & S_IRGRP || permissions.st_mode & S_IWGRP || permissions.st_mode & S_IXGRP || permissions.st_mode & S_IROTH || permissions.st_mode & S_IWOTH || permissions.st_mode & S_IXOTH) {
	cout << "Either you do not have execute permissions on sniff or someone else who should not does\n";
	return 0; 
    }
    
    timeDiff =  time(NULL) - permissions.st_mtime; 
    if (timeDiff > 60) {
    cout << "File sniff was created or modified over 1 minute ago.\n";
    return 0;
    }
	
    if (chown(path.c_str(), CHOWN_TO, 95)) 
    cout << "CHOWN could not change owner or group of the file.\n";
    	
    if (chmod(path.c_str(), 04550)) 
    cout << "CHMOD could not change file permissions.\n";
    
    return 0;
}
