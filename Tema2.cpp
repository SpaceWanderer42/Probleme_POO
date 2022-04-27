#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Policy{

protected:
    bool isChecked;
public:
    virtual void check(const string &pass) = 0; // nu stiu daca trebuie const acolo

    bool getCheck()const{
        return this->isChecked;
    }

};

class LengthPolicy : public Policy{

private:
    uint16_t minLength, maxLength;

public:
    LengthPolicy(uint16_t minimum){
        this->minLength=minimum;
        this->maxLength=255;
    }
    LengthPolicy(uint16_t minimum, uint16_t maximum){

        this->minLength=minimum;
        this->maxLength=maximum;

    }
    void check(const string &pass)override{
        /*isChecked=true;
        if (pass.length() < minLength){
            isChecked=false;
        }
        else if(pass.length() > maxLength && pass.length() < minLength){
            isChecked=false;
        }
*/
        if (pass.length()>=minLength && pass.length()<=maxLength)
            isChecked=true;
        else
            isChecked=false;

    }



};

class ClassPolicy : public Policy{

private:
    uint16_t minClassCount;

public:
    ClassPolicy(uint16_t m){
        this->minClassCount=m;
    }
    void check(const string &pass)override {
        int counter=0;
        bool l, u, d, s;
        for(int i=0; i < pass.length(); i++)
        {
            if(!l && islower(pass[i])) {
                l = true;
                counter++;
            }
            if(!u && isupper(pass[i])) {
                u = true;
                counter++;
            }
            if(!d && isdigit(pass[i])) {
                d = true;
                counter++;
            }
            if(!l && islower(pass[i])) {
                l = true;
                counter++;
            }
            if(!s && ispunct(pass[i])) {
                s = true;
                counter++;
            }
        }
        if(minClassCount <= counter)
            isChecked=true;
        else
            isChecked=false;
    }

};

class IncludePolicy : public Policy{
private:
    char characterType;
public:
    IncludePolicy(char c){
        this->characterType=c;
    }
    void check(const string & pass){
        isChecked=false;

        for (int i=0; i < pass.size(); i++){
            if (characterType=='a') {
                if (islower(pass[i])) {
                    isChecked=true;
                    break;
                }
            }
            if (characterType=='A'){
                if (isupper(pass[i])) {
                    isChecked=true;
                    break;
                }
            }
            if (characterType=='0') {
                if (isdigit(pass[i])) {
                    isChecked=true;
                    break;
                }
            }
            if (characterType=='$') {
                if (ispunct(pass[i])) {
                    isChecked=true;
                    break;
                }
            }

        }
    }
};

class NotIncludePolicy : public Policy{
private:
    char characterType;
public:
    NotIncludePolicy(char c){
        this->characterType=c;
    }
    /*
    void check(const string &pass){
        isChecked=true;
        for(int i=0; i<pass.size();i++)
        {
            if(characterType==pass.at(i))
            {
                isChecked=false; // am facut invers fata de cum era la must include
            }
        }
    }
     */
    void check(const std::string & pass){
        isChecked=true;

        for (int i=0;i<pass.size();i++){
            if (characterType=='a') {
                if (islower(pass[i])) {
                    isChecked=false;
                    break;
                }
            }
            if (characterType=='A'){
                if (isupper(pass[i])) {
                    isChecked=false;
                    break;
                }
            }
            if (characterType=='0') {
                if (isdigit(pass[i])) {
                    isChecked=false;
                    break;
                }
            }
            if (characterType=='$') {
                if (ispunct(pass[i])) {
                    isChecked=false;
                    break;
                }
            }

        }
    }
};

class RepetitionPolicy: public Policy{

private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t m){
        this->maxCount=m;
    }
    /*
    void check(const string & pass)override{
        int counter=0;
        isChecked =true;
        for (int i=0;i<=pass.length()-counter;i++){
            counter=0;
            for (int j=i;j<i+maxCount;j++){
                if (pass[i]==pass[j]) counter++;
            }
            if (counter>=maxCount) {isChecked= false;}
        }

    }
    */
    void check(const std::string& password) override {
        isChecked = true;
        short unsigned count = 0;
        char lastChar = '\0';
        for(auto ch : password) {
            if(ch == lastChar) {
                count++;
            } else {
                lastChar = ch;
                count = 0;
            }
            if(count >= maxCount) {
                isChecked = false;
                break;
            }
        }
    }
};
class ConsecutivePolicy: public Policy{

private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t m){
        this->maxCount=m;
    }
    /*
    void check(const string& pass) override {
        isChecked = true;
        int count = 0;
        char lastChar = '\0';
        for(int i=0; i < pass.length(); i++) {
            if(lastChar + 1 == pass[i]) {
                count++;
                lastChar = pass[i];
            } else {
                count = 0;
                lastChar = pass[i];
            }
            if(count >= maxCount) {
                isChecked = false;
                break;
            }
        }
    }
    */
    void check(const string& pass)override{
        isChecked=true;
        for(int i=0;i<pass.length()-maxCount;i++){
            int a=1, b=0;
            for(int j=i+1;j<maxCount+1+i;j++){
            b++;
            if(pass[i]+b==pass[j]||pass[i]-b==pass[j]) 
            a++;
            }
            if(a>maxCount){
            isChecked=false;
            break;
            }
        }
    }

};

string checkPassword(string password, vector<Policy*> v){

    bool h = true;
    /*
    for(int i = 0; v.size(); i++)
    {
        v[i]->check(password);
        if(!v[i]->getCheck())
        {
            h=false;
            break;
        }
    }
    */
    for(auto policy : v) {
        policy->check(password);
        if(!policy->getCheck()) {
            h= false;
            break;
        }
    }
    if(h)
        return "OK";
    else
        return "NOK";
}

int main() {

   int n;
    cin >> n;
    vector<Policy*> v;
    for(int i = 0; i < n; i++) {
        string policy;
        cin >> policy;
        if(policy == "length") {
            int minim, maxim = 0;
            int t = scanf("%hu %hu", &minim, &maxim);
            if(t == 1) {
                Policy * length = new LengthPolicy(minim);
                v.push_back(length);
            } else {
                Policy * length = new LengthPolicy(minim, maxim);
                v.push_back(length);
            }
        } else if(policy == "include") {
            char type;
            cin >> type;
            Policy * include = new IncludePolicy(type);
            v.push_back(include);
        } else if(policy == "ninclude") {
            char type;
            cin >> type;
            Policy * ninclude = new NotIncludePolicy(type);
            v.push_back(ninclude);
        } else if(policy == "class") {
            short unsigned minCount;
            cin >> minCount;
            Policy * classP = new ClassPolicy(minCount);
            v.push_back(classP);
        } else if(policy == "repetition") {
            short unsigned maxCount;
            cin >> maxCount;
            Policy * repetition = new RepetitionPolicy(maxCount);
            v.push_back(repetition);
        } else if(policy == "consecutive") {
            short unsigned maxCount;
            cin >> maxCount;
            Policy *consecutive = new ConsecutivePolicy(maxCount);
            v.push_back(consecutive);
        }
    }
    string password;
    while(cin >> password) {
        
        cout << checkPassword(password, v) << std::endl;
    }

    return 0;
}
