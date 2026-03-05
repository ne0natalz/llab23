#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size(); i++) y[i] = toupper((unsigned char)x[i]);
    return y;
}

static inline string trim(const string &s){
    size_t l = 0, r = s.size();
    while(l < r && isspace((unsigned char)s[l])) l++;
    while(r > l && isspace((unsigned char)s[r-1])) r--;
    return s.substr(l, r - l);
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename.c_str());
    if(!fin) return;

    string line;
    while(getline(fin, line)){
        if(line.empty()) continue;

        size_t pos = line.find(':');
        if(pos == string::npos) continue;

        string name = trim(line.substr(0, pos));
        string rest = trim(line.substr(pos + 1));

        int a = 0, b = 0, c = 0;
        vector<string> parts;
        string cur;
        for(char ch : rest){
            if(isspace((unsigned char)ch)){
                if(!cur.empty()){
                    parts.push_back(cur);
                    cur.clear();
                }
            }else{
                cur.push_back(ch);
            }
        }
        if(!cur.empty()) parts.push_back(cur);
        if(parts.size() < 3) continue;

        try{
            a = stoi(parts[0]);
            b = stoi(parts[1]);
            c = stoi(parts[2]);
        }catch(...){
            continue;
        }

        int total = a + b + c;
        char g = score2grade(total);

        names.push_back(name);
        scores.push_back(total);
        grades.push_back(g);
    }
    fin.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    if(!(cin >> command)){
        command = "EXIT";
        key = "";
        return;
    }

    string temp;
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE"){
        getline(cin, temp);
        key = trim(temp);
        if(key.empty()){
            key = "";
        }
    }else{
        getline(cin, temp);
        key = "";
    }
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    cout << "---------------------------------\n";
    if(key.empty()){
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
        return;
    }

    char g = toupper((unsigned char)key[0]);
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        if(toupper((unsigned char)grades[i]) == g){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}