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
         << "7) Manage activities." << endl
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
        case 5:
            SUPSchool.viewClients();
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
    }
}

int Menu::showManageClients() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Create a new client." << endl
         << "2) Change the information of a client." << endl //<- perhaps ask for admin permission/password
         << "3) Remove an existent client." << endl
         << "4) Enrole a client in an activity." << endl //<- and remove him from a planned activity
         << "0) Go back" << endl
         << endl;

    return readOption(0, 4);
}

void Menu::manageClientsSelection(int selected) {
    int selected_client, selected_activity;

    clearScreen();

    switch(selected) {
        case 2:
            cout << "Which client do you wish to change the information of? Insert the corresponding key." << endl
                 << endl;

            SUPSchool.viewClients(false);

            cout << endl;

            selected_client = readOption(0, SUPSchool.Clients.size()); // <- Get Max ID
            pause();
            return;
        case 4:
            cout << "Insert the client ID: " << endl; //Make function to display the clients
            selected_client = readOption(0, SUPSchool.Clients.size());

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
    //SUPSchool.Clients[0]->setActivities(SUPSchool.getActivities());

    Schedule test(SUPSchool.Clients[0]->getScheduledActivities());

    switch (selected) {
        case 1:
            test.view(Time(18, 10, 2019), 30);
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
