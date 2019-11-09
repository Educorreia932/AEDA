#include "../Headers/Menu.h"

Menu::Menu(School SUPSchool) {
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
            manageTeachersSelection(showManageClients());
            return;
        case 5: // Consult clients
            SUPSchool.viewClients();
            pause();
            return;
        case 6:
            SUPSchool.viewStaff();
            pause();
            return;
        case 7: // Consult activities
            SUPSchool.viewActivities();
            pause();
            return;
        case 8: // Consult schedules
            consultScheduleSelection(showConsultSchedule());
            return;
        case 9: // Consult school's information
            cout << SUPSchool<< endl;
            pause();
            return;
        case 0:
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
         << "4) Enrole a client in an activity." << endl //<- and remove him from a planned activity
         << "0) Go back" << endl
         << endl;

    return readOption(0, 4);
}

void Menu::manageClientsSelection(int selected) {
    int selected_client, selected_activity;

    clearScreen();

    switch (selected) {
        case 2:
            cout << "Which client do you wish to change the information of? Insert the corresponding key." << endl
                 << endl;

            SUPSchool.viewClients(false);

            cout << endl;

            selected_client = readOption(0, SUPSchool.Clients[0]->getLastID());

            pause();
            return;
        case 4:
            cout << "Insert the client ID: " << endl; //Make function to display the clients
            selected_client = readOption(0, SUPSchool.Clients[0]->getLastID());

            cout << "Insert the activity ID: " << endl;
            selected_activity = readOption(0, SUPSchool.Activities.size());

            try {
                SUPSchool.enroll(selected_client, selected_activity);
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

    switch (selected) {

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
    //test -v
    int selected_client;
    int client_index;
    Schedule* s;

    switch (selected) {
        case 1:
            clearScreen();

            cout << "Which client's schedule do you wish to see? Insert the corresponding key." << endl
                 << endl;

            SUPSchool.viewClients(false);

            cout << endl;

            selected_client = readOption(0, SUPSchool.Clients[0]->getLastID());
            client_index = SUPSchool.clientIndex(selected_client);

            clearScreen();

            cout << "You're seeing the schedule of " << SUPSchool.Clients[client_index]->getName() << '.' << endl
                 << endl;

            s = new Schedule(SUPSchool.Clients[client_index]->getScheduledActivities());
            s->view(Time(18, 10, 2019), 30);

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
