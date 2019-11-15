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
        case 1:
            rentMaterial();
            return;
        case 2: // Manage clients
            manageClientsSelection(showManageClients());
            return;
        case 3: // Manage teachers
            manageTeachersSelection(showManageTeachers());
            return;
        case 4: //Manage activities
            manageActivitiesSelection(showManageActivities());
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

void Menu::rentMaterial() {
    string aux;
    int selected_client,selected_material;
    Time startTime, endTime;


    cout << "Which client want to rent equipment? Insert the corresponding key." << endl
         << endl;

    SUPSchool->viewClients(false);

    cout << endl;

    do {
        selected_client = readOption(0, Client::getLastID() - 1);

        if(selected_client == 0)
            return;
    } while(SUPSchool->clientIndex(selected_client) == -1);


    cout << "Which material does the client want to rent? " << endl << endl;

    SUPSchool->viewMaterial(false);


    do {
        selected_material = readOption(0, Material::getLastID() - 1);

        if(selected_material == 0)
            return;
    } while(SUPSchool->materialIndex(selected_material) == -1);


    do{
        cout << "Starting time(DD/MM/YYYY HH:MM):";
        getline(cin,aux);

        if(aux == "0")
            return;

        try{
            startTime = Time(aux);
            break;
        } catch (InvalidDate & e){
            cerr << e.getMsg();
        }

    } while (true);

    do{
        cout << "Ending time(DD/MM/YYYY  HH:MM):";
        getline(cin,aux);

        if(aux == "0")
            return;

        try{
            endTime = Time(aux);
            break;
        } catch (InvalidDate & e){
            cerr << e.getMsg();
        }

    } while (true);


    try{
        SUPSchool->rent(selected_material,selected_client,startTime,endTime);
    } catch(NonExistentClient & e){
        cerr << e;
    } catch(NonExistentMaterial & e) {
        cerr << e;
    } catch(alreadyInUse & e) {
        cerr << e;
    }

    cout << endl;
    pause();
}

// Client --------------------

int Menu::showManageClients() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Create a new client." << endl
         << "2) Change the information of a client." << endl
         << "3) Add funds." << endl
         << "4) Purchase gold card." << endl
         << "5) Remove an existent client." << endl
         << "6) Enroll a client in an activity." << endl
         << "7) Generate monthly report." << endl
         << "0) Go back" << endl
         << endl;

    return readOption(0, 7);
}



void Menu::manageClientsSelection(int selected) {
    int selected_client, selected_activity;
    double amount;
    Client* SelectedClient;

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
        case 3:
            cout << "Which client do you want to add funds to? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            do {
                selected_client = readOption(0, Client::getLastID() - 1);

                if(selected_client == 0)
                    return;
            } while(SUPSchool->clientIndex(selected_client) == -1);

            cout << "Current funds: " << SUPSchool->Clients[SUPSchool->clientIndex(selected_client)]->getBalance() << endl;

            cout << "How much do you want to add (Only positive amounts)? " << endl;

            amount = readOption(0.0, 1.79769e+308);

            SUPSchool->Clients[SUPSchool->clientIndex(selected_client)]->addBalance(amount);

            pause();
            return;
        case 4:
            cout << "Which client wants to purchase the gold card?" << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            do {
                selected_client = readOption(0, Client::getLastID() - 1);

                if(selected_client == 0)
                    return;
            } while(SUPSchool->clientIndex(selected_client) == -1);

            try{
                SUPSchool->Clients[SUPSchool->clientIndex(selected_client)]->purchaseGold();

            }

            catch(insufficientFunds &e){
                cerr << e;
            }

            catch(alreadyGoldMember &e){
                cerr << e;
            }

            pause();
            return;
        case 5:
            cout << "Which client do you want to remove?" << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            do {
                selected_client = readOption(0, Client::getLastID() - 1);

                if(selected_client == 0)
                    return;
            } while(SUPSchool->clientIndex(selected_client) == -1);

            try {
                SUPSchool->removeClient(selected_client);

            }

            catch(NonExistentClient &e){
                cerr << e;
            }

            pause();
            return;
        case 6:
            cout << "Insert the client ID: " << endl; //Make function to display the clients

            SUPSchool->viewClients(false);

            do {
                selected_client = readOption(0, Client::getLastID() - 1);

                if(selected_client == 0)
                    return;
            } while(SUPSchool->clientIndex(selected_client) == -1);

            cout << "Insert the activity ID: " << endl;
            selected_activity = readOption(0, SUPSchool->ScheduledActivities.size() - 1);

            try {
                SUPSchool->enroll(selected_client, selected_activity);
            }

            catch (clientAlreadHasActivity &e) {
                cerr << e;
            }

            catch (NonExistentClient &e) {
                cerr << e;
            }

            pause();
            return;
        case 7:
            cout << "Which gold member client wants to generate its monthly report? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewClients(false);

            cout << endl;

            selected_client = readOption(0, Client::getLastID() - 1);

            SelectedClient = SUPSchool->Clients[SUPSchool->clientIndex((selected_client))];

            if (!SelectedClient->isGoldMember()) {
                cerr << "Not gold member.";
                pause();
                return;
            }

            monthlyReport(SelectedClient);
            return;
        case 0:
            return;
    }
}

void Menu::createClient() {
    auto *c = new Client();
    string aux;
    stringstream activities;

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

    cout << "Which are the past activities of the new client (insert IDs separated by Space)? " << endl;
    cin.ignore();
    getline(cin, aux);
    activities << aux;

    cout << "Which are the scheduled activities of the new client (insert IDs separated by Space)? " << endl;
    cin.ignore();
    getline(cin, aux);
    activities << aux;

    SUPSchool->readClientsActivities(&activities, c);

    cout << endl;
    pause();
}

void Menu::monthlyReport(Client* C) {
    clearScreen();

    Time BeginDate = SUPSchool->currentTime;
    BeginDate.setDay(1);

    Time EndDate = SUPSchool->currentTime;

    vector<Activity*> MonthActivities = C->getScheduleActivitiesByDate(BeginDate, EndDate);

    cout << "The client " << C->getName() << " participated in the following activities during this month (" << BeginDate.getMonth() << '/' << BeginDate.getYear() << "): " << endl
         << endl;

    for (auto a : MonthActivities) {
        cout << *a
             << "---------------------" << endl;
    }

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

            do {
                selected_teacher = readOption(0, Teacher::getLastID() - 1);

                if(selected_teacher == 0)
                    return;
            }while(SUPSchool->teacherIndex(selected_teacher) == -1);

            changeTeachers(selected_teacher); //Needs to catch exception in client index inside function

            pause();
            return;
        case 3:
            cout << "Which client do you wish to remove? Insert the corresponding ID." << endl
                 << endl;

            SUPSchool->viewTeachers(false);

            cout << endl;

            do {
                selected_teacher = readOption(0, Teacher::getLastID() - 1);

                if(selected_teacher == 0)
                    return;
            } while(SUPSchool->teacherIndex(selected_teacher) == -1);

            try {
                SUPSchool->removeTeacher(selected_teacher);
            } catch(NonExistentTeacher &e){
                cout << e;
            }

            pause();
            return;
        case 4:
            cout << "Insert the teacher ID: " << endl; //Make function to display the clients

            SUPSchool->viewTeachers(false);

            do {
                selected_teacher = readOption(0, Teacher::getLastID() - 1);

                if(selected_teacher == 0)
                    return;
            } while(SUPSchool->teacherIndex(selected_teacher) == -1);

            cout << "Insert the activity ID: " << endl;
            SUPSchool->viewActivities(false);
            do {
                selected_activity = readOption(0, Activity::getLastID() - 1);

                if(selected_activity == 0)
                    return;
            }while(SUPSchool->activityIndex(selected_activity, false) == -1);

            try {
                SUPSchool->assign(selected_teacher, selected_activity);
            }

            catch (teacherAlreadHasActivity &e) {
                cerr << e;
            }

            catch (NonExistentTeacher &e) {
                cerr << e;

            } catch(activityNonExistent &e){

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

//Activity --------------------

int Menu::showManageActivities(){
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Create a new activity." << endl
         << "2) Remove an existent activity." << endl //Remove from everything
         << "0) Go back" << endl
         << endl;

    return readOption(0, 3);
}
void Menu::manageActivitiesSelection(int selected) {
    clearScreen();

    switch (selected) {
        case 1:
            createActivity();
            return;
        case 3:
            removeActivity();
            return;
        case 0:
            return;
    }
}
void Menu::createActivity() {
    //auto *a = new Activity();
    string aux;

    string name;
    string type;
    Time startTime;
    Time endTime;

    //Ask for name
    cout << "What's the name of the new activity? ";

    getline(cin, name);
    if(name[0] >= 97 && name[0] <= 122){
        name[0] -= 32;
    }

    //Ask for the type of activity
    cout << "Is it a ride (R) or a Lesson (L)? ";

    getline(cin, type);
    try {
        if (type != "R" && type != "L") {
            throw(ImproperString("Type isn't \"R\" nor \"L\".\n"));
        }
    }
    catch(ImproperString &i){
        cerr << i.getMsg();
        return;
    }

    //Ask for start date
    cout << endl << "What's the start date (DD/MM/YYYY HH:MM) of the activity? ";
    getline(cin, aux);

    try {
        startTime = Time(aux);
    }
    catch(InvalidDate &d){
        cerr << d.getMsg();
        return;
    }


    //Ask for end date
    cout << endl << "What's the end date (HH:MM) of the activity? ";
    getline(cin, aux);
    try {
        endTime = Time(aux);
    }
    catch(InvalidDate &d){
        cerr << d.getMsg();
        return;
    }

    //Check if it's a ride or lesson
    if(type == "R"){
        cout << "What's the cost of the Ride? ";
        getline(cin, aux);
        try{
            unsigned int cost = stoul(aux);
            auto* a = new Ride();
            a->setName(name);
            a->setStartTime(startTime);
            a->setEndTime(endTime);
            a->setCost(cost);
            SUPSchool->addActivity(a, false);
        }
        catch(exception &e){
            cerr << e.what();
            return;
        }
    }
    else if(type == "L"){
        try {
            auto *a = new Lesson();
            a->setName(name);
            a->setStartTime(startTime);
            a->setEndTime(endTime);
            SUPSchool->addActivity(a, false);
        }
        catch(exception &e){
            cerr << e.what();
            return;
        }
    }
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


    bool scheduled;

    int index = -1;
    //Check if ID exists
    try {
        for(int i = 0; i < SUPSchool->ScheduledActivities.size(); i++){
            if(SUPSchool->ScheduledActivities[i]->getId() == ID){
                index = i;
                scheduled = true;
            }
        }
        for(int e = 0; e < SUPSchool->PastActivities.size(); e++) {
            if (SUPSchool->PastActivities[e]->getId() == ID){
                index = e;
                scheduled = false;
            }
        }
        if(index == -1){
            throw IdAlreadyExists();
        }
    }
    catch(IdAlreadyExists &e){
        cerr << "ID doesn't exists.\n";
        return;
    }
    //Removing the activity from every client
    for(int i = 0; i < SUPSchool->getClients().size(); i++){
        if(!scheduled) {
            for (int e = 0; e < SUPSchool->getClients()[i]->getPastActivities().size(); e++) //Itera pelas atividades passadas dos clientes, remove-as a adiciona o dinheiro de volta se for uma ride
                if (SUPSchool->getClients()[i]->getPastActivities()[e]->getId() == ID) {
                    //SUPSchool->getClients()[i]->setActivities(eraseAndReturnVectorClient(SUPSchool->getClients()[i]->getScheduledActivities(), i));
                    //Make the materials used by the client unused
                    SUPSchool->getClients()[i]->setPastActivities(eraseAndReturnVectorActivity(SUPSchool->getClients()[i]->getPastActivities(), e)); //Algo está mal

                    //Add balance back to client, if and only if it's a ride (Don't do it if it's a past activity
                    //if(SUPSchool->PastActivities[index]->getType() == "R") {
                    //    SUPSchool->getClients()[i]->addBalance(SUPSchool->PastActivities[index]->CalcCost());
                    //}
                }
        }
        for(int j = 0; j < SUPSchool->getClients()[i]->getScheduledActivities().size(); j++){
            if(SUPSchool->getClients()[i]->getScheduledActivities()[j]->getId() == ID){
                SUPSchool->getClients()[i]->setScheduledActivities(eraseAndReturnVectorActivity(SUPSchool->getClients()[i]->getScheduledActivities(), j)); //Algo está mal

                //Add balance back to client, if and only if it's a ride
                if(SUPSchool->PastActivities[index]->getType() == "R") {
                    SUPSchool->getClients()[i]->addBalance(SUPSchool->PastActivities[index]->CalcCost());
                }
            }
        }

    }
    for(int mat = 0; mat < SUPSchool->getMaterials().size(); mat++){
        for(int ac = 0; ac < SUPSchool->getMaterials()[mat]->getActivities().size(); ac++){
            if(SUPSchool->getMaterials()[mat]->getActivities()[ac]->getId() == ID){
                SUPSchool->getMaterials()[mat]->setActivities(eraseAndReturnVectorActivity(SUPSchool->getMaterials()[mat]->getActivities(), ac));
            }
        }
    }
    if(scheduled){
        SUPSchool->ScheduledActivities.erase(SUPSchool->ScheduledActivities.begin() + index);
    }
    else{
        SUPSchool->PastActivities.erase(SUPSchool->PastActivities.begin() + index);
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
    Client* SelectedClient;
    Schedule<Client>* s1;
    Schedule<Teacher>* s2;
    vector<Time> PossibleDates;
    Time beginDate, endDate;
    bool first = true;

    clearScreen();

    switch (selected) {
        case 1:
            cout << "Which client's schedule do you wish to see? Insert the corresponding key." << endl
                 << endl;

            do {
                clearScreen();

                if (first) {
                    cout << "Which client's schedule do you wish to see? Insert the corresponding key." << endl
                         << endl;

                    first = false;
                }

                else
                    cerr << "The selected client doesn't have scheduled activities. Select another: " << endl
                         << endl;

                SUPSchool->viewClients(false);

                selected_client = readOption(0, Client::getLastID() - 1);
                client_index = SUPSchool->clientIndex(selected_client);

                SelectedClient = SUPSchool->Clients[client_index];

                PossibleDates = SUPSchool->getDatesFromActivicties(SelectedClient ->getScheduledActivities());
            } while (PossibleDates.empty());

            clearScreen();

            cout << "Which one is the begin date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            begin_date = readOption(0, PossibleDates.size());

            if (!begin_date)
                return;

            beginDate = PossibleDates[begin_date - 1];

            clearScreen();

            cout << "Which one is the end date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            end_date = readOption(0, PossibleDates.size());

            if (!end_date)
                return;

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

            selected_teacher = readOption(0, Teacher::getLastID() - 1);
            teacher_index = SUPSchool->teacherIndex(selected_teacher);

            clearScreen();

            PossibleDates = SUPSchool->getDatesFromActivicties(SUPSchool->Teachers[teacher_index]->getScheduledActivities());

            if (PossibleDates.empty()) {
                cerr << "The selected teacher doesn't have scheduled activities." << endl;
                return;
            }

            cout << "Which one is the begin date? Insert the corresponding key." << endl
                 << endl;

            SUPSchool->viewDates(PossibleDates);

            cout << endl;

            begin_date = readOption(0, PossibleDates.size());
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
}

void Menu::pause() {
    cout << "Press any key to continue ...";
    cin.get();
}





