/*       ATM machine project           */

#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>
#include<iomanip>
#include <ctime>
using namespace std;

// Class ATM to get user details
class ATM
{
private:
	char username[30];
	int password;
	long long balance;
	long long  acc_no;

public:
	char* usernames(void)
	{
		// Return username
		return username;
	}

	int passwords(void)
	{
		// Return the password
		return password;
	}
	
	long long acc_nos(void)
	{
		return acc_no;
	}
	// Function to get the data
	void getData(void)
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nEnter username:";
		cin.getline(username, 30);
		

		cout << "\nEnter Account Number:";
		cin>> acc_no;

		// storing data of added user in excel file
		ofstream Data;
		Data.open("outfile.csv", ios::app);
		Data << username << "," << acc_no <<endl;	// storing username and account number of user


		cout << "\nEnter 4-digit password:";
		cin >> password;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nEnter initial balance:";
		cin >> balance;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Function displaying the data
	void showData(void)
	{
		cout << "Username: " << username
			<< ", Password: " << password
			<< ", Balance: " << balance
			<< ", Account number: " << acc_no << endl;
	}

	// Member Functions
	int add_user();
	int display_all_users();
	int delete_User(char*);
	void update_user_deposit(char*);
	void update_user_withdraw(char*);
	int search_specific_User(char*, int);
	int search_users_to_display(char*);
	int update_changePassword(char*, int a);
};

// Function to implement functionality
// of ATM User

void atmUser()
{
	ATM a;

	char uname[30];
	int pass, ch, ch1, ch2, found = 0;

mainmenu:
	system("cls");
	cout << "\n\t\t\t***********MAIN PAGE**************\n";
	cout << "\n\t\t\tLogin as :\n\t\t\t1. Admin\n\t\t\t2. User\n\t\t\t3.Exit\n\t\t\tChoose one : ";
	cin >> ch;

	switch (ch)
	{
	case 1:
	rerun:
		system("cls");
		cout << "\nEnter details to login as Admin\n";
		cout << "\nEnter password: ";
		cin >> pass;
		if (pass == 1234)
		{
			sleep(2);
		admin:
			system("cls");
			cout << "\nWelcome to Admin Menu";
			cout << "\n1. Add User\n2."
			    	" Delete User\n3. "
				    "View All User\n4. "
				    "Exit";

			cout << "\nSelect one option : ";
			cin >> ch1;

			switch (ch1)
			{
			case 1:
				a.add_user();
				cout << "\nUser is added successfully !!";
				sleep(2);
				goto admin;

			case 2:
				cout << "\nEnter the username to be deleted : ";

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.getline(uname, 30);
				a.delete_User(uname);
				sleep(2);
				goto admin;

			case 3:
				a.display_all_users();
				system("pause");
				goto admin;

			case 4:
				break;
			}
		}

		else
		{
			cout << "\nDetails are incorrect ! Please try again";
			cin.get();
			goto rerun;
		}

		goto mainmenu;

	case 2:
		system("cls");
		cout << "\n Enter details to login as user\n";

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Enter username:";
		cin.getline(uname, 30);

		cout << "\nEnter password:";
		cin >> pass;
		found = a.search_specific_User(uname, pass);

		if (found)
		{
			user:

			/*This is used to find at what time user log into his account*/
			time_t now = time(0);				// current date and time on the current system
			char* date_time = ctime(&now);		// convert now to string form

			// to store data of added user in excel file
			ofstream login_Data;
			login_Data.open("user_data.csv", ios::app);
			login_Data << uname <<","<< date_time << endl;	// storing username , date and time when user logins

			cout << "\nWelcome " << uname;

			cout << "\nWelcome to User Menu";
			cout << "\n1. Deposit\n2."
				" Withdraw\n3. View "
				"Account\n4. Change Password\n5. "
				"Exit\nEnter your choice:";
			cin >> ch2;

			switch (ch2)
			{
				case 1:
					a.update_user_deposit(uname);
					cout<<"\n";
					system("pause");
					system("cls");
					goto user;
				case 2:
					a.update_user_withdraw(uname);
					cout<<"\n";
					system("pause");
					system("cls");
					goto user;
				case 3:
					a.search_users_to_display(uname);
					cout<<"\n";
					system("pause");
					system("cls");
					goto user;
	
				case 4:
				{
	
					cout << "Please enter the original password" << endl;
					int count = 0;
					while (count <= 2)		//Only give three chances to enter the original password
					{
						int pass1;
						cin >> pass1;
	
						if (pass1 == pass)
						{
							cout << "Please enter new password:" << endl;
							int changedpassword;
							cin >> changedpassword;
	
							pass = changedpassword;
							cout << "Password reset complete!" << endl;
	
							a.update_changePassword(uname, pass);
							cout<<"\n";
							system("pause");
							system("cls");
							goto user;
						}
	
						else
						{
							cout << "Password entered incorrectly, please enter again" << endl;
	
						}
	
					}
					cout << "The password has been entered incorrectly 3 times, please try again tomorrow!" << endl;	//Enter three errors and cannot be modified
					
					cout<<"\n";
					system("pause");
					goto user;
				}

				case 5:
					cout << "Thank you";
					sleep(2);
					break;
			}
		}

		else
		{
			cout << "\nNo account found with username " << uname << "\n\nHit ENTER to continue";
			cin.get();
		}
		goto mainmenu;

	case 3:
		cout << "\n**********Thankyou For Banking With Us**********";
		cin.get();
		break;
	}
}

// Function to add user
int ATM::add_user()
{
	ATM a;

	ofstream file;

	// Open file in write mode
	file.open("DATA.txt", ios::out | ios::app);

	if (!file)
	{
		cout << "Error in creating file..." << endl;
		return 0;
	}

	// Read from user
	a.getData();

	// Write into file
	file.write((char*)&a, sizeof(a));

	// Close the file
	file.close();

	return 0;
}

// View Users
int ATM::display_all_users()
{

	ATM a;

	ifstream file1;

	// Open file in read mode
	file1.open("DATA.txt", ios::in);

	if (!file1)
	{
		cout << "Error in opening file...";
		return 0;
	}

	// Read data from file
	file1.read((char*)&a, sizeof(a));

	while (!file1.eof())
	{

		// Display data on monitor
		a.showData();
		file1.read((char*)&a, sizeof(a));
	}

	// Close the file
	file1.close();
	return 0;
}

// Function to delete the user
int ATM::delete_User(char* uname)
{

	ATM a;

	fstream original, temp;
	original.open("DATA.txt", ios::in);

	if (!original)
	{
		cout << "\nFile not found";
		return 0;
	}

	else
	{
		temp.open("temp.txt", ios::out | ios::app);
		original.read((char*)&a, sizeof(a));

		// Till end of file is reached
		while (!original.eof())
		{

			if (!strcmp(a.usernames(), uname))
			{
				cout << "Data Found and Deleted\n" << a.username << "\n";
			}

			else
			{
				temp.write((char*)&a, sizeof(a));
			}

			original.read((char*)&a, sizeof(a));
		}

		original.close();
		temp.close();
		remove("DATA.txt");
		rename("temp.txt", "DATA.txt");

	}
	return 0;
}

// Function to update user by
// depositing money
void ATM::update_user_deposit(char* uname)
{

	ATM a;
	fstream file, temp;
	file.open("DATA.txt", ios::in | ios::out | ios::ate);
	temp.open("temp.txt", ios::out | ios::app);
	file.seekg(0);
	file.read((char*)&a, sizeof(a));

	// Till end of the file
	while (!file.eof())
	{
		if (!strcmp(a.usernames(), uname))   // condition when two string are equal
		{
			long long b;

			cout << "\nEnter amount to deposit:";
			cin >> b;

			a.balance = a.balance + b;
			cout << "\nAmount deposited successfully !!\nRemaining Balance is:" << a.balance;
			temp.write((char*)&a, sizeof(a));
		}

		else
		{
			temp.write((char*)&a, sizeof(a));
		}

		file.read((char*)&a, sizeof(a));
	}

	file.close();
	temp.close();
	remove("DATA.txt");
	rename("temp.txt", "DATA.txt");
}

// Function to update user by depositing withdrawing money
void ATM::update_user_withdraw(char* uname)
{

	ATM a;
	fstream file, temp;
	file.open("DATA.txt", ios::in | ios::out | ios::ate);
	temp.open("temp.txt", ios::out | ios::app);
	file.seekg(0);
	file.read((char*)&a, sizeof(a));

	// Till end of file is reached
	while (!file.eof())
	{
		if (!strcmp(a.usernames(), uname))
		{
			long long b;
			cout << "\nEnter amount to withdraw:";
			cin >> b;
			if (a.balance < b)
			{
				cout
					<< "\nInsufficient balance to withdraw";
			}

			else
			{
				a.balance = a.balance - b;
				temp.write((char*)&a, sizeof(a));
				cout << "\nAmount withdraw successfully!!\nBalance is:" << a.balance;
			}
		}

		else
		{
			temp.write((char*)&a, sizeof(a));
		}

		file.read((char*)&a, sizeof(a));
	}

	// Close the file
	file.close();
	temp.close();
	remove("DATA.txt");
	rename("temp.txt", "DATA.txt");
}

// Search user
int ATM::search_specific_User(char* uname, int pass)
{
	ATM a;
	fstream f;

	// Open the file
	f.open("DATA.txt", ios::in);
	if (!f)
	{
		cout << "Error in opening file..";
		return 0;
	}

	// Read data from file
	f.read((char*)&a, sizeof(a));

	while (!f.eof())
	{

		if (!strcmp(a.usernames(), uname))
		{
			if (a.passwords() == pass)
			{
				return 1;
			}
		}

		f.read((char*)&a, sizeof(a));
	}

	// Close the file
	f.close();
	return 0;
}

// Search specific user
int ATM::search_users_to_display(char* uname)
{
	ATM a;
	fstream file1;

	// Open the file
	file1.open("DATA.txt", ios::in);

	if (!file1)
	{
		cout << "Error in opening file..";
		return 0;
	}

	// Read data from file
	file1.read((char*)&a, sizeof(a));

	while (!file1.eof())
	{
		if (!strcmp(a.usernames(), uname))
		{
			a.showData();
			return 0;
		}
		file1.read((char*)&a, sizeof(a));
	}

	// Close the file
	file1.close();
	return 0;
}


// update the changed password in file "DATA"
int ATM::update_changePassword(char* uname, int ucp)
{
	ATM a;
	fstream file, temp;
	file.open("DATA.txt", ios::in | ios::out | ios::ate);
	temp.open("temp.txt", ios::out | ios::app);
	file.seekg(0);
	file.read((char*)&a, sizeof(a));

	// Till end of file is reached
	while (!file.eof())
	{
		if (!strcmp(a.usernames(), uname))
		{
			a.password = ucp;
			temp.write((char*)&a, sizeof(a));
		}

		else
		{
			temp.write((char*)&a, sizeof(a));
		}

		file.read((char*)&a, sizeof(a));
	}

	// Close the file
	file.close();
	temp.close();
	remove("DATA.txt");
	rename("temp.txt", "DATA.txt");
}




// Driver Code
int main()
{
	system("color E0");
	cout << "\n	    Group Members : TAMANPREET KAUR | SUSHANT KUMAR  |  CHANDRABHUSHAN KUMAR  " << endl;
	cout << "				   Class :- BD1 Group (A) 	\n\n"  << endl;
	cout << "\n	====================================================================================" << endl;
	cout << "\n 	===================================================================================" << endl;
	cout << "\n 		    ||  @--@ WELCOME TO AUTOMATIC TELLER MACHINE @--@   ||" << endl;
	cout << "\n 	===================================================================================" << endl;
	cout << "\n 	===================================================================================\n\n" << endl;
	sleep(5);
	// Function Call
	atmUser();

	return 0;
}


