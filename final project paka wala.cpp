#include <iostream>
#include <string>
using namespace std;

struct Snack {
    string name;
    int price;
    int stock;
};

int totalBalance = 0;
const int MAX_RESTOCK = 50;

// Function declarations
void displayMenu(string menu[], int size);
void adminMode(Snack snacks[], int size);
void customerMode(Snack snacks[], int size);
void displaySnacks(Snack snacks[], int size);
void restockSnack(Snack snacks[], int index);
void purchaseSnack(Snack snacks[], int size);
void checkBalance();
void resetBalance();
bool exitProgram(int choice);

// Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Background Color Codes
#define BG_RED    "\033[41m"
#define BG_GREEN  "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE   "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN   "\033[46m"
#define BG_WHITE  "\033[47m"

// Function to display the menu
void displayMenu(string menu[], int size) 
{
    for (int i = 0; i < size; ++i)
	 {
        cout << menu[i] << endl;
    }
}
//adminMode function

void adminMode(Snack snacks[], int size) 
{
    int adminChoice;
    do
	 {
        system("Cls");

        string menu[] = {
            BG_CYAN BOLD "                            Admin Mode                                        " RESET,
            BG_YELLOW "                             1. Restock Snack                                    " RESET,
            BG_YELLOW "                             2. View Snacks                                      " RESET,
            BG_YELLOW "                             3. Check Total Balance                              " RESET,
            BG_YELLOW "                             4. Reset Total Balance                              " RESET,
            BG_YELLOW "                             5. Back to Main Menu                                " RESET
        };
        
        
        displayMenu(menu, 5);

        cin >> adminChoice;
        if (exitProgram(adminChoice)) break;

        switch (adminChoice) {
            case 1:
                int snackIndex;
                cout << "Enter snack number to restock (0 to " << size - 1 << "): ";
                cin >> snackIndex;
                if (snackIndex >= 0 && snackIndex < size) {
                    restockSnack(snacks, snackIndex);
                } else {
                    cout << RED "Invalid snack number!" RESET << endl;
                }
                break;
            case 2:
                displaySnacks(snacks, size);
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                resetBalance();
                break;
            case 5:
                cout << GREEN "Returning to main menu..........**" RESET << endl;
                break;
            default:
                cout << RED "Invalid choice, try again!" RESET << endl;
        }

        
       cout << "Press Enter to continue the code";
       
	    cin.ignore(); 
        cin.get();  
    }
	 while (adminChoice != 5);
}
 //customerMode function
 
void customerMode(Snack snacks[], int size) 
{
    int customerChoice;
    do 
	{
        system("Cls");

        string menu[] = {
            BG_CYAN BOLD "                      Customer Mode                           " RESET,
            BG_YELLOW "                         1. View Snacks                          " RESET,
            BG_YELLOW "                         2. Purchase Snack                       " RESET,
            BG_YELLOW "                         3. Back to Main Menu                    " RESET
        };
        displayMenu(menu, 4);

        cin >> customerChoice;
        if (exitProgram(customerChoice)) break;

        switch (customerChoice) 
		{
            case 1:
                displaySnacks(snacks, size);
                break;
            case 2:
                purchaseSnack(snacks, size);
                break;
            case 3:
                cout << GREEN "Returning to main menu...........**" RESET << endl;
                break;
            default:
                cout << RED "Invalid choice, try again!" RESET << endl;
        }

        
       cout << "Press Enter to continue the code";
        cin.ignore(); 
        cin.get();  
    } while (customerChoice != 3);
}
// displaySnack fumction using void for both 

void displaySnacks(Snack snacks[], int size)
 {
    system("Cls");
    cout << CYAN "Available Snacks:" RESET << endl;
    for (int i = 0; i < size; ++i) 
	{
        cout << BG_BLUE << i << ". " << snacks[i].name << " - $" << snacks[i].price
             << " (Stock: " << snacks[i].stock << ")" RESET << endl;
    }
}

//adminMode  function for restocking snacks

void restockSnack(Snack snacks[], int index)
 {
    system("Cls");
    int quantity;
    cout << YELLOW "Enter quantity to restock for " << snacks[index].name << " (Max " << MAX_RESTOCK << "): " RESET;
    cin >> quantity;
    if (quantity <= MAX_RESTOCK && quantity > 0)
	 {
        snacks[index].stock += quantity;
        cout << GREEN "Restocked " << quantity << " units of " << snacks[index].name << "." RESET << endl;
    }
	 else
	 {
        cout << RED "Invalid quantity!" RESET << endl;
    }

    
   cout << "Press Enter to continue the code";
    cin.ignore();  
    cin.get();  
}

//customer function to purchase snack

void purchaseSnack(Snack snacks[], int size) 
{
    system("Cls");
    int totalCost = 0;
    int totalPaid = 0;
    char anotherPurchase;
    do
	 {
        int snackIndex;
        cout << YELLOW "Enter snack number to purchase (0 to " << size - 1 << "): " RESET;
     cin >> snackIndex;

    if (snackIndex >= 0 && snackIndex < size)
		 {
    if (snacks[snackIndex].stock > 0)
	 {
   snacks[snackIndex].stock--;
   
 totalCost += snacks[snackIndex].price;
 
cout << GREEN "You added " << snacks[snackIndex].name << " for $" << snacks[snackIndex].price << "." RESET << endl;
            }
			 else
			 {
                cout << RED "Sorry, " << snacks[snackIndex].name << " is out of stock!" RESET << endl;
            }
        } 
		else
		 {
            cout << RED "Invalid snack number!" RESET << endl;
        }

        cout << "Do you want to add another item? (y/n): ";
        cin >> anotherPurchase;
    }
	 while (anotherPurchase == 'y' || anotherPurchase == 'Y');

    cout << "Total cost: $" << totalCost << endl;
    cout << YELLOW "Enter amount to pay: $" RESET;
    cin >> totalPaid;

    if (totalPaid >= totalCost) 
	{
        totalBalance += totalCost;
        int change = totalPaid - totalCost;
        cout << GREEN "You paid $" << totalPaid << ". Your change is $" << change << "." RESET << endl;
        cout << "Thank you for your purchase!" << endl;
    } 
	else
	 {
        cout << RED "Insufficient funds!" RESET << endl;
    }

    
    cout << "Press Enter to continue the code";
    cin.ignore();  
    cin.get();  
}

//function for admin o check balance

void checkBalance()
 {
    system("Cls");
    cout << CYAN "Total balance from customer purchases: $" << totalBalance << RESET << endl;

    
   cout << "Press Enter to continue the code";
    cin.ignore();  
    cin.get();  
}

// fumnction for adminMode to rese balance

void resetBalance() 
{
    system("Cls");
    totalBalance = 0;
    cout << CYAN "Total balance has been reset to $0." RESET << endl;

    
    cout << "Press Enter to continue the code";
    cin.ignore();  
    cin.get(); 
}

bool exitProgram(int choice) 
{
    system("Cls");
    if (choice == 100)
	 {
        cout << "Exiting program..." << endl;
        return true;
    }
    return false;
}
// staring main program

int main() 
{

    int choice;
    const string ADMIN_PASSWORD = "irfaalisha";  // Admin password

    Snack snacks[] = {
        {"Chips", 10, 5},
        {"Soda", 15, 5},
        {"Chocolate", 20, 5},
        {"Candy Bar", 12, 5},
        {"Cookies", 18, 5},
        {"Gum", 5, 5}
    };
    int size = sizeof(snacks) / sizeof(snacks[0]);

    do 
	{
        system("Cls");

        string menu[] = {
            BG_CYAN BOLD"                                  Welcome to Snack Machine!                             " RESET,
            BG_YELLOW "                                     1. Admin Mode                                         " RESET,
            BG_YELLOW "                                     2. Customer Mode                                      " RESET,
            BG_YELLOW "                                     3. Exit                                               " RESET
        };
        
        displayMenu(menu, 4);

        cin >> choice;
        if (exitProgram(choice)) break;

        switch (choice) 
		{
            case 1:
			 {
                string password;
                
                cout << YELLOW "Enter admin password: " RESET;
                cin >> password;
                if (password == ADMIN_PASSWORD)
				 {
                    adminMode(snacks, size);
                } else 
				{
                    cout << RED "Incorrect password!" RESET << endl;
                }
                break;
            }
            case 2:
            	
                customerMode(snacks, size);
                
                break;
            case 3:
                cout << GREEN "Exiting..." RESET << endl;
                break;
            default:
                cout << RED "Invalid choice, please try again!" RESET << endl;
                
                break;
        }

    } while (choice != 3);

    return 0;
}

