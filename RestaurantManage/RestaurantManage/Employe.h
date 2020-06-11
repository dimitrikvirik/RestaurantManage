#pragma once
#ifndef __Employe_h_
#define __Employe_h_

#include <iostream>
#include <string>
#include <fstream>

#define dollar '$'

//გატესტიური Visual Studio 2019-ში//
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


//თანამშრომელის კლასი
class Employe {
protected:
	//მონაცემები//
	std::string name; //სახელი
	std::string id; //პირადი ნომერი
	char post; //თანამდებობა
	double salary; //ხელფასი
public:
	Employe(); //უპარამეტრო კონსტრუქტორი
	Employe(std::string name, std::string id, char post); //პარამეტრიანი კონსტრუქტორი
	Employe(std::ifstream& ifs);
	//ფუნქციები//
	virtual void print(std::ostream& out = std::cout) const; //ვირტუალური ფუნქცია დაბეჭდვა
	virtual ~Employe() = default;
	void set_salary(double salary); //ხელფასის დანიშნება
	char get_post() const; //პოსტის გაგება
	std::string get_id() const; //პირადობის გაგება
	virtual void  set_file(std::ifstream& ifs);
};
//მფლობელის კლასი
class Owner : public Employe {
public:
	Owner(); //უპარამეტრო კონსტრუქტორი
	Owner(std::string name, std::string  id); //პარამეტრიანი კონსტრუქტორი
	Owner(std::ifstream& ifs);
	//ფუნქციები//
	void print(std::ostream& out = std::cout) const override;
	~Owner() = default;
	void  set_file(std::ifstream& ifs) override;
};
//შეფის კლასი
class Chef : public Employe {
private:
	std::string expert; //რომელ დარგშია ექსპერტი
public:
	Chef(); //უპარამეტრო კონსტრუქტორი
	Chef(std::string name, std::string id, std::string expert); //პარამეტრიანი კონსტრუქტორი
	Chef(std::ifstream& ifs);
	//ფუნქციები//
	void print(std::ostream& out = std::cout) const override;
	void set_expert(std::string expert);
	~Chef() = default;
	void  set_file(std::ifstream& ifs) override;
};
//მიმტანის კლასი
class Waitress : public Employe {
private:
	unsigned internship; //სტაჟი თვეებში
public:
	Waitress(); //უპარამეტრო კონსტრუქტორი
	Waitress(std::string name, std::string id, unsigned internship); //პარამეტრიანი კონსტრუქტორი
	Waitress(std::ifstream& ifs);
	//ფუნქციები//
	void print(std::ostream& out = std::cout) const override;
	unsigned get_internship() const; //სტაჟი გამოტანა
	void set_internship(unsigned internship);
	~Waitress() = default;
	void  set_file(std::ifstream& ifs) override;
};
//**ოპერატორების გადატვირთვა**//
//შეტანა//
std::istream& operator>>(std::istream& in, Employe& emp); //თანამშრომელი
std::ifstream& operator>>(std::ifstream& ifs, Employe& emp);
//გამოტანა
std::ostream& operator<<(std::ostream& out, Employe& emp); //თანამშრომელი

///***იმპლემენტაცია***///

//**Employe Class**//

//კონსტრუქტორები
Employe::Employe() : name(""), id(""), post('N'), salary(0) {}
Employe::Employe(std::string name, std::string id, char post) : name(name), id(id), post(post), salary(0) {}
Employe::Employe(std::ifstream& ifs) {
	set_file(ifs);
}
//ფუნქციები//

//დაბეჭდვა
inline void Employe::print(std::ostream& out) const {
	std::string fullpost; //თანამდებობის სრული სახელი
	switch (post) {
	case 'O': fullpost = "Owner"; break;
	case 'C': fullpost = "Chef"; break;
	case 'W': fullpost = "Waitress"; break;
	case 'N': fullpost = "Not-Set"; break;
	}
	out << name << " Info: \n" <<
		"ID: " << id << std::endl <<
		"Post: " << fullpost << std::endl <<
		"Salary: " << salary << dollar << std::endl;
}
//ხელფასის დანიშვნა
inline void Employe::set_salary(double salary) {
	this->salary = salary;
}
//გეთერები//
char Employe::get_post() const {
	return post;
}
std::string Employe::get_id() const {
	return id;
}
//ფაილიდან ჩაწერა
void Employe::set_file(std::ifstream& ifs) {
	int check = 0;
	std::string InputText;
	salary = 0;
	post = 'N';
	while (ifs >> InputText) {
		switch (check)
		{
		case 0:
			if (InputText == "Owner") {
				post = 'O';
			}
			else if (InputText == "Chef") {
				post = 'C';
			}
			else if (InputText == "Waitress") {
				post = 'W';
			}
			break;
		case 1:
			name = InputText;
			break;
		case 2: case 3: break;
		case 4:
			id = InputText;
			return;
			break;
		}
		check++;
	}
}
//**Owner Class**//
Owner::Owner() : Employe("", "", 'O') {}
Owner::Owner(std::string name, std::string id) : Employe(name, id, 'O') {}
Owner::Owner(std::ifstream& ifs) {
	this->set_file(ifs);
}
//დაბეჭდვა
inline void Owner::print(std::ostream& out) const {
	out << BOLDRED << "Owner ";
	Employe::print(out);
	out << RESET << std::endl;
}
//ფაილიდან ჩაწერა
inline void Owner::set_file(std::ifstream& ifs) {
	Employe::set_file(ifs);
}
//**Chef Class**//

//კონსტრუქტორები
Chef::Chef() : Employe("", "", 'C') {} //უპარამეტრო კონსტრუქტორი
Chef::Chef(std::string name, std::string id, std::string expert) : Employe(name, id, 'C'), expert(expert) {} //პარამეტრიანი კონსტრუქტორი
Chef::Chef(std::ifstream& ifs) {
	this->set_file(ifs);
}
//ფუნქციები
void Chef::print(std::ostream& out) const {
	out << BOLDGREEN << "Chef ";
	Employe::print(out);
	out << "Expert: " << expert << std::endl << RESET << std::endl;
}
//ექსპერტის მნიშვნელობის შეცვლა
inline void Chef::set_expert(std::string expert) {
	this->expert = expert;
}

inline void Chef::set_file(std::ifstream& ifs) {
	Employe::set_file(ifs);
	int check = 0;
	std::string inputText;
	while (ifs >> inputText) {
		switch (check) {
		case 0: break;
		case 1:
			expert = inputText;
			return;
			break;
		}
		check++;
	}
}
//**Waitress Class**//

//კონსტრუქტორები
Waitress::Waitress() : Employe("", "", 'W'), internship(0) {} //უპარამეტრო კონსტრუქტორი
Waitress::Waitress(std::string name, std::string id, unsigned internship) : Employe(name, id, 'W'), internship(internship) {} //პარამეტრიანი კონსტრუქტორი
Waitress::Waitress(std::ifstream& ifs) {
	this->set_file(ifs);
}
//ფუნქციები
inline void Waitress::print(std::ostream& out) const {
	out << BOLDBLUE << "Waitress ";
	Employe::print(out);
	out << "Internship: " << internship << RESET << std::endl << std::endl;
}
//სტაჟირების გაგება
inline unsigned Waitress::get_internship() const {
	return internship;
}
//სტაჟირების შეცვლა
inline void Waitress::set_internship(unsigned internship) {
	this->internship = internship;
}
inline void Waitress::set_file(std::ifstream& ifs) {
	Employe::set_file(ifs);
	internship = 0;
	int check = 0;
	std::string inputText;
	while (ifs >> inputText) {
		switch (check) {
		case 0: break;
		case 1:
			internship = stoul(inputText);
			return;
			break;
		}
		check++;
	}
}
//**ოპერატორის გადატვირთვა**//
//შეტანა
inline std::ifstream& operator>>(std::ifstream& ifs, Employe& emp) {
	emp.set_file(ifs);
	return ifs;
}
inline std::istream& operator>>(std::istream& in, Employe& emp) {

	Employe* newEmp = 0;
	std::string name;
	std::string id;
	char post = 'N';
	std::string fullpost;
	unsigned internship;
	std::string expert;
	//ტიპის შემოწმება
	if (typeid(emp).name() == typeid(Owner).name()) {
		post = 'O';
		fullpost = "Owner";
	}
	else if (typeid(emp).name() == typeid(Chef).name()) {
		post = 'C';
		fullpost = "Chef";
	}
	else if (typeid(emp).name() == typeid(Waitress).name()) {
		post = 'W';
		fullpost = "Waitress";
	}
	//მომხმრაბელი შეჰყავს...
	std::cout << "Adding " << fullpost << " INFO: \n";
	std::cout << "Name: ";
	in >> name;
	std::cout << "ID: ";
	in >> id;
	//იქმნება გარკვეული ტიპი
	if (post == 'C') {
		std::cout << "Expert: ";
		in >> expert;
		newEmp = new Chef(name, id, expert);
	}
	else if (post == 'W') {
		std::cout << "Internship: ";
		in >> internship;
		newEmp = new Waitress(name, id, internship);
	}
	else if (post == 'O') {
		newEmp = new Employe(name, id, 'O');
	}
	else {
		newEmp = new Employe(name, id, 'N');
	}

	emp = *newEmp;
	std::cout << std::endl;
	if (post == 'W') {
		static_cast<Waitress&>(emp).set_internship(internship);
	}
	if (post == 'C') {
		static_cast<Chef&>(emp).set_expert(expert);
	}
	return in;
}
inline std::ifstream& operator>>(std::ifstream& ifs, Employe& emp) {
	emp.set_file(ifs);
	return ifs;
}
//გამოტანა
inline std::ostream& operator<<(std::ostream& out, Employe& emp) {
	emp.print(out);
	return out;
}
#endif // !__Employe_h_
