#include "../Headers/Menu.h"

Menu::Menu(School* SUPSchool) {
    this->SUPSchool = SUPSchool;
}

int Menu::showMainMenu() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Rent material." << endl
         << "2) Manage clients." << endl
         << "3) Manage teachers." << endl
         << "4) Manage activities." << endl
         << "5) Consult clients." << endl
         << "6) Consult teachers." << endl
         << "7) Consult activities." << endl
         << "8) Consult schedules." << endl
         << "9) Consult school's information." << endl
         << "0) Exit" << endl //And save to files
         << endl;

    return readOption(0, 9);
}

void Menu::mainMenuSelection(int selected) {
    clearScreen();

    switch (selected) {
        case 2: // Manage clients
            manageClientsSelection(showManageClients());
            return;
        case 3: // Manage teachers
            manageTeachersSelection(showManageTeachers());
            return;
        case 4: //Manage activities
            manageActivitiesSelection(showManageActivities());
            pause();
        case 5: // Consult clients
            SUPSchool->viewClients();
            pause();
            return;
        case 6: // Consult teachers
            SUPSchool->viewTeachers();
            pause();
            return;
        case 7: // Consult activities
            SUPSchool->viewActivities();
            pause();
            return;
        case 8: // Consult schedules
            consultScheduleSelection(showConsultSchedule());
            return;
        case 9: // Consult school's information
            cout << *SUPSchool<< endl;
            pause();
            return;
        default:
            cout << "NOT IMPLEMENTED YET" << endl;
            pause();
            return;
    }
}

// Client --------------------

int Menu::showManageClients() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Create a new client." << endl
         << "2) Change the information of a client." << endl //<- perhaps ask for admin permission/password
         << "3) Remove an existent client." << endl //<- Remove all information associated with him
         << "4) Enroll a client in an activity." << endl //<- and remove him from a planned activity
         << "0) Go back" << endl
         << endl;

    return readOption(0, 4);
}

void Menu::manageClientsSelection(int selected) {
    int selected_client, selected_activity;

    clearScreen();

    switch (selected) {
        case 1:
            createClient();
            return;
        case 2:
            cout << "Which client do you wish to change the information of? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            selected_client = readOption(0, Client::getLastID() - 1);

            pause();
            return;
        case 4:
            cout << "Insert the client ID: " << endl; //Make function to display the clients
            selected_client = readOption(0, Client::getLastID() - 1);

            cout << "Insert the activity ID: " << endl;
            selected_activity = readOption(0, SUPSchool->Activities.size() - 1);

            try {
                SUPSchool->enroll(selected_client, selected_activity);
            }

            catch (clientAlreadHasActivity &e) {
                cerr << e;
            }

            catch (NonExistantClient &e) {
                cerr << e;
            }

            pause();
            return;
        case 0:
            return;
        default:
            cout << "NOT IMPLEMENTED YET" << endl;
    }
}

void Menu::createClient() {
    auto *c = new Client();
    string aux;
    stringstream aux_stream;

    cout << "What's the name of the new client? " << endl;
    getline(cin, aux);
    c->setName(aux);
    cout << endl;

    cout << "Is the new client a gold member (Y/N)? " << endl;
    cin >> aux;
    cout << endl;

    c->setGoldMember(aux == "Y");

    try {
        SUPSchool->addClient(c);
    }

    catch (ClientAlreadyExists &e) {
        cout << e;
        pause();
    }

    cout << "Which are the scheduled activities of the new client (insert IDs separated by Space)? " << endl;
    cin.ignore();
    getline(cin, aux);
    aux_stream << aux;

    SUPSchool->readClientsActivities(&aux_stream, c);

    cout << endl;
    pause();
}

// Teacher --------------------

int Menu::showManageTeachers() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Create a new teacher." << endl
         << "2) Change the information of a teacher." << endl //<- perhaps ask for admin permission/password
         << "3) Remove an existent teacher." << endl //<- Remove all information associated with him
         << "4) Designate a lesson to a teacher." << endl
         << "0) Go back" << endl
         << endl;

    return readOption(0, 4);
}

void Menu::manageTeachersSelection(int selected) {
    clearScreen();

    int selected_teacher, selected_activity;

    switch (selected) {
        case 1:
            createTeacher();
            return;
        case 2:
            cout << "Which teacher do you wish to change the information of? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewTeachers(false);

            cout << endl;

            selected_teacher = readOption(0, Teacher::getLastID() - 1);

            changeTeachers(selected_teacher); //Needs to catch exception in client index inside function

            pause();
            return;
        case 3:
            cout << "Which client do you wish to remove? Insert the corresponding ID." << endl
                 << endl;

            SUPSchool->viewTeachers(false);

            cout << endl;

            selected_teacher = readOption(0, Teacher::getLastID() - 1);

            try {
                SUPSchool->removeTeacher(selected_teacher);
            }catch(NonExistantTeacher &e){
                cout << e;
            }

            pause();
            return;
        case 4:
            cout << "Insert the teacher ID: " << endl; //Make function to display the clients

            SUPSchool->viewTeachers(false);
            selected_teacher = readOption(0, Teacher::getLastID() - 1);

            cout << "Insert the activity ID: " << endl;
            SUPSchool->viewActivities(false);
            selected_activity = readOption(0, Activity::getLastID() - 1);

            try {
                SUPSchool->assign(selected_teacher, selected_activity);
            }

            catch (teacherAlreadHasActivity &e) {
                cerr << e;
            }

            catch (NonExistantTeacher &e) {
                cerr << e;

            } catch(activityNonExistant &e){

                cerr << e;
            }

            pause();
            return;
        case 0:
            return;
        default:
            cout << "NOT IMPLEMENTED YET" << endl;
    }
}

void Menu::createTeacher() {
    auto *t = new Teacher();
    string aux;
    stringstream aux_stream;

    cout << "What's the name of the new teacher? " << endl;
    getline(cin, aux);
    t->setName(aux);
    cout << endl;


    try {
        SUPSchool->addTeacher(t);
    }

    catch (TeacherAlreadyExists &e) {
        cout << e;
        pause();
    }

    cout << "Which are the scheduled activities of the new teacher(insert IDs separated by Space)? " << endl;
    cin.ignore();
    getline(cin, aux);
    aux_stream << aux;

    SUPSchool->readTeachersActivities(&aux_stream, t);

    cout << endl;
    pause();
}

void Menu::changeTeachers(int teacherId) {

    cout << "What information do you want to change? Insert the corresponding key." << endl
         << endl
         << "1) Change the teacher name" << endl
         << "0) Go back" << endl
         << endl;

    int selected_option = readOption(0, 4);
    string aux;

    switch (selected_option) {
        case 1:
            cout << "What's the name of the new teacher? " << endl;
            getline(cin, aux);
            SUPSchool->Teachers[SUPSchool->teacherIndex(teacherId)]->setName(aux);
            cout << endl;
            break;
        case 0:
            return;

    }
}


int Menu::showManageActivities(){
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Create a new activity." << endl
         << "2) Change the information of a activity." << endl
         << "3) Remove an existent activity." << endl //Remove from everything
         << "0) Go back" << endl
         << endl;

    return readOption(0, 3);
}


void Menu::manageActivitiesSelection(int selected) {
    clearScreen();

    switch (selected) {
        case 1:
            createActivity();
        case 2:
            removeActivity();
        case 0: return;
    }
}

void Menu::createActivity(){

    cout << "Add Activity:" << endl << endl;
    cout << "Name " << endl;
    string thing;
    string name;
    getline(cin, name);
    cout << "Start Date (DD/MM/YYYY HH:MM) " << endl;
    getline(cin, thing);
    string currentDatePart = "";
    int streamPhase = 0;
    int date[5] = {};
    try { //Parsing strings
        cout << "Date: " << endl;
        for (int i = 0; i < thing.length(); i++) {
            if (thing[i] == '/') {
                if (streamPhase < 2) {
                    date[streamPhase] = stoi(currentDatePart);
                    streamPhase++;
                    currentDatePart = "";
                } else {
                    throw ImproperString("Too many forward slashes in date\n.");
                }
            } else if (thing[i] == ' ') {
                if(streamPhase == 2){
                    date[streamPhase] = stoi(currentDatePart);
                    streamPhase++;
                    currentDatePart = "";
                }
                else{
                    throw ImproperString("Too many spaces in date\n.");
                }
            } else if (thing[i] == ':') {
                if(streamPhase == 3){
                    date[streamPhase] = stoi(currentDatePart);
                    streamPhase++;
                    currentDatePart = "";
                }
                else{
                    throw ImproperString("Too many colons in date\n.");
                }
            }
            else if (!isdigit(thing[i])){
                throw ImproperString("Non number included in date\n.");
            }
            else{
                currentDatePart += thing[i];
            }
        }
        date[4] = stoi(currentDatePart);
    }
    catch(ImproperString &s){
        cerr << s.getMsg();
        cin.ignore(1000, '\n');
    }
    int date2[5] ={};
    date2[0] = date[0];
    date2[1] = date[1];
    date2[2] = date[2];

    cout << "End Date (HH:MM) " << endl;
    streamPhase = 3;
    getline(cin, thing);
    currentDatePart = "";
    try{
        for(int i = 0; i < thing.length(); i++){
            if(thing[i] == ':'){
                if(streamPhase < 4){
                    date2[streamPhase] = stoi(currentDatePart);
                    streamPhase++;
                    currentDatePart = "";
                }
                else{
                    throw ImproperString("Too many colons in string.\n");
                }
            }
            else if(!isdigit(thing[i])){
                throw ImproperString("Invalid symbol in string.\n");
            }
            else{
                currentDatePart += thing[i];
            }
        }
        date2[4] = stoi(currentDatePart);
    }
    catch(ImproperString &e){
        cerr << e.getMsg();
    }
    //Setting times and creating activities
    //Activity *ac;
    try{
        Time t1(date[0], date[1], date[2], date[3], date[4]);
        Time t2(date2[0], date2[1], date2[2], date2[3], date2[4]);
        Activity a(t1, t2, name);
        SUPSchool->addActivity(&a);
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
        cout << (*SUPSchool->getActivities()[7]) << endl;
    }
    catch(InvalidActivity &e){
        cerr << e.getMsg();
    }
    cin.ignore(1000, '\n');
}


void Menu::removeActivity() {
    string IDstring;
    cout << "Insert ID of the activity:\n";
    cin >> IDstring;

    //Checking if IDstring is a number
    try{
        for(int i = 0; i < IDstring.size(); i++){
            if(!isdigit(IDstring[i])){
                throw(ImproperString("Not a number.\n"));
            }
        }
    }
    catch(ImproperString &e){
        cerr << e.getMsg();
    }

    //Convert IDstring to int
    int ID = stoi(IDstring);


    int index = -1;
    //Check if ID already exists
    try {
        for(int i = 0; i < SUPSchool->Activities.size(); i++){
            if(SUPSchool->Activities[i]->getId() == ID){
                index = i;
            }
        }
        if(index == -1){
            throw IdAlreadyExists();
        }
    }
    catch(IdAlreadyExists &e){
        cerr << "ID already exists.\n";
    }
    //Removing the activity
    for(int i = 0; i < SUPSchool->getClients().size(); i++){
        if(SUPSchool->getClients()[i]->getId() == ID){
            SUPSchool->getClients()[i]->setActivities(eraseAndReturnVector(SUPSchool->getClients()[i]->getScheduledActivities(), i));
            //Make the materials used by the client unused
        }
    }


}

// Schedule --------------------

int Menu::showConsultSchedule() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) View a client's schedule." << endl
         << "2) View a teacher's schedule." << endl
         // << "3) View school's schedule." << endl
         << "0) Go back." << endl
         << endl;

    return readOption(0, 2);
}

void Menu::consultScheduleSelection(int selected) {
    int selected_client, selected_teacher, client_index, teacher_index, begin_date, end_date;
    Schedule<Client>* s1;
    Schedule<Teacher>* s2;
    vector<Time> PossibleDates;
    Time beginDate, endDate;

    clearScreen();

    switch (selected) {
        case 1:
            cout << "Which client's schedule do you wish to see? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            selected_client = readOption(0, SUPSchool->Clients[0]->getLastID() - 1);
            client_index = SUPSchool->clientIndex(selected_client);

            clearScreen();

            PossibleDates = SUPSchool->getDatesFromActivicties(SUPSchool->Clients[client_index]->getScheduledActivities());

            cout << "Which one is the begin date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            begin_date = readOption(1, PossibleDates.size());
            beginDate = PossibleDates[begin_date - 1];

            clearScreen();

            cout << "Which one is the end date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            end_date = readOption(1, PossibleDates.size());
            endDate = PossibleDates[end_date - 1];

            clearScreen();

            cout << "You're seeing the schedule of " << SUPSchool->Clients[client_index]->getName() << '.' << endl
                 << endl;

            s1 = new Schedule<Client>(beginDate, endDate, SUPSchool->Clients[client_index]);
            cout << *s1 << endl;

            pause();
            return;
        case 2:
            cout << "Which teacher's schedule do you wish to see? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewTeachers(false);

            cout << endl;

            selected_teacher = readOption(0, SUPSchool->Teachers[0]->getLastID() - 1);
            teacher_index = SUPSchool->teacherIndex(selected_teacher);

            clearScreen();

            PossibleDates = SUPSchool->getDatesFromActivicties(SUPSchool->Teachers[teacher_index]->getScheduledActivities());

            cout << "Which one is the begin date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            begin_date = readOption(1, PossibleDates.size());
            beginDate = PossibleDates[begin_date - 1];

            clearScreen();

            cout << "Which one is the end date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            end_date = readOption(1, PossibleDates.size());
            endDate = PossibleDates[end_date - 1];

            clearScreen();

            cout << "You're seeing the schedule of " << SUPSchool->Teachers[teacher_index]->getName() << '.' << endl
                 << endl;

            s2 = new Schedule<Teacher>(beginDate, endDate, SUPSchool->Teachers[teacher_index]);
            cout << *s2 << endl;

            pause();
            return;
        case 0:
            return;
    }
}

// Utils --------------------

void Menu::clearScreen() {
    #ifdef __unix__
        system("clear");
    #endif

    #ifdef _WIN32
        system("cls");
    #endif

    //cout << string( 100, '\n' );
}

void Menu::pause() {
    cout << "Press any key to continue ...";
    cin.get();
}



