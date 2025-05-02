
class Wallet {
public:
	string currentUser;
	set<User> users;
	list<Transaction> trans;
	list<Request> requests;

	User* find_user(string username) {
		auto temp = users.find(User(username));
		if (temp != users.end())
			return const_cast<User*>(&(*temp));
		else
			return nullptr;
	}

	bool delete_user(string username) {
		User* temp = find_user(username);
		if (temp == nullptr) {
			return false;
		}
		users.erase(*temp);
		return true;
	}

	bool add_user(string username, string password, bool status, float balance, string phone) {
		User* temp = find_user(username);
		if (temp != nullptr) {
			return false;
		}

		users.insert(User(username, hash_password(password), status, balance, phone));
		return true;
	}

	bool check_user(string username, string password) {
		User* temp = find_user(username);
		if (temp == nullptr) {
			return false;
		}
		if (verify_password(password, temp->password)) {
			return true;
		}
		return false;
	}

	void display_user(string username) {
		User* user = find_user(username);
		cout << "\nUsername: " << user->username << endl;
		cout << "Status: " << user->status << endl;
		cout << "Balance: " << user->balance << endl;
		cout << "Phone: " << user->phone << endl;
		cout << "++++++++++++++++++++++++++" << endl;
	}

	bool edit(string username, string field, string value) {
		User* user = find_user(username);
		if (user == nullptr) {
			return false;
		}
		if (field == "password") {
			if (value.length() >= 1)
			user->password = hash_password(value);
			return true;
		}
		else if (field == "status") {
			user->status = string_to_bool(value);
			return true;
		}
		else if (field == "balance") {
			user->balance = stof(value);
			return true;
		}
		else if (field == "phone") {
			user->phone = value;
			return true;
		}
		return false;
		
	}

	bool make_trans(string sender, string recipient, float amount) {
		User* s = find_user(sender);
		User* r = find_user(recipient);
		if (s == nullptr || r == nullptr) {
			cout << "User(s) not found.\n";
			return false;
		}
		if (s->balance >= amount && s->status && r->status) {
			trans.push_back(Transaction(sender, recipient, amount, datetime_now()));
			s->balance -= amount;
			r->balance += amount;
			return true;
		}
		return false;
	}

	int get_all_users() {
		int n = 0;
		for (auto u : users) {
			display_user(u.username);
			cout << "Transactions: ";
			get_all_trans(u.username);

			cout << "**********************************" << endl;
			n++;
		}
		if (n == 0) {
			cout << "The wallet system doesn't have any users yet!";
		}
		return n;
	}

	void get_all_trans() {
		for (auto i : trans) {
			cout << "Transaction ID: " << i.id << endl;
			cout << "Sender: " << i.sender << endl;
			cout << "Recipient: " << i.recipient << endl;
			cout << "Amount: " << i.amount << endl;
			cout << "Time: " << i.date_time << endl;
			cout << "----------------------------" << endl;
		}
	}

	void get_all_trans(string username) {
		int n = 0;
		for (auto i : trans) {
			if (i.sender == username || i.recipient == username) {
				cout << "Transaction ID: " << i.id << endl;
				cout << "Sender: " << i.sender << endl;
				cout << "Recipient: " << i.recipient << endl;
				cout << "Amount: " << i.amount << endl;
				cout << "Time: " << i.date_time << endl;
				cout << "----------------------------" << endl;
				n++;
			}

		}
		if (n == 0) {
			cout << "No transactions transactions yet!" << endl;
		}
	}

	Request* find_requests(int id) {
		try {
			auto it = find_if(requests.begin(), requests.end(), [id](const Request& r) {
				return r.id == id; // Search by ID
				});

			if (it != requests.end()) {
				return &(*it);
			}
			else
				return nullptr;
		}
		catch (int err) {
			return nullptr;
		}

	}

	bool create_request(string requester, string sender, float amount) {
		User* req = find_user(requester);
		User* rec = find_user(sender);
		if (rec->balance >= amount && req->status && rec->status) {
			requests.push_back(Request(requester, sender, amount, datetime_now()));
			return true;
		}
		return false;
	}

	bool finalize_request(int id) {
		Request* request = find_requests(id);
		if (request == nullptr) {
			cout << "Request not found.\n";
			return false;
		}

		if (make_trans(request->sender, request->requester, request->amount)) {
			requests.remove(*request);
			return true;
		}
		else
			return false;
	}

	bool delete_request(int id) {
		Request* request = find_requests(id);
		if (request == nullptr) {
			cout << "Request not found.\n";
			return false;
		}
		requests.remove(*request);
		return true;
	}

	void get_all_requests() {
		for (auto i : requests) {
			cout << "Request ID: " << i.id << endl;
			cout << "Requester (Made the request): " << i.requester << endl;
			cout << "Recipient (Should send money): " << i.sender << endl;
			cout << "Amount: " << i.amount << endl;
			cout << "Time: " << i.date_time << endl;
			cout << "----------------------------" << endl;
		}
	}

	int get_all_requests(string username) {
		int n = 0;
		for (auto i : requests) {
			if (i.sender == username) {
				cout << "Request ID: " << i.id << endl;
				cout << "Requester (Made the request): " << i.requester << endl;
				cout << "Recipient (Should send money): " << i.sender << endl;
				cout << "Amount: " << i.amount << endl;
				cout << "Time: " << i.date_time << endl;
				cout << "----------------------------" << endl;
				n++;
			}
		}
		if (n == 0) {
			cout << "You don't have any requests currently!\n" << endl;
		}
		return n;
	}

	int n_requests(string username) {
		int n = 0;
		for (auto i : requests) {
			if (i.sender == username) {
				n++;
			}
		}
		return n;
	}

	bool save() {
		try {
			ofstream Users("users.txt");
			for (auto& x : users) {
				Users << x.username << "\t" << x.password << "\t" << x.status << "\t" << x.balance << "\t" << x.phone << endl;
			}
			Users.close();

			ofstream Trans("transactions.txt");
			for (auto& x : trans) {
				Trans << x.id << "\t" << x.sender << "\t" << x.recipient << "\t" << x.amount << "\t" << x.date_time << endl;
			}
			Trans.close();

			ofstream Requests("requests.txt");
			for (auto& x : requests) {
				Requests << x.id << "\t" << x.requester << "\t" << x.sender << "\t" << x.amount << "\t" << x.date_time << endl;
			}
			Requests.close();

			return true;
		}

		catch (int num) {
			cout << num << endl;
			return false;
		}
	}

	bool load() {

		try {
			string temp;
			ifstream Users("users.txt");
			vector<string> values;
			while (getline(Users, temp)) {

				values = getWords(temp);
				users.insert(User(values[0], values[1], string_to_bool(values[2]), stof(values[3]), values[4]));
			}

			Users.close();

			ifstream Trans("transactions.txt");
			while (getline(Trans, temp)) {

				values = getWords(temp);
				trans.push_back(Transaction(stoi(values[0]), values[1], values[2], stof(values[3]), values[4]));
			}

			Trans.close();

			ifstream Requests("requests.txt");
			while (getline(Requests, temp)) {

				values = getWords(temp);
				requests.push_back(Request(stoi(values[0]), values[1], values[2], stof(values[3]), values[4]));
			}

			Requests.close();

			return true;
		}
		catch (int num) {
			cout << num << endl;
			return false;
		}
	}

	vector<string> getWords(string s) {
		vector<string> res;
		string delim = "\t";
		string token = "";
		for (int i = 0; i < s.size(); i++) {
			bool flag = true;
			for (int j = 0; j < delim.size(); j++) {
				if (s[i + j] != delim[j]) flag = false;
			}
			if (flag) {
				if (token.size() > 0) {
					res.push_back(token);
					token = "";
					i += delim.size() - 1;
				}
			}
			else {
				token += s[i];
			}
		}
		res.push_back(token);
		return res;
	}

	string hash_password(const string& password) {
		char hashed[crypto_pwhash_STRBYTES];

		if (crypto_pwhash_str(
			hashed,
			password.c_str(),
			password.length(),
			crypto_pwhash_OPSLIMIT_INTERACTIVE,
			crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
			throw runtime_error("Password hashing failed (possibly out of memory)");
		}

		return string(hashed);
	}

	bool verify_password(const string& password, const string& hashed) {
		return crypto_pwhash_str_verify(
			hashed.c_str(),
			password.c_str(),
			password.length()) == 0;
	}

	bool string_to_bool(string string) {
		if (string == "true" || string == "1") {
			return true;
		}
		else if (string == "false" || string == "0") {
			return false;
		}
	}

	string datetime_now() {
		time_t now = time(0);
		char buffer[80];

		struct tm timeinfo;
		localtime_s(&timeinfo, &now);

		// Format time to "YYYY-MM-DD HH:MM:SS"
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

		return string(buffer);  // Return the formatted string
	}
};

