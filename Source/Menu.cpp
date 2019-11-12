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
    //test -v
    int selected_client, client_index, begin_date, end_date;
    Schedule* s;
    vector<Time> PossibleDates;
    bool not_finished = true;
    Time beginDate, endDate;
    vector<Schedule> Schedules;

    switch (selected) {
        case 1:
            clearScreen();

            cout << "Which client's schedule do you wish to see? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            selected_client = readOption(0, Client::getLastID());
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

            s = new Schedule(beginDate, endDate, SUPSchool->Clients[client_index]);
            cout << *s << endl;

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



