#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<string>
#include<chrono>
#include<thread>
#include<sstream>
#include <fstream>
using namespace std;

//Settings

//Set to true to have all text and etc appear instantly
bool speedUp = false;
//Set to false to stop suggesting events and to generate specialists
bool suggestions = true;
//Set to true to sometimes add a hidden flag to encounters
bool hiddenFlag = false;
//Fun Evil Descriptions
bool evilDesc = true;


//Loops

//Travel Loop
bool travelLoop = true;

//Vectors

//Main Encounter Types
vector<string> encounters = {"Combat","Shop","Resource","Event"};
//Combat Flavors
vector<string> combat = {"Pushover","Competent","Elite"};
//Shop Flavors
vector<string> shop = {"Resources","Upgrades","Specialist","Black Market","Evil","Random","Items","Magical"};
//Resource Flavors
vector<string> resource = {"Money","Food","Building Materials","Crew","Random","None"};
//Event Flavors
vector<string> event = {"Positive","Negative","Random","Stranded Specialist"};
//Hidden Chance
vector<string> hiddenChance = {"false","false","true"};
//Evil Numbers
vector<int> evilNum = {1, 11, 21, 31, 41, 51, 61, 71, 81, 91};
//Evil Events

void evilEvent1();
void evilEvent2();
void evilEvent3();
void evilEvent4();
void evilEvent5();
void evilEvent6();
void evilEvent7();
void evilEvent8();
void evilEvent9();
void evilEvent10();

//Evil Events List
vector<void (*)()> evilEvents = {evilEvent1,evilEvent2,evilEvent3,evilEvent4,evilEvent5,evilEvent6,evilEvent7,evilEvent8,evilEvent9,evilEvent10};
//Names (Figure out how to grab from external file)
vector<string> names;
//Nicknames
vector<string> nickNames;
//Skill Levels - Lousy: 5%; Trained: 10%,5%; Skilled: 15%,10%; Elite: 20%,15%
vector<string> skillLevels = {"Lousy","Lousy","Lousy","Lousy","Trained","Trained","Trained","Skilled","Skilled","Elite"};
//Job List
vector<string> jobList = {"Guard","Soldier","Pirate","Farmer","Cook","Butcher","Merchant","Trader","Tax Collector","Diplomat","Negotiator","Prostitute","Lumberjack","Carpenter","Woodworker","Metalsmith","Scrapper","Junker","Scientist","Mage","Researcher"};
//Races
vector<string> races;
//Destination
vector<string> destination;
//Settings
vector<string> settings;


//Functions

//Roll a Dice
int roll(int max)
{
    return(rand() % max + 1);
}

//Select a Choice from a List
string select(vector<string> selectList)
{
    return(selectList[rand() % selectList.size()]);
}

//Wait for a Certain Amount of Time (In Milliseconds)
void wait(int time){
    if(speedUp == false){
        this_thread::sleep_for(chrono::milliseconds(time));
    }
}

//Import Settings From a File
void importSettings(){
    fstream myfile;
    // open file
    myfile.open("Settings.txt");

    if (myfile.is_open()) {
        // checking if the file is open
        string str;

        // read data from file object
        // and put it into string.
        while (getline(myfile, str)) {
            if(str == "true" || str == "false"){
                settings.push_back(str);
            }
        }
        // close the file object.
        myfile.close();
    }
}

//Import Names From a File
void importNames(){
    fstream myfile;
    // open file
    myfile.open("Names.txt");

    if (myfile.is_open()) {
        // checking if the file is open
        string str;

        // read data from file object
        // and put it into string.
        while (getline(myfile, str)) {
            names.push_back(str);
        }
        // close the file object.
        myfile.close();
    }
}

//Import Nicknames From a File
void importNicknames(){
fstream myfile;
    // open file
    myfile.open("Nicknames.txt");

    if (myfile.is_open()) {
        // checking if the file is open
        string str;

        // read data from file object
        // and put it into string.
        while (getline(myfile, str)) {
            nickNames.push_back(str);
        }
        // close the file object.
        myfile.close();
    }
}

//Import Races From a File
void importRaces(){
fstream myfile;
    // open file
    myfile.open("Races.txt");

    if (myfile.is_open()) {
        // checking if the file is open
        string str;

        // read data from file object
        // and put it into string.
        while (getline(myfile, str)) {
            races.push_back(str);
        }
        // close the file object.
        myfile.close();
    }
}

//Delay the Input Text by Specified Int (In Milliseconds)
void textDelay(string sentence, int delay){
    vector<std::string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        wait(delay);
        cout << " " << word << flush;
    }
}

//Generate a Specialist
 void genSpecialist(){

    string job = select(jobList);
    string level = select(skillLevels);
    string bonus1;
    string bonus1Resource;
    string bonus2;
    string bonus2Resource;
    vector<string> resourceList = {"Food","Money","Crew","Wood","Metal","Research"};

    //Generate a Name
    if(roll(4) == 1){
        cout << endl << "NAME: " << select(names) << " \"" << select(nickNames) << "\" " << select(names) << endl;
    }else{
        cout << endl << "NAME: " << select(names) << " " << select(names) << endl;
    }
    cout << "DESC: " << level << " " << select(races) << " " << job  << endl;
    
    if(level == "Lousy"){
        bonus1 = "5%";
        bonus2 = "0%";
    }else if(level == "Trained"){
        bonus1 = "10%";
        bonus2 = "5%";
    }else if(level == "Skilled"){
        bonus1 = "15%";
        bonus2 = "10%";
    }else if(level == "Elite"){
        bonus1 = "20%";
        bonus2 = "15%";
    }

    if(job == "Guard" || job == "Soldier" || job == "Pirate"){
        bonus1Resource = select(resourceList);
        bonus2Resource = select(resourceList);
    }else if(job == "Farmer" || job == "Cook" || job == "Butcher"){
        bonus1Resource = "Food";
        bonus2Resource = select(resourceList);
    }else if(job == "Merchant" || job == "Trader" || job == "Tax Collector"){
        bonus1Resource = "Money";
        bonus2Resource = select(resourceList);
    }else if(job == "Diplomat" || job == "Negotiator" || job == "Prostitute"){
        bonus1Resource = "Crew";
        bonus2Resource = select(resourceList);
    }else if(job == "Lumberjack" || job == "Carpenter" || job == "Woodworker"){
        bonus1Resource = "Wood";
        bonus2Resource = select(resourceList);
    }else if(job == "Metalsmith" || job == "Junker" || job == "Scrapper"){
        bonus1Resource = "Metal";
        bonus2Resource = select(resourceList);
    }else if(job == "Scientist" || job == "Mage" || job == "Researcher"){
        bonus1Resource = "Research";
        bonus2Resource = select(resourceList);
    }

    if(level != "Lousy"){
        cout << "ROOM: " << bonus1 << " " << bonus1Resource << " Bonus" << endl;
        cout << "ROOM: " << bonus2 << " " << bonus2Resource << " Bonus" << endl;
    }else{
        cout << "ROOM: " << bonus1 << " " << bonus1Resource << " Bonus" << endl;
    }
    

 }

int main()
{

    importSettings();
    importNames();
    importNicknames();
    importRaces();

    if(settings[0] == "true"){
        speedUp = true;
    }else{
        speedUp = false;
    }

    if(settings[1] == "true"){
        suggestions = true;
    }else{
        suggestions = false;
    }

    if(settings[2] == "true"){
        hiddenFlag = true;
    }else{
        hiddenFlag = false;
    }

    if(settings[3] == "true"){
        evilDesc = true;
    }else{
        evilDesc = false;
    }

    //Generate random seed
    srand(time(0));


    while(travelLoop == true){

        //Roll for how many encounters there are to choose from
        int randNum = roll(4);

        //Set up the empty vectors
        //List of current encounters
        vector<string> curEncounters;
        //List of the current encounter's flavors
        vector<string> curFlavors;
        //List of which encounters are flagged hidden
        vector<string> curHidden;
        //List of how long it'll take to reach each encounter
        vector<int> travelTime;

        //For the number of encounters rolled, add everything to each specific list
        for(int i = 0; i < randNum; i++) {

            //Add the encounter to the vector
            string selection = select(encounters);
            curEncounters.push_back(selection);

            //Choose a flavor for each encounter
            //Case doesn't support strings :(
            if(selection == "Combat") {
                curFlavors.push_back(select(combat));
            }
            else if(selection == "Shop") {
                curFlavors.push_back(select(shop));
            }
            else if(selection == "Resource") {
                curFlavors.push_back(select(resource));
            }
            else if(selection == "Event") {
                curFlavors.push_back(select(event));
            }

            //If hiddenFlag is true, roll whether or not the flavor of the event is hidden
            if(hiddenFlag == true) {
                curHidden.push_back(select(hiddenChance));
            }
            //If hiddenFlag is false, all events will not be hidden
            else {
                curHidden.push_back("false");
            }

            //Randomize amount of time taken for travel
            travelTime.push_back(rand()%(21-7)+7);

        }


        //Choice area

        //Silly boat because I can
        cout << R"(               ':,`:,':,                
           __||_||_||_||__             
      ____["""""""""""""""]____        
     | '''''''''''''''''''' " /        
 ^~^~~^^~^~^~~^~^~^~^~^~^~^~^^~^~^~^~^^~ )" << endl;
        cout << "-----------------------------------------" << endl;
        wait(500);
        cout << "Where would you like to sail?" << endl;
        wait(1500);
        //Print each encounter choice
        for(int i = 0; i < randNum; i++) {
            //If the encounter is hidden, add a hidden tag
            if(curHidden[i] == "true") {
                cout << i+1 << ") " << curEncounters[i] << flush;
                wait(250);
                cout << ", " << curFlavors[i] << " (Hidden), " << flush;
                wait(250);
                cout << to_string(travelTime[i]) << " days" << endl;
            }
            //Else just print normally
            else {
                cout << i+1 << ") " << curEncounters[i] << flush;
                wait(250);
                cout << ", " << curFlavors[i] << ", " << flush;
                wait(250);
                cout << to_string(travelTime[i]) << " days" << endl;
            }
            wait(500);
        }
        //Decorative line
        cout << "-----------------------------------------" << endl;
        wait(1000);

        //Lock the user in until they choose a valid choice. DON'T PUT LETTERS
        //I didn't wanna go through the effort of idiot-proofing letters
        //You know better Chris
        bool choiceLoop = true;
        while(choiceLoop == true){
            int choice;
            cout << "> ";
            cin >> choice;

            if(choice-1 < 0 || choice-1 > curEncounters.size()-1){
                cout << "Not an option!" << endl;
            }else{
                choiceLoop = false;
                destination.push_back(curEncounters[choice-1]);
                destination.push_back(curFlavors[choice-1]);
                destination.push_back(to_string(travelTime[choice-1]));
                break;
            }
        }
        

        system("cls");

        //Load Bar
        cout << "Sailing" << flush;
        for(int i = 0; i < rand()%(7-3)+3; i++){
            wait(1450);
            cout << "." << flush;
        }
        cout << endl;

        //Incident check
        bool safeTravels = true;
        //Roll a d100
        int incident = roll(100);
        //If the roll is in the list of Evil Numbers, roll an Evil Event and disable Safe Message
        for(int num : evilNum){
            if(incident == num){
                cout << "\nCaptain." << endl;
                wait(2000);
                safeTravels = false;
                int evilEvent = roll(10);
                //evilEvent4();
                evilEvents[evilEvent-1]();
                string t;
                cout << "Continue?\n> ";
                cin >> t;
                system("cls");
                cout << "You made it to the " << destination[1] << " " << destination[0] << ", after " << destination[2] << " days." << endl;
                break;
            }
        }
        //Safe Message :)
        //You made it :)
        if(safeTravels == true){cout << "You made it to the " << destination[1] << " " << destination[0] << ", safely, after " << destination[2] << " days!" << endl;}

        wait(500);

        //Throw in suggestions for certain encounters here
        if(suggestions == true){
            if(destination[0] == "Event" && destination[1] == "Stranded Specialist"){
                cout << endl;
                cout << "You found: " << flush;
                genSpecialist();
            }else if(destination[0] == "Shop" && destination[1] == "Specialist"){
                for(int i = 0; i < 3; i++){
                    cout << endl;
                    cout << "You found: " << flush;
                    genSpecialist();
                    cout << endl;
                }
            }
        }

        //Ask to End or Roll Again
        string confirm;
        cout << "\nRoll Again? (y/n)" << endl;
        wait(1000);
        bool confirmLoop = true;
        while(confirmLoop == true){
            cout << "> ";
            cin >> confirm;
            if(confirm == "y" || confirm == "Y"){
                system("cls");
                destination.clear();
                confirmLoop = false;
                break;
            }else if(confirm == "n" || confirm == "N"){
                confirmLoop = false;
                travelLoop = false;
                break;
            }else{
                cout << "Not an option!" << endl;
            }
        }
        

        

    }       
    return 0;
}


//Siren Attack
void evilEvent1(){
    //Random part of the deck gets attacked by a Siren, with all rooms in a 1-room radius hearing the song
    //DC 13 Wisdom Save to not be hypnotized by the Siren's song
    //By the time the Captain becomes aware of the problem, everyone who's been hypnotized has already made it to the Siren's side, and will fight for them
    //You have 10 rounds to kill the Siren before it takes off, bringing everyone who fell under it's song with it
    //An Expedition may be launched to regain the stolen, if any, people
    if(evilDesc == true){
        cout << "Siren!" << endl;
    }
    else{
        cout << "Siren" << endl;
    }
    
}

//Kraken Attack
void evilEvent2(){
    //1d6+2 Tentacles attack randomly on the deck
    //You have 10 rounds to kill all the tentacles, before the ship takes 1HP damage for each remaining tentacle
    if(evilDesc == true){
        cout << "Kraken!" << endl;
    }
    else{
        cout << "Kraken" << endl;
    }
}

//Giant Rats Eat Your Food
void evilEvent3(){
    //2d6 Giant Rats appear in random rooms across the ship, and you have 10 rounds to kill all of them, otherwise, you lose 5% of your food for each remaining rat, lose 10% food 
    if(evilDesc == true){
        cout << "It's bad." << endl;
        wait(450);
        cout << "We've" << flush;
        textDelay("found holes in our food storage.",150);
        wait(300);
        cout << endl;
        cout << "It" << flush;
        textDelay("seems we've got rats somewhere on board,",250);
        wait(300);
        textDelay("the bad kind!",100);
        cout << endl;
        wait(300);
        cout << "We" << flush;
        textDelay("need to find them,",250);
        wait(450);
        textDelay("before it's too late!",500);
        cout << endl;
    }
    else{
        cout << "Giant Rats" << endl;
    }
    
}

//Dragon Recruitment
void evilEvent4(){
    //One of your specialists got an amazing job offer at your last stop, and has left your crew, along with 5%-25% of all your various resources. These resources and the specialist join the dragon's hoard, and can be regained if the dragon is defeated

    int percent = rand()%(25-5)+5;

    if(evilDesc == true){
        cout << "Better Job Offer!" << endl;
    }
    else{
        cout << "Better Job Offer" << endl;
    }

    cout << percent << "% loss of resources." << endl;

    

    
    
}

//Lost - Complete
void evilEvent5(){
    //You got lost at sea, rerolling your destination, and adding 1d4 days to your journey
    if(evilDesc == true){
        cout << " It's time to finally admit it." << flush;
        wait(1500);
        cout <<" You," << flush;
        wait(500);
        textDelay("have gotten us lost at sea.", 210);
        cout << endl;
        wait(1750);
        cout << "You've" << flush;
        textDelay("been sailing for days now,", 250);
        textDelay("with no sight of your destination in view.",150);
        wait(1000);
        cout << endl;
        cout << "Your" << flush;
        textDelay("crew is getting worried.",650);
        wait(2000);
        cout << endl;
        cout << "There" << flush;
        textDelay("is hope, however.",150);
        cout << endl;
        wait(1500);
        cout << "You've" << flush;
        textDelay("gotten reports of something on the horizon, Captain.",150);
        cout << endl;
        cout << "It" << flush;
        string description = "looks to be some sort of";
        string selection = select(encounters);
        if(selection == "Combat") {
            description += " " + select(combat);
        }
        else if(selection == "Shop") {
            description += " " + select(shop);
        }
        else if(selection == "Resource") {
            description += " " + select(resource);
        }
        else if(selection == "Event") {
            description += " " + select(event);
        }
        description += " " + selection + " Encounter, " + to_string(roll(4)) + " days out.";
        textDelay(description, 100);
        cout << endl;
        wait(1500);
        cout << "We" << flush;
        textDelay("must set sail.",1000);
        wait(2000);
        cout << endl;
    }
    else{
        cout << "Lost" << endl;
    }
    
}

//Madness/Sabotage
void evilEvent6(){
    //One of your specialists has gone mad! Either put them down, or find some way to negotiate/heal them, otherwise, the ship takes 3 damage, and the room the specialist was assigned to is damaged by 1 level
    if(evilDesc == true){
        cout << "Uh oh, Sabotage" << endl;
    }
    else{
        cout << "Sabotage" << endl;
    }

}

//Ghost - Complete
void evilEvent7(){
    //Roll a wisdom save, and get various levels of exhaustion for how bad you roll, these are in effect for the next node you land on
    //5 Levels: <0; 4 Levels: <5; 3 Levels: <10; 2 Levels: <15; 1 Level: <20; No levels: 20 or higher
    if(evilDesc == true){
        cout << "You've" << flush;
        textDelay("been getting reports of crew members seeing things at night.",150);
        wait(500);
        cout << endl;
        cout << "Hearing" << flush;
        textDelay("things,",250);
        wait(300);
        cout << " at night." << endl;
        wait(500);
        cout << "Unsettling " << flush;
        wait(400);
        cout << "things." << endl;
        wait(500);
        cout << "Haunting " << flush;
        wait(600);
        cout << "things." << endl;
        cout << "Things," << flush;
        wait(300);
        textDelay("that keep them up at night.",250);
        wait(500);
        cout << endl;
        cout << "Your" << flush;
        textDelay("crew is complaining about being unable to sleep,",150);
        wait(300);
        cout << " Captain." << endl;
        cout << "And now," << flush;
        wait(450);
        textDelay("as ghostly figures descend towards where you lay frozen on your bed,",175);
        wait(300);
        textDelay("you understand why.",250);
        cout << endl;
        wait(700);
        cout << "Something" << flush;
        textDelay("must be done about this,",200);
        wait(150);
        textDelay("before it gets worse.",500); 
        cout << endl;
        cout << endl;
    }
    else{
        cout << "Ghost" << endl;
    }
}

//Rot
void evilEvent8(){

    int percent = rand()%(25-5)+5;

    if(evilDesc == true){
        //Things are not looking good. You've just gotten a report that rot has been found spreading throughout your food stores. Thankfully, your crew caught it early, but you've already lost several days worth of food. The rot must be stopped before it can spread any further. What will you do, Captain?
        cout << "Rot" << endl;
    }
    else{
        cout << "Rot" << endl;
    }

    cout << percent << "% loss of food." << endl;
}

//Pirate Raid
void evilEvent9(){
    //2d4 pirate ships attack, with the pirates getting an ambush round if during night
    if(select(hiddenChance) == "true"){
        if(evilDesc == true){
            cout << "Pirate Raid Night" << endl;
        }
        else{
            cout << "Pirate Raid Night" << endl;
        }
    }else{
        if(evilDesc == true){
            //Things are not going well for you, at the moment. Everything was going fine, at first, until one of your deckhands ran into the bridge, shouting "Captain! Captain! Look! On the horizon! Quick!" You quickly begin scanning the horizon, until finally, you see them. 2d4 pirate ships sailing straight for you. There's no way out. It's a fight!
            cout << "Pirate Raid Day" << endl;
        }
        else{
            cout << "Pirate Raid Day" << endl;
        }
    }
}

//Iceberg - Complete
void evilEvent10(){
    //Need to succeed on a DC14 Dexterity Save or the ship will take 5 DMG
    if(evilDesc == true){
        cout << "You" << flush;
        textDelay("are woken from your slumber by a banging on your door.",150); 
        cout << endl;
        wait(1000);
        cout << "Muffled," << flush;
        textDelay("you hear",250);
        textDelay("\"Captain!",300); 
        textDelay("Captain!",300); 
        textDelay("Come quick! It's an emergency!\"",50); 
        textDelay("from outside your quarters.",250); 
        cout << endl;
        wait(550);
        cout << "Jolted" << flush;
        textDelay("awake, you rush outside,",200); 
        textDelay("running towards the bridge.",150); 
        cout << endl;
        wait(750);
        cout << "\"It's" << flush; 
        textDelay("an emergency Captain, we're heading straight for it!\"",100);
        cout << endl;
        cout << "\"It's" << flush; 
        textDelay("an iceberg, Captain,",50);
        wait(150);
        textDelay("appeared out of nowhere!",50);
        wait(250);
        textDelay("We're directly on course to hit it!\"",25);
        cout << endl;
        wait(700);
        cout << "\"You" << flush; 
        textDelay("need to take action,",150);
        textDelay("or we'll hit it!\"",500);
        cout << endl;
    }
    else{
        cout << "Iceberg" << endl;
    }
}



