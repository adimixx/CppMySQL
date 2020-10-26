#pragma warning(disable : 4996)
#include<iostream>
#include <iomanip>
#include<string>
#include<conio.h>
#include<mysql.h>

using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res; //result data

string UserID, EquipmentID; //user session //store user ID
// Global Variable End


//Database Connection
class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            //(void)getchar();
            //system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "dbFire", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            _getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};
//End Database Connection

//Function Declaration
void Register();
void Login();
void AdminMenu();
void CustomerMenu();
void InsertNewEquipment();
void ListofEquipment();
void UpdateDelEquipment();
void SearchEquipment();
//End Function Declaration


int main()
{
    system("cls");
    system("title SMS Fire Equipment");
    system("color 0f");
    db_response::ConnectionFunction();

    int chooseOneFromMenu = 0;

    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
        case 1:
            Login();
            break;
        case 2:
            Register();
            break;
        case 3:
            cout << "Program Exiting..." << endl;
            exit(0);
        default:
            cout << "Please choose between 1 - 3. Press Enter To Continue...";
            _getch(); // get char // pause console //
            system("cls"); // clear console
            main(); //
            break;
    }
    return 0;
}

void Register()
{
    system("cls");
    string name, phone, address, username, password;

    cout << "Enter Name: ";
    cin.ignore(1, '\n'); // ignore space as next line
    getline(cin, name); // include space in input
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Username: "; //should be unique
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);

    // check username yang dah sedia ada dalam database
    string checkUser_query = "select * from Customer where Username = '" + username + "' limit 1"; //get the first line only
    //compare input dgn data dlm databse
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu); //execute query

    if (!qstate) //boleh execute
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1) //username exist
        {
            cout << "Username is already exist. Press Enter to Try Again...";
            _getch();
            Register();
        }
        else
        {
            string insertCustomer_query = "insert into Customer (Name, Phone, Address, Username, Password) values ('" + name + "', '" + phone + "', '" + address + "', '" + username + "', '" + password + "')";
            const char* q = insertCustomer_query.c_str(); // convert
            qstate = mysql_query(conn, q); //execute

            if (!qstate) //query boleh jalan
            {
                cout << endl << "You have been registered. Press Enter to Continue...";
                _getch();
                main(); //go main function
            }
            else
            {
                cout << "Error" << endl;
            }
        }

    }

}

void Login()
{
    system("cls");
    string username, password;
    int role = 0; //Admin role = 1 //Customer role = 2

    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    do
    {
        cout << "\nAdmin (1) or Customer (2) : ";
        cin >> role;
    } while (role != 1 && role != 2); //selain 1 & 2 //keep looping

    if (role == 1) //admin
    {
        //check username & password ygg dimasukkan
        string checkUser_query = "select * from Admin where Username = '" + username + "' and Password = '" + password + "'";
        const char* cu = checkUser_query.c_str();//convert
        qstate = mysql_query(conn, cu);//executee

        if (!qstate) //query boleh jalan
        {
            res = mysql_store_result(conn); //store result
            if (res->row_count == 1) //jumpa user
            {
                while (row = mysql_fetch_row(res)) //loop each of row dalam result
                    UserID = row[0]; //store ID in variable

                AdminMenu();
            }
            else //tak jumpa user //username & password salah
            {
                char c;
                cout << "Invalid username or password. Want to try again? (y/n): ";
                cin >> c;
                if (c == 'y' || c == 'Y')
                    Login();
                else
                    main();
            }
        }
    }

    else if (role == 2)
    {
        string checkUser_query = "select * from Customer where Username = '" + username + "' and Password = '" + password + "'";
        const char* cu = checkUser_query.c_str();//convert
        qstate = mysql_query(conn, cu);//executee

        if (!qstate) //query boleh jalan
        {
            res = mysql_store_result(conn); //store result
            if (res->row_count == 1) //jumpa user
            {
                while (row = mysql_fetch_row(res)) //loop each of row dalam result
                    UserID = row[0]; //store ID in variable

                CustomerMenu();
            }
            else //tak jumpa user //username & password salah
            {
                char c;
                cout << "Invalid username or password. Want to try again? (y/n): ";
                cin >> c;
                if (c == 'y' || c == 'Y')
                    Login();
                else
                    main();
            }
        }
    }
}

void AdminMenu()
{
    system("cls");
    int choose;

    cout << "Admin Menu" << endl;
    cout << "1. Insert New Equipment" << endl;
    cout << "2. List of Equipment" << endl;
    cout << "Pls choose: ";
    cin >> choose;
    switch (choose)
    {
        case 1:
            InsertNewEquipment(); //function to insert new data
            break;
        case 2:
            ListofEquipment();
            break;
    }
}

void CustomerMenu()
{
    system("cls");
    cout << "Customer Menu" << endl;
}

void InsertNewEquipment()
{
    system("cls");
    string name, mfgdate, expdate, quantity, price;

    cout << "Insert New Equipment" << endl;
    cin.ignore(1, '\n');
    cout << "Name of Equipment: ";
    getline(cin, name);
    cout << "Quantity of Stock: ";
    getline(cin, quantity);
    cout << "Price of Equipment: ";
    getline(cin, price);
    cout << "Manafacturer Date (dd/mm/yyyy): ";
    getline(cin, mfgdate);
    cout << "Expired Date (dd/mm/yyyy): ";
    getline(cin, expdate);

    //YYYY-MM-DD //default date format - MySQL

    string insert_query = "insert into Equipment (Name,Quantity,Price,Mfg_Date,Exp_Date) values ('" + name + "','" + quantity + "','" + price + "', STR_TO_DATE('" + mfgdate + "','%d/%m/%Y'), STR_TO_DATE('" + expdate + "','%d/%m/%Y'))";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate) //query boleh jalan
    {
        cout << endl << "Equipment is successful added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    char choose;
    do
    {
        cout << "Do you want add another equipment? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            InsertNewEquipment();
        }
        else if (choose == 'n' || choose == 'N')
        {
            AdminMenu();
        }
    } while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}

void ListofEquipment()
{
    system("cls");
    qstate = mysql_query(conn, "select EquipmentID, Name, Quantity, Price, date_format(Mfg_Date, '%d %M %Y'), date_format(Exp_Date, '%d %M %Y') from Equipment");

    //set width //header
    cout << setw(11) << "EquipmentID" << setw(17) << "Name" << setw(11) << "Stock" << setw(5) << " " << setw(5) << "Price" << setw(25) << "Manafacturer Date" << setw(25) << "Expired Date" << endl;

    if (!qstate)
    {
        //body table
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) //fetch every row until the end of data
        {
            cout << setw(6) << row[0] << setw(25) << row[1] << setw(7) << row[2] << setw(6) << "RM" << setw(7) << row[3] << setw(23) << row[4] << setw(26) << row[5] << endl;
        }
    }

    char choose;
    cout << "\nChoose (e) to edit or (s) to search equipment: ";
    cin >> choose;
    if (choose == 'e' || choose == 'E')
        UpdateDelEquipment();
    else if (choose == 's' || choose == 'S')
        SearchEquipment();
    else
        AdminMenu();

}

void UpdateDelEquipment()
{
    int stock = 0;
    int newquantity;
    char choose;

    string name, mfgdate, expdate, quantity, price;

    do
    {
        cout << "Update (u) or Delete (d): ";
        cin >> choose;
    } while (choose != 'u' && choose != 'U' && choose != 'd' && choose != 'D');

    cout << "Enter Equipment ID: ";
    cin >> EquipmentID;

    if (choose == 'u' || choose == 'U')
    {
        int chooseUpdate = 0;

        do
        {
            system("cls");
            string search_query = "select EquipmentID, Name, Quantity, Price, date_format(Mfg_Date, '%d %M %Y'), date_format(Exp_Date, '%d %M %Y') from Equipment where EquipmentID = '" + EquipmentID + "'";
            const char* q = search_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) //looping to retreive the data
            {
                cout << "--- Current Details of Equipment ---" << endl;
                cout << "Equipment ID: " << row[0] << " (Uneditable)"
                     << "\n\n1. Name: " << row[1]
                     << "\n2. Quantity: " << row[2]
                     << "\n3. Price: RM " << row[3]
                     << "\n4. Manafacturer Date: " << row[4]
                     << "\n5. Expired Date: " << row[5]
                     << "\n6. Save";
                stock = stoi(row[2]); // stoi = convert string to integer
            }
            cout << "\nChoose one: ";
            cin >> chooseUpdate;
            cin.ignore(1, '\n');
            if (chooseUpdate == 1)
            {
                cout << "Insert New Name: ";
                getline(cin, name);
                string update_query = "update Equipment set Name = '" + name + "' where EquipmentID = '" + EquipmentID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
            }
            else if (chooseUpdate == 2)
            {
                cout << "Insert New Quantity: ";
                cin >> newquantity;
                quantity = to_string(stock + newquantity); //calculate
                string update_query = "update Equipment set Quantity = '" + quantity + "' where EquipmentID = '" + EquipmentID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
            }
            else if (chooseUpdate == 3)
            {
                cout << "Insert New Price: RM ";
                getline(cin, price);
                string update_query = "update Equipment set Price = '" + price + "' where EquipmentID = '" + EquipmentID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);

            }
            else if (chooseUpdate == 4)
            {
                cout << "Insert New Mfg Date (dd/mm/yyyy): ";
                getline(cin, mfgdate);
                string update_query = "update Equipment set Mfg_Date = STR_TO_DATE('" + mfgdate + "', '%d/%m/%Y') where EquipmentID = '" + EquipmentID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
            }
            else if (chooseUpdate == 5)
            {
                cout << "Insert New Exp Date (dd/mm/yyyy): ";
                getline(cin, expdate);
                string update_query = "update Equipment set Exp_Date = STR_TO_DATE('" + expdate + "', '%d/%m/%Y') where EquipmentID = '" + EquipmentID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
            }
            else if (chooseUpdate == 6)
            {
                ListofEquipment();
            }
        } while (true);
    }

    else if (choose == 'd' || choose == 'D')
    {
        char choose2;
        do
        {
            cout << "Are you sure want to remove this Equipment? (y/n): ";
            cin >> choose2;
            if (choose2 == 'y' || choose2 == 'Y')
            {
                string delete_query = "delete from Equipment where EquipmentID = '" + EquipmentID + "'";
                const char* q = delete_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    cout << "The Equipment has been removed. Press Enter to Continue...";
                    _getch();
                    ListofEquipment();
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                }
            }

        } while (choose2 != 'y' && choose2 != 'Y' && choose2 != 'n' && choose2 != 'N');

    }
}

void SearchEquipment()
{
    system("cls");
    char choose;
    string name;
    cin.ignore(1, '\n');
    cout << "Search equipment by name: ";
    getline(cin, name);

    cout << "\t\t\t\t--- List of Searched Equipment ---" << endl;

    string search_query = "select EquipmentID, Name, Quantity, Price, date_format(Mfg_Date, '%d %M %Y'), date_format(Exp_Date, '%d %M %Y') from Equipment where name like '%" + name + "%'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(11) << "EquipmentID" << setw(17) << "Name" << setw(11) << "Stock" << setw(5) << " " << setw(5) << "Price" << setw(25) << "Manafacturer Date" << setw(25) << "Expired Date" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(6) << row[0] << setw(25) << row[1] << setw(7) << row[2] << setw(6) << "RM" << setw(7) << row[3] << setw(23) << row[4] << setw(26) << row[5] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "\nChoose (e) to edit or (s) to search equipment: ";
    cin >> choose;
    if (choose == 'e' || choose == 'E')
        UpdateDelEquipment();
    else if (choose == 's' || choose == 'S')
        SearchEquipment();
    else
        AdminMenu();
}