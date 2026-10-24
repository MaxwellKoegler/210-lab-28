#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include<algorithm>
#include<numeric>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 5:
                trip.sort(); //sorts
                display_trip(trip);
                break;
            case 6:{
                string x;
                list<string> n;
                for(auto g:trip){
                    n.push_back(g.get_name());
                }
                cout << "Name";
                cin >> x;
                auto p = find(n.begin(),n.end(),x);//finds by name
                if(p!=n.end()){
                    cout << "Found " << *p << endl;
                } else {
                    cout << "Not found";
                }
                break;
            }
            case 7:{
                int a = accumulate(trip.begin(),trip.end(), 0, [](int s, Goat g){return s+g.get_age();}); //adds the member var
                cout << "Total age: " << a << endl;
                break;
            }
            case 8:{
                int x;
                cout << "Age: ";
                cin >> x;
                bool b = any_of(trip.begin(), trip.end(), [x](Goat g){return g.get_age()>x;}); //check goats ages
                if (b)
                    cout << "Some goats are older.\n";
                else
                    cout << "No goats are older.\n";
                break;
            }
            case 9:{
                for_each(trip.begin(), trip.end(), [](Goat g){cout << g.get_name()<<" "<<g.get_age() << " "<<g.get_color()<<endl;});//display goats
                break;
            }
            case 10:{
                int x=select_goat(trip);
                auto p=trip.begin();
                advance(p,x-1);
                trip.erase(p);//remove selected goat
                display_trip(trip);
                break;
            } case 11: {
                string x;
                string y;
                list<string> n;
                for(auto g:trip){
                    n.push_back(g.get_color());
                }
                cout << "Color to replace";
                cin >> x;
                cout << "New color: ";
                cin>>y;
                replace(n.begin(),n.end(),x,y); //color replacment 
                auto p=n.begin();
                for(auto &g:trip){
                    g.set_color(*p);
                    ++p;
                }
                display_trip(trip);
                break;
            } 
            case 12:{
                trip.sort();
                auto p=trip.begin();
                while(p!=trip.end()){
                    auto q=p;
                    ++q;
                    if(q!=trip.end() && p->get_name()==q->get_name()) //remove dup goats
                        trip.erase(q);
                    else
                        ++p;
                }
                display_trip(trip);
                break;
            }

        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "[5] Sort Goats\n";
    cout << "[6] Find goat by name\n";
    cout << "[7] Total goat ages\n";
    cout << "[8] Check goat ages\n";
    cout << "[9] Display goats with for_each\n";
    cout << "[10] Remove select goat\n";
    cout << "[11] Replace goat colors\n";
    cout << "[12] Remove duplicate goats\n";

    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}


int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}