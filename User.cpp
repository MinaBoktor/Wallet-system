class User {
public:
    string username;
    string password;
    bool status;
    float balance;
    string phone;

    // Default constructor
    User() : username(""), password(""), status(true), balance(0.0), phone("") {}

    // One parameter constructor
    User(string name) : username(name), password(""), status(true), balance(0.0), phone("") {}

    // Parameterized constructor
    User(string uname, string pass, bool stat, float bal, string ph)
        : username(uname), password(pass), status(stat), balance(bal), phone(ph) {}


    // Comparison operators (for use in BST)
    bool operator<(const User& other) const {
        return username < other.username;
    }

    bool operator==(const User& other) const {
        return username == other.username;
    }

    // Stream output operator
    friend ostream& operator<<(ostream& os, const User& u) {
        os << u.username;
        return os;
    }
};