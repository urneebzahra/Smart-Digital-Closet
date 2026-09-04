#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// ============================================================
// BASE CLASS: ClothingItem
// ============================================================
class ClothingItem {
protected:
    string name;
    string color;
    string gender;
    int season;
    int occasion;
    string category;

public:
    ClothingItem() {}

    ClothingItem(string n, string col, string gen, int sea, int occ, string cat) {
        name = n; color = col; gender = gen;
        season = sea; occasion = occ; category = cat;
    }

    string getName()     { return name;     }
    string getColor()    { return color;    }
    string getGender()   { return gender;   }
    int    getSeason()   { return season;   }
    int    getOccasion() { return occasion; }
    string getCategory() { return category; }

    void setName(string n)   { name     = n; }
    void setColor(string c)  { color    = c; }
    void setGender(string g) { gender   = g; }
    void setSeason(int s)    { season   = s; }
    void setOccasion(int o)  { occasion = o; }

    string getSeasonText() {
        switch (season) {
            case 1: return "Summer";
            case 2: return "Winter";
            case 3: return "Both (Summer & Winter)";
            default: return "Unknown";
        }
    }

    string getOccasionText() {
        switch (occasion) {
            case 1: return "Wedding";
            case 2: return "Sports";
            case 3: return "Formal";
            case 4: return "Casual";
            case 5: return "Party";
            case 6: return "University";
            default: return "Unknown";
        }
    }

    virtual void displayItem() {
        cout << "  Name     : " << name              << endl;
        cout << "  Color    : " << color             << endl;
        cout << "  Gender   : " << gender            << endl;
        cout << "  Season   : " << getSeasonText()   << endl;
        cout << "  Occasion : " << getOccasionText() << endl;
        cout << "  Category : " << category          << endl;
    }

    virtual ~ClothingItem() {}
};

// ============================================================
// DERIVED CLASS 1: Upper
// ============================================================
class Upper : public ClothingItem {
private:
    string fabric;
public:
    Upper() {}
    Upper(string n, string col, string gen, int sea, int occ, string fab)
        : ClothingItem(n, col, gen, sea, occ, "Upper") { fabric = fab; }

    string getFabric()         { return fabric; }
    void   setFabric(string f) { fabric = f; }

    void displayItem() override {
        cout << "  [UPPER WEAR]" << endl;
        ClothingItem::displayItem();
        cout << "  Fabric   : " << fabric << endl;
    }
};

// ============================================================
// DERIVED CLASS 2: Lower
// ============================================================
class Lower : public ClothingItem {
private:
    string fabric;
public:
    Lower() {}
    Lower(string n, string col, string gen, int sea, int occ, string fab)
        : ClothingItem(n, col, gen, sea, occ, "Lower") { fabric = fab; }

    string getFabric()         { return fabric; }
    void   setFabric(string f) { fabric = f; }

    void displayItem() override {
        cout << "  [LOWER WEAR]" << endl;
        ClothingItem::displayItem();
        cout << "  Fabric   : " << fabric << endl;
    }
};

// ============================================================
// DERIVED CLASS 3: Shoes
// ============================================================
class Shoes : public ClothingItem {
private:
    string shoeType;
public:
    Shoes() {}
    Shoes(string n, string col, string gen, int sea, int occ, string sType)
        : ClothingItem(n, col, gen, sea, occ, "Shoes") { shoeType = sType; }

    string getShoeType()          { return shoeType; }
    void   setShoeType(string st) { shoeType = st; }

    void displayItem() override {
        cout << "  [SHOES]" << endl;
        ClothingItem::displayItem();
        cout << "  Shoe Type: " << shoeType << endl;
    }
};

// ============================================================
// GLOBAL STORAGE
// ============================================================
const int    MAX_ITEMS    = 100;
const string USERS_FILE   = "users.txt";
const string CLOTHES_FILE = "clothes.txt";

Upper  upperItems[MAX_ITEMS];
Lower  lowerItems[MAX_ITEMS];
Shoes  shoeItems[MAX_ITEMS];

int upperCount = 0;
int lowerCount = 0;
int shoeCount  = 0;

string currentUser = "";

// ============================================================
// UI HELPERS
// ============================================================
void printLine() { cout << "============================================================" << endl; }
void printDash() { cout << "------------------------------------------------------------" << endl; }

// ============================================================
// MATCHING HELPERS
// ============================================================
bool colorsMatch(string c1, string c2) {
    string lc1 = "", lc2 = "";
    for (char ch : c1) lc1 += tolower(ch);
    for (char ch : c2) lc2 += tolower(ch);

    if (lc1=="black"||lc1=="white"||lc1=="grey"||lc1=="gray"||
        lc2=="black"||lc2=="white"||lc2=="grey"||lc2=="gray") return true;
    if (lc1 == lc2) return true;
    if ((lc1=="navy"||lc1=="dark blue")&&(lc2=="white"||lc2=="beige"||lc2=="grey")) return true;
    if ((lc2=="navy"||lc2=="dark blue")&&(lc1=="white"||lc1=="beige"||lc1=="grey")) return true;
    if (lc1=="blue" &&(lc2=="beige"||lc2=="cream"||lc2=="khaki")) return true;
    if (lc2=="blue" &&(lc1=="beige"||lc1=="cream"||lc1=="khaki")) return true;
    if (lc1=="brown"&&(lc2=="beige"||lc2=="cream"||lc2=="white")) return true;
    if (lc2=="brown"&&(lc1=="beige"||lc1=="cream"||lc1=="white")) return true;
    if (lc1=="green"&&(lc2=="beige"||lc2=="khaki"||lc2=="cream")) return true;
    if (lc2=="green"&&(lc1=="beige"||lc1=="khaki"||lc1=="cream")) return true;
    if (lc1=="maroon"&&(lc2=="beige"||lc2=="white"||lc2=="cream")) return true;
    if (lc2=="maroon"&&(lc1=="beige"||lc1=="white"||lc1=="cream")) return true;
    return false;
}

bool shoeValid(string shoeType, int occasion) {
    string st = "";
    for (char ch : shoeType) st += tolower(ch);
    switch (occasion) {
        case 1: return (st=="formal"||st=="heels");
        case 2: return (st=="sports");
        case 3: return (st=="formal"||st=="heels");
        case 4: return (st=="casual"||st=="sandals"||st=="sports");
        case 5: return (st=="formal"||st=="heels"||st=="casual");
        case 6: return (st=="casual"||st=="sports");
        default: return false;
    }
}

// ============================================================
// FILE HANDLING
// ============================================================
string extractUser(const string& line) {
    int pipeCount = 0;
    string user = "";
    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == '|') {
            pipeCount++;
            if (pipeCount == 2) break;
        } else if (pipeCount == 1) {
            user += line[i];
        }
    }
    return user;
}

void saveClothesToFile() {
    string otherLines[MAX_ITEMS * 3];
    int otherCount = 0;

    ifstream readFile(CLOTHES_FILE);
    if (readFile.is_open()) {
        string line;
        while (getline(readFile, line)) {
            if (line.empty()) continue;
            if (extractUser(line) != currentUser)
                otherLines[otherCount++] = line;
        }
        readFile.close();
    }

    ofstream file(CLOTHES_FILE);
    if (!file.is_open()) {
        cout << "  [ERROR] Cannot open clothes file for saving." << endl;
        return;
    }

    for (int i = 0; i < otherCount; i++)
        file << otherLines[i] << "\n";

    for (int i = 0; i < upperCount; i++)
        file << "UPPER|" << currentUser << "|"
             << upperItems[i].getName()     << "|"
             << upperItems[i].getColor()    << "|"
             << upperItems[i].getGender()   << "|"
             << upperItems[i].getSeason()   << "|"
             << upperItems[i].getOccasion() << "|"
             << upperItems[i].getFabric()   << "\n";

    for (int i = 0; i < lowerCount; i++)
        file << "LOWER|" << currentUser << "|"
             << lowerItems[i].getName()     << "|"
             << lowerItems[i].getColor()    << "|"
             << lowerItems[i].getGender()   << "|"
             << lowerItems[i].getSeason()   << "|"
             << lowerItems[i].getOccasion() << "|"
             << lowerItems[i].getFabric()   << "\n";

    for (int i = 0; i < shoeCount; i++)
        file << "SHOES|" << currentUser << "|"
             << shoeItems[i].getName()     << "|"
             << shoeItems[i].getColor()    << "|"
             << shoeItems[i].getGender()   << "|"
             << shoeItems[i].getSeason()   << "|"
             << shoeItems[i].getOccasion() << "|"
             << shoeItems[i].getShoeType() << "\n";

    file.close();
}

void loadClothesFromFile() {
    upperCount = lowerCount = shoeCount = 0;

    ifstream file(CLOTHES_FILE);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        string fields[8];
        int fi = 0;
        string temp = "";
        for (int i = 0; i <= (int)line.size(); i++) {
            if (i == (int)line.size() || line[i] == '|') {
                if (fi < 8) fields[fi++] = temp;
                temp = "";
            } else temp += line[i];
        }
        if (fi < 8) continue;

        string type = fields[0], user = fields[1];
        string nm   = fields[2], col  = fields[3];
        string gen  = fields[4], last = fields[7];
        int sea = stoi(fields[5]);
        int occ = stoi(fields[6]);

        if (user != currentUser) continue;

        if      (type == "UPPER" && upperCount < MAX_ITEMS)
            upperItems[upperCount++] = Upper(nm, col, gen, sea, occ, last);
        else if (type == "LOWER" && lowerCount < MAX_ITEMS)
            lowerItems[lowerCount++] = Lower(nm, col, gen, sea, occ, last);
        else if (type == "SHOES" && shoeCount  < MAX_ITEMS)
            shoeItems[shoeCount++]   = Shoes(nm, col, gen, sea, occ, last);
    }
    file.close();
}

bool userExists(string username) {
    ifstream file(USERS_FILE);
    if (!file.is_open()) return false;
    string line;
    while (getline(file, line)) {
        string u = "";
        for (char ch : line) { if (ch == '|') break; u += ch; }
        if (u == username) { file.close(); return true; }
    }
    file.close(); return false;
}

bool verifyLogin(string username, string password) {
    ifstream file(USERS_FILE);
    if (!file.is_open()) return false;
    string line;
    while (getline(file, line)) {
        string f[2]; int fi = 0; string tmp = "";
        for (int i = 0; i <= (int)line.size(); i++) {
            if (i == (int)line.size() || line[i] == '|') {
                if (fi < 2) f[fi++] = tmp;
                tmp = "";
            } else tmp += line[i];
        }
        if (fi >= 2 && f[0] == username && f[1] == password) {
            file.close(); return true;
        }
    }
    file.close(); return false;
}

bool registerUser(string username, string password) {
    if (userExists(username)) return false;
    ofstream file(USERS_FILE, ios::app);
    if (!file.is_open()) return false;
    file << username << "|" << password << "\n";
    file.close(); return true;
}

// ============================================================
// AUTH MENUS
// ============================================================
bool signupMenu() {
    string username, password, confirm;
    printLine();
    cout << "            USER SIGNUP" << endl;
    printLine();
    cout << "  Enter Username : "; cin >> username;
    cout << "  Enter Password : "; cin >> password;
    cout << "  Confirm Pass   : "; cin >> confirm;

    if (password != confirm) {
        cout << "\n  [ERROR] Passwords do not match!" << endl; return false;
    }
    if (username.size() < 3 || password.size() < 4) {
        cout << "\n  [ERROR] Username >= 3 chars, Password >= 4 chars." << endl; return false;
    }
    if (registerUser(username, password)) {
        cout << "\n  [SUCCESS] Account created! You can now login." << endl; return true;
    }
    cout << "\n  [ERROR] Username already taken." << endl; return false;
}

bool loginMenu() {
    string username, password;
    printLine();
    cout << "             USER LOGIN" << endl;
    printLine();
    cout << "  Username : "; cin >> username;
    cout << "  Password : "; cin >> password;

    if (verifyLogin(username, password)) {
        currentUser = username;
        loadClothesFromFile();
        cout << "\n  [SUCCESS] Welcome, " << username << "!" << endl;
        return true;
    }
    cout << "\n  [ERROR] Invalid username or password." << endl;
    return false;
}

// ============================================================
// ADD FUNCTIONS
// ============================================================
void addUpper() {
    if (upperCount >= MAX_ITEMS) { cout << "  [ERROR] Upper wear storage is full!" << endl; return; }
    string name, color, gender, fabric; int season, occasion;
    printDash(); cout << "  ADD UPPER WEAR" << endl; printDash();
    cin.ignore(1000, '\n');
    cout << "  Item Name (e.g. Shirt, Kameez)          : "; getline(cin, name);
    cout << "  Color     (e.g. Blue, White, Black)     : "; getline(cin, color);
    cout << "  Gender    (Boys / Girls / Unisex)       : "; getline(cin, gender);
    cout << "  Fabric    (Cotton/Wool/Polyester/Silk)  : "; getline(cin, fabric);
    cout << "  Season    (1=Summer  2=Winter  3=Both)  : "; cin >> season;
    cout << "  Occasion  (1=Wedding 2=Sports 3=Formal\n"
            "             4=Casual  5=Party  6=Univ)   : "; cin >> occasion;
    upperItems[upperCount++] = Upper(name, color, gender, season, occasion, fabric);
    saveClothesToFile();
    cout << "\n  [SUCCESS] Upper wear added!" << endl;
}

void addLower() {
    if (lowerCount >= MAX_ITEMS) { cout << "  [ERROR] Lower wear storage is full!" << endl; return; }
    string name, color, gender, fabric;
	 int season, occasion;
    printDash(); 
	cout << "  ADD LOWER WEAR" << endl; 
	printDash();
    cin.ignore(1000, '\n');
    cout << "  Item Name (e.g. Jeans, Shalwar)         : "; 
	getline(cin, name);
    cout << "  Color     (e.g. Blue, Black, Beige)     : "; 
	getline(cin, color);
    cout << "  Gender    (Boys / Girls / Unisex)       : "; 
	getline(cin, gender);
    cout << "  Fabric    (Denim/Cotton/Wool/Polyester) : "; 
	getline(cin, fabric);
    cout << "  Season    (1=Summer  2=Winter  3=Both)  : "; 
	cin >> season;
    cout << "  Occasion  (1=Wedding 2=Sports 3=Formal\n"
            "             4=Casual  5=Party  6=Univ)   : "; 
	cin >> occasion;
    lowerItems[lowerCount++] = Lower(name, color, gender, season, occasion, fabric);
    saveClothesToFile();
    cout << "\n  [SUCCESS] Lower wear added!" << endl;
}

void addShoes() {
    if (shoeCount >= MAX_ITEMS) { cout << "  [ERROR] Shoes storage is full!" << endl; return; }
    string name, color, gender, shoeType; int season, occasion;
    printDash(); cout << "  ADD SHOES" << endl; printDash();
    cin.ignore(1000, '\n');
    cout << "  Item Name (e.g. Oxford, Nike Air)             : "; 
	getline(cin, name);
    cout << "  Color     (e.g. Black, White, Brown)          : "; 
	getline(cin, color);
    cout << "  Gender    (Boys / Girls / Unisex)             : "; 
	getline(cin, gender);
    cout << "  Shoe Type (Formal/Sports/Casual/Sandals/Heels): "; 
	getline(cin, shoeType);
    cout << "  Season    (1=Summer  2=Winter  3=Both)        : "; 
	cin >> season;
    cout << "  Occasion  (1=Wedding 2=Sports 3=Formal\n"
            "             4=Casual  5=Party  6=Univ)         : "; 
			cin >> occasion;
    shoeItems[shoeCount++] = Shoes(name, color, gender, season, occasion, shoeType);
    saveClothesToFile();
    cout << "\n  [SUCCESS] Shoes added!" << endl;
}

// ============================================================
// VIEW CLOSET
// ============================================================
void viewAllClothes() {
    printLine();
    cout << "          YOUR DIGITAL CLOSET" << endl;
    printLine();
    if (upperCount == 0 && lowerCount == 0 && shoeCount == 0) {
        cout << "  Your closet is empty! Add some clothes first." << endl; return;
    }
    if (upperCount > 0) {
        cout << "\n  === UPPER WEAR (" << upperCount << " items) ===" << endl;
        for (int i = 0; i < upperCount; i++) {
            printDash(); cout << "  Item #" << (i + 1) << endl;
            upperItems[i].displayItem();
        }
    }
    if (lowerCount > 0) {
        cout << "\n  === LOWER WEAR (" << lowerCount << " items) ===" << endl;
        for (int i = 0; i < lowerCount; i++) {
            printDash(); cout << "  Item #" << (i + 1) << endl;
            lowerItems[i].displayItem();
        }
    }
    if (shoeCount > 0) {
        cout << "\n  === SHOES (" << shoeCount << " items) ===" << endl;
        for (int i = 0; i < shoeCount; i++) {
            printDash(); cout << "  Item #" << (i + 1) << endl;
            shoeItems[i].displayItem();
        }
    }
    printLine();
    cout << "  Total: Upper=" << upperCount
         << "  Lower=" << lowerCount
         << "  Shoes=" << shoeCount << endl;
    printLine();
}

// ============================================================
// DELETE CLOTHING
// ============================================================
void deleteClothing() {
    printLine();
    cout << "          DELETE CLOTHING ITEM" << endl;
    printLine();

    if (upperCount == 0 && lowerCount == 0 && shoeCount == 0) {
        cout << "  Your closet is empty. Nothing to delete." << endl; return;
    }

    cout << "  Select category to delete from:" << endl;
    cout << "  1. Upper Wear  (" << upperCount << " items)" << endl;
    cout << "  2. Lower Wear  (" << lowerCount << " items)" << endl;
    cout << "  3. Shoes       (" << shoeCount  << " items)" << endl;
    cout << "  0. Back" << endl;
    printDash();
    cout << "  Choice: "; int catChoice; cin >> catChoice;
    if (catChoice == 0) return;

    if (catChoice == 1) {
        if (upperCount == 0) { cout << "  [INFO] No upper wear to delete." << endl; return; }
        cout << "\n  === UPPER WEAR ===" << endl;
        for (int i = 0; i < upperCount; i++) {
            printDash();
            cout << "  [" << (i+1) << "] " << upperItems[i].getName()
                 << " | " << upperItems[i].getColor()
                 << " | " << upperItems[i].getFabric() << endl;
        }
        printDash();
        cout << "  Enter item number to delete (0 to cancel): ";
        int num; cin >> num;
        if (num < 1 || num > upperCount) { cout << "  [ERROR] Invalid number." << endl; return; }
        cout << "\n  You are about to delete: " << upperItems[num-1].getName() << endl;
        cout << "  Are you sure? (1=Yes  0=No): ";
        int confirm; cin >> confirm;
        if (confirm != 1) { cout << "  Delete cancelled." << endl; return; }
        for (int i = num-1; i < upperCount-1; i++) upperItems[i] = upperItems[i+1];
        upperCount--;
        saveClothesToFile();
        cout << "  [SUCCESS] Item deleted successfully!" << endl;
    }
    else if (catChoice == 2) {
        if (lowerCount == 0) { cout << "  [INFO] No lower wear to delete." << endl; return; }
        cout << "\n  === LOWER WEAR ===" << endl;
        for (int i = 0; i < lowerCount; i++) {
            printDash();
            cout << "  [" << (i+1) << "] " << lowerItems[i].getName()
                 << " | " << lowerItems[i].getColor()
                 << " | " << lowerItems[i].getFabric() << endl;
        }
        printDash();
        cout << "  Enter item number to delete (0 to cancel): ";
        int num; cin >> num;
        if (num < 1 || num > lowerCount) { cout << "  [ERROR] Invalid number." << endl; return; }
        cout << "\n  You are about to delete: " << lowerItems[num-1].getName() << endl;
        cout << "  Are you sure? (1=Yes  0=No): ";
        int confirm; cin >> confirm;
        if (confirm != 1) { cout << "  Delete cancelled." << endl; return; }
        for (int i = num-1; i < lowerCount-1; i++) lowerItems[i] = lowerItems[i+1];
        lowerCount--;
        saveClothesToFile();
        cout << "  [SUCCESS] Item deleted successfully!" << endl;
    }
    else if (catChoice == 3) {
        if (shoeCount == 0) { cout << "  [INFO] No shoes to delete." << endl; return; }
        cout << "\n  === SHOES ===" << endl;
        for (int i = 0; i < shoeCount; i++) {
            printDash();
            cout << "  [" << (i+1) << "] " << shoeItems[i].getName()
                 << " | " << shoeItems[i].getColor()
                 << " | " << shoeItems[i].getShoeType() << endl;
        }
        printDash();
        cout << "  Enter item number to delete (0 to cancel): ";
        int num; cin >> num;
        if (num < 1 || num > shoeCount) { cout << "  [ERROR] Invalid number." << endl; return; }
        cout << "\n  You are about to delete: " << shoeItems[num-1].getName() << endl;
        cout << "  Are you sure? (1=Yes  0=No): ";
        int confirm; cin >> confirm;
        if (confirm != 1) { cout << "  Delete cancelled." << endl; return; }
        for (int i = num-1; i < shoeCount-1; i++) shoeItems[i] = shoeItems[i+1];
        shoeCount--;
        saveClothesToFile();
        cout << "  [SUCCESS] Item deleted successfully!" << endl;
    }
    else {
        cout << "  [ERROR] Invalid category choice." << endl;
    }
}

// ============================================================
// EDIT HELPERS 
// ============================================================

// askNewText: NO cin.ignore() inside.
// cin.ignore() is called ONCE before the first field in each edit block.
// This prevents the first character of every field from being eaten.
string askNewText(string prompt, string oldVal) {
    string newVal;
    cout << "  " << prompt << " [current: " << oldVal << "]: ";
    // NO cin.ignore() here — caller handles it once before first call
    getline(cin, newVal);
    if (newVal.empty()) return oldVal;   // Enter = keep old value
    return newVal;
}

int askNewInt(string prompt, int oldVal) {
    string input;
    cout << "  " << prompt << " [current: " << oldVal << "]: ";
    getline(cin, input);
    if (input.empty()) return oldVal;    // Enter = keep old value
    return stoi(input);
}

// ============================================================
// EDIT CLOTHING — FIXED
// ============================================================
void editClothing() {
    printLine();
    cout << "          EDIT CLOTHING ITEM" << endl;
    printLine();

    if (upperCount == 0 && lowerCount == 0 && shoeCount == 0) {
        cout << "  Your closet is empty. Nothing to edit." << endl; return;
    }

    cout << "  Select category to edit:" << endl;
    cout << "  1. Upper Wear  (" << upperCount << " items)" << endl;
    cout << "  2. Lower Wear  (" << lowerCount << " items)" << endl;
    cout << "  3. Shoes       (" << shoeCount  << " items)" << endl;
    cout << "  0. Back" << endl;
    printDash();
    cout << "  Choice: "; int catChoice; cin >> catChoice;
    if (catChoice == 0) return;

    if (catChoice == 1) {
        if (upperCount == 0) { cout << "  [INFO] No upper wear to edit." << endl; return; }
        cout << "\n  === UPPER WEAR ===" << endl;
        for (int i = 0; i < upperCount; i++) {
            printDash();
            cout << "  [" << (i+1) << "] " << upperItems[i].getName()
                 << " | " << upperItems[i].getColor()
                 << " | " << upperItems[i].getFabric() << endl;
        }
        printDash();
        cout << "  Enter item number to edit (0 to cancel): ";
        int num; cin >> num;
        if (num < 1 || num > upperCount) { cout << "  [ERROR] Invalid number." << endl; return; }

        int idx = num - 1;
        cout << "\n  Editing: " << upperItems[idx].getName() << endl;
        cout << "  (Press Enter to keep current value)\n" << endl;
        cin.ignore();
        string nm  = askNewText("New Name  ", upperItems[idx].getName());
        string col = askNewText("New Color ", upperItems[idx].getColor());
        string gen = askNewText("New Gender", upperItems[idx].getGender());
        string fab = askNewText("New Fabric", upperItems[idx].getFabric());
        cout << "  Season   (1=Summer 2=Winter 3=Both)" << endl;
        int sea = askNewInt("  Enter", upperItems[idx].getSeason());
        cout << "  Occasion (1=Wedding 2=Sports 3=Formal 4=Casual 5=Party 6=Univ)" << endl;
        int occ = askNewInt("  Enter", upperItems[idx].getOccasion());

        upperItems[idx].setName(nm);      upperItems[idx].setColor(col);
        upperItems[idx].setGender(gen);   upperItems[idx].setSeason(sea);
        upperItems[idx].setOccasion(occ); upperItems[idx].setFabric(fab);
        saveClothesToFile();
        cout << "\n  [SUCCESS] Item updated!" << endl;
        printDash(); upperItems[idx].displayItem();
    }
    else if (catChoice == 2) {
        if (lowerCount == 0) { cout << "  [INFO] No lower wear to edit." << endl; return; }
        cout << "\n  === LOWER WEAR ===" << endl;
        for (int i = 0; i < lowerCount; i++) {
            printDash();
            cout << "  [" << (i+1) << "] " << lowerItems[i].getName()
                 << " | " << lowerItems[i].getColor()
                 << " | " << lowerItems[i].getFabric() << endl;
        }
        printDash();
        cout << "  Enter item number to edit (0 to cancel): ";
        int num; cin >> num;
        if (num < 1 || num > lowerCount) { cout << "  [ERROR] Invalid number." << endl; return; }

        int idx = num - 1;
        cout << "\n  Editing: " << lowerItems[idx].getName() << endl;
        cout << "  (Press Enter to keep current value)\n" << endl;

        cin.ignore();
        string nm  = askNewText("New Name  ", lowerItems[idx].getName());
        string col = askNewText("New Color ", lowerItems[idx].getColor());
        string gen = askNewText("New Gender", lowerItems[idx].getGender());
        string fab = askNewText("New Fabric", lowerItems[idx].getFabric());
        cout << "  Season   (1=Summer 2=Winter 3=Both)" << endl;
        int sea = askNewInt("  Enter", lowerItems[idx].getSeason());
        cout << "  Occasion (1=Wedding 2=Sports 3=Formal 4=Casual 5=Party 6=Univ)" << endl;
        int occ = askNewInt("  Enter", lowerItems[idx].getOccasion());

        lowerItems[idx].setName(nm);      lowerItems[idx].setColor(col);
        lowerItems[idx].setGender(gen);   lowerItems[idx].setSeason(sea);
        lowerItems[idx].setOccasion(occ); lowerItems[idx].setFabric(fab);
        saveClothesToFile();
        cout << "\n  [SUCCESS] Item updated!" << endl;
        printDash(); lowerItems[idx].displayItem();
    }
    else if (catChoice == 3) {
        if (shoeCount == 0) { cout << "  [INFO] No shoes to edit." << endl; return; }
        cout << "\n  === SHOES ===" << endl;
        for (int i = 0; i < shoeCount; i++) {
            printDash();
            cout << "  [" << (i+1) << "] " << shoeItems[i].getName()
                 << " | " << shoeItems[i].getColor()
                 << " | " << shoeItems[i].getShoeType() << endl;
        }
        printDash();
        cout << "  Enter item number to edit (0 to cancel): ";
        int num; cin >> num;
        if (num < 1 || num > shoeCount) { cout << "  [ERROR] Invalid number." << endl; return; }

        int idx = num - 1;
        cout << "\n  Editing: " << shoeItems[idx].getName() << endl;
        cout << "  (Press Enter to keep current value)\n" << endl;

        cin.ignore();
        string nm  = askNewText("New Name     ", shoeItems[idx].getName());
        string col = askNewText("New Color    ", shoeItems[idx].getColor());
        string gen = askNewText("New Gender   ", shoeItems[idx].getGender());
        string stp = askNewText("New Shoe Type", shoeItems[idx].getShoeType());
        cout << "  Season   (1=Summer 2=Winter 3=Both)" << endl;
        int sea = askNewInt("  Enter", shoeItems[idx].getSeason());
        cout << "  Occasion (1=Wedding 2=Sports 3=Formal 4=Casual 5=Party 6=Univ)" << endl;
        int occ = askNewInt("  Enter", shoeItems[idx].getOccasion());

        shoeItems[idx].setName(nm);      shoeItems[idx].setColor(col);
        shoeItems[idx].setGender(gen);   shoeItems[idx].setSeason(sea);
        shoeItems[idx].setOccasion(occ); shoeItems[idx].setShoeType(stp);
        saveClothesToFile();
        cout << "\n  [SUCCESS] Item updated!" << endl;
        printDash(); shoeItems[idx].displayItem();
    }
    else {
        cout << "  [ERROR] Invalid category choice." << endl;
    }
}

// ============================================================
// RECOMMENDATION SYSTEM
// ============================================================
void recommendOutfits() {
    printLine();
    cout << "       OUTFIT RECOMMENDATION SYSTEM" << endl;
    printLine();

    if (upperCount == 0 || lowerCount == 0 || shoeCount == 0) {
        cout << "  [INFO] You need at least 1 Upper, 1 Lower, and 1 Pair of Shoes." << endl;
        return;
    }

    int targetOccasion, targetSeason;
    cout << "  Select Occasion:" << endl;
    cout << "  1=Wedding  2=Sports  3=Formal  4=Casual  5=Party  6=University" << endl;
    cout << "  Your choice: "; cin >> targetOccasion;
    cout << "\n  Select Season:  1=Summer  2=Winter  3=Both" << endl;
    cout << "  Your choice: "; cin >> targetSeason;

    int foundCount = 0;
    printLine();
    cout << "  RECOMMENDED OUTFITS" << endl;
    printLine();

    for (int u = 0; u < upperCount; u++) {
        for (int l = 0; l < lowerCount; l++) {
            for (int s = 0; s < shoeCount; s++) {
                if (upperItems[u].getOccasion() != targetOccasion) continue;
                if (lowerItems[l].getOccasion() != targetOccasion) continue;
                if (shoeItems[s].getOccasion()  != targetOccasion) continue;

                int uS = upperItems[u].getSeason();
                int lS = lowerItems[l].getSeason();
                int sS = shoeItems[s].getSeason();
                bool seasonOk = (uS==3||lS==3||sS==3) ||
                                (uS==targetSeason && lS==targetSeason && sS==targetSeason);
                if (!seasonOk) continue;

                if (!colorsMatch(upperItems[u].getColor(), lowerItems[l].getColor())) continue;
                if (!colorsMatch(lowerItems[l].getColor(), shoeItems[s].getColor()))  continue;
                if (!shoeValid(shoeItems[s].getShoeType(), targetOccasion))           continue;

                foundCount++;
                cout << "\n  >> OUTFIT #" << foundCount << " <<" << endl;
                printDash();
                cout << "  UPPER  : " << upperItems[u].getName()
                     << " (" << upperItems[u].getColor() << ", " << upperItems[u].getFabric() << ")\n";
                cout << "  LOWER  : " << lowerItems[l].getName()
                     << " (" << lowerItems[l].getColor() << ", " << lowerItems[l].getFabric() << ")\n";
                cout << "  SHOES  : " << shoeItems[s].getName()
                     << " (" << shoeItems[s].getColor() << ", " << shoeItems[s].getShoeType() << ")\n";
                cout << "  SEASON : " << upperItems[u].getSeasonText()   << endl;
                cout << "  FOR    : " << upperItems[u].getOccasionText() << " Occasion\n";
            }
        }
    }

    printLine();
    if (foundCount == 0) {
        cout << "  No matching outfits found." << endl;
        cout << "  Tips: Add items with matching occasions & seasons." << endl;
        cout << "        Use neutral colors (Black, White, Grey)." << endl;
    } else {
        cout << "  Total Outfits Found: " << foundCount << endl;
    }
    printLine();
}

// ============================================================
// MENUS
// ============================================================
void addClothingMenu() {
    int choice;
    printLine();
    cout << "       ADD CLOTHING TO YOUR CLOSET" << endl;
    printLine();
    cout << "  1. Add Upper Wear (Shirt, Kameez, Jacket...)" << endl;
    cout << "  2. Add Lower Wear (Jeans, Shalwar, Trousers...)" << endl;
    cout << "  3. Add Shoes" << endl;
    cout << "  0. Back" << endl;
    printDash();
    cout << "  Choice: "; cin >> choice;
    switch (choice) {
        case 1: addUpper(); break;
        case 2: addLower(); break;
        case 3: addShoes(); break;
        case 0: break;
        default: cout << "  [ERROR] Invalid choice." << endl;
    }
}

void closetMenu() {
    int choice;
    bool running = true;
    while (running) {
        printLine();
        cout << "          DIGITAL CLOSET MENU" << endl;
        cout << "          User: " << currentUser << endl;
        printLine();
        cout << "  1. Add Clothing"               << endl;
        cout << "  2. View My Closet"             << endl;
        cout << "  3. Edit a Clothing Item"       << endl;
        cout << "  4. Delete a Clothing Item"     << endl;
        cout << "  5. Get Outfit Recommendations" << endl;
        cout << "  0. Logout"                     << endl;
        printDash();
        cout << "  Choice: "; cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: addClothingMenu();  break;
            case 2: viewAllClothes();   break;
            case 3: editClothing();     break;
            case 4: deleteClothing();   break;
            case 5: recommendOutfits(); break;
            case 0:
                currentUser = "";
                running = false;
                cout << "  Logged out successfully." << endl;
                break;
            default:
                cout << "  [ERROR] Invalid option." << endl;
        }
        cout << endl;
    }
}

// ============================================================
// MAIN
// ============================================================
int main() {
    int choice;
    while (true) {
        printLine();
        cout << "   SMART DIGITAL CLOSET & OUTFIT RECOMMENDATION" << endl;
        printLine();
        cout << "  1. Login"  << endl;
        cout << "  2. Signup" << endl;
        cout << "  0. Exit"   << endl;
        printDash();
        cout << "  Choice: "; cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                if (loginMenu()) { cout << endl; closetMenu(); }
                break;
            case 2:
                signupMenu();
                break;
            case 0:
                printLine();
                cout << "  Thank you for using Smart Digital Closet!" << endl;
                printLine();
                return 0;
            default:
                cout << "  [ERROR] Invalid option." << endl;
        }
        cout << endl;
    }
    return 0;
}