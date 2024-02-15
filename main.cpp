#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

/* Global Variables */
string databaseFile = "database/"; // file handling database location
string dtStudent = "database/.studentsID";
string dtBooks = "database/.books";
string dtRentBooks = "database/.rentBooks";
int stuDataCount = 4;

class Student
{
private:
    string f_name;
    string l_name;
    string branch;
    string roll;
    int uid;

public:
    void insert(string f_name, string l_name, string branch, string roll, int uid)
    {
        this->f_name = f_name;
        this->l_name = l_name;
        this->branch = branch;
        this->roll = roll;
        this->uid = uid;
    }
    string getName()
    {
        string fullName = f_name;
        fullName += " ";
        fullName += l_name;
        return fullName;
    }
    string getBranch()
    {
        return this->branch;
    }
    string getRollNumber()
    {
        return this->roll;
    }
    int getUID()
    {
        return this->uid;
    }
};

class Book
{
private:
    string bookName;
    string author;
    int bookID;
    bool status;

public:
    void insert(string bookName, string author, bool status, int id)
    {
        this->bookName = bookName;
        this->author = author;
        this->status = status;
        this->bookID = id;
    }
    string getBookName()
    {
        return bookName;
    }
    string getAuthor()
    {
        return this->author;
    }
    bool getStatus()
    {
        return status;
    }
    int getID()
    {
        return this->bookID;
    }
    void setStatus(bool Status)
    {
        this->status = Status;
    }
};

class Rentbooks
{
private:
    int UID;
    int BookID;

public:
    void insert(int uid, int bookID)
    {
        this->UID = uid;
        this->BookID = bookID;
    }
    int getUID()
    {
        return UID;
    }
    int getBookID()
    {
        return BookID;
    }
};

int getTotalStudents(string filename)
{
    ifstream data(filename);
    int count = 0;
    string _tmp;
    while (!data.eof())
    {
        getline(data, _tmp);
        count++;
    }
    data.close();
    return count / stuDataCount;
}

int getTotalBooks()
{
    ifstream data(dtBooks);
    int count = 0;
    string _tmp;
    while (!data.eof())
    {
        getline(data, _tmp);
        count++;
    }
    data.close();
    return count / 3;
}

int getTotalRent()
{
    ifstream data(dtRentBooks);
    int count = 0;
    string _tmp;
    while (!data.eof())
    {
        getline(data, _tmp);
        count++;
    }
    data.close();
    return count / 2;
}

int initializeAllStudents(Student stu[])
{
    ifstream studentData(dtStudent);
    int count = 0;
    for (; count < getTotalStudents(dtStudent); count++)
    {
        string f_name, l_name, branch, roll;
        int uid;
        studentData >> f_name >> l_name >> branch >> roll;
        studentData >> uid;
        stu[count].insert(f_name, l_name, branch, roll, uid);
    }
    return stu[count - 1].getUID();
}

void showStudent(Student data)
{
    string stuName = data.getName();
    string stuRoll = data.getRollNumber();
    string stuBranch = data.getBranch();
    int stuUID = data.getUID();

    cout << "Name        : " << stuName << endl;
    cout << "Roll Number : " << stuRoll << endl;
    cout << "Branch      : " << stuBranch << endl;
    cout << "UID         : " << stuUID << endl;
}

void previewIDCard(Student data)
{
    string stuName = data.getName();
    string stuBranch = data.getBranch();
    string stuRoll = data.getRollNumber();
    string dateNow = "23/10/2022";
    int stuUID = data.getUID();

    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "|                                        |" << endl;
    cout << "           Library ID Card                " << endl;
    cout << "|         ------------------             |" << endl;
    cout << "                                          " << endl;
    cout << "|                                        |" << endl;
    cout << "    Name        :  " << stuName << "      " << endl;
    cout << "|                                        |" << endl;
    cout << "    Roll Number :  " << stuRoll << "       " << endl;
    cout << "|                                        |" << endl;
    cout << "    Branch      :  " << stuBranch << "    " << endl;
    cout << "|                                        |" << endl;
    cout << "    UID         :  " << stuUID << "       " << endl;
    cout << "|                                        |" << endl;
    cout << "    Valid upto  :  " << dateNow << "      " << endl;
    cout << "|                                        |" << endl;
    cout << "------------------------------------------" << endl;

    cout << endl
         << endl;
}

void startupHeader()
{
    system("clear");
    cout << "   Welcome to Library Management System" << endl;
    cout << "  ----------------------------------------" << endl
         << endl;
}

int userInpCh(string message = "")
{
    int choice = 0;
    cout << "\n    " << message << " -> ";
    cin >> choice;
    return choice;
}

/* MenuItems */
void showMenu()
{
    cout << endl;
    cout << "     1. Show All Students (" << getTotalStudents(dtStudent) << ")" << endl;
    cout << "     2. Generate Library Card" << endl;
    cout << "     3. Show All Library Card" << endl;
    cout << "     4. Show Particuar Student" << endl;
    cout << "     5. Show Library Card with UID" << endl;
    cout << "     6. Show All Books (" << getTotalBooks() << ")" << endl;
    cout << "     7. Show Available Books" << endl;
    cout << "     8. Register New Books" << endl;
    cout << "     9. Books Rent to Students" << endl;
    cout << "    10. Rent books with student name" << endl;
    cout << "    11. Return rent books(" << getTotalRent() << ")" << endl;
    cout << "     0. Exit Application" << endl;
}

void menu_ShowAllStudents(Student stu[])
{
    startupHeader();
    cout << "/ShowAllStudents\n\n";
    for (int c = 0; c < getTotalStudents(dtStudent); c++)
    {
        cout << "\n"
             << c + 1 << ".\n------------------------\n";
        showStudent(stu[c]);
        cout << endl;
    }
    cout << "\n0. Back\n";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
}

void showParticularStudent(Student stu[])
{
SPS:
    startupHeader();
    cout << "/ShowParticularStudent\n\n";
    cout << "Enter the UID : ";
    int uid;
    cin >> uid;
    cout << "\n\n";
    int av = 0;
    for (int c = 0; c < getTotalStudents(dtStudent); c++)
    {
        if (stu[c].getUID() == uid)
        {
            av++;
            showStudent(stu[c]);
        }
    }
    if (av < 1)
        cout << "Sorry, UID Student not Found.\n";
    cout << "\n0. Back\n1. Search Again";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
        goto SPS;
}

void getLibraryCard(int lastUIDNo)
{
GLC:
    startupHeader();
    cout << "/GenerateLibraryCard\n\n";
    Student std;
    string f_name, l_name, branch, roll;
    int uid;
    cout << "Enter your first name : ";
    cin >> f_name;
    cout << "Enter your last name : ";
    cin >> l_name;
    cout << "Enter your Branch : ";
    cin >> branch;
    cout << "Enter your Roll : ";
    cin >> roll;
    uid = lastUIDNo + 1;

    std.insert(f_name, l_name, branch, roll, uid);

    previewIDCard(std);

    ofstream studentSource(dtStudent, ios::app);

    studentSource << endl
                  << std.getName() << endl
                  << std.getBranch() << endl
                  << std.getRollNumber() << endl
                  << std.getUID();

    cout << "\n0. Back\n1. Generate Other ID";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
        goto GLC;
}

void showAllLibraryCard(Student stu[])
{
SALC:
    startupHeader();
    cout << "/ShowAllLibraryCard\n\n";
    for (int count = 0; count < getTotalStudents(dtStudent); count++)
    {
        previewIDCard(stu[count]);
    }
    cout << "\n0. Back";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
        goto SALC;
}

void showLibraryCardOne(Student stu[])
{
SALC:
    startupHeader();
    cout << "/ShowLibraryCard\n\n";
    cout << "Enter the UID : ";
    int uid;
    cin >> uid;
    cout << "\n\n";
    int av = 0;
    for (int c = 0; c < getTotalStudents(dtStudent); c++)
    {
        if (stu[c].getUID() == uid)
        {
            av++;
            previewIDCard(stu[c]);
        }
    }
    if (av < 1)
        cout << "Sorry, UID Student not Found.\n";
    cout << "\n0. Back\n1. Search Again";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
        goto SALC;
}

void showBook(Book dataBook)
{
    string bName = dataBook.getBookName();
    string bAuthor = dataBook.getAuthor();
    int ID = dataBook.getID();
    string available = dataBook.getStatus() ? "Not Available" : "Available";

    cout << "Book Name   : " << bName << endl;
    cout << "Author      : " << bAuthor << endl;
    cout << "Book ID     : " << ID << endl;
    cout << "Availability   : " << available << endl;
}

int initializeBooks(Book dataIn[])
{
    ifstream bookRaw(dtBooks);
    int count = 0;
    for (; count < getTotalBooks(); count++)
    {
        string bookName, author;
        int bookID;
        bool status;
        bookRaw >> bookName >> author;
        bookRaw >> bookID >> status;
        dataIn[count].insert(bookName, author, status, bookID);
    }
    return dataIn[count - 1].getID();
}

void ShowAllBooks(Book dataBook[])
{
    startupHeader();
    cout << "/ShowAllBooks\n\n";
    for (int c = 0; c < getTotalBooks(); c++)
    {
        cout << "\n"
             << c + 1 << ".\n------------------------\n";
        showBook(dataBook[c]);
        cout << endl;
    }
    cout << "\n0. Back\n";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
}

void ShowAvailableBooks(Book dataBook[])
{
    startupHeader();
    cout << "/ShowAvailableBooks\n\n";
    for (int c = 0; c < getTotalBooks(); c++)
    {
        if (!dataBook[c].getStatus())
        {
            cout << "\n"
                 << c + 1 << ".\n------------------------\n";
            showBook(dataBook[c]);
            cout << endl;
        }
    }
    cout << "\n0. Back\n";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
}

void registerNewBooks(int lastBookID)
{
RNB:
    startupHeader();
    cout << "/RegisterNewBooks\n\n";
    Book bookFile;
    string bName, bAuthor;
    int bid;
    cout << "Enter book name : ";
    cin >> bName;
    cout << "Enter Author : ";
    cin >> bAuthor;
    bid = lastBookID + 1;

    bookFile.insert(bName, bAuthor, 0, bid);

    ofstream bookSource(dtBooks, ios::app);

    bookSource << endl
               << bookFile.getBookName() << " "
               << bookFile.getAuthor() << endl
               << bookFile.getID() << endl
               << bookFile.getStatus();

    cout << "\n0. Back\n1. Add more books";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
        goto RNB;
}

bool studentAvailable(Student stu[], int UID)
{
    int av = 0;
    for (int c = 0; c < getTotalStudents(dtStudent); c++)
    {
        if (stu[c].getUID() == UID)
        {
            av++;
            cout << "\n";
            showStudent(stu[c]);
            cout << endl;
        }
    }
    if (av < 1)
        return false;
    else
        return true;
}

bool bookAvailable(Book bookData[], int ID)
{
    int av = 0;
    for (int c = 0; c < getTotalBooks(); c++)
    {
        if (bookData[c].getID() == ID)
        {
            av++;
            showBook(bookData[c]);
        }
    }
    if (av < 1)
        return false;
    else
        return true;
}

Student getStudentDetails(Student stu[], int uid)
{
    Student retVal;
    for (int c = 0; c < getTotalStudents(dtStudent); c++)
    {
        if (stu[c].getUID() == uid)
        {
            retVal = stu[c];
        }
    }
    return retVal;
}

Book getBookDetails(Book data[], int id)
{
    Book retVal;
    for (int c = 0; c < getTotalStudents(dtBooks); c++)
    {
        if (data[c].getID() == id)
        {
            retVal = data[c];
        }
    }
    return retVal;
}

void updateBookFile(Book bookData[], int totalBooks)
{
    ofstream bookFile(dtBooks);
    for (int i = 0; i < totalBooks; i++)
    {
        bookFile << bookData[i].getBookName() << " " << bookData[i].getAuthor()
                 << endl
                 << bookData[i].getID() << endl
                 << bookData[i].getStatus() << endl;
    }
    bookFile.close();
}

int getBkIndex(Book data[], int id)
{
    int retVal = 0;
    for (int c = 0; c < getTotalStudents(dtBooks); c++)
    {
        if (data[c].getID() == id)
            break;
        retVal++;
    }
    return retVal;
}

bool checkStudentBookSlot(Rentbooks bkRntData[], int UID)
{
    int avCheck = 0;
    for (int count = 0; count < getTotalRent(); count++)
    {
        if (bkRntData[count].getUID() == UID)
            avCheck++;
    }
    return avCheck >= 3 ? false : true;
}

bool checkBooksAvailable(Book bkData[], int ID)
{
    return bkData[getBkIndex(bkData, ID)].getStatus();
}

void rentBooksStu(Student stuData[], Book bookData[], Rentbooks bookRented[])
{
RBS:
    startupHeader();
    cout << "/RentBooksStudents\n\n";

    int UIDs, BookID;

    cout << "Enter UID of Student : ";
    cin >> UIDs;
    if (!studentAvailable(stuData, UIDs))
    {
        cout << "Sorry, UID Student not Found.\n";
        cout << "\n0. Back\n1. Retry";
        int choice = userInpCh();
        if (choice == 0)
        {
            return;
        }
        else
            goto RBS;
    }
    if (!checkStudentBookSlot(bookRented, UIDs))
    {
        cout << "Sorry, Student already has max(3) books.\n";
        cout << "\n0. Back\n1. Retry";
        int choice = userInpCh();
        if (choice == 0)
        {
            return;
        }
        else
            goto RBS;
    }
GOTO_getBookID:
    cout << "Enter Book ID : ";
    cin >> BookID;
    if (!bookAvailable(bookData, BookID))
    {
        cout << "Sorry, Book not Found.\n";
        cout << "\n0. Back\n1. Retry";
        int choice = userInpCh();
        if (choice == 0)
        {
            return;
        }
        else
        {
            cout << endl;
            goto GOTO_getBookID;
        }
    }
    if (checkBooksAvailable(bookData, BookID))
    {
        cout << "Sorry, Book already taken .\n";
        cout << "\n0. Back\n1. Retry";
        int choice = userInpCh();
        if (choice == 0)
        {
            return;
        }
        else
        {
            cout << endl;
            goto GOTO_getBookID;
        }
    }
    ofstream bookRentFl(databaseFile + ".rentBooks", ios::app);

    bookRentFl << UIDs << endl
               << BookID << endl;

    bookRentFl.close();

    int bIndex = getBkIndex(bookData, BookID);

    bookData[bIndex].setStatus(true);

    cout << endl
         << getStudentDetails(stuData, UIDs).getName() << " has successfully rented "
         << getBookDetails(bookData, BookID).getBookName() << " book.\n";

    updateBookFile(bookData, getTotalBooks());

    cout << "\n0. Back\n1. Rent more books";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
        goto RBS;
}

void initializeRentBooks(Rentbooks rentBookdt[])
{
    /* Temporary Made for checking available rent books data */
    ifstream _tmp_bookDt(dtRentBooks);
    string _tmp_dtBookText;
    _tmp_bookDt >> _tmp_dtBookText;

    if (_tmp_dtBookText == "")
    {
        _tmp_bookDt.close();
        return;
    }
    else
    {
        ifstream bookDt(dtRentBooks);
        int rbUID, rbBookID;
        for (int count = 0; count < getTotalRent(); count++)
        {

            bookDt >> rbUID;
            bookDt >> rbBookID;
            rentBookdt[count]
                .insert(rbUID, rbBookID);
        }
        bookDt.close();
    }
    _tmp_bookDt.close();
}

void rentBooksWithStudentsName(Student stuData[], Book bkData[], Rentbooks rbData[])
{
    startupHeader();
    cout << "/RentBooksWithStudentName\n\n";
    if (getTotalRent() < 1)
    {
        cout << "Sorry there are no rented books." << endl;
    }
    else
    {
        cout << "The Students are : \n\n";
        for (int count = 0; count < getTotalRent(); count++)
        {
            cout << "     " << count + 1 << ". " << getStudentDetails(stuData, rbData[count].getUID()).getName();
            cout << " - " << getBookDetails(bkData, rbData[count].getBookID()).getBookName() << "(" << getBookDetails(bkData, rbData[count].getBookID()).getID() << ")" << endl;
        }
        cout << endl
             << endl;
    }

    cout << "\n0. Back\n";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
}

void returnRentBooks(Book bkData[], Rentbooks rbData[])
{
RRB:
    startupHeader();
    cout << "/ReturnRentedBooks\n\n";

    int UIDs, BookID;

    cout << "Enter UID of Student : ";
    cin >> UIDs;
    cout << endl
         << "Registered Books are : \n   ";
    for (int count = 0; count < getTotalRent(); count++)
    {
        if (rbData[count].getUID() == UIDs)
        {
            cout << rbData[count].getBookID() << " ";
        }
    }
    cout << endl
         << endl;
    cout << "Enter Book ID : ";
    cin >> BookID;

    int avCheckBK = 0, chkID;
    for (int count = 0; count < getTotalRent(); count++)
    {
        if (rbData[count].getBookID() == BookID && rbData[count].getUID() == UIDs)
        {
            avCheckBK++;
            chkID = count;
        }
    }

    if (avCheckBK < 1)
    {
        cout << "Sorry, Registered Student for that Book doesn't exist.\n";
        cout << "\n0. Back\n1. Retry";
        int choice = userInpCh();
        if (choice == 0)
        {
            return;
        }
        else
        {
            cout << endl;
            goto RRB;
        }
    }

    /* Resetting the book availability to 0 (false) */
    for (int count = 0; count < getTotalBooks(); count++)
    {
        if (bkData[count].getID() == BookID)
        {
            bkData[count].setStatus(0);
        }
    }
    updateBookFile(bkData, getTotalBooks());

    /* Deleting the BookID and UID from the Object */
    for (int count = chkID; count < (getTotalRent() - 1); count++)
    {
        int bkID = rbData[count + 1].getBookID();
        int stUID = rbData[count + 1].getUID();
        rbData[count].insert(stUID, bkID);
    }

    int current_totalRentNumber = getTotalRent() - 1;

    ofstream bkDatabaseDotFile(dtRentBooks, ios::out);

    for (int count = 0; count < current_totalRentNumber; count++)
    {
        bkDatabaseDotFile << rbData[count].getUID() << endl
                          << rbData[count].getBookID() << endl;
    }
    bkDatabaseDotFile.close();

    cout << "\n0. Back \n1. Re-Enter\n";
    int choice = userInpCh();
    if (choice == 0)
    {
        return;
    }
    else
    {
        goto RRB;
    }
}

int main()
{
START:
    /* Retriving data from the Student Database */
    Student stu[50];
    Book bookRaw[50];
    Rentbooks rentedStuBks[50];

    ifstream studentData(dtStudent);
    ifstream bookData(dtBooks);
    ifstream rentBookdt(dtBooks);

    int lstUID = initializeAllStudents(stu);
    int lstBookID = initializeBooks(bookRaw);
    initializeRentBooks(rentedStuBks);

    while (1)
    {
        startupHeader();
        showMenu();

        int choice = userInpCh();

        switch (choice)
        {
        case 1:
            menu_ShowAllStudents(stu);
            break;
        case 2:
            getLibraryCard(lstUID);
            goto START;
            break;
        case 3:
            showAllLibraryCard(stu);
            break;
        case 4:
            showParticularStudent(stu);
            break;
        case 5:
            showLibraryCardOne(stu);
            break;
        case 6:
            ShowAllBooks(bookRaw);
            break;
        case 7:
            ShowAvailableBooks(bookRaw);
            break;
        case 8:
            registerNewBooks(lstBookID);
            goto START;
            break;
        case 9:
            rentBooksStu(stu, bookRaw, rentedStuBks);
            goto START;
            break;
        case 10:
            rentBooksWithStudentsName(stu, bookRaw, rentedStuBks);
            break;
        case 11:
            returnRentBooks(bookRaw, rentedStuBks);
            goto START;
            break;
        case 0:
            goto END;
            break;
        }
    }
/* Ending of the Program */
END:
    rentBookdt.close();
    bookData.close();
    studentData.close();
    cout << endl
         << endl;
    return 0;
}
