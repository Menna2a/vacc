#pragma once
#include <cstring>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include<iostream>
#include<conio.h>
#include<queue>
#include<unordered_map>
#include <vector>
#include<cstdio>

using namespace std;
class Record
{
	public:

		//variables
		string fname, lname, ID, password, passConfirm, gov;
		char  gender;
		bool flag, vaccinated , fullyVaccinated , halfVaccinated ;
		int age=0,doses=0, choice=0;

		//hash table iterartor
		unordered_map<string, Record >::iterator itr;

		//FirstPage functions
		void displayTitle();
		void mainMenu();
		void displayChoices();

		//signIn functions
        void SignIn();

		//signUp functions
		void recData();
		void getnatID();
		void CheckRegisteredID(string);
		void getAge();
		void createPass();
		void displayGov();
		void getGov();
		void gotVaccine();
		void insertUserData();


		//admin functions
		void adminOptions();
		void adminDisplay();
		void adminDelete();
		void ViewDelete();
		
		//statistics functions
		void Counters();
		void displayStats();
		void StatOneDose();
		void StatTwoDose();
		void StatFemaleMale();
		void StatGiza();
		void StatPortSaid();
		void StatSharqia();
		void StatOthers();
		void StatCairo();
		void StatAlex();
		void Statnodoses();


		// user functions
		void displayUserData();
        void UserOptions();
        void deleteUserData();

		// editting functions
		void diplayEditChoices();
		void editUserData();
		void EditAgain(char);
		bool checknumber(string);
		
		//redirecting function (between different functions)
        void BackOption();	

		//file related functions
		Record retrieve(string id);
		void bringFromFile();
		void updatefiles();
		void deleteFiles();
};

class Node // used in implementing queue by linked list
{  
 public:
	string data;
	Node* next;
	Node(string d) {
		data = d;
		next = NULL;
	}
};
class Queue
{
 public:
	Node* front,* back;
	Queue() {
		front = back = NULL;
	}
	void enQueue(string);
	void deQueue(string);
};



