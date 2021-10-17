#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isComment(const string &line)
{
    for (int i = 0; i < line.size(); i++){
        if (line[i] == ' '){
            continue;
        }
        else if (line[i] == '/' && line[i + 1] == '/') {
            return true;
        }
        return false;
    }
    return false;
}

int isCommentInStorage(const vector<string>& storage, const string &line) {
    for (int i = 0; i < storage.size(); i++)
    {
        if (storage[i] == line) {
            return i;
        }
    }
    return -1;
}

void searchCommentsInFile(const string name, vector<int> &firstOccurence, vector<int> &amountOfOccurence, vector<string> &comments)
{
    ifstream input(name);
    if (!input.is_open()){
        cout << "File can not be open\n";
        input.close();
        return;
    }
    string line;
    int currentString = 0;
    while (getline(input, line)){
        currentString++;
        if (isComment(line)) {
            int position = isCommentInStorage(comments, line);
            if (position < 0) {
                comments.push_back(line);
                firstOccurence.push_back(currentString);
                amountOfOccurence.push_back(1);
            }else{
                amountOfOccurence[position]++;
            }
        }
    }
    input.close();
}

void writeCommentsInFile(const string name, const vector<string>& comments, const vector<int>& firstOccurence, const vector<int>& amountOfOccurence) {
    ofstream output(name);
    if (!output.is_open()) {
        output.close();
        cout << "File can not be open\n";
        return;
    }
    for (int i = 0; i < comments.size(); i++) {
        output << firstOccurence[i] << " | " << amountOfOccurence[i] << " | " << comments[i] << "\n";
    }
    output.close();
}

void printFileInConsole(string name)
{
    ifstream in(name);
    string line;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << "\n";
        }
    }else{
        cout << "File can not be found\n";
    }
    in.close();
}

void callMenu()
{
    cout << "1 - Print file content\n";
    cout << "2 - Search Comments in file\n";
    cout << "3 - Fill Comments in file\n";
    cout << "0 - Exit\n";
}

int main()
{
    callMenu();
    int state;
    vector<string> comments;
    vector<int> amountOfOccurence;
    vector <int> firstOccurence;
    string fileName;
    cin >> state;
    while (state != 0) {
        switch (state)
        {
        case 1:
            cout << "Print file Name\n";
            cin >> fileName;
            printFileInConsole(fileName);
            cin >> state;
            break;
        case 2:
            cout << "Print file Name, where you will search comments\n";
            cin >> fileName;
            searchCommentsInFile(fileName, firstOccurence, amountOfOccurence, comments);
            cin >> state;
            break;
        case 3:
            cout << "Print file Name, where you will write comments\n";
            cin >> fileName;
            writeCommentsInFile(fileName, comments, firstOccurence, amountOfOccurence);
            cin >> state;
            break;
        case 0:
            return -1;
        default:
            break;
        }
    }
}

