#include<iostream>
#include<map>
using namespace std;

//another idea for error messages is to use try catch
void ErrorD()
{
    cout << "wrong denominations used" << endl;
}
void ErrorC()
{
    cout << "can't give out change" << endl;
}
void ErrorI()
{
    cout << "wrong input" << endl;
}

//function converts grosze into zloty
float into_zl(int gr)
{
    return gr/100.0;
}

//function converts zloty into grosze
int into_gr(float zl)
{
    int gr = zl * 100;
    return gr;
}

class VendingMachine{
private:
        int account; //stores the value of the current
public:
    map<float, int> denominals; //map stores the number of each denomination in the machine
    virtual void showOptions() = 0;
    virtual float Choice(int x) = 0;
    VendingMachine() //the constructor assigns the available coin pool for the different denominations (1zl-100zl and 10gr-50 gr) and sets the account value to 0
    {
        denominals[0.1] = 10;
        denominals[0.2] = 10;
        denominals[0.5] = 10;
        denominals[1] = 10;
        denominals[2] = 10;
        denominals[5] = 10;
        denominals[10] = 10;
        denominals[20] = 10;
        denominals[50] = 10;
        denominals[100] = 10;
        account = 0;
    }

    //the function accepts coins from the user (calculates the amount deposited and counts the available coins)
    void chargeAccount(float zl)
    {
       if(denominals.count(zl) == 0)//if fiven denomination doesnt exist throw an exception
        {
            ErrorD();
        }
       else
       {
            account += into_gr(zl); //the account balance increases by the denomination amount specified by the user
            denominals[zl]++; //number of given denomination increases by 1
       }
    }

    //substracts price of bought product from the account
    void buyProduct(int gr)
    {
        if(gr > account || gr < 0)
            ErrorD();
        else
            account -= gr;
    }

    //method prints amounts and types of denominations needed to give the change
    //it is done using the greedy method, with the zloty (denomination in Poland) it is possible  to do it without errors
    //using dynamic programming would be more optimal
    void giveChange()
    {
        if(account < 10)
            {
                cout << account << endl;
                account = 0;
                ErrorC();
            }
        else
        {
            map<float, int> change; //stores denominations and their number needed to give out the change
            int remaining_amount = account;
            cout << "I need to give: " << remaining_amount << "gr change: " << endl;

            map<float, int>::iterator it; //enables to iterate through the loop
            for (it = denominals.begin(); it != denominals.end(); it++)
            {
                float nominal = it->first;
                int number = it->second;
                while(remaining_amount >= nominal * 100 && denominals[nominal] > 0)
                {
                    remaining_amount -= nominal * 100;
                    denominals[nominal]--;
                    if(change.find(nominal) == change.end()) //adds to my map change amount of denominations
                        change[nominal] = 1;
                    else
                        change[nominal]++;
                }
            }
            if(remaining_amount != 0) //if there is charge left, it means there is no chance to give the change
            {
                cout << account << endl;
                account = 0;
                ErrorC();
            }
            else
            {
                map<float, int>::iterator it; //iterator
                //actualizes state of current number of denominationals
                for (it = denominals.begin(); it != denominals.end(); it++)
                {
                    float nominal =  it->first;
                    int number = it->second;
                    denominals[nominal] -= number;
                }
                //outputs the charge
                for (it = change.begin(); it != change.end(); it++)
                {
                    float nominal =  it->first;
                    int number = it->second;
                    cout << number << " * "<< nominal << " zl" << endl;
                    change[nominal] -= number;
                }
            }
            account = 0;
        }
    }
    void accountBalance()
    {
        cout << "Account balance: " << into_zl(account) << " zl" << endl;
    }
    ~VendingMachine()
    {
    }

};

class CoffeeMachine : public VendingMachine
{
    string Offer[8] = {"Hot Milk", "Expresso", "Cappuchino", "Coffee Latte", "Carmel Latte", "Americano", "Iced Coffe Latte", "Mocha"};
    float Price[8] = {0.8, 4.50, 6.20, 6.50, 11, 7, 10.50, 11};
public:
    CoffeeMachine()
    {
    }
    void showOptions()
    {
        for(int i = 0; i < 8; i++)
        {
            cout << "option " << i << ": " << Offer[i] << " for " << Price[i] << endl;
        }cout << endl;
    }
    float Choice(int c)
    {
        if(c < 0 || c > 7)
            {
               ErrorI();
               return 1;
            }
        else
            return Price[c];
    }
};

class SnackMachine : public VendingMachine
{
    string Offer[9] = {"Chocolate Muffin", "Carmen Muffin", "Cinnamon Pretzel", "Fruit Joghurt", "Yeast Crumble", "Oat bar", "Wanilla Protein Bar", "Toast with Peanut Butter", "Puff Pastry With Apples"};
    float Price[9] = {5, 5.20, 6.50, 9, 5.50, 2.30, 7.80, 12.30, 12};
public:
    SnackMachine()
    {
    }
    //shows the product options
    void showOptions()
    {
        for(int i = 0; i < 9; i++)
        {
            cout << "option " << i << ": " << Offer[i] << " for " << Price[i] << endl;
        }cout << endl;
    }
    float Choice(int c)
    {
        if(c < 0 || c > 8)
            {
                ErrorI();
                return 1;
            }
        else
            return Price[c];
    }
};

int main()
{
    VendingMachine *Machines[2];
    Machines[0] = new CoffeeMachine();
    Machines[1] = new SnackMachine();

    cout << "Welcome to my Vending Machines program." << endl;
    cout << "Press 1 if you want use Coffee Machine, 2 if you want to use Snack Machine." << endl;
    cout << "While using Vending Machines the only available denominations are 1zl-100zl and 10gr-50gr" << endl;
    cout << endl;

    char c = 'y';
    while (c == 'y' || c == 'Y')
    {
        int option;
        cin >> option;
        if(option == 1 || option == 2)
        {
            int nr, o = 0;
            Machines[option-1]->showOptions();
            cout << "Input the product number you want to buy." << endl;
            cin >> nr;
            cout << "You need to pay " << Machines[option-1]->Choice(nr) << " for the product." << endl;
            while(o >= 0 && o < 4)
            {
                cout << "Press 1 charge your account, 2 to check your account, 3 to buy the product" << endl;
                cin >> o;
                if(o == 1)
                {
                    int m;
                    cout << "How much do you want to charge your account in zloty?" << endl;
                    cin >> m;
                    Machines[option-1]->chargeAccount(m);
                }
                else if(o == 2)
                {
                    Machines[option-1]->accountBalance();
                }
                else if(o == 3)
                {
                    Machines[option-1]->buyProduct(into_zl(Machines[option-1]->Choice(nr)));
                    Machines[option-1]->giveChange();
                    break;
                }
                else
                    ErrorI();
            }
        }
        else
            ErrorI();

        cout << "Press y or Y if you want to use one of the machines once again" << endl;
        cin >> c;
    }
return 0;
}
