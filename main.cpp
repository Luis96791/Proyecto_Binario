#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int tamano_registro=52;

class Player{
public:
    string username;
    string password;
    int credits, bwon, blost;
    Player(string username, string password, int credits, int bwon, int blost){
        this->username=username;
        this->password = password;
        this->credits = 0;
        this->bwon = 0;
        this->blost = 0;
    }
    void print(){
        cout<<"Username: "<<username<<" , "<<"Password: "<<password<<" , "<<"Credits: "<<credits<<" , "
        <<"Bwon: "<<bwon<<" , "<<"Blost: "<<blost<<endl;
    }
};

vector<Player>players;
string nombre_archivo = "players.txt";

bool searchPlayer(string username){
    for(int i =0; i < players.size(); i++){
        if(players[i].username==username){
            return true;
        }
    }
    return false;
}

vector<Player> cargarPlayers(){
    int cant_players;
     ifstream in(nombre_archivo.c_str());
     in.seekg(0,ios::end);
     cant_players = in.tellg()/tamano_registro;

     char user[20];
     char pass[20];
     int credit, bw, bl;

         for(int i = 0; i < cant_players; i++){
            in.read(user,20);
            in.read(pass,20);
            in.read((char*)&credit,4);
            in.read((char*)&bw,4);
            in.read((char*)&bl,4);
            players.push_back(Player(user,pass,credit,bw,bl));
         }
        in.close();
     return players;
}

void escribirArchivo(){
    ofstream out(nombre_archivo.c_str(),ios::in);
    out.clear();
    out.seekp(0,ios::beg);
     if(!out.is_open())
     {
         out.open(nombre_archivo.c_str());
     }

     for(int i =0; i < players.size(); i++){
         out.write((char*)&players[i].username,20);
         out.write((char*)&players[i].password,20);
         out.write((char*)&players[i].credits,4);
         out.write((char*)&players[i].bwon,4);
         out.write((char*)&players[i].blost,4);
     }
     out.close();
}

void escribirPlayer(string username, string password){
    if(!searchPlayer(username)){
        players.push_back(Player(username,password,0,0,0));
        escribirArchivo();
    }
}

void printPlayers(){
    for(int i = 0;i<players.size();i++){
        players[i].print();
    }
}

int main()
{
    cargarPlayers();
    int opc = 0;
    string us, pass;

    do{
        cout<<"1-. Agregar Player"<<endl;
        cout<<"2-. Leer Players"<<endl;
        cout<<"Escoja una Opcion: ";
        cin>>opc;

        switch(opc){
        case 1:
            cout<<"Ingrese Username: ";
            cin>>us;
            cout<<"Ingrese Password: ";
            cin>>pass;
            escribirPlayer(us,pass);
            break;
        case 2:
            printPlayers();
            break;
        }
    }while(opc != 0);
    return 0;
}
