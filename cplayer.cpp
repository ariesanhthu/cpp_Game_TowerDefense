#include "cplayer.h"

void cplayer::setName(string nName) {
    strcpy(name, nName.c_str());
    // name = nName;
}
void cplayer::setPass(string nPass) {
    strcpy(pass, nPass.c_str());
    // pass = nPass;
}

void cplayer::registerUser(string nName, string nPass) {
    //check available user name
    cplayer temp;
    ifstream ifi("test.catfamuser", ios::binary);
    if (ifi) {
        while (ifi.read((char*)(&temp), sizeof(cplayer))) {
            if (nName == string(temp.name)) {
                //throw name error
                // cout << "available user name" << endl;
                // cout << temp.name << endl;
                return;
            }
        }
    }
    ifi.close();
    setName(nName);
    setPass(nPass);
    ofstream ofi("test.catfamuser", ios::binary | ios::app);
    ofi.write((char*)(this), sizeof(cplayer));
    ofi.close();
}

void cplayer::login(string nName, string nPass) {
    cplayer temp;
    ifstream ifi("test.catfamuser", ios::binary);
    if (ifi) {
        while (ifi.read((char*)(&temp), sizeof(cplayer))) {
            if (nName == string(temp.name)) {
                if (nPass == string(temp.pass)) {
                    setName(nName);
                    setPass(nPass);
                    cout << "logined in" << endl;
                    return;
                }
                else {
                    // throw wrong pass 
                    cout << "wrong pass";
                    return;
                }
                return;
            }
        }
    }
    ifi.close();
    //throw not available user error
    cout << "no user";
    return;
}