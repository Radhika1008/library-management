#include <iostream>
#include <fstream>
#include<string>
using namespace std;


int bookOptions() {
	cout << "1. Add Book" << endl;
	cout << "2. Update Book" << endl;
	cout << "3. Delete Book" << endl;
	cout << "4. Show All Books" << endl;
	cout << "5. Total Number of Books" << endl;
	cout << "6. Reset Library" << endl;
	cout << "7. change password" << endl;
	cout << "8. issue book" << endl;
	cout << "9. Show All Issued Books" << endl;
	cout << "0. Exit" << endl;
	cout << "\n";
	cout << "--- Choose any one option ---" << endl;
	cout << "Enter one option: ";

	int selectedOption = 0;
	cin >> selectedOption;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return selectedOption;
}


void addBook() {
	string bookTitle, bookAuthor, bookDetail, line;
	int count;
	int x;
	cout << "Number of Books to be added : ";
	cin >> x;
	cin.ignore();
	for (int i = 0; i < x; i++) {

		cout << endl << "--- Provide Book Details ---" << endl;
		cout << "Title: ";
		getline(cin, bookTitle);
		cout << "Author: ";
		getline(cin, bookAuthor);

		// reading file for number of book
		ifstream countData("count.dat");
		countData >> count;
		countData.close();

		ofstream ofs("count.dat", ios::trunc);
		ofs << count + 1;
		ofs.close();

		// open file for writing
		ofstream writeToLibrary;

		writeToLibrary.open("library.dat", ios::app);

		bookDetail = to_string(count) + " : " + bookTitle + " BY " + bookAuthor;

		// write
		writeToLibrary << bookDetail << endl;

		// close the opened file.
		writeToLibrary.close();

		cout << "Book added: " << bookDetail << endl;
	}

}


void UpdateBook() {
	cout << endl << "--- Update Book ---" << endl;
	string id;
	cout << "Enter Book ID: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool bookExist = false;
	ifstream data("library.dat");
	ofstream temp;
	temp.open("temp.dat", ios::app); //Temporary file

	if (!data || !temp)
	{
		cout << "Error opening files!" << endl;
		return;
	}

	string strTemp;
	while (getline(data, strTemp))
	{
		size_t found = strTemp.rfind(id + " ", 0);
		if (found != string::npos) {
			string title, author;

			cout << "Book: " << strTemp << endl;

			cout << "New Book Title: ";
			getline(cin, title);
			cout << "New Book Author: ";
			getline(cin, author);

			strTemp = id + " : " + title + " BY " + author;
			bookExist = true;
		}
		temp << strTemp << endl;
	}

	data.close();
	temp.close();

	if (bookExist) {
		// delete old file
		if (remove("library.dat") != 0)
			perror("Error deleting file");

		// rename new file to old file
		if (rename("temp.dat", "library.dat")) {
			perror("Error renaming");
			return;
		}

		cout << "Book Details Updated" << endl;

	}
	else cout << "No book found with ID " << id << endl;
}


void DeleteBook() {
	int x;
	cout << "Number of Books to be deleted : ";
	cin >> x;


	for (int i = 0; i < x; i++) {

		cout << endl << "--- Delete Book ---" << endl;
		string id;
		cout << "Enter Book ID: ";
		cin >> id;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		bool bookExist = false;
		ifstream data("library.dat");
		ofstream temp;
		temp.open("temp.dat", ios::app); //Temporary file

		if (!data || !temp)
		{
			cout << "Error opening files!" << endl;
			return;
		}

		string strTemp;
		bool delBook = false;
		while (getline(data, strTemp))
		{
			size_t found = strTemp.rfind(id + " ", 0);
			if (found != string::npos) {
				cout << "Book: " << strTemp << endl;
				bookExist = true;
				delBook = true;
			}
			if (delBook) {
				delBook = false;
				continue;
			}
			temp << strTemp << endl;
		}

		data.close();
		temp.close();

		if (bookExist) {

			// delete old file
			if (remove("library.dat") != 0)
				perror("Error deleting file");

			// rename new file to old file
			if (rename("temp.dat", "library.dat")) {
				perror("Error renaming");
				return;
			}

			cout << "Book Deleted" << endl;

		}
		else cout << "No book found with ID " << id << endl;
	}
}


void showBooks() {
	cout << "--- List of books ---" << endl;

	ifstream data("library.dat");
	string row;
	while (getline(data, row))
	{
		cout << row << endl;
	}
}

void totalBooks() {
	int count = 0;
	string line;
	ifstream countData("library.dat");
	while (getline(countData, line)) {
		count++;

	}
	cout << "Total Number of Books are : " << count << endl;
}

void resetLibrary() {
	ofstream countData("count.dat", ios::trunc);
	countData << 1;
	countData.close();

	ofstream bookData("library.dat", ios::trunc);
	bookData << "";
	bookData.close();

	ofstream issueBook("issue.dat", ios::trunc);
	issueBook << "";
	issueBook.close();
}
void changepass(char password[10])
{
	int m = 1;
	char newpass[10];
	string current;

	cout << "Remember: The passsword must start with a capital letter" << endl;
	cout << "Enter new password: ";
	while (m == 1)
	{
		cin >> newpass;
		if (newpass[0] >= 'A' && newpass[0] <= 'Z')
		{
			password = newpass;
			m = 0;
			cout << "the password is changed";
		}
		else
			cout << "the password is not according to the regulations ..try again";
	}
	ofstream passDat("pass.dat", ios::trunc);
	passDat << newpass;
	passDat.close();
}

void issueBook() {
	cout << endl << "--- Issue Book ---" << endl;
	string id;
	cout << "Enter Book ID: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool bookExist = false;
	ifstream data("library.dat");
	ofstream temp;
	ofstream iss;
	temp.open("temp.dat", ios::app); //Temporary file

	if (!data || !temp)
	{
		cout << "Error opening files!" << endl;
		return;
	}

	string strTemp;
	while (getline(data, strTemp))
	{
		size_t found = strTemp.rfind(id + " ", 0);
		if (found != string::npos) {
			string StrIssue, student_name, date_of_iss, rollno;

			cout << "Book: " << strTemp << endl;

			cout << "Student roll number: ";
			getline(cin, rollno);
			cout << "Student name: ";
			getline(cin, student_name);
			cout << "Date of issue: ";
			getline(cin, date_of_iss);

			StrIssue = id + " : Book issued by " + rollno + " " + student_name + " ON " + date_of_iss;
			bookExist = true;
			iss.open("issue.dat", ios::app); //Temporary file
			iss << StrIssue << endl;
			iss.close();
			continue;
		}
		temp << strTemp << endl;
	}

	data.close();
	temp.close();


	if (bookExist) {
		// delete old file
		if (remove("library.dat") != 0)
			perror("Error deleting file");

		// rename new file to old file
		if (rename("temp.dat", "library.dat")) {
			perror("Error renaming");
			return;
		}

		cout << "Book Issued" << endl;

	}
	else cout << "No book found with ID " << id << endl;

}
void ShowIssuedBooks() {
	cout << "--- List of Issued books ---" << endl;

	ifstream data("issue.dat");
	string row;
	while (getline(data, row))
	{
		cout << row << endl;
	}
}
void bookActions(int option, char password[10]) {
	switch (option) {
	case 1:
		addBook();
		break;
	case 2:
		UpdateBook();
		break;
	case 3:
		DeleteBook();
		break;
	case 4:
		showBooks();
		break;
	case 5:
		totalBooks();
		break;
	case 6:
		resetLibrary();
		break;
	case 7:
		changepass(password);
		break;
	case 8:
		issueBook();
		break;
	case 9:
		ShowIssuedBooks();
		break;
	}
}


void home(char password[10]) {
	int option = bookOptions();
	if (option != 0 && option <= 9) {
		bookActions(option, password);
	}
	else if (option > 9) {
		cout << endl << "!!! Enter Valid Option !!!" << endl;
		option = bookOptions();
	}
	else {
		exit(0);
	}
}


int main() {
	cout << "          ****WELCOME****     \n\n";
	string choice;
	char password[10];
	char pass[10];

	ifstream Pass("pass.dat");
	Pass >> password;
	Pass.close();
	
	cout << "enter the password ";
	cin >> pass;
	while (strcmp(password, pass) != 0) {
		cout << "the password entered is wrong\n\n";
		cout << "enter the password ";
		cin >> pass;
	}

	while (true) {
		cout << endl << "--- LIBRARY DATABASE MANAGEMENT ---" << endl;
		cout << "\n";

		home(password);
		cout << endl << "continue? (y/n) :";
		cin >> choice;
		if (choice != "y")
			break;
	}
	return 0;
}
