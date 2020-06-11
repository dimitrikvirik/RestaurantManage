#pragma once
#ifndef __Restaurant__
#define __Restaurant__
#include "Employe.h"

//მთავარი კლასი, რომელიც შეიცავს თანამშრომელთა სიას
class Restaurant
{
private:
	//***მონაცემები****//

	//ზოგადი ინფორმაცია
	std::string name; // დასახელება
	std::string adresss; //მისამართი
	//თანამშრომელთა რაოდენება
	unsigned owners; //მფლობელების 
	unsigned chefs; //შეფების
	unsigned waiters; //მიმტანების
	//თანამშრომელთა ხელფასი - ფიქსირებული
	double ownerSalary; //მფლობელების 
	double chefSalary; //შეფების
	double waitressSalary; //მიმტანების
	//თანამშრომელთა ხელფასი - პროცენტული
	double ownerPerc; //მფლობელების 
	double chefPerc; //შეფების
	double SumInternship; //ყველა მიმტანის ჯამური სტაჟი
	//შემოსავლები
	double income; //არა სუფთა შემოსავალი
	double incomeNet; //სუფთა შემოსავალი
	double tips; //ფეხის ქილა(ჩაი)
	//გასავალები
	double utility; //კომუნალურის
	double rent; //ქირის

	//***სია****//

	//Node კლასი
	class Node {
	public:
		Employe* emp; //თანამშრომელი
		Node* back; //უკანა თანამშრომელი
		Node* next; //შემდეგი თანამშრომელი
		//პარამეტრიანი კონსტრუქტორი
		Node(Employe& emp, Node* nextLink, Node* backLink) : emp(&emp), next(nextLink), back(backLink) {}
		//კავშირის შესაცვლელი ფუნქცია
		void ChangeLink(Node* nextLink, Node* backLink) {
			this->back = backLink;
			this->next = nextLink;
		}
	};
	typedef  Node* NodePtr;
	NodePtr FirstPtr;
	NodePtr LastPtr;

	//**ფუნქციები**//
	//ხელფასების განახლება
	void UpdateSalary();
public:
	Restaurant(); //უპარამეტრო კონსტრუქტორი
	//პარამეტრიანი კონსტრუქტორი - შეყვანით
	Restaurant(std::string name, std::string adress,
		int ownerSalary, int chefSalary, int waitressSalary,
		int ownerPerc,
		int income, int tips,
		int utility, int rent
	);
	//პარამეტრიანი კონსტრუქტორი - ფაილით
	Restaurant(std::ifstream& ifs);
	//დესტრუქტორი
	~Restaurant();
	///***ფუნქციები***//
	//შექმნა ფაილით
	void set_file(std::ifstream& ifs);
	//არის თუ არა თანამშრომელი//
	bool empty();
	double size();
	//დამატება
	void addEmploye(Employe& emp);
	void addEmploye(const std::string& filename);
	//წაშლა კონკრეტულის
	void removeById(const std::string& id);
	//თანამშრომლების წაშლა
	void clearEmploye();
	//დაბეჭდვა
	void print(std::ostream& out = std::cout);
};
//**ოპერატორის გადატვირთვა**//
std::istream& operator>>(std::istream& in, Restaurant& rest); //რესტორანი
std::ifstream& operator>>(std::ifstream& ifs, Restaurant& rest);//რეტორანი ფაილით
//გამოტანა
std::ostream& operator<<(std::ostream& out, Restaurant& rest);
/***იმპლემენტაცია***///


//კონსტრუქტორები//
Restaurant::Restaurant() : FirstPtr(0), LastPtr(0){}
Restaurant::Restaurant(std::string name, std::string adress,
	int ownerSalary, int chefSalary, int waitressSalary,
	int ownerPerc,
	int income, int tips,
	int utility, int rent
) : name(name), adresss(adress),
ownerSalary(ownerSalary), chefSalary(chefSalary), waitressSalary(waitressSalary),
ownerPerc(ownerPerc), chefPerc(100 - ownerPerc),
income(income), tips(tips),
utility(utility), rent(rent), FirstPtr(0), LastPtr(0), SumInternship(0),
owners(0), chefs(0), waiters(0), incomeNet(0)
{}
//პარამეტრიანი კონსტრუქტორი - ფაილით
Restaurant::Restaurant(std::ifstream& ifs) {
	set_file(ifs);
}
//დესტრუქტორი
Restaurant::~Restaurant() {
	clearEmploye();
}
//**ფუნქციები PRIVATE**//
//ხელფასის განახლება
inline void Restaurant::UpdateSalary() {
	incomeNet = income - (ownerSalary * owners + chefSalary * chefs + waitressSalary * waiters + rent + utility); //სუფთა ხელფასი
	double RealSalary = 0; //ნამდვილი ხელფასი
	for (NodePtr ptr = FirstPtr; ptr != 0; ptr = ptr->next) {
		switch (ptr->emp->get_post()) {
		case 'O':  RealSalary = ownerSalary + incomeNet * (ownerPerc / owners) / 100; break; //მფლობელი
		case 'C': RealSalary = chefSalary + incomeNet * (chefPerc / chefs) / 100.; break; //შეფი
		case 'W': RealSalary = waitressSalary + tips * dynamic_cast<Waitress&>(*ptr->emp).get_internship() / SumInternship; //მიმტანი
			break; 
		case 'N': RealSalary = 0; break;
		}
		ptr->emp->set_salary(RealSalary);
	}
}
//**ფუნქციები PUBLIC**//
inline void Restaurant::set_file(std::ifstream& ifs) {
	FirstPtr = LastPtr = 0;
	SumInternship = owners = chefs = waiters = incomeNet = 0;
	std::string InputText;
	std::ifstream ifo;
	Owner ow;
	Chef cf;
	Waitress wt;
	int check = 0;
	while (ifs >> InputText) {
		switch (check) {
		case 0: break;
		case 1: name = InputText; break;
		case 3: adresss = InputText; break;
		case 7: ownerSalary = stod(InputText); break;
		case 11: chefSalary = stod(InputText); break;
		case 15: waitressSalary = stod(InputText); break;
		case 20: ownerPerc = stod(InputText); chefPerc = 100 - ownerPerc; break;
		case 22: income = stod(InputText); break;
		case 24: tips = stod(InputText); break;
		case 26: utility = stod(InputText); break;
		case 28: rent = stod(InputText); break;
		case 29: addEmploye(InputText); break;
		case 30: addEmploye(InputText); break;
		case 31: addEmploye(InputText); break;
		}
		check++;
	}
}
//შემოწმებები
inline bool Restaurant::empty() {
	return FirstPtr == 0;
}
inline double Restaurant::size() {
	return owners + chefs + waiters;
}
//თანამშრომელის დამატება
inline void Restaurant::addEmploye(Employe& emp) {
	//რაოდენობის გაზრდა
	switch (emp.get_post()) {
	case 'O':  owners++; break;
	case 'C': chefs++; break;
	case 'W': waiters++; SumInternship += static_cast<Waitress*>(&emp)->get_internship();  break;
	}
	//სიაში დამატება
	if (empty()) {
		FirstPtr = new Node(emp, 0, 0);
		LastPtr = FirstPtr;
	}
	else if (size() == 2) {
		LastPtr = new Node(emp, 0, FirstPtr);
		FirstPtr->ChangeLink(LastPtr, 0);
	}
	else {
		LastPtr = new Node(emp, 0, LastPtr);
		LastPtr->back->ChangeLink(LastPtr, LastPtr->back->back);
	}
	UpdateSalary(); //ხელფასების განახლება
}
 //დამატება თანამშრომელის - ფაილის სახელთ
inline  void Restaurant::addEmploye(const std::string& filename) {
	 if (filename == "waitress.txt") {
		 std::ifstream ifsn(filename);
		 while (ifsn.peek() != EOF) {
			 addEmploye(*(new Waitress(ifsn)));
		 }
	 }
	 else if (filename == "chefs.txt") {
		 std::ifstream ifsn(filename);

		 while (ifsn.peek() != EOF) {
			 addEmploye(*(new Chef(ifsn)));
		 }
	 }
	 else if (filename == "owner.txt") {
		 std::ifstream ifsn(filename);
		 while (ifsn.peek() != EOF) {
			 addEmploye(*(new Owner(ifsn)));
		 }
	 }

 }
//თანამშრომელის ამოშლა სიიდან პირადი ნომერით
inline void Restaurant::removeById(const std::string& id) {
	NodePtr ptr = 0;
	for (ptr = FirstPtr; ptr != 0; ptr = ptr->next) {
		if (ptr->emp->get_id() == id) {
			//თუ ემთხვევა წავშალოთ
			ptr->back->ChangeLink(ptr->next, ptr->back->back);
			delete ptr;
			return; // ფუნქციიდან გამოსვლა
		}
	}
}
//გასუფთავება
void Restaurant::clearEmploye() {
	bool StaqueEmpty = !empty();
	NodePtr ptr = FirstPtr;
	while (ptr != 0) {
		ptr = FirstPtr->next;
		delete FirstPtr;
		FirstPtr = ptr;
	}
	LastPtr = 0;
	FirstPtr = 0;
}
//დაბეჭდვა
inline void Restaurant::print(std::ostream& out) {
	UpdateSalary();
	out << "Restaurant " << name << " INFO: \n" <<
		"Adress: " << adresss << std::endl <<
		owners << " Owner's Fixed Salary: " << ownerSalary << dollar << std::endl <<
		chefs << " Chef's Fixed Salary: " << chefSalary << dollar << std::endl <<
		waiters << " Waitress's Fixed Salary: " << waitressSalary << dollar << std::endl <<
		"Income: " << income << dollar << std::endl <<
		"Net Income: " << incomeNet << dollar << std::endl <<
		"Tips: " << tips << dollar << std::endl <<
		"Utility: " << utility << dollar << std::endl <<
		"Rent: " << rent << dollar << std::endl << std::endl << "Employe's INFORMATION: \n\n";

	for (NodePtr ptr = FirstPtr; ptr != 0; ptr = ptr->next) {
		if (ptr->emp->get_post() == 'O')
		out << *ptr->emp;
	}
	for (NodePtr ptr = FirstPtr; ptr != 0; ptr = ptr->next) {
		if (ptr->emp->get_post() == 'C')
			out << *ptr->emp;
	}
	for (NodePtr ptr = FirstPtr; ptr != 0; ptr = ptr->next) {
		if (ptr->emp->get_post() == 'W')
			out << *ptr->emp;
	}
}
//**ოპერატორის გადატვირთვა**//
//რესოტარინის შექმნა 
inline std::istream& operator>>(std::istream& in, Restaurant& rest) {
	std::cout << "\tAdding New Restaurant: \n";
	Restaurant* newRest;
	std::string name; std::string adress;
	int ownerSalary, chefSalary, waitressSalary,
		ownerPerc,
		income, tips,
		utility, rent;
	//მომხმრაბელის შეჰყავს..
	std::cout << "\tName: ";
	getline(in, name);
	std::cout << "\tAdress: ";
	getline(in, adress);
	std::cout << "\tOwner's Fixed Salary: ";
	in >> ownerSalary;
	std::cout << "\tChef's Fixed Salary: ";
	in >> chefSalary;
	std::cout << "\tWaitress's Fixed Salary: ";
	in >> waitressSalary;
	std::cout << "\tOwner Percant Salary: ";
	in >> ownerPerc;
	std::cout << "\tIncome: ";
	in >> income;
	std::cout << "\tTips: ";
	in >> tips;
	std::cout << "\tUtility: ";
	in >> utility;
	std::cout << "\tRent: ";
	in >> rent;
	//იქმნება თანამშრომლები
	newRest = new Restaurant(name, adress, ownerSalary, chefSalary, waitressSalary, ownerPerc, income, tips, utility, rent);
	int owners;
	std::cout << "\tHow many Owners in Restaurant? ";
	int chefs;
	in >> owners;
	std::cout << "\tHow many Chefs in Restaurant? ";
	in >> chefs;
	int waiters;
	std::cout << "\tHow many waiters in Restaurant? ";
	in >> waiters;
	Owner* ow;
	Chef* cf;
	Waitress* wt;
	rest = *newRest;
	//მფლობელების შეყვანა
	for (int i = 0; i < owners; i++) {
		ow = new Owner;
		in >> *ow;
		rest.addEmploye(*ow);
	}
	//შეფების
	for (int i = 0; i < chefs; i++) {
		cf = new Chef;
		in >> *cf;
		rest.addEmploye(*cf);
	}
	//მიმტანების
	for (int i = 0; i < waiters; i++) {
		wt = new Waitress;
		in >> *wt;
		rest.addEmploye(*wt);
	}
	return in;
}
inline std::ifstream& operator>>(std::ifstream& ifs, Restaurant& rest) {
	rest.set_file(ifs);
	return ifs;
}
//გამოტანა
inline std::ostream& operator<<(std::ostream& out, Restaurant& rest) {
	rest.print(out);
	return out;
}
#endif // !__Restaurant__
