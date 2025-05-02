
class Request {
public:
    int id;
    static int max;  // Static count variable for generating unique IDs
    string requester;  // The person who made the request to get money from someone else
    string sender;     // The person who received the request to send money to the requester
    float amount;      // The amount requested
    string date_time;  // The time the request was made


    Request() : id(max++), requester(""), sender(""), amount(0.0), date_time("") {}


    Request(string requester, string sender, float amount, string date_time)
        : id(max++), requester(requester), sender(sender), amount(amount), date_time(date_time) {}

    Request(int id, string requester, string sender, float amount, string date_time)
        : id(id), requester(requester), sender(sender), amount(amount), date_time(date_time) {
        if (id > max) {
            max = id + 1;
        }
        else if (id == max) {
            max++;
        }
    }

    bool operator==(const Request& other) const {
        return id == other.id &&
            sender == other.sender &&
            requester == other.requester &&
            amount == other.amount;
    }

};

// Initialize the static count variable
int Request::max = 0;