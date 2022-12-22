#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
using namespace std;

const int SIZE = 51;

struct InventoryItem
{
    char name[SIZE];
    int item_ID;
    char category[SIZE];
    int item_count;
    int people_count = 0;
    char Allocated_to[SIZE][SIZE] = {};
};
//<--------------------List of All Functions--------------------------->

void AddItems(fstream &, char filename[]);
void ViewItems(fstream &, char filename[]);
void SearchItems(fstream &, char filename[]);
void UpdateItems(fstream &, char filename[]);
void DeleteItems(fstream &, char filename[]);
void Allocate_to(fstream &, char filename[]);
void Retrieve(fstream &, char filename[]);
void View_Members(fstream &, char filename[]);

//<-----------------------Main Functions----------------------->
int main()
{
    fstream file;
    char again, enter;
    int menu_no;

    char file_name[SIZE] = "Inventory_items_data.txt";
    do
    {
        cout << "MENU: " << endl;
        cout << "Press 1 to Add Item" << endl;
        cout << "Press 2 to View Items" << endl;
        cout << "Press 3 to Search items" << endl;
        cout << "Press 4 to Update items" << endl;
        cout << "Press 5 to Assign items" << endl;
        cout << "Press 6 to Retrieve items" << endl;
        cout << "Press 7 to View Members" << endl;
        cout << "Press 8 to Delete Members" << endl;
        cout << "Press 0 to exit the Program" << endl;
        cin >> menu_no;
        cin.ignore();
        if (menu_no == 1)
        {
            AddItems(file, file_name);
        }
        else if (menu_no == 2)
        {
            ViewItems(file, file_name);
        }
        else if (menu_no == 3)
        {
            do
            {
                SearchItems(file, file_name);
                cout << "Do you want to search again?";
                cin.get(again);
            } while (again == 'y' || again == 'Y');
        }
        else if (menu_no == 4)
        {
            do
            {
                UpdateItems(file, file_name);
                cout << "Do you want to update again?";
                cin.get(again);
            } while (again == 'y' || again == 'Y');
        }
        else if (menu_no == 5)
        {

            do
            {
                Allocate_to(file, file_name);
                cout << "Do you want to assign again?" << endl;
                cin.get(again);
                cin.ignore();
            } while (again == 'y' || again == 'Y');
        }
        else if (menu_no == 6)
        {
            do
            {
                Retrieve(file, file_name);
                cout << "Do you want to retrieve again?";
                cin.get(again);
            } while (again == 'y' || again == 'Y');
            Retrieve(file, file_name);
        }
        else if (menu_no == 7)
        {
            View_Members(file, file_name);
        }
        else if (menu_no == 8)
        {
            DeleteItems(file, file_name);
        }
        else if (menu_no == 0)
        {
            exit(0);
        }
        else
        {
            cout << "Invalid number" << endl;
        }
        cout << "\nPress Enter to Continue" << endl;
        cin.get(enter);
        // cin.ignore();
    } while (1);

    return 0;
}
//-------------------------------ADD Functions--------------------->

void AddItems(fstream &filex, char filename[])
{
    InventoryItem item;
    char again;
    filex.open(filename, ios::binary | ios::out);
    do
    {

        cout << "Enter the details of the item" << endl;
        cout << "Enter name: ";
        cin.getline(item.name, SIZE);
        cout << "Enter the item ID: ";
        cin >> item.item_ID;
        cin.ignore();
        cout << "Enter the item category: ";
        cin.getline(item.category, SIZE);
        cout << "Enter the item count: ";
        cin >> item.item_count;

        filex.write(reinterpret_cast<char *>(&item), sizeof(item));

        cout << "Do you want to add more data?(y/n)?";
        cin >> again;
        cin.ignore();
    } while (again == 'y' || again == 'Y');

    filex.close();
}

//--------------------------VIEW Functions------------------------->

void ViewItems(fstream &filex, char filename[])
{
    InventoryItem items;
    char next;

    filex.open(filename, ios::binary | ios::in);
    if (!filex)
    {
        cout << "Error in file opening";
    }

    else
    {
        cout << "Here are the items in the Inventory" << endl;

        filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        cout << left << setw(12) << "NAME" << setw(10) << "ID" << setw(13) << "Category" << setw(14) << "item-Count" << endl;
        while (!filex.eof())
        {

            cout << left << setw(12) << items.name << setw(10) << items.item_ID << setw(13)
                 << items.category << setw(14) << items.item_count << endl;

            filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        }
        cout << "That's All the items in inventory";
    }
    filex.close();
}

//-----------------------------SEARCH items Function--------------------

void SearchItems(fstream &filex, char filename[])
{
    InventoryItem items;
    bool available = 0;
    int id;
    char name[20];
    cout << "\nEnter the name of the item ";
    cin.getline(name, 20);
    filex.open(filename, ios::binary | ios::in | ios::out);
    // cout << "\nenter the id ";

    // cin >> id;
    // cin.ignore();
    if (!filex)
    {
        cout << "Error in file opening";
    }
    else
    {
        filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        while (!filex.eof())
        {
            if (strcmp(name, items.name) == 0)
            {
                cout << "\nName of item: " << items.name << endl;
                cout << "The item ID is: " << items.item_ID << endl;
                cout << "The item category is: " << items.category << endl;
                cout << "The item count is: " << items.item_count << endl;
                available = 1;
                filex.close();
                return;
            }

            filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        }
        if (!available)
        {
            cout << "Record of that item does not exists" << endl;
        }
    }
    filex.close();
}

//------------------------Update items function-----------------------

void UpdateItems(fstream &filex, char filename[])
{
    int num;
    char name[20];
    cout << "\nEnter the name of the item ";
    cin.getline(name, 20);
    bool available = 0;
    InventoryItem items;
    // cout << "\nEnter the ID to be updated ?";
    // cin >> num;
    // cin.ignore();
    filex.open(filename, ios::binary | ios::in | ios::out);
    filex.seekg(0);
    if (!filex)
    {
        cout << "file did not opened successfully";
    }
    else
    {
        filex.read(reinterpret_cast<char *>(&items), sizeof(items));

        while (!filex.eof())
        {
            if (strcmp(name, items.name) == 0)
            {
                cout << "\nName of item: " << items.name << endl;
                cout << "The item ID is: " << items.item_ID << endl;
                cout << "The item category is: " << items.category << endl;
                cout << "The item count is: " << items.item_count << endl;
                // now to update the given data.
                cout << "Enter new values to update " << endl;

                cout << "Enter name: ";
                cin.getline(items.name, SIZE);
                cout << "Enter the item ID: ";
                cin >> items.item_ID;
                cin.ignore();
                cout << "Enter the item category: ";
                cin.getline(items.category, SIZE);
                cout << "Enter the item count: ";
                cin >> items.item_count;
                // filex.seekp(filex.tellp()-sizeof(items));
                long pos = sizeof(items);
                filex.seekp(-pos, ios::cur);
                filex.write(reinterpret_cast<char *>(&items), sizeof(items));
                cout << "Item updated successfully\n";
                available = 1;
                break;
            }
            else
            {
                filex.read(reinterpret_cast<char *>(&items), sizeof(items));
            }
        }
        if (!available)
        {
            cout << "Record of that item does not exists" << endl;
        }
    }
    // filex.clear();
    filex.close();
}

//------------------------------Delete Item Function--------------------

void DeleteItems(fstream &filex, char filename[])
{
    int num;
    char name[20];
    cout << "\nEnter the name of the item ";
    cin.getline(name, 20);
    bool available = 0;
    InventoryItem items;
    fstream tempfile;
    tempfile.open("temp.txt", ios::binary | ios::out);
    filex.open(filename, ios::binary | ios::in | ios::out);
    // cout << "Enter the ID to be deleted: ";
    // cin >> num;

    if ((!filex) || (!tempfile))
    {
        cout << "file did not opened successfully";
    }
    else
    {
        filex.read(reinterpret_cast<char *>(&items), sizeof(items));

        while (!filex.eof())
        {
            if (strcmp(name, items.name) != 0)
            {
                available = 1;

                tempfile.write(reinterpret_cast<char *>(&items), sizeof(items));
            }
            filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        }
        if (!available)
        {
            cout << "Record of that item does not exists" << endl;
        }
    }
    filex.close();
    tempfile.close();

    remove("Inventory_items_data.txt");
    rename("temp.txt", "Inventory_items_data.txt");

    cout << "\nRecord deleted successfully\n";
}

//-------------------------Assign Functions-------------------------

void Allocate_to(fstream &filex, char filename[])
{
    InventoryItem items;
    char Name[20];
    char name[20];
    cout << "\nEnter the name of the item ";
    cin.getline(name, 20);
    int num;
    // cout << "Enter the id to allocate: ";
    // cin >> num;
    // cin.ignore();
    filex.open(filename, ios::binary | ios::in | ios::out);
    if (!filex)
    {
        cout << "file did not opened successfully";
    }
    else
    {
        filex.read(reinterpret_cast<char *>(&items), sizeof(items));

        while (!filex.eof())
        {
            if (strcmp(name, items.name) == 0)
            {
                cout << "list the people allocated to { ";
                for (int i = 0; i < items.people_count; i++)
                {
                    cout << items.Allocated_to[i] << endl;
                }
                cout << "}." << endl;

                cout << "Enter the name who want to borrw:" << endl;
                cin.getline(Name, 20);

                strcpy(items.Allocated_to[items.people_count], Name);
                items.people_count++;
                --items.item_count;
                cout << "The remaiing count of items is " << items.item_count;

                cout << "\nlist the people allocated to { ";
                for (int i = 0; i < items.people_count; i++)
                {
                    cout << items.Allocated_to[i] << endl;
                }
                cout << "}." << endl;
                long pos = sizeof(items);
                filex.seekp(-pos, ios::cur);
                filex.write(reinterpret_cast<char *>(&items), sizeof(items));
                break;
            }
            else
            {
                filex.read(reinterpret_cast<char *>(&items), sizeof(items));
            }
        }
    }
    filex.close();
}

//-------------------------------Retrieve Item Function------------------------------

void Retrieve(fstream &filex, char filename[])
{
    int num;
    char Name[20];
    InventoryItem items;
    char name[20];
    cout << "\nEnter the name of the item ";
    cin.getline(name, 20);

    // cout << "\nEnter the item ID to return ";
    // cin >> num;
    // cin.ignore();
    cout << "Enter the name of person ";
    cin.getline(Name, 20);
    filex.open(filename, ios::binary | ios::in | ios::out);

    if (!filex)
    {
        cout << "file did not opened successfully";
    }
    else
    {
        filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        while (!filex.eof())
        {

            if (strcmp(name, items.name) == 0)
            {
                for (int i = 0; i < items.people_count; i++)
                {
                    if (strcmp(items.Allocated_to[i], Name) == 0)
                    {
                        cout << "list the people allocated to before { ";
                        for (int i = 0; i < items.people_count; i++)
                        {
                            cout << items.Allocated_to[i] << " ";
                        }
                        cout << "}." << endl;
                        strcpy(Name, "");

                        strcpy(items.Allocated_to[i], Name);

                        cout << "\nlist the people allocated to after { ";
                        for (int i = 0; i < (items.people_count + 1); i++)
                        {
                            cout << items.Allocated_to[i] << " ";
                        }
                        cout << "}." << endl;
                        items.people_count--;
                        items.item_count++;
                        cout << "The remaiing count of items is " << items.item_count;

                        long pos = sizeof(items);
                        filex.seekp(-pos, ios::cur);
                        filex.write(reinterpret_cast<char *>(&items), sizeof(items));
                        filex.close();
                        return;
                    }
                }
            }
            else
            {
                filex.read(reinterpret_cast<char *>(&items), sizeof(items));
            }
        }
    }

    filex.close();
}

//------------------------VIEW All faculty members Function ------------------

void View_Members(fstream &filex, char filename[])
{
    InventoryItem items;
    cout << "Here is the list of all the faculty members who have borrowed a specific item" << endl;
    filex.open(filename, ios::binary | ios::in);
    if (!filex)
    {
        cout << "file did not opened successfully";
    }
    else
    {
        filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        while (!filex.eof())
        {
            cout << items.name << " : " << endl;
            for (int i = 0; i < (items.people_count + 1); i++)
            {
                if (strlen(items.Allocated_to[i]) > 1)
                {
                    cout << "\t" << items.Allocated_to[i] << endl;
                }
            }

            filex.read(reinterpret_cast<char *>(&items), sizeof(items));
        }
    }
    filex.close();
}