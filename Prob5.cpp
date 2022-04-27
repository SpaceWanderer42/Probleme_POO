#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>

using namespace std;

class Person{

public:
    string mName;
    uint16_t mAge;
    double mSalary;

    Person(){
        this->mName="";
        this->mAge=0;
        this->mSalary=0;
    }
    Person(string name, uint16_t age, double s){

        this->mName = name;
        this->mAge = age;
        this->mSalary = s;

    }
    bool operator ==(const Person& other)const {

        bool b = false;
        if(this->mName == other.mName && this->mAge == other.mAge && this->mSalary == other.mSalary)
        {
            b=true;
        }

        return b;

    }
    bool operator < (const Person& other) const {

        bool b = false;
        if(this->mName < other.mName)
        {
            b = true;
        }
        return b;
    }

};

class Building{

protected:
    string mBuildingName;
    string mType;
    Person mCoordinator;
    vector <Person> mEmployees;
    vector <Person> mCitizens;

public:
    Building(){

    };
    Building(string buildingName, string type)
    {
        this->mBuildingName = buildingName;
        this->mType = type;
    }
    virtual void add(const Person& a) = 0;
    virtual void remove(const Person& a) = 0;
    virtual Building* operator +(const Person& other) = 0;
    virtual Building* operator-() = 0;
    virtual Building* operator-(const Person& other) = 0;

    string getBuildingName()const{
        return this->mBuildingName;
    }
    string getType()const{
        return this->mType;
    }
    uint16_t getEmployeesSize()const{

        return this->mEmployees.size();

    }
    uint16_t getCitizensSize()const{
        return this->mCitizens.size();
    }
    Person getEmployee(uint16_t i)const{
        return this->mEmployees.at(i);
    }
    Person getCitizen(uint16_t i)const{
        return this->mCitizens.at(i);
    }
    Person getCoordinator() const{
        return this->mCoordinator;
    }

};

class CityHall : public Building{

public:

    explicit CityHall(string name){
        this->mBuildingName = name;
        this->mType="CityHall";
        this->mCitizens.clear();
        Person a;
        this->mCoordinator.mName=a.mName;
        this->mCoordinator.mAge=a.mAge;
        this->mCoordinator.mSalary=a.mSalary;


    }
    Building* operator +(const Person& other)  {
        if(mCoordinator.mName =="") {
            this->mCoordinator.mName = other.mName;
            this->mCoordinator.mAge = other.mAge;
            this->mCoordinator.mSalary = other.mSalary;

        }
        return this;
    }
    Building* operator-()  {
        this->mCoordinator.mName = "";
        this->mCoordinator.mAge=0;
        this->mCoordinator.mSalary=0;
        return this;
    }
    Building* operator-(const Person& other)  {return this;}
    void add(const Person& a)  {
        this->mCitizens.push_back(a);
    }
    void remove(const Person& a)  {
        for(int i=0; i<this->mCitizens.size();i++)
        {
            if(this->mCitizens.at(i) == a)
            {
                for (int j = i; j < this->mCitizens.size() - 1; j++) {
                    this->mCitizens.at(j).mAge = this->mCitizens.at(j + 1).mAge;
                    this->mCitizens.at(j).mSalary = this->mCitizens.at(j + 1).mSalary;
                    this->mCitizens.at(j).mName = this->mCitizens.at(j + 1).mName;

                }

            }
        }
        this->mCitizens.erase(mCitizens.end()-1);
    }

};

class Hospital : public Building{

public:

    Hospital (string name){

        this->mBuildingName = name;
        this->mType="Hospital";
        this->mCitizens.clear();
        this->mEmployees.clear();
    }
    Building* operator +(const Person& a) {

        this->mEmployees.push_back(a);
        return this;
    }
    Building* operator - (const Person& a){
    
        for(int i=0; i<this->mEmployees.size();i++)
        {
            if(this->mEmployees.at(i).mName == a.mName)
            {
                for (int j = i; j < this->mEmployees.size() - 1; j++) {
                    this->mEmployees.at(j).mAge = this->mEmployees.at(j + 1).mAge;
                    this->mEmployees.at(j).mSalary = this->mEmployees.at(j + 1).mSalary;
                    this->mEmployees.at(j).mName = this->mEmployees.at(j + 1).mName;

                }

            }
        }
        this->mEmployees.erase(mEmployees.end()-1);
        return this;

    }
    Building* operator - ()  {return this;}

    void add(const Person& a) {
        this->mCitizens.push_back(a);
    }
    void remove(const Person& a) {
        for(int i=0; i<this->mCitizens.size();i++)
        {
            if(this->mCitizens.at(i).mName==a.mName)
            {
                for (int j = i; j < this->mCitizens.size() - 1; j++) {
                    this->mCitizens.at(j).mAge = this->mCitizens.at(j + 1).mAge;
                    this->mCitizens.at(j).mSalary = this->mCitizens.at(j + 1).mSalary;
                    this->mCitizens.at(j).mName = this->mCitizens.at(j + 1).mName;

                }

            }
        }
        this->mCitizens.erase(mCitizens.end()-1);
    }

};


class PoliceStation : public Building {

public:

    PoliceStation (string name){

        this->mBuildingName = name;
        this->mType="PoliceStation";
        this->mCitizens.clear();
        this->mEmployees.clear();
    }
    Building* operator +(const Person& a) {

        this->mEmployees.push_back(a);
        return this;
    }
    Building* operator- (const Person& a) {	
        for(int i=0;i<this->mEmployees.size();i++){	
            if(this->mEmployees.at(i).mName==a.mName){	
                for(int j=i;j<this->mEmployees.size()-1;j++){	
                    this->mEmployees.at(j).mAge=this->mEmployees.at(j+1).mAge;	
                    this->mEmployees.at(j).mSalary=this->mEmployees.at(j+1).mSalary;	
                    this->mEmployees.at(j).mName=this->mEmployees.at(j).mName;	
                }	
            }	
        }	
        this->mEmployees.erase(mEmployees.end()-1);	
        return this;	

    }

    Building* operator - ()  {return this;}

    void add(const Person& a) {
        this->mCitizens.push_back(a);
    }
    
    void remove(const Person& a) {
        for(int i=0;i<this->mCitizens.size();i++){	
            if(this->mCitizens.at(i).mName==a.mName){	
                for(int j=i;j<this->mCitizens.size()-1;j++){	
                    this->mCitizens.at(j).mAge=this->mCitizens.at(j+1).mAge;	
                    this->mCitizens.at(j).mSalary=this->mCitizens.at(j+1).mSalary;	
                    this->mCitizens.at(j).mName=this->mCitizens.at(j).mName;	
                }	
            }	
        }
        this->mCitizens.erase(mCitizens.end()-1);
    }


};

class House : public Building{

private:
    uint16_t mMaxNumber;

public:

    House(string name, uint16_t number){
        this->mBuildingName = name;
        this->mType = "House";
        this->mCitizens.clear();
        this->mMaxNumber = number;
        this->mCoordinator.mName = "";
        this->mCoordinator.mAge=0;
        this->mCoordinator.mSalary=0;
    }

    Building* operator +(const Person& other)  {
        if(mCoordinator.mName =="") {
            this->mCoordinator.mName = other.mName;
            this->mCoordinator.mAge = other.mAge;
            this->mCoordinator.mSalary = other.mSalary;

        }
        return this;
    }
    Building* operator-() {
        this->mCoordinator.mName = "";
        this->mCoordinator.mAge=0;
        this->mCoordinator.mSalary=0;
        return this;
    }

    Building* operator-(const Person& other)  {return this;}
    void add(const Person& a) {

        if(this->mCitizens.size() < this->mMaxNumber)
            this->mCitizens.push_back(a);
    }
    void remove(const Person& a) {
            for (int i = 0; i < this->mCitizens.size(); i++) {
                if (this->mCitizens.at(i).mName == a.mName) {
                    if (this->mCitizens[i].mAge >= 18){
                    for (int j = i; j < this->mCitizens.size() - 1; j++) {
                        this->mCitizens.at(j).mAge = this->mCitizens.at(j + 1).mAge;
                        this->mCitizens.at(j).mSalary = this->mCitizens.at(j + 1).mSalary;
                        this->mCitizens.at(j).mName = this->mCitizens.at(j + 1).mName;
                    }
                     this->mCitizens.erase(mCitizens.end()-1);
                    }
                }
            }
            
        }
};

class Block : public Building{

private:

    uint16_t mMaxNumberPerFloor;

public:
    Block(string name, uint16_t floors, uint16_t pMax){

        this->mBuildingName=name;
        this->mType="Block";
        this->mCitizens.clear();
        this->mMaxNumberPerFloor = pMax*floors;
        this->mCoordinator.mName = "";
        this->mCoordinator.mAge=0;
        this->mCoordinator.mSalary=0;

    }
    Building* operator +(const Person& other)  {
        if(mCoordinator.mName =="") {
            this->mCoordinator.mName = other.mName;
            this->mCoordinator.mAge = other.mAge;
            this->mCoordinator.mSalary = other.mSalary;

        }
        return this;
    }
    Building* operator-() {
        this->mCoordinator.mName = "";
        this->mCoordinator.mAge=0;
        this->mCoordinator.mSalary=0;
        return this;
    }
    Building* operator-(const Person& other)  {return this;}
    void add(const Person& a) {

        if(this->mCitizens.size() < this->mMaxNumberPerFloor)
            this->mCitizens.push_back(a);
    }
    void remove(const Person& a) {

            for (int i = 0; i < this->mCitizens.size(); i++) {
                if (this->mCitizens.at(i).mName == a.mName) {
                    if (this->mCitizens[i].mAge >= 18){
                        for (int j = i; j < this->mCitizens.size() - 1; j++) {
                            this->mCitizens.at(j).mAge = this->mCitizens.at(j + 1).mAge;
                            this->mCitizens.at(j).mSalary = this->mCitizens.at(j + 1).mSalary;
                            this->mCitizens.at(j).mName = this->mCitizens.at(j + 1).mName;
                        }
                        this->mCitizens.erase(mCitizens.end()-1);
                    }
                }
            }
           
        }

        void empty(){
            Person p;
            for (int i = 0; i < this->mCitizens.size(); i++) {
                if (this->mCitizens.at(i) == p) {
                    for (int j = i; j < this->mCitizens.size() - 1; j++) {
                        this->mCitizens.at(j).mAge = this->mCitizens.at(j + 1).mAge;
                        this->mCitizens.at(j).mSalary = this->mCitizens.at(j + 1).mSalary;
                        this->mCitizens.at(j).mName = this->mCitizens.at(j + 1).mName;
                    }
                    this->mCitizens.erase(mCitizens.end()-1);
                    i--;
                }
            }

    }



};

int main() {

    string action, w, name, place;
    int size, floors;
    uint16_t age;
    double salary;
    vector <CityHall*> city;
    vector <Hospital*> hospital;
    vector <PoliceStation*>police;
    vector <House*> house;
    vector <Block*> block;
    vector <int> houseN;
    vector <int> blockN;
    int counter=0;
    bool ok=false;
    while(cin>>action>>w)
    {
        if(w=="CityHall"){
            cin>>name;

            city.push_back(new CityHall(name));

        }

        if(w=="Hospital"){
            cin>>name;

            hospital.push_back(new Hospital(name));
        }


        if(w=="PoliceStation"){
            cin>>name;


            police.push_back(new PoliceStation(name));

        }
        if (w=="House")
        {
            cin>>name>>size;
            house.push_back((new House(name, size)));
            houseN.push_back(counter);
            counter++;
        }
        if(w=="Block")
        {
            cin>>name>>floors>>size;
            block.push_back(new Block(name, floors, size));
            blockN.push_back(counter);
            counter++;
        
        }
        if(w=="coordinator" || w=="employee" || w=="citizen")
        {
            if(action=="add") {
                cin >> name >> age >> salary >> place;
                Person p(name, age, salary);
                for (int i = 0; i < city.size(); i++) {
                    if (ok) { break; }
                    if (place == city[i]->getBuildingName()) {
                        if (w == "coordinator") {
                            city[i]->operator+(p);
                            ok=true;
                            
                        } else if (w == "citizen") {
                            city[i]->add(p);
                            ok = true;

                        }

                    }
                }
                for (int i = 0; i < hospital.size(); i++) {
                    if (ok) { break; }
                    if (place == hospital[i]->getBuildingName()) {

                        if (w == "employee") {
                            hospital[i]->operator+(p);
                            ok = true;

                        } else if (w == "citizen") {
                            hospital[i]->add(p);
                            ok = true;
                        }
                    }
                }
                for (int i = 0; i < police.size(); i++) {
                    if (ok) { break; }
                    if (place == police[i]->getBuildingName()) {

                        if (w == "employee") {
                            police[i]->operator+(p);
                            ok = true;

                        } else if (w == "citizen") {
                            police[i]->add(p);
                            ok = true;
                        }
                    }
                }
                for (int i = 0; i < house.size(); i++) {
                    if (ok) { break; }
                    if (place == house[i]->getBuildingName()) {
                        if (w == "coordinator") {
                            if(house[i]->getCoordinator().mName=="")
                                house[i]->add(p);

                            house[i]->operator+(p);

                            ok=true;
                        } else if (w == "citizen") {
                            house[i]->add(p);
                            ok = true;

                        }

                    }

                }

                for (int i = 0; i < block.size(); i++) {
                    if (ok) { break; }
                    if (place == block[i]->getBuildingName()) {
                            if (w == "coordinator") {
                                if (block[i]->getCoordinator().mName == "")
                                    block[i]->add(p);

                                block[i]->operator+(p);

                                ok = true;
                            } else if (w == "citizen") {
                                block[i]->add(p);
                                ok = true;

                            }


                    }

                }
                ok=false;
            }
            else if(action=="remove")
            {
                cin >> name >> place;
                Person p(name, age, salary);
                for (int i = 0; i < city.size(); i++) {
                    if (ok) { break; }
                    if (place == city[i]->getBuildingName()) {
                        if (w == "coordinator") {
                            city[i]->operator-();
                            ok=true;
                        } else if (w == "citizen") {
                            city[i]->remove(p);
                            ok = true;

                        }

                    }
                }
                for (int i = 0; i < hospital.size(); i++) {
                    if (ok) { break; }
                    if (place == hospital[i]->getBuildingName()) {

                        if (w == "employee") {
                            hospital[i]->operator-(p);
                            ok = true;

                        } else if (w == "citizen") {
                            hospital[i]->remove(p);
                            ok = true;
                        }
                    }
                }
                for (int i = 0; i < police.size(); i++) {
                    if (ok) { break; }
                    if (place == police[i]->getBuildingName()) {

                        if (w == "employee") {
                            police[i]->operator-(p);
                            ok = true;

                        } else if (w == "citizen") {
                            police[i]->remove(p);
                            ok = true;
                        }
                    }
                }
                for (int i = 0; i < house.size(); i++) {
                    if (ok) { break; }
                    if (place == house[i]->getBuildingName()) {
                        if (w == "coordinator") {
                            house[i]->operator-();
                            house[i]->remove(p);
                            ok=true;
                        } else if (w == "citizen") {
                            house[i]->remove(p);
                            ok = true;

                        }

                    }
                }
                for (int i = 0; i < block.size(); i++) {
                    if (ok) { break; }
                    if (place == block[i]->getBuildingName()) {
                        if (w == "coordinator") {
                            block[i]->operator-();
                            block[i]->remove(p);
                            ok=true;
                        } else if (w == "citizen") {
                            block[i]->remove(p);
                            ok = true;

                        }

                    }
                }
                ok=false;
            }
        }

    }

    for(int i=0;i<block.size();i++)
    {
        block[i]->empty();
    }


    if(city.size()>=3 && hospital.size()>=2 && police.size()>=3 &&house.size()>=8 && block.size() >=4)
    {
        cout<<"Type: Capital"<<"\n";
    }
    else if(city.size()>=2 && hospital.size()>=1 && police.size()>=2 &&house.size()>=4 && block.size() >=1)
    {
        cout<<"Type: Town"<<"\n";
    }
    else
    {
        cout<<"Type: Village"<<"\n";
    }
    double num=0, m=0;
    for(int i=0;i<hospital.size();i++)
    {
        num=num+hospital[i]->getCitizensSize();
    }

    cout<<"Number of patients in hospitals: "<<num<<"\n";

    num=0;
    m=0;
    for(int i=0;i<hospital.size();i++){
        if(hospital[i]->getEmployeesSize()==0)
            continue;
        for(int j=0;j<hospital[i]->getEmployeesSize();j++)
        {
            num=num+hospital[i]->getEmployee(j).mSalary;
            m++;
        }
    }
    if(m==0)
        std::cout<<"Average salary for doctors: 0"<<'\n';
    else
        std::cout<<"Average salary for doctors: "<<num/m<<'\n';
    num=0;
    m=0;

    for(int i=0;i<police.size();i++){
        if(police[i]->getEmployeesSize()==0)
            continue;
        for(int j=0;j<police[i]->getEmployeesSize();j++)
        {
            num=num+police[i]->getEmployee(j).mSalary;
            m++;
        }
    }
    if(m==0)
        std::cout<<"Average salary for cops: 0"<<'\n';
    else
        std::cout<<"Average salary for cops: "<<num/m<<'\n';

    num=0;
    m=0;
    for(int i=0;i<city.size();i++)
    {
        if(city[i]->getCoordinator().mName=="")
            continue;
        num=num+city[i]->getCoordinator().mSalary;
        m++;
    }
    if(m==0)
        std::cout<<"Average salary for mayors: 0"<<'\n';
    else
        std::cout<<"Average salary for mayors: "<<num/m<<'\n';
    num=0;
    m=0;

    for(int i=0;i<city.size();i++){
        if(city[i]->getCitizensSize()==0)
            continue;
        for(int j=0;j<city[i]->getCitizensSize();j++)
        {
            num=num+city[i]->getCitizen(j).mSalary;
            m++;
        }
    }
    if(m==0)
        std::cout<<"Average salary for city hall employees: 0"<<'\n';
    else
        std::cout<<"Average salary for city hall employees: "<<num/m<<'\n';

    num=0;
    m=0;
    for(int i=0;i<police.size();i++){
        if(police[i]->getCitizensSize()==0)
            continue;
        for(int j=0;j<police[i]->getCitizensSize();j++)
        {
            num=num+police[i]->getCitizen(j).mAge;
            m++;
        }
    }
    if(m==0)
        std::cout<<"Average age of busted in police stations: 0"<<'\n';
    else
        std::cout<<"Average age of busted in police stations: "<<num/m<<'\n';

    num=0;
    m=0;
    while(m<counter)
    {
        for(int i=0;i<houseN.size();i++) {
            if (houseN[i] == m) {
                cout << "Number of people in House " << house[i]->getBuildingName() << ": "
                     << house[i]->getCitizensSize() << "\n";
                break;
            }
        }
        for(int i=0;i<blockN.size();i++) {

            if (blockN[i] == m) {
                cout << "Number of people in Block " << block[i]->getBuildingName() << ": "
                     << block[i]->getCitizensSize() << "\n";
                break;
            }
        }
        m++;
    }
    bool k=false;
    cout<<"Administrators of house and block: ";
    for(int j=0;j<house.size();j++){


    for(int i=0;i<block.size();i++) {

        
            if (block[i]->getCoordinator() == house[j]->getCoordinator() && block[i]->getCoordinator().mName != "") {
                cout << block[i]->getCoordinator().mName<<" ";
                k = true;
            }
        
    }
    }
    if(k==false)
    {
        cout<<"Nobody";
    }

    return 0;
}
