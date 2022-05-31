#include "Record.h"
#include <string>


//Global variables
fstream myfile;

Queue waitingList;
Queue SecDoseWaitingList;

bool start = 0;
float noDoses=0,oneDose = 0, twoDose = 0, cairoCount = 0, alexCount = 0, gizaCount = 0, portsaidCount = 0, sharqiaCount = 0, otherCount = 0, female = 0, male = 0;

unordered_map<string, Record> userMap; 

Record rc;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Main Menu 

void Record:: mainMenu() //Main menu function resposible for user choice of action
{
	
	bringFromFile();
	if (start == 0) {
		Counters();
		start = 1;
	}
	int choice = 0;
	
	while (choice != 3) {
		displayChoices();

		while (!(cin >> choice)) { //to make sure user entered an int not anything else
			cout << "\tInvalid Choice\n ";
			system("pause");
			system("cls");
			cin.clear();
			displayChoices();
			cin.ignore(123, '\n');
		}

		cout << "\t-----------------------------------" << endl;
		cout << endl;
		cout << endl;

		switch (choice)
		{
		case 1:

			//sign in function
			displayTitle();
			displayChoices();
			system("cls");
			SignIn();
			system("cls");//clearing the console
			break;

		case 2:

			//sign up function
			system("cls");
			rc.recData();
			rc.insertUserData();
			Sleep(500);
			system("PAUSE");
			system("cls");
			//clearing the console
			break;

		case 3:

			//exit program
			//clearing the console
			system("CLS");
			cout << "\t\t\t\t\t===================================" << endl;
			cout << "\t\t\t\t\tThank You for using our system ! :D" << endl;
			cout << "\t\t\t\t\tHope to see you again! :D"<< endl;
			cout << "\t\t\t\t\t===================================\n\n";
			exit(3);
			break;

		default:
			//displayTitle();
			cout << "\tInvalid Choice" << endl;
			BackOption();
			mainMenu();

			break;

		}
	}
}


//Displaying The System Title
void Record::displayTitle() {
	cout << "\t\t\t\t\t ===================================" << endl;
	cout << "\t\t\t\t\t Vaccine Tracking System (COVID-19) " << endl;
	cout << "\t\t\t\t\t ===================================\n\n" ;
}


// Creating New Records
void  Record::recData()
{

	displayTitle();

	cout << "\tMake sure the National ID you are using aren't already registered." << endl;
	cout << "\tPlease fill in the following information to create your record:" << endl;
	cout << endl;
	lab:
	cout << "\tFirst name: ";
	cin >> fname;
	for (int i = 0; i<fname.size(); i++) {
		if (isalpha(fname[i]) == 0) {
			cout << "\tInvalid, name must contain letters only." << endl;
			goto lab;
			break;
		}
	}
	lab2:
	cout << "\tLast name: ";
	cin >> lname;
	for (int i = 0; i < lname.size(); i++) {
		if (isalpha(lname[i]) == 0) {
			cout << "\tInvalid, name must contain letters only." << endl;
			goto lab2;
			break;
		}
	}
	cout << endl;

	getnatID();
	while (ID.size() != 13) {
		cout << "\tInvalid ID , please re-enter your ID: " << endl;
		getnatID();
	}
	CheckRegisteredID(ID);
	
	
	createPass();
	
	cout << endl;
	
	
	getAge();
	char ans;
	while (age < 15) {
		cout << "\tKids under 15 aren't allowed to take the vaccine" << endl;
	Q:
		cout << "\tDo you wish to continue with different age? y/n ";
		while (!(cin >> ans)) {

			cout << "\tInvalid Input.\n ";
			cin.clear();
			cin.ignore(123, '\n');
			goto Q;
		}
		if (ans == 'y' || ans == 'Y') {
			getAge();
		}
		else if(ans=='N'||ans=='n') {
			system("cls");
			mainMenu();
		}


	}
	cout << endl;

	cout << "\tPlease choose gender F for female or M for male: " ;
	cin >> gender;
	while (gender != 'F' && gender != 'M' && gender != 'm' && gender != 'f') {
		cout << "\tInvalid value, please re-enter: ";
		cin >> gender;
		
	}
	
	cout << endl;

	getGov();
	cout << endl;

	myfile.open("all.txt", ios::app);

	myfile << ID << endl;
	myfile.close();
	string fn = ID + ".txt";

	myfile.open(fn, ios::app);
	myfile << fname << endl;
	myfile << lname << endl;
	myfile << ID << endl;
	myfile << passConfirm << endl;
	myfile << age << endl;
	myfile << gender << endl;
	myfile << gov << endl;
	
	gotVaccine();

	myfile << doses << endl;
	myfile.close();
	
	cout << "\tYour record is successfully saved." << endl;

}


//Verifying User ID
void Record::getnatID()
{
	cout << "\tEnter National ID (make sure it is 13 digits ): ";
	cin >> ID;
	if (ID[0] != '2' && ID[0] != '3') { //century
		cout << "\tInvaild ID" << endl;
		getnatID();
	}
	if (ID[1] != '0' && ID[1] != '1' && ID[1] != '2' && !(0 <= ID[2] >= 9)) { //year
		cout << "\tInvaild ID" << endl;
		getnatID();
	}
	if (ID[3] != '0' && ID[3] != '1' && !(0 <= ID[4] >= 9)) { // month
		cout << "\tInvaild ID" << endl;
		getnatID();
	}
	if (ID[5] != '0' && ID[5] != '1' && ID[5] != '2' && ID[5] != '3' && !(0 <= ID[6] >= 9)) { //day
		cout << "\tInvaild ID" << endl;
		getnatID();
	}
	if (ID[7] != '0' && ID[7] != '1' && ID[7] != '2' && ID[7] != '3' && ID[7] != '8' && !(1 <= ID[8] >= 9)) { //governorate
		cout << "\tInvaild ID" << endl;
			getnatID();
	}
	
}
void Record::CheckRegisteredID(string enteredID) {
	char choice;
	for (itr = userMap.begin(); itr != userMap.end(); itr++) {
		if ( enteredID== itr->first) {
			cout << "\tID already Registered!" << endl;
			q:
			cout << "\t Do you want to sign in ? (y/n) ";
			cin >> choice;
			switch (choice) {
			case 'y':
				system("cls");
				SignIn();
				break;
			case'n':
				system("cls");
				mainMenu();
				break;
			default:
				cout << "\tInvalid choice , try again." << endl;
				goto q;
				break;
			}
			getnatID();
			break;
			
	
		}
		
		
	}
}


//Verifying User Age
void Record::getAge() {

	cout << "\tPlease enter your age: ";
	while (!(cin >> age)) {
		cout << "\tInvalid Age\n ";
		cin.clear();
		cin.ignore(123, '\n');
		cout << "\tplease enter a correct age: ";

	}
}


//Verifying User Password
void Record::createPass()
{
	bool msg = true;
	password = "";
	passConfirm = "";
	
	cout << "\tCreate a new password : ";
	cin >> password;
	
	cout << "\tConfirm your password : ";
	cin >> passConfirm;

	while (password.size() < 5) {
		cout << "\tPassword too short" << endl;
		msg = false;
		createPass();
		break;
	}
	if (msg) {

	  if (password == passConfirm) {
		cout << "\n\tPassword created successfully" << endl;

	  }
	  else {
		cout << "\n\tPasswords don't match , please try again" << endl;
		createPass();
	  }
	}
}


//Verifying User Governorate
void Record::displayGov() {
	cout << "\t1 ---> Cairo " << endl;
	cout << "\t2 ---> Alexandria " << endl;
	cout << "\t3 ---> Giza " << endl;
	cout << "\t4 ---> Sharqia " << endl;
	cout << "\t5 ---> Port Said " << endl;
	cout << "\t6 ---> Other " << endl;
	cout << "\tPlease enter number of governorate you are currently living at: ";
}
void Record::getGov() {

	displayGov();
	while (!(cin >> choice)) {
		cout << "\tInvalid governorate\n ";
		cin.clear();
		cin.ignore(123, '\n');
		displayGov();

	}


	switch (choice) {
	case 1:
		gov = "Cairo";
		break;
	case 2:
		gov = "Alexandria";
		break;
	case 3:
		gov = "Giza";
		break;
	case 4:
		gov = "Sharqia";
		break;
	case 5:
		gov = "PortSaid";
		break;
	case 6:
		gov = "other";
		break;
	default:
	{
		cout << "\tInvalid value entered.\n\tPlease make sure to enter a value from the  options below." << endl;
		getGov();

	}
	}
}


//Managing User Vaccine
void Record::gotVaccine() {
	char ans;
	S:
	cout << "\tDid you get the COIVD-19 Vaccine? y/n : " ;
	while (!(cin >> ans)) {
		cout << "\tInvalid Input.";
		cin.clear();
		cin.ignore(123, '\n');
		goto S;
		break;

	}

	switch (ans) 
	{
	case 'y':
	case'Y':
	{
	label:
		E:
		cout << "\tHave you taken 1 or 2 doses? 1/2 : ";
		while (!(cin >> doses)) {
			cout << "\tInvalid Input. ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		
		switch(doses){
	    case 1:
		{
			cout << "\tYou will be added on 2nd dose waiting list" << endl;
			//put them in the second dose waiting list
			SecDoseWaitingList.enQueue(ID);
			break;
		}
	    case 2:
	    {
			fullyVaccinated = true;
			break;
		}
		default :
		{
	    cout << "\tInvalid choice" << endl;
		goto label;
		break;
		}
		}
	
		break;
	}
	case 'n':
	case'N':
	{
		vaccinated = false;
		doses = 0; //in file
		cout << "\tYou will be registered into our waiting list" << endl;
		//put them is the first dose waiting list
		waitingList.enQueue(ID);
		break;
	}
	default:
		cout << "\tInvalid choice" << endl;
            gotVaccine();
		break;

	}

}


//Queues Implemented Using Linked List
void Queue::enQueue(string id) {
	Node* temp = new Node(id);

	if (back == NULL) { //empty
		front = back = temp;
		return;
	}
	back->next = temp;
	back = temp;
}
void Queue::deQueue(string id)
{
	// If queue is empty, return NULL.
	if (front == NULL)
		return;

	// Store previous front and
	// move front one node ahead
	Node* temp = front;
	front = front->next;

	// If front becomes NULL, then
	// change rear also as NULL
	if (front == NULL)
		back = NULL;

	delete (temp);
}


//Displaying The Main Menu Options
void Record::displayChoices() {
	
	displayTitle();

	cout << "\t\t\t\t Notice that this application is for Egyptains in Egypt only" << endl;
	cout << endl;
	cout << endl;
	cout << "\tHow can we help you?" << endl;
	cout << "\t1. Sign In." << endl;
	cout << "\t2. Sign Up as a new memeber." << endl;
	cout << "\t3. Exit Program" << endl;
	cout << "\tPlease enter number of your choice: ";

}


//Inserting User Data 
void Record::insertUserData() {
	
	userMap[rc.ID] = rc;
	
}


//Displaying User Panel Options
void Record::UserOptions() {
	H:
	displayTitle();
	
	int userchoice;
	cout << "\t-->> User Panel <<--\n";
	cout << "\t~choose one of the following choices~\n";
	cout << "\t1->Display Record.\n";
	cout << "\t2->Edit/Update Record.\n";
	cout << "\t3->Delete Record.\n";
	cout << "\t4->Log Out.\n";
	cout << "\tEnter your choice:";
	cin >> userchoice;

	switch (userchoice) {
	case 1:
		system("CLS");
		displayUserData();
		
		break;
	case 2:
		system("CLS");
		editUserData();
		
		break;
	case 3:
		system("CLS");
		deleteUserData();
		
		break;
	case 4:
		system("cls");
		updatefiles();
		mainMenu();
		break;
	default:
		cout << "\tInvalid choice!\n";
		BackOption();
		UserOptions();
		break;
	}

}


//Displaying User Data
void Record::displayUserData() {
	
	displayTitle();

	
	
		// type itr->first stores the key part  and
		// itr->second stores the value part
		cout << "\t-----------------Recorded Data-----------------\n\n";
		cout << "\tFirstname:" << "  " << itr->second.fname << endl;
		cout << "\tLastname:" << "  " << itr->second.lname << endl;
		cout << "\tNational ID:" << "  " << itr->first << endl;
		cout << "\tPassword:" << "  " << itr->second.password << endl;
		cout << "\tAge:" << "  " << itr->second.age << endl;
		cout << "\tGender:" << "  " << itr->second.gender << endl;
		cout << "\tGovernorate:" << "  " << itr->second.gov << endl;
		cout << "\tDoses taken:" << "  " << itr->second.doses << endl;
		BackOption();
		UserOptions();





	
}


//Signing In
void Record::SignIn() {

	displayTitle();

c:
	cout << "\tenter your id: ";
	cin >> rc.ID;


B:
	cout << "\tenter your password:";
	cin >> rc.password;
	//checking the ID in the sign in page
	itr = userMap.find(rc.ID);
	if (rc.ID == "admin") {

		cout << "\n\n\n\t\t\t\t\t| Verfiying ADMIN |\n\t\t\t\t\t";
		for (int a = 1; a < 8; a++)
		{
			Sleep(500);
			cout << "...";
		}
		if (rc.password == "admin") {
			cout << "\n\n\tAccess Granted..\n\n";
			system("PAUSE");
			system("cls");
			adminOptions();
		}
		else {

			cout << "\n\n\tinvalid password!\n\n";
			int passchoice;
		jj:
			cout << "\tDo You want to ->\n";
			cout << "\t1->try again?\n";
			cout << "\t2->go back to the sign up page?\n";
			cout << "\tenter your choice:";
			cin >> passchoice;
			switch (passchoice) {
			case 1:
				system("cls");
				goto B;
				break;
			case 2:
				system("cls");
				mainMenu();
				break;
			default:
				cout << "\tinvalid Choice.";
				goto jj;
				break;
			}
			system("PAUSE");
			system("cls");
			goto B;
		}

	}
	else if (itr == userMap.end()) {
		cout << "\n\n\n\t\t\t\t\t| Verfiying USER |\n\t\t\t\t\t";
		for (int a = 1; a < 8; a++)
		{
			Sleep(500);
			cout << "...";
		}
		cout << "\n\tInvalid ID...\n";
		cout << "\tMake Sure You Sign Up First!\n\n";
		system("PAUSE");
		system("cls");
		mainMenu();
		goto c;
	}

	else {
		cout << "\n\n\n\t\t\t\t\t| Verfiying USER |\n\t\t\t\t\t";
		for (int a = 1; a < 8; a++)
		{
			Sleep(500);
			cout << "...";
		}

		if (rc.password == itr->second.password) {
			cout << endl;
			cout << "\n\n\tAccess Granted..\n\n";
			system("PAUSE");
			system("cls");
			UserOptions();

		}
		else {

			cout << "\n\n\tinvalid password!\n\n";
			int passchoice;
		j:
			cout << "\tDo You want to ->\n";
			cout << "\t1->try again?\n";
			cout << "\t2->go back to the sign up page?\n";
			cout << "\tenter your choice:";
			cin >> passchoice;
			switch (passchoice) {
			case 1:
				system("cls");
				goto B;
				break;
			case 2:
				system("cls");
				mainMenu();
				break;
			default:
				cout << "\tinvalid Choice.";
				goto j;
				break;
			}
			system("PAUSE");
			system("cls");
			goto B;
		}

		cout << endl;
		cout << "\n\n\tAccess Granted..\n\n";
		system("PAUSE");
		system("cls");
		UserOptions();
	}
	cout << endl;


}


//Displaying Edit Options
void Record::diplayEditChoices() {

	displayTitle();

	cout << "\t\t\t\t\t----------Pick Your Choice!----------\n\n\n";
	cout << "\t1->First Name.\n";
	cout << "\t2->Last Name.\n";
	cout << "\t3->Password.\n";
	cout << "\t4->Age.\n";
	cout << "\t5->Gender.\n";
	cout << "\t6->Governorate.\n";
	cout << "\t7->Doses taken.\n";
	cout << "\tenter your choice:";
}


//Checking if the Inputs are Strings or Numbers
bool Record::checknumber(string value) {
	for (int i = 0; i < value.length(); i++)
		if (isdigit(value[i]) == false) {
			return false;
		}
	return true;
}


//Editing User Data
void Record::editUserData() {
	
	char answer;
	int editoption;
	string option;
	string optionNum;
	string optionChar;

	diplayEditChoices();
	cin >> editoption;
	


	switch (editoption)
	{
	case 1:
	{

		cout << "\tFirst Name:";
		cin >> option;
		if (checknumber(option) == false) {
			itr->second.fname = option;
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);
		}
		else {
			cout << "\tInvalid Input!\n";
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);
		}
		break;
	}


	case 2: 
	{
		cout << "\tLast Name:";
		cin >> option;
		if (checknumber(option) == false) {
			itr->second.lname = option;
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);
		}
		else {
			cout << "\tInvalid Input!\n";
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);

		}
		
		
		break;
	}

	case 3:
	{
		cout << "\tpassword:";
		cin >> option;
		itr->second.password = option;
		cout << "\tdo you want to edit anything else?";
		cin >> answer;
		EditAgain(answer);
		
		break;
	}
	
	case 4:
	{
		cout << "\tcurrent age:" << itr->second.age<<endl;
		cout << "\tAge:";
		cin >> optionNum;
		editoption = stoi(optionNum);
		if (editoption < itr->second.age) {
				cout << "\tInvalid Age. Please enter a correct one" << endl;
				cout << "\tdo you want to edit anything else?";
				cin >> answer;
				EditAgain(answer);
			
		}
		else {
			if (checknumber(optionNum) == false) {
				cout << "\tInvalid Input!\n";
				cout << "\tdo you want to edit anything else?";
				cin >> answer;
				EditAgain(answer);
			}
			else {

				itr->second.age = editoption;
				cout << "\tdo you want to edit anything else?";
				cin >> answer;
				EditAgain(answer);
			}
		}
		break;
	}
	
	case 5:
	{
		cout << "\tGender(F/M):";
		cin >> optionChar;
		if (checknumber(optionChar) == false) {
			itr->second.gender = optionChar[0];
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);
		}
		else {
			cout << "\tInvalid Input!\n";
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);

		}
		
		
		break;
	}
	
	case 6:
	{
		cout << "\t-------Governorates-------" << endl;
		cout << "\t1 ---> Cairo " << endl;
		cout << "\t2 ---> Alexandria " << endl;
		cout << "\t3 ---> Giza " << endl;
		cout << "\t4 ---> Sharqia " << endl;
		cout << "\t5 ---> Port Said " << endl;
		cout << "\t6 ---> Other " << endl;
		cout << "\tgovernorate:";
		cin >> optionNum;
		if (checknumber(optionNum) == true) {
			editoption = stoi(optionNum);

			switch (editoption) {
			case 1:
				cairoCount++;
				itr->second.gov = "Cairo";
				break;
			case 2:
				itr->second.gov = "Alexandria";
				alexCount++;
				break;
			case 3:
				itr->second.gov = "Giza";
				gizaCount++;
				break;
			case 4:
				itr->second.gov = "Sharqia";
				sharqiaCount++;
				break;
			case 5:
				itr->second.gov = "PortSaid";
				portsaidCount++;
				break;
			case 6:
				itr->second.gov = "other";
				otherCount++;
				break;
			default:
			{
				cout << "\tInvalid value entered.\n\tPlease make sure to enter a value from the  options below." << endl;
				getGov();
				break;
			}
			
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);
			}
		}
		else {
			cout << "\tInvalid Input!\n";
			cout << "\tdo you want to edit anything else?";
			cin >> answer;
			EditAgain(answer);
		}
		
		
		break;
	}
	
	case 7:
	{
		cout << "\tDoses taken(1 Or 2):";
		cin >> optionNum;
		if (checknumber(optionNum) == true) {
			editoption = stoi(optionNum);
			if ((editoption == 1 )|| (editoption == 2)) {
				itr->second.doses = editoption;
				if (editoption == 1) {
					waitingList.deQueue(rc.ID);
					SecDoseWaitingList.enQueue(rc.ID);
					cout << "\n\tyou have been added to the second dose waiting list\n";
				}
				else if (editoption == 2) {
					SecDoseWaitingList.deQueue(rc.ID);
					cout << "\n\tyou have been fully vaccinated!\n ";
				}
				cout << "\tdo you want to edit anything else?";
				cin >> answer;
				EditAgain(answer);
			}
			else {
				cout << "\tInvalid Input!\n";
				cout << "\tdo you want to edit anything else?";
				cin >> answer;
				EditAgain(answer);
			}

	    }
		break;
	}

	default: {
		system("cls");
		cout << "\tinvalid choice\n";
		BackOption();
		UserOptions();
		break;
	}
	}
	BackOption();
	UserOptions();
	system("cls");
		if (itr->second.gender == 'f' || itr->second.gender == 'F') {
		female--;
	}
	if (itr->second.gender == 'm' || itr->second.gender == 'M') {
		male--;
	}
	if (itr->second.doses == 0) {
		noDoses--;
	}
	if (itr->second.doses == 1) {
		oneDose--;
	}
	if (itr->second.doses == 2) {
		twoDose--;
	}
	if (itr->second.gov == "Cairo") {
		cairoCount--;
	}
	if (itr->second.gov == "Alexandria") {
		alexCount--;
	}
	if (itr->second.gov == "Giza") {
		gizaCount--;
	}
	if (itr->second.gov == "Sharqia") {
		sharqiaCount--;
	}
	if (itr->second.gov == "PortSaid") {
		portsaidCount--;
	}
	if (itr->second.gov == "other") {
		otherCount--;
	}
	
	
}


//Checking if the User Want to Edit Again
void Record::EditAgain(char ans) {

	if (ans == 'y' || ans == 'Y') {
		system("cls");
		editUserData();
	}
	else if (ans == 'n' || ans == 'N') {
		system("cls");
		UserOptions();
	}
	else {
		cout << "\tinvalid choice\n";
		BackOption();
		UserOptions();
	}
		
}


//Backs
void Record::BackOption() {
	
	Sleep(500);
	system("PAUSE");
	system("cls");

}


//Deleting User Data 
void Record::deleteUserData(){

	string verify;

	VV:
	cout << "\tenter your ID for verfication:";
	cin >> verify;
	itr = userMap.find(rc.ID);
	if (verify!=itr->second.ID) {
		cout << "\tWrong ID\n";
		goto VV;
	}

	else if(verify == itr->second.ID) {

		if (itr->second.gender == 'f' || itr->second.gender == 'F') {
			female--;
		}
		if (itr->second.gender == 'm' || itr->second.gender == 'M') {
			male--;
		}
		if (itr->second.doses == 0) {
			noDoses--;
		}
		if (itr->second.doses == 1) {
			oneDose--;
		}
		if (itr->second.doses == 2) {
			twoDose--;
		}
		if (itr->second.gov == "Cairo") {
			cairoCount--;
		}
		if (itr->second.gov == "Alexandria") {
			alexCount--;
		}
		if (itr->second.gov == "Giza") {
			gizaCount--;
		}
		if (itr->second.gov == "Sharqia") {
			sharqiaCount--;
		}
		if (itr->second.gov == "PortSaid") {
			portsaidCount--;
		}
		if (itr->second.gov == "other") {
			otherCount--;
		}
		
	}
	char* fname;
	string filename = itr->first + ".txt";
	fname = &filename[0];
	remove(fname);
	userMap.erase(rc.ID);
	cout << "\tDeleted Successfully!\n";
	updatefiles();
	BackOption();
	mainMenu();

}


//Displaying Admin Options
void Record::adminOptions() {

	int adminchoice;
	displayTitle();

	cout << "\t-->> Welcome Admin <<--\n";
	cout << "\t--- Choose one of the following choices. ---\n";
	cout << "\t1-> Display Record\n";
	cout << "\t2-> Delete Record\n";
	cout << "\t3-> Display Statistics\n";
	cout << "\t4-> View or Delete all\n";
	cout << "\t5-> Log Out\n";
	cout << "\tEnter your choice:";

	cin >> adminchoice;
	switch (adminchoice) {
	case 1:
		system("CLS");
		adminDisplay();

		break;
	case 2:
		system("CLS");
		adminDelete();

		break;
	case 3:
		system("CLS");
		displayStats();

		break;
	case 4:
		system("cls");
		ViewDelete();
		break;
	case 5: 
		system("cls");
		mainMenu();
	default:
		cout << "\tInavlid choice , try again." << endl;
		system("pause");
		system("cls");
		adminOptions();
	}
	

}


//Viewing and Deleting All Records 
void Record::ViewDelete() {
	int adchoice;

	displayTitle();
	cout << "\t--- Choose one of the following choices. ---\n";
	cout << "\t1-> Display All Records\n";
	cout << "\t2-> Delete All Records\n";
	cout << "\t3->Go back?\n";
	cout << "\tEnter your choice:";

	cin >> adchoice;
	switch (adchoice) {
	case 1:
		system("CLS");

		for (itr = userMap.begin(); itr != userMap.end(); ++itr) {
			cout << "\t-----------------Recorded Data-----------------\n\n";
			cout << "\tFirstname:" << "  " << itr->second.fname << endl;
			cout << "\tLastname:" << "  " << itr->second.lname << endl;
			cout << "\tNational ID:" << "  " << itr->first << endl;
			cout << "\tPassword:" << "  " << itr->second.password << endl;
			cout << "\tAge:" << "  " << itr->second.age << endl;
			cout << "\tGender:" << "  " << itr->second.gender << endl;
			cout << "\t-------Governorates-------" << endl;
			cout << "\t1 ---> Cairo " << endl;
			cout << "\t2 ---> Alexandria " << endl;
			cout << "\t3 ---> Giza " << endl;
			cout << "\t4 ---> Sharqia " << endl;
			cout << "\t5 ---> Port Said " << endl;
			cout << "\t6 ---> Other " << endl;
			cout << "\tgovernorate:" << "  " << itr->second.gov << endl;
			cout << "\tDoses taken:" << "  " << itr->second.doses << endl;
		}
		BackOption();
		adminOptions();

		break;

	case 2:
		system("CLS");
		if (userMap.empty()) {
			cout << "\tNo records found!\n";
		}
		else {
			deleteFiles();
			userMap.clear();
			cout << "\tAll Records Deleted Successfully!\n";
		}
		BackOption();
		adminOptions();


		break;
	case 3:
		system("CLS");
		BackOption();
		adminOptions();
		break;
	default:
		system("CLS");
		cout << "\tinvalid choice\n";
		BackOption();
		adminOptions();

	}
}


//Displaying User Data When Entering the National ID
void Record::adminDisplay() {

	cout << "\tPlease enter the National ID of the User whose data you would like displayed:";
	cin >> rc.ID;
	system("cls");

	itr = userMap.find(rc.ID);

	if (itr == userMap.end()) {
		cout << "\tno record!\n";
		BackOption();
		adminOptions();

	}
	else {

		cout << "\t-----------------Recorded Data-----------------\n\n";
		cout << "\tFirstname:" << "  " << itr->second.fname << endl;
		cout << "\tLastname:" << "  " << itr->second.lname << endl;
		cout << "\tNational ID:" << "  " << itr->first << endl;
		cout << "\tPassword:" << "  " << itr->second.password << endl;
		cout << "\tAge:" << "  " << itr->second.age << endl;
		cout << "\tGender:" << "  " << itr->second.gender << endl;
		cout << "\t-------Governorates-------" << endl;
		cout << "\t1 ---> Cairo " << endl;
		cout << "\t2 ---> Alexandria " << endl;
		cout << "\t3 ---> Giza " << endl;
		cout << "\t4 ---> Sharqia " << endl;
		cout << "\t5 ---> Port Said " << endl;
		cout << "\t6 ---> Other " << endl;
		cout << "\tgovernorate:" << "  " << itr->second.gov << endl;
		cout << "\tDoses taken:" << "  " << itr->second.doses << endl;
		BackOption();
		adminOptions();
	}
}


//Deleting User Data When Entering the National ID
void Record::adminDelete() {

	displayTitle();

	cout << "\tPlease enter the National ID of the User whose data you would like deleted:";
	cin >> rc.ID;
	string verify;

kk:
	cout << "\tenter your ID for verfication:";
	cin >> verify;
	itr = userMap.find(rc.ID);
	if (verify != itr->second.ID) {
		cout << "\tWrong ID\n";
		goto kk;
	}


	else if (verify == itr->second.ID) {

		if (itr->second.gender == 'f' || itr->second.gender == 'F') {
			female--;
		}
		if (itr->second.gender == 'm' || itr->second.gender == 'M') {
			male--;
		}
		if (itr->second.doses == 0) {
			noDoses--;
		}
		if (itr->second.doses == 1) {
			oneDose--;
		}
		if (itr->second.doses == 2) {
			twoDose--;
		}
		if (itr->second.gov == "Cairo") {
			cairoCount--;
		}
		if (itr->second.gov == "Alexandria") {
			alexCount--;
		}
		if (itr->second.gov == "Giza") {
			gizaCount--;
		}
		if (itr->second.gov == "Sharqia") {
			sharqiaCount--;
		}
		if (itr->second.gov == "PortSaid") {
			portsaidCount--;
		}
		if (itr->second.gov == "other") {
			otherCount--;
		}


	}
	char* fname;
	string filename = itr->first + ".txt";
	fname = &filename[0];
	remove(fname);
	userMap.erase(rc.ID);
	cout << "\tDeleted Successfully!\n";
	updatefiles();
	BackOption();
	adminOptions();
}


void Record::Counters() {
	for (itr = userMap.begin(); itr != userMap.end(); ++itr) {
		if (itr->second.doses == 1) {
			oneDose++;
		}
		if (itr->second.doses == 2) {
			twoDose++;
		}
		if (itr->second.doses == 0) {
			noDoses++;
		}
		if (itr->second.gender == 'f' || itr->second.gender == 'F') {
			female++;
		}
		if (itr->second.gender == 'm' || itr->second.gender == 'M') {
			male++;
		}
		if (itr->second.gov == "Cairo") {
			cairoCount++;
		}
		if (itr->second.gov == "Giza") {
			gizaCount++;
		}
		if (itr->second.gov == "Alexandria") {
			alexCount++;
		}
		if (itr->second.gov == "PortSaid") {
			portsaidCount++;
		}
		if (itr->second.gov == "Sharqia") {
			sharqiaCount++;
		}
		if (itr->second.gov == "Others") {
			otherCount++;
		}
	}
}

//Displaying Statistics Options
void Record::displayStats() {

	displayTitle();

	int adminchoice;
	cout << "\t-->>which one of the statistics do you want to be displayed.\n\n";

	cout << "\t1->Percentage of people registered in the system that hasn't recieved any doses.\n\n";

	cout << "\t2->Percentage of people registered in the system that has received the first dose.\n\n";

	cout << "\t3->Percentage of people registered in the system that has received both doses.\n\n";

	cout << "\t4-> Percentage of Females and Males registered in the system.\n\n";

	cout << "\t5->Percentage of Cairo citizens.\n\n";

	cout << "\t6->Percentage of Alexandria citizens.\n\n";

	cout << "\t7->Percentage of Giza citizens.\n\n";

	cout << "\t8->Percentage of Port Said citizens.\n\n";

	cout << "\t9->Percentage of Sharqia citizens.\n\n";

	cout << "\t10->Percentage of Other citizens.\n\n";

	cout << "\t11->Go back to options.\n\n";

	cout << "\tEnter your choice:";
	cin >> adminchoice;

	switch (adminchoice)
	{
	case 1:
		system("cls");
		Statnodoses();
		break;
	case 2:
		system("cls");
		StatOneDose();
		break;
	case 3:
		system("cls");
		StatTwoDose();
		break;
	case 4:
		system("cls");
		StatFemaleMale();
		break;
	case 5:
		system("cls");
		StatCairo();
	case 6:
		system("cls");
		StatAlex();
		break;
	case 7:
		system("cls");
		StatGiza();
		break;
	case 8:
		system("cls");
		StatPortSaid();
		break;
	case 9:
		system("cls");
		StatSharqia();
		break;
	case 10:
		system("cls");
		StatOthers();
		break;
	case 11:
		system("cls");
		adminOptions();
		break;
	default:
		cout << "\tInvalid choice.\n";
		BackOption();
		adminOptions();
		break;
	}


}


//Calculating One Dose Statistics
void Record::StatOneDose() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {
		

		float statdoseone = (oneDose / (float)userMap.size()) * 100;
		cout << "\tPercentage of people registered in the system that has received the first dose: " << statdoseone << "%" << endl;
		BackOption();
		displayStats();
	}

}


//Calculating Two Doses Statistics
void Record::StatTwoDose() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {

		float statdosetwo = (twoDose / (float)userMap.size()) * 100;
		cout << "\tPercentage of people registered in the system that has received both doses: " << statdosetwo << "%" << endl;
		BackOption();
		displayStats();
	}
}


//Calculating Female and Male Statistics
void Record::StatFemaleMale() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {

		float statfemale = (female / (float)userMap.size()) * 100;
		cout << "\tPercentage of Females registered in the system: " << statfemale << "%" << endl;

		float statmale = (male / (float)userMap.size()) * 100;
		cout << " \tPercentage of Males registered in the system: " << statmale << "%" << endl;

		BackOption();
		displayStats();
	}

}


//Calculating Giza Citizens Statistics
void Record::StatGiza() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {

		float statgiza = ((float)gizaCount / (float)userMap.size()) * 100;
		cout << "\tPercentage of Giza citizens: " << statgiza << "%" << endl;

		BackOption();
		displayStats();
	}
}


//Calculating PortSaid Citizens Statistics
void Record::StatPortSaid() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {

		float statportsaid = (portsaidCount / (float)userMap.size()) * 100;
		cout << "\tPercentage of Port Said citizens: " << statportsaid << "%" << endl;

		BackOption();
		displayStats();
	}

}


//Calculating Sharqia Citizens Statistics
void Record::StatSharqia() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {
		float statsharqia = (sharqiaCount / (float)userMap.size()) * 100;
		cout << "\tPercentage of Sharqia citizens: " << statsharqia << "%" << endl;

		BackOption();
		displayStats();
	}
}


//Calculating No Doses Statistics
void Record::Statnodoses() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {
		float statnodoses = (noDoses / (float)userMap.size()) * 100;
		cout << "\tPercentage of people registered in the system that didnt received any doses: " << statnodoses << "%" << endl;
		BackOption();
		displayStats();
	}
}


//Calculating Cairo Citizens Statistics
void Record::StatCairo() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {

		float statCairo = (cairoCount / (float)userMap.size()) * 100;
		cout << "\tPercentage of people that registered in cairo: " << statCairo << "%" << endl;
		BackOption();
		displayStats();
	}
}


//Calculating Alex Citizens Statistics
void Record::StatAlex() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {
		float statAlex = (alexCount / (float)userMap.size()) * 100;
		cout << "\tPercentage of people that registered in alex: " << statAlex << "%" << endl;
		BackOption();
		displayStats();
	}
}


//Calculating other Citizens Statistics
void Record::StatOthers() {
	displayTitle();
	if (userMap.size() == 0) {
		cout << "\t\t\t\t\tno users to display their statistics.....\n";
		BackOption();
		displayStats();

	}
	else {
		float statothers = (otherCount / (float)userMap.size()) * 100;
		cout << "\tPercentage of citizens living in other governates: " << statothers << "%" << endl;

		BackOption();
		displayStats();
	}
}


//File Related Functions
Record Record::retrieve(string file) {

	Record r;

	myfile.open(file, ios::in);
	myfile >> fname;
	r.fname = fname;
	myfile >> lname;
	r.lname = lname;
	myfile >> ID;
	r.ID = ID;
	myfile >> passConfirm;
	r.password = passConfirm;
	myfile >> age;
	r.age = age;
	myfile >> gender;
	r.gender = gender;
	myfile >> gov;
	r.gov = gov;
	myfile >> doses;
	r.doses = doses;
	myfile.close();
	return r;
}
void Record::bringFromFile() {
	string line;
	string filename;
	vector<string> v;
	myfile.open("all.txt", ios::in);
	for (string line; getline(myfile, line);) {
		v.push_back(line);
	}
	myfile.close();
	for (int i = 0; i < v.size(); i++)
	{
		filename = v[i] + ".txt";
		Record r = retrieve(filename);
		userMap[r.ID] = r;
	}
	//Counters();
}
void Record::updatefiles() {
	vector<string> v;
	for (itr = userMap.begin(); itr != userMap.end(); itr++) {
		string filename = itr->first + ".txt";
		myfile.open(filename);
		if (myfile.is_open()) {
			myfile.close();
			char* fname;
			fname = &filename[0];
			remove(fname);
			myfile.open(filename, ios::app);
			myfile << itr->second.fname << endl;
			myfile << itr->second.lname << endl;
			myfile << itr->second.ID << endl;
			myfile << itr->second.password << endl;
			myfile << itr->second.age << endl;
			myfile << itr->second.gender << endl;
			myfile << itr->second.gov << endl;
			myfile << itr->second.doses << endl;
			myfile.close();
			v.push_back(itr->first);
		}
		else {
			cout << "failed to open file\n";
		}
		/*else if (!myfile.is_open()) {
			myfile.close();
			myfile.open(filename, ios::app);
			myfile << itr->second.fname << endl;
			myfile << itr->second.lname << endl;
			myfile << itr->second.ID << endl;
			myfile << itr->second.passConfirm << endl;
			myfile << itr->second.age << endl;
			myfile << itr->second.gov << endl;
			myfile << itr->second.doses << endl;
			myfile.close();

		}*/



	}
	string all = "all.txt";
	char* allf;
	allf = &all[0];
	remove(allf);
	myfile.open("all.txt", ios::app);
	for (int i = 0; i < v.size(); i++) {
		myfile << v[i] << endl;
	}
	myfile.close();
}
void Record::deleteFiles() {
	for (itr = userMap.begin(); itr != userMap.end(); itr++) {
		string filename = itr->first + ".txt";
		char* fname;
		fname = &filename[0];
		remove(fname);
	}
	string all = "all.txt";
	char* allf;
	allf = &all[0];
	remove(allf);
}
