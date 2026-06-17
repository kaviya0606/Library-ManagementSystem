#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

struct Book
{
    int id;
    string title;
    string author;
};

struct Member
{
    int id;
    string name;
    string department;
};

void addBook()
{
    Book b;

    cout << "Enter Book ID: ";
    cin >> b.id;

    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, b.title);

    cout << "Enter Author: ";
    getline(cin, b.author);

    ofstream file("books.txt", ios::app);

    file << b.id << "|"
         << b.title << "|"
         << b.author << endl;

    file.close();

    cout << "Book Added Successfully!\n";
}

void viewBooks()
{
    ifstream file("books.txt");

    string line;

    cout << "\n===== BOOK LIST =====\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

void searchBook()
{
    ifstream file("books.txt");

    string searchTitle;
    string line;

    cin.ignore();

    cout << "Enter Book Title to Search: ";
    getline(cin, searchTitle);

    bool found = false;

    while(getline(file, line))
    {
        if(line.find(searchTitle) != string::npos)
        {
            cout << "\nBook Found:\n";
            cout << line << endl;
            found = true;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

void addMember()
{
    Member m;

    cout << "Enter Member ID: ";
    cin >> m.id;

    cin.ignore();

    cout << "Enter Member Name: ";
    getline(cin, m.name);

    cout << "Enter Department: ";
    getline(cin, m.department);

    ofstream file("members.txt", ios::app);

    file << m.id << "|"
         << m.name << "|"
         << m.department << endl;

    file.close();

    cout << "Member Added Successfully!\n";
}

void viewMembers()
{
    ifstream file("members.txt");

    string line;

    cout << "\n===== MEMBER LIST =====\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

void issueBook()
{
    int bookId, memberId;

    cout << "Enter Book ID: ";
    cin >> bookId;

    cout << "Enter Member ID: ";
    cin >> memberId;

    ofstream file("issued.txt", ios::app);

    file << bookId << "|"
         << memberId << endl;

    file.close();

    cout << "Book Issued Successfully!\n";
}

void returnBook()
{
    int bookId;

    cout << "Enter Book ID to Return: ";
    cin >> bookId;

    ifstream file("issued.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        size_t pos = line.find('|');

        if(pos == string::npos)
            continue;

        string idStr = line.substr(0, pos);

        int currentBookId = atoi(idStr.c_str());

        if(currentBookId != bookId)
        {
            temp << line << endl;
        }
        else
        {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("issued.txt");
    rename("temp.txt", "issued.txt");

    if(found)
    {
        cout << "Book Returned Successfully!\n";
    }
    else
    {
        cout << "Book ID Not Found in Issued Records!\n";
    }
}

void viewIssuedBooks()
{
    ifstream file("issued.txt");

    string line;

    cout << "\n===== ISSUED BOOKS =====\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Add Member\n";
        cout << "5. View Members\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. View Issued Books\n";
        cout << "9. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;

            case 4:
                addMember();
                break;
            case 5:
                viewMembers();
                break;

            case 6:
                issueBook();
                break;
            case 7:
                returnBook();
                break;
            case 8:
            viewIssuedBooks();
            break;

            case 9:
            cout << "Exiting...\n";
            break;

            default:
                cout << "Feature not implemented yet!\n";
        }

    } while(choice != 9);

    return 0;
}
