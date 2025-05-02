
class Transaction {
public:
    int id;
    static int max;
    string sender;
    string recipient;
    float amount;
    string date_time;

    Transaction() : id(max++), sender(""), recipient(""), amount(0.0), date_time("") {}

    Transaction(string sender, string recipient, float amount, string date_time)
        : id(max++), sender(sender), recipient(recipient), amount(amount), date_time(date_time) {}

    Transaction(int id, string sender, string recipient, float amount, string date_time)
        : id(id), sender(sender), recipient(recipient), amount(amount), date_time(date_time) {
        if (id > max) {
            max = id + 1;
        }
        else if (id == max) {
            max++;
        }
    }
};

int Transaction::max = 0;