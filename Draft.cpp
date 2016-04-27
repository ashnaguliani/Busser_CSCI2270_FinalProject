#include "Draft.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;
Picks *pickHead = NULL;
Team *head = NULL;

Draft::Draft()
{

}

Draft::~Draft()
{

}


void Draft::createTeamLinkedList(){
    string teamArray[30] = {"Boston Celtics", "Brooklyn Nets", "New York Knicks", "Philadelphia 76ers", "Toronto Raptors", "Chicago Bulls", "Cleveland Cavaliers", "Detroit Pistons", "Indiana Pacers", "Milwaukee Bucks", "Atlanta Hawks", "Charlotte Hornets", "Miami Heat", "Orlando Magic", "Washington Wizards", "Denver Nuggets", "Minnesota Timberwolves", "Oklahoma City Thunder", "Portland Trail Blazers", "Utah Jazz", "Golden State Warriors", "Los Angeles Clippers", "Los Angeles Lakers", "Phoenix Suns", "Sacramento Kings", "Dallas Mavericks", "Houston Rockets", "Memphis Grizzlies", "New Orleans Pelicans", "San Antonio Spurs" };
    head = new Team;
    head->previous = NULL;
    head->next = NULL;
    head->teamName = teamArray[0];
    Team *temp = head;
    //creating a linked list of all the teams
    for(int i = 1; i<30; i++){
        Team *current = new Team;
        current->previous = temp;
        current->next = NULL;
        current->teamName = teamArray[i];
        temp->next = current;
        temp = current;
    }


}

bool Draft::TeamisThere(string teamPicked){  //making sure the team entered by the user is an actual team
    Team * temp = head;
    bool found = false;
    while ((found == false) && (temp != NULL)){
        if(temp->teamName == teamPicked){
            found = true;
            break;
        }
        else {
            temp = temp->next;
        }
    }
    if (found == true){
        return true;
    }
    else{
        return false;;
    }


}


void Draft::determineOrder(){   //creating linked list of all the picks, assigning a pick to each team
    int picksArray[30] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    pickHead = new Picks;
    pickHead->previous = NULL;
    pickHead->next = NULL;
    pickHead->number = picksArray[0];
    Picks *tempo = pickHead;
    for (int i = 1; i<30; i++){   //creating a linked list of numbers (so that can assign individual pick number to each team) ->the random number function can generate the same number twice, dont want two teams with same pick
        Picks*current = new Picks;
        current->previous = tempo;
        current->next = NULL;
        current->number = i+1;
        tempo->next = current;
        tempo = current;
    }
    //generating a unique, random pick for each team
    Team * temp = head;
    srand(time(NULL));
    int pickNumber = (rand() % 30 +1);
    while(temp != NULL){
        if(pickSearch(pickNumber) == true){  //if the pick has not been assigned to another team yet
            temp->pick = pickNumber; //assign the pick to the team
            deletePick(pickNumber); //delete the pick from the linked list so it can't be used agaain
            temp = temp->next;
            pickNumber = (rand() % 30 +1);  //generate a new random number

        }
        else{  //if random number generated has already been used
            pickNumber = (rand() % 30 +1);   //generate a new number
        }

    }

}

bool Draft::pickSearch(int searchNumber){  //looking to see if the pick has already been assigned
    Picks *temp = pickHead;
    bool found = false;
    while ((found == false) && temp != NULL){
        if(temp->number == searchNumber){
            found = true;

        }
        else{
            temp = temp->next;
        }
    }

    if(found == true){
        return true;
    }

    else {
        return false;
    }


}


void Draft::deletePick(int pick){    // function to remove a pick from the linked list once it is assigned to a team, so that no team can have the same pick
    Picks *temp = pickHead;
    Picks *removePick;
        while (temp != NULL){
            if (pickHead->next == NULL){  //if node is the only node in the list
                pickHead = NULL;
                break;
            }

            else if(pickHead->number == pick){  //node to delete is the head
                removePick = pickHead;
                pickHead->next->previous = NULL;
                pickHead = pickHead->next;
                temp = pickHead;
                delete removePick;
                break;
            }

            else if((temp->next == NULL) && (temp->number == pick)){ //if number to delete is the last one... Tail case
                removePick = temp;
                removePick->previous->next = NULL;
                delete removePick;
                break;
            }


            else if (temp->number == pick){  //general case
                removePick = temp;
                removePick->previous->next = removePick->next;
                removePick->next->previous = removePick->previous;
                delete removePick;
                break;
            }
            else {
                temp = temp->next;
            }
        }
    }


void Draft::yourPickIs(string teamName){  //telling user what pick they have in the draft
    Team *temp = head;
    bool found = false;
    while ((found == false) && (temp != NULL)){  //searching for the user's team choice, then getting that team's pick
        if (temp->teamName == teamName){
            found = true;
            cout<<"You have pick "<<temp->pick<<" in the draft"<<endl;
            break;
           }
        else {
            temp = temp->next;
        }
    }
}


void Draft::draftBoard(){  //function to display each team and what draft pick they have
    cout<<"Here is the draft order: "<<endl;
    Team *temp = head;
    int pick = 1;
    while(temp != NULL){
        if ((temp->pick == pick) && (temp->seen == false) &&(pick <= 30)){
            cout<<temp->pick<<".   "<<temp->teamName<<endl;
            temp->seen = true;
            temp = head;   //want to loop  through every team, every time, so set temp equal to head again, and mark the the team just used as seen so that it is not selected again
            pick++;
        }
        else {
            temp = temp->next;
        }
    }

}


void Draft::Drafting(){  //the actual drafting of players for each team
    string cArray[50] = {"Demarcus Cousins", "Andre Drummond", "Karl-Anthony Towns", "Hassan Whiteside", "Pau Gasol", "Brook Lopez", "DeAndre Jordan", "Dwight Howard", "Nikola Vucevic", "Al Horford", "Jonas Valanciunas", "Marc Gasol", "Tim Duncan", "Marcin Gortat", "Enes Kanter", "Rudy Gobert", "Tristian Thompson", "Greg Monroe", "Al Jefferson", "Jared Sullinger", "Jahlil Okafor", "Robin Lopez", "Myles Turner", "Nikola Pekovic", "Nikola Jokic", "Gorgui Dieng", "Andrew Bogut", "Joakim Noah", "Boban Marjanovic", "Kelly Olynyk", "Steven Adams", "Mason Plumlee", "Nerlens Noel", "Zaza Pachulia", "Nene", "Festus Ezeli", "Cody Zeller", "Larry Sanders", "Jordan Hill", "Ed Davis", "Amar’e Stoudemire", "Ian Mahinmi", "JaVale McGee", "Clint Capela", "Timofey Mozgov", "Joffrey Lauvergne", "Alex Len", "Marreese Speights", "John Henson", "Tyson Chandler"};
    string pfArray[50] = {"Anthony Davis", "Draymond Green", "Blake Griffin", "LaMarcus Aldridge", "Dirk Nowitzki", "Chris Bosh", "Derrick Favors", "Paul Millsap", "Kevin Love", "Zach Randolph", "Kenneth Faried", "Kristaps Porzingis", "Serge Ibaka", "Thaddeus Young", "Ryan Anderson", "Michael Beasley", "Jabari Parker", "Marvin Williams", "Aaron Gordon", "David West", "Mirza Teletovic", "Markieff Morris", "Julius Randle", "Taj Gibson", "Luis Scola", "Amir Johnson", "Darrell Arthur", "Boris Diaw", "Nicola Mirotic", "David Lee", "Dwight Powell", "Dontas Motiejunas", "Brandon Bass", "Jon Leuer", "Terrence Jones", "Carlos Boozer", "Channing Frye", "Bobby Portis", "Ersan Ilyasova", "Carl Landry", "Kevin Garnett", "Jamychal Green", "Patrick Patterson", "Reggie Evans", "Thomas Robinson", "Josh Smith", "Andrew Nicholson", "Trevor Booker", "Quincy Acy", "Andrea Bargnani"};
    string sfArray[50] = {"LeBron James", "Kevin Durant", "Kawhi Leonard", "Paul George", "Carmelo Anthony", "Giannis Antetokounmpo", "Gordon Hayward", "Jae Crowder", "Andrew Wiggins", "Tyreke Evans", "Danilo Gallinari", "Nicolas Batum", "Rudy Gay", "Chandler Parsons", "Tobias Harris", "Andre Iguodala", "Michael Kidd-Gilchrist", "Harrison Barnes", "Luol Deng", "Wilson Chandler", "Jeff Green", "T.J Warren", "Evan Turner", "Otto Porter", "Trevor Ariza", "Joe Johnson", "Justise Winslow", "Al-Farouq Aminu", "Demarre Carroll", "Shabazz Muhammad", "C.J Miles", "Bojan Bogdanovic", "Jared Dudley", "Terrence Ross", "Thabo Sefolosha", "Solomon Hill", "Doug McDermott", "Marcus Morris", "Derrick Williams", "Lance Thomas", "Kyle Anderson", "P.J Tucker", "James Johnson", "Corey Brewer", "Rondae Hollis-Jefferson", "Maurice Harkless", "Jerami Grant", "Vince Carter", "Robert Covington", "Paul Pierce"};
    string sgArray[50] = {"James Harden", "Demar DeRozan", "Klay Thompson", "Jimmy Butler", "Dwayne Wade", "C.J McCollum", "Kris Middleton", "Manu Ginobili", "Avery Bradley", "Will Barton", "Rodney Hood", "Victor Oladipo", "Monta Ellis", "Kobe Bryant", "Devin Booker", "Bradley Beal", "J.J Redick", "Evan Fournier", "Zach LaVine", "Louis Williams", "Alec Burks", "Wesley Matthews", "Tony Allen", "Kentavious  Caldwell-Pope", "Eric Gordon", "Jamal Crawford", "Courtney Lee", "Lance Stephenson", "Garry Harris", "Jeromy Lamb", "Rodney Stuckey", "J.R Smith", "Marcus Thornton", "Tyler Johnson", "Aaron Afflalo", "Gary Neal", "Allen Crabbe", "Josh Richardson", "Kyle Korver", "Sean Kilpatrick", "Jodie Meeks", "Iman Shumpert", "Danny Green", "Norman Powell", "Dion Waiters", "E’Twaun Moore", "Marco Belinelli", "Isiah Canaan", "Gerald Green", "Andre Roberson" };
    string pgArray[50] = {"Stephen Curry", "Russel Westbrook", "Chris Paul", "John Wall", "Damian Lillard", "Kyle Lowry", "Kyrie Irving", "Isiah Thomas", "Eric Bledsoe", "Kemba Walker", "Mike Conley", "Rajon Rondo", "Jrue Holliday", "Tony Parker", "Darren Collison", "Derrick Rose", "Brandon Knight", "Ricky Rubio", "Goran Dragic", "Deron Williams", "Dennis Schroder", "Jeff Teague", "Jordan Clarkson", "D’Angelo Russel", "Patrick Beverley", "George Hill", "Ish Smith", "J.J Barea", "Michael Carter-Williams", "Jarret Jack", "Mario Chalmers", "Jeremy Lin", "Emmanuel Mudiay", "Matthew Dellavedova", "Brandon Jennings", "Tony Wroten", "Corey Joseph", "Shelvin Mack", "Ramon Sessions", "Sean Livingston", "Elfrid Payton", "Jose Calderon", "Patty Mills", "Beno Udrih", "Norris Cole", "Marcus Smart", "Trey Burke", "Devon Harris", "Austin Rivers", "Jerryd Bayless" };
    Team *inOrderArray[30];  //array of pointers to the Team type
    int index = 0;   //this will be an index counter for the abover array
    int wantedPick = 1;  //counter for putting the teams in order based on their pick
    Team *temp = head;
    while (temp != NULL){
            //creating an array of teams in the order of their picks
        if (temp->pick == wantedPick){
            inOrderArray[index] = temp;
            wantedPick++;
            index++;
            if (temp->pick == 30){
                break;
            }
            temp = head;

        }
        else{
            temp = temp->next;
        }

    }
    temp = head;
    int pgIndex = 0; //creating indexes for each player array
    int sgIndex = 0;
    int sfIndex = 0;
    int pfIndex = 0;
    int cIndex = 0;

    for (int i = 0; i<5; i++){  //5 rounds
        for (int j = 0; j<30; j++){  //30 teams, 30 picks each round
            int positionNumber = (rand() % 5 +1);
            bool keepGoing = true;    //checking to see if the team already has drafted a player at the position chosen (since there are only 5 rounds, only one player per position)
            while (keepGoing == true){
                if (positionNumber == 1){
                    if (inOrderArray[j]->PGneeded == false){
                        positionNumber = (rand() % 5 +1);
                    }
                    else{
                        keepGoing = false;
                    }
                }
                else if(positionNumber == 2){
                    if (inOrderArray[j]->SGneeded == false){
                        positionNumber = (rand() % 5 +1);
                    }
                    else {
                        keepGoing = false;
                    }
                }
                else if(positionNumber == 3){
                    if(inOrderArray[j]->SFneeded == false){
                        positionNumber = (rand() % 5 +1);
                    }
                    else {
                        keepGoing = false;
                    }
                }
                else if (positionNumber == 4){
                    if (inOrderArray[j]->PFneeded == false){
                        positionNumber = (rand() % 5 +1);
                    }
                    else {
                        keepGoing = false;
                    }
                }
                else if (positionNumber == 5){
                    if (inOrderArray[j]->Cneeded == false){
                        positionNumber = (rand() % 5 +1);
                    }
                    else {
                        keepGoing = false;
                    }
                }
            }
            //assigning players to their team's roster
            if (positionNumber == 1){
                inOrderArray[j]->pg = pgArray[pgIndex];
                pgIndex++;
                inOrderArray[j]->PGneeded = false;
                cout<<"The "<<inOrderArray[j]->teamName<<" have selected "<<inOrderArray[j]->pg<<endl;
            }
            else if(positionNumber == 2){
                inOrderArray[j]->sg = sgArray[sgIndex];
                sgIndex++;
                inOrderArray[j]->SGneeded = false;
                cout<<"The "<<inOrderArray[j]->teamName<<" have selected "<<inOrderArray[j]->sg<<endl;
            }
            else if (positionNumber == 3){
                inOrderArray[j]->sf = sfArray[sfIndex];
                sfIndex++;
                inOrderArray[j]->SFneeded = false;
                cout<<"The "<<inOrderArray[j]->teamName<<" have selected "<<inOrderArray[j]->sf<<endl;
            }
            else if (positionNumber == 4){
                inOrderArray[j]->pf = pfArray[pfIndex];
                pfIndex++;
                inOrderArray[j]->PFneeded = false;
                cout<<"The "<<inOrderArray[j]->teamName<<" have selected "<<inOrderArray[j]->pf<<endl;
            }
            else if (positionNumber == 5){
                inOrderArray[j]->c = cArray[cIndex];
                cIndex++;
                inOrderArray[j]->Cneeded = false;
                cout<<"The "<<inOrderArray[j]->teamName<<" have selected "<<inOrderArray[j]->c<<endl;
            }

        }

    }

}

void Draft::viewYourTeam(string yourTeamName){  //function to view the players on your team after the draft
    Team * temp = head;
    while (temp != NULL){
        if (temp->teamName == yourTeamName){
            cout<<"The "<<temp->teamName<<": "<<endl;
            cout<<"Point Guard: "<<temp->pg<<endl;
            cout<<"Shooting Guard: "<<temp->sg<<endl;
            cout<<"Small Forward: "<<temp->sf<<endl;
            cout<<"Power Forward: "<<temp->pf<<endl;
            cout<<"Center: "<<temp->c<<endl;
            break;
        }
        else {
            temp = temp->next;
        }
    }
}

void Draft::viewTeam(string teamName){  //function to view the players on other teams after the draft
        Team * temp = head;
        while (temp != NULL){
            if (temp->teamName == teamName){
            cout<<"The "<<temp->teamName<<": "<<endl;
            cout<<"Point Guard: "<<temp->pg<<endl;
            cout<<"Shooting Guard: "<<temp->sg<<endl;
            cout<<"Small Forward: "<<temp->sf<<endl;
            cout<<"Power Forward: "<<temp->pf<<endl;
            cout<<"Center: "<<temp->c<<endl;
            break;
            }
            else {
                temp = temp->next;
            }
        }
}

