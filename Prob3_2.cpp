#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>


using namespace std;

class Account{
private:
    string mCurrency, mName;
    float  mSold;

public:

    Account(){
        this->mCurrency="Unknown";
        mSold=0;
    }
    Account(string mCurrency){
        this->mCurrency=mCurrency;
        mSold=0;
    }

    Account(string mCurrency, float mSold){
        this -> mCurrency = mCurrency;
        this -> mSold = mSold;
    }
    Account(string mName, string mCurrency, float mSold){
        this -> mName = mName;
        this -> mCurrency = mCurrency;
        this ->mSold = mSold;
    }

    Account(const Account &other)
    {
        mCurrency = other.mCurrency;
        mSold = other.mSold;
        mName = other.mName;
    }
    Account operator+( const Account &other) {
        float s = 0;
        if(mCurrency == other.mCurrency)
        {
            s += other.mSold + mSold;
            return Account(mName, mCurrency, s);
        }
        return Account();
    }

    Account operator ^(string mCurrency)
    {

        float s = this -> mSold;

        if( mCurrency=="RON" && this->mCurrency=="USD" )
        {
            s = this -> mSold * 4.09;

        }
        else
        if(mCurrency=="RON" && this->mCurrency=="EUR")
        {
            s = this -> mSold * 4.86;

        }
        else
        if(mCurrency=="EUR" && this->mCurrency=="USD")
        {

            s=this->mSold*0.84;

        }
        else
        if(mCurrency=="EUR" && this->mCurrency=="RON")
        {

            s=this->mSold*0.20;

        }
        else
        if(mCurrency=="USD" && this->mCurrency=="RON")
        {

            s=this->mSold*0.24;

        }
        else
        if(mCurrency=="USD" && this->mCurrency=="EUR")
        {

            s=this->mSold*1.19;

        }



        Account cont(mName, mCurrency, s);
        return cont;

    }


    bool operator <(const Account &other)
    {
        return mSold < other.mSold;
    }

    bool operator >(const Account &other)
    {
        return mSold > other.mSold;
    }

    string getCurrency(){
        return mCurrency;
    }

    float getSold(){
        return mSold;
    }

    string getNume(){
        return mName;
    }
};
bool comparator (Account x, Account y) {
    return x.getSold() > y.getSold();
}

int main(){
    int n;
    float  mSold;
    string name , val, mCurrency;
    vector<Account>v;

    cin>>n;

    for(int i = 0; i < n; i++){
        cin>>name>>mCurrency>>mSold;

        v.push_back(Account(name,mCurrency,mSold));

    }
    cin>>val;


    for(int i = 0; i < n; i++)
    {
        if(v[i].getCurrency() != val)
        {
            v[i] = v[i] ^ val;
        }

    }


    for(int i = 0; i < v.size(); i++)
    {
        for(int j= i+1; j < v.size(); j++)
        {
            if(v[i].getNume()==v[j].getNume())
            {
                v[i]=v[i]+v[j];
                v.erase(v.begin()+j);
                j--;
            }
        }
    }
    sort (v.begin(), v.end(), comparator);



    for(int i = 0; i < v.size(); i++)
    {
        cout<<v[i].getNume()<<" -> ";
        printf("%.2f ", v[i].getSold());
        cout<<val<<endl;

    }
    return 0;
}
