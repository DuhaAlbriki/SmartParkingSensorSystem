#include <iostream>
#include <string>
using namespace std;

//نسوي النود
struct NodeClass {
public:
	int ID;
	string Name;
	string first_day;
	string MobileNo;
	string Address;
	string work_hours;
	double salary;
	NodeClass* next;
};

//هذا الهد
NodeClass* head = new NodeClass();

//تشيك اذا الموطف موجود ولالا بالايدي
bool checker(int x)
{
	if (head == NULL) //معناتو فاضية
		return false;
		
	NodeClass*	var = new NodeClass;
	var = head;
	while (var != NULL) {
		if (var->ID == x)
			return true;
		var = var->next;
	}
	return false;
}
//يحدث الراتب لو الساعات اكثر من ٣٢ يعطيه بونس
double updateSalary(double sal,int workingHours) {
	int differenceofhours = 0;
	double var = 0;
	if (workingHours > 32) {
		differenceofhours = workingHours - 32;
		for (int i = 0; i < differenceofhours; i++) {
			var = var+0.02 * sal;
		}
			
	}
	return var;

}
void Insert_employee_Record(int i, string n, string f, string w, string m, string a, double s)
{
	int var1 = 0,var2=0;
	//نرسل الايدي للتشكر
	if (checker(i)) {
		cout << "Already have this record" << endl;
		return;
	}
	NodeClass* temp = new NodeClass();
	temp->ID = i;
	temp->Name = n;
	temp->first_day = f;
	temp->MobileNo = m;
	temp->Address = a;
	temp->work_hours =w;
	
	//يحول عدد الساعات ل انتقر
	var1 = stoi(w);
	
	if (var1 > 32) {
		var2=updateSalary(s,var1);
		temp->salary = s+var2;
	}
	else {
		temp->salary = s;
	}
	
	temp->next = NULL;

    //هنا اذا النود فاضية
	if (head == NULL|| (head->ID >= temp->ID)) 
	{
		temp->next = head;
		head = temp;
	}
	//وهنا اذا النود مو فاضية
	else 
	{
		NodeClass* temp2 = head;
		while (temp2->next != NULL && temp2->next->ID < temp->ID) 
		{
			temp2 = temp2->next;
		}
		temp->next = temp2->next;
		temp2->next = temp;
	}
	cout << "Record added" << endl;;
}

void Search_employee_Record(int id)
{
	// اذا اللست فاضية
	if (!head) {
		cout << "No such Record Available" << endl;
		return;
	}
	else {
		NodeClass* temp = head;
		while (temp) {
			if (temp->ID == id) {
				cout << "Employee ID: " << temp->ID << endl;
				cout << "Employee Name: " << temp->Name << endl;
				cout << "Employee First Day: " << temp->first_day << endl;
				cout << "Employee Phone Number: " << temp->MobileNo << endl;
				cout << "Employee Address: " << temp->Address << endl;
				cout << "Employee Working Hours: " << temp->work_hours << endl;
				cout << "Employee Salary: " << temp->salary << endl;
				return;
			}
			temp = temp->next;
		}

		if (temp == NULL)
			cout << "No such Record available" << endl;
	}
}
int Delete_employee_Record(int id)
{
	NodeClass* temp = head;
	NodeClass* point = NULL;

	// نحذف من البداية
	if (temp != NULL && temp->ID == id) {
		head = temp->next;
		delete temp;
		cout << "data Deleted " << endl;
		return 0;
	}

    //نحذف من الاخير
	while (temp != NULL && temp->ID != id) {
		point = temp;
		temp = temp->next;
	}
	if (temp == NULL) {
		cout << "no data" << endl;
		return -1;
		point->next = temp->next;
		delete temp;
		cout << "data delted" << endl;
		return 0;
	}
	//نحذف من النص
	struct NodeClass* slow_ptr = head;
	struct NodeClass* fast_ptr = head;
	struct NodeClass* prev=NULL;
	
	while (fast_ptr != NULL && fast_ptr->next != NULL) {
		fast_ptr = fast_ptr->next->next;
		prev = slow_ptr;
		slow_ptr = slow_ptr->next;
	}
	
	prev->next = slow_ptr->next;
	delete slow_ptr;
	cout << "data delted" << endl;
}

void Show_employee()
{
	NodeClass* temp = head;
	if (temp == NULL) {
		cout << "No Record Available" << endl;
	}
	else {
		while (temp != NULL) {
		cout << "\n\nID:" << temp->ID <<"\nName:" << temp->Name << "\nFirst_Day:" << temp->first_day << 
			"\nMobileNo:" << temp->MobileNo << "\nAddress:" << temp->Address << "\nWorking_Hours:" << temp->work_hours <<
			 "\nSalary:" << temp->salary << endl;
			temp = temp->next;
		}
	}
}

void updatedata(int id) {
	if (!head) 
	{
		cout << "no data exits" << endl;
		return;
	}
	else 
	{
		NodeClass* temp = head;
		while (temp)
		{
			if (temp->ID == id)
			{
				cout << "Employee ID:" << temp->ID << endl;
				cout << "Employee Name:" << temp->Name << endl;
				cout << "Employee Address:" << temp->Address << endl;
				cout << "Employee Working Hours:" << temp->work_hours << endl;
				cout << "Employee Phone Number:" << temp->MobileNo << endl;
				cout << "Employee First Day:" << temp->first_day << endl;
				cout << "Employee Salary:" << temp->salary << endl;
				string n,w,f,m,a;
				double salary;
				int ID;
				//م ناخذ انبوت م نحتاجو عشان لا يلخبط
				cin.ignore();
				cout << "Enter Name of Employee:";
				getline(cin, n); //ناخذ بس سترنق
				cout << "Enter Employee First_Day:";
				getline(cin, f);
				cout << "Enter Employee Address:";
				getline(cin, a);
				cout << "Enter Employee Working Hours:";
				getline(cin, w);
				cout << "Enter Employee Phone No:";
				getline(cin, m);
				cin.ignore();
				cout << "Enter Employee Salary:";
				cin >> salary;
				cout << "Enter Employee ID:";
				cin >> ID;
				
				temp->Name = n;
				temp->MobileNo = m;
				temp->Address = a;
				temp->salary = salary;
				temp->first_day = f;
				temp->work_hours = w;
				temp->ID = ID;
				

				cout << endl<<"updated record" << endl;
				cout << "Employee ID:" << temp->ID << endl;
				cout << "Employee Name:" << temp->Name << endl;
				cout << "Employee First Day:" << temp->first_day << endl;
				cout << "Employee Phone Number:" << temp->MobileNo << endl;
				cout << "Employee Address:" << temp->Address << endl;
				cout << "Employee Working Hours:" << temp->work_hours << endl;
				cout << "Employee Salary:" << temp->salary << endl;
				return;
			}
			temp = temp->next;
		}

		if (temp == NULL)
		{
			cout << "No such data available" << endl;
		}
	}
}
int main()
{
	head = NULL;
	string temp1, temp2, temp3, temp4, temp5; // عشان ناخذ من اليوزر
	int ID = 0;
	int idcheck;
	double salary;
	while (true) {
		cout << "\n\t\tWelcome to Employee Management System\n" << endl;
		cout << "1. To Create new record" << endl;
		cout << "2. To delete a record" << endl;
		cout << "3. To Search a record" << endl;
		cout << "4. To view all Records" << endl;
		cout << "5. To update Employee Record" << endl;
		cout << "6. To Exit" << endl;
		cout << "\nEnter your Choice\n";
		int var2;
		//الاختيارات
		cin >> var2;
		if (var2 == 1) {
			cin.ignore();
			cout << "Enter Name of Employee:";
			getline(cin, temp1);
			cout << "Enter Employee First_Day:";
			getline(cin, temp2);
			cout << "Enter Employee Working Hours:";
			getline(cin, temp3);
			cout << "Enter Employee Phone No:";
			getline(cin, temp4);
			cout << "Enter Employee Address:";
			getline(cin, temp5);
			cout << "Enter Employee Salary:";
			cin >> salary;
			cout << "Enter Employee ID:";
			cin >> ID;
			Insert_employee_Record(ID, temp1, temp2, temp3, temp4, temp5, salary);
		}
		else if (var2 == 2)
		{
			cout << "Enter ID: ";
			cin >> idcheck;
			Delete_employee_Record(idcheck);
		}
		else if (var2 == 3)
		{
			cout << "Enter ID: ";
			cin >> idcheck;
			Search_employee_Record(idcheck);
		}
		else if (var2 == 4)
		{
			Show_employee();
		}
		else if (var2 == 5) {
			cout << "Enter ID: ";
			cin >> idcheck;
			updatedata(idcheck);
		}
		else if (var2 == 6) {
			break;
		}
		else {
			cout << "Invalid input !" << endl;;
		}
	}
	return 0;
}
