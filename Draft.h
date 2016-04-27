#ifndef DRAFT_H
#define DRAFT_H
#include <iostream>
using namespace std;



struct Team{
        Team *next;
        Team *previous;
        string teamName;
        int pick;
        bool seen = false;
        bool PGneeded = true;
        bool SGneeded = true;
        bool SFneeded = true;
        bool PFneeded = true;
        bool Cneeded = true;
        string pg;
        string sg;
        string sf;
        string pf;
        string c;
};

struct Picks{
    int number;
    Picks *next;
    Picks *previous;
};

struct Player{
    Player *next;
    Player *previous;
    string name;
    int ranking;
};



class Draft
{



    public:
        Draft();
        virtual ~Draft();
        void createTeamLinkedList();
        bool TeamisThere(string teamEntered);
        void determineOrder();
        void deletePick(int pickNumber);
        bool pickSearch(int pick);
        void yourPickIs(string teamName);
        void draftBoard();
        void Drafting();
        void viewYourTeam(string yourTeamName);
        void viewTeam(string teamName);




    protected:
    private:
        Team * head;
        Picks *pickHead;
        Player *pgHead;
        Player *sgHead;
        Player *sfHead;
        Player *pfHead;
        Player *cHead;
        /*void createPGlist();
        void createSGlist();
        void createSFlist();
        void createPFlist();
        void createClist();*/
};

#endif // DRAFT_H
