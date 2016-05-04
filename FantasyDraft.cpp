//Samuel Busser
//Data Structures Final Project
//Instructor: Rhonda Hoenigman

#include <iostream>
#include <fstream>
#include "Draft.h"

using namespace std;

int main()
{
    Draft Sam;
    Sam.createTeamLinkedList();

	bool exit = false;
	while(exit == false){
		cout<<"Welcome to the NBA Fantasy Draft. This is your chance to build your very own dream team."<<endl;
		bool firstKeepGoing = true;
		while (firstKeepGoing == true){
			cout<<"Would you like to begin?"<<endl;
			cout<<"1. Yes"<<endl;
			cout<<"2. No"<<endl;
			string go;
			getline(cin, go);
			if (go == "1"){
				firstKeepGoing = false;
			}
			else if (go == "2"){
				cout<<"Please? It's really cool I promise"<<endl;
				cout<<endl;
				cout<<endl;
			}
			else if(go == "q"){
				exit = true;
				firstKeepGoing = false;
			}
			else {
				cout<<"This is not a valid input...please try again."<<endl;
			}
		}
		if(exit == true){
			cout << "Goodbye" << endl;
			break;
		}
		cout<<"If at anytime you would like to quit, just press q."<<endl;
 		cout<<endl;
		cout<<"To start, please select a team."<<endl;
		string lineTeam;
		ifstream fileTeam("TeamList.txt");    //reading in text file of teams, displaying the teams to the user
		while (getline(fileTeam, lineTeam)){
			cout<<lineTeam<<endl;
		}
		fileTeam.close();
		string chosenTeam;
		cout<<endl;
		bool keepLooping = true;
		while (keepLooping == true){
			cout<<"Select a team: "<<endl;
			getline(cin,chosenTeam);
			if(chosenTeam == "q"){
				exit = true;
				keepLooping = false;
			}
			else if (Sam.TeamisThere(chosenTeam) == false){
				cout<<"This is not a NBA team. Please try again"<<endl;
			}
			else{
				keepLooping = false;
				cout<<"You have selected the "<<chosenTeam<<endl;
			}
		}
		if(exit == true){
			cout << "Goodbye" << endl;
			break;
		}


		Sam.determineOrder();
		Sam.yourPickIs(chosenTeam);
		Sam.draftBoard();
		bool draftReady = false;
		string draftChoice;


    string reassignChoice;
    bool reassign = false;
    while (reassign == false)
    {
        cout << "Would you like to reassign picks or continue?" << endl;
        cout << "1. Continue with the draft" << endl << "2. Reassign" << endl;
        getline(cin, reassignChoice);
        if(reassignChoice == "2")
        {
            Sam.determineOrder();
            Sam.yourPickIs(chosenTeam);
        }
        else
        {
            reassign = true;
            break;
        }
    }

		while (draftReady == false){
			cout<<endl;
			cout<<endl;
			cout<<"Are you ready to begin the draft?"<<endl;
			cout<<"1. Yes"<<endl;
			cout<<"2. No"<<endl;
			getline(cin, draftChoice);
			if (draftChoice == "1"){
				draftReady = true;
				cout<<"The draft starts now!"<<endl;
			}
			else if(draftChoice == "q"){
				exit = true;
				draftReady = true;
			}
			else {
				cout<<"How about now?"<<endl;
			}
		}
		if(exit == true){
			cout << "Goodbye" << endl;
			break;
		}

		Sam.Drafting();
		cout<<endl;
		cout<<endl;
		cout<<"The draft has completed"<<endl;
		bool finalKeepGoing = true;
		while (finalKeepGoing == true){
			cout<<"1. View your team"<<endl;
			cout<<"2. View another team"<<endl;
			cout<<"3. Quit"<<endl;
			string finalChoice;
			getline(cin, finalChoice);
			if (finalChoice == "3"){
				cout<<"Thanks for playing!"<<endl;
				cout<<"Goodbye"<<endl;
				finalKeepGoing = false;
				exit = true;
			}
			else if(finalChoice == "1"){
				Sam.viewYourTeam(chosenTeam);
			}
			else if (finalChoice == "2"){
				string wantedTeam;
				bool seeAnotherTeam = true;
				while (seeAnotherTeam == true){
					cout<<"Select a team that you would like to see:"<<endl;
					getline(cin,wantedTeam);
					if (Sam.TeamisThere(wantedTeam) == true){
						break;
					}
					else{
						cout<<"This is not a NBA team... Please try again."<<endl;
					}
				}
				cout<<endl;
				cout<<endl;
				Sam.viewTeam(wantedTeam);


			}
			else if(finalChoice == "q"){
				cout << "Goodbye" << endl;
				exit = true;
				finalKeepGoing = false;
			}
			else {
				cout<<"This is not a valid choice... please try again"<<endl;
			}
		}
	}






        return 0;
}
