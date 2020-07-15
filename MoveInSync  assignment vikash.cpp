#include<iostream>
#include<windows.h>    
#include<conio.h>    
#include<iomanip>      
#include<string>
#include<unistd.h>      
#include<fstream>
#include<ctime>
#include<bits/stdc++.h>

using namespace std;

char opt;
void admin();
void mainmenu();
void seller();
void admindetail();
void bonddetails();
void customer();
void showdetail();
void setting();
void loaddata();
void cus_bonddetails();
void loginscreen();
void changepin();
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int datetest(string d){
	if(d.find('/')>=1&&d.rfind('/')>=3&&d.find('/')<=2&&d.rfind('/')<=6){
		string a=d.substr(0,2);
		string b=d.substr(d.find('/')+1,2);
		string c=d.substr(d.length()-2,2);
		int a1=atoi(a.c_str());	
		int b1=atoi(b.c_str());
		int c1=atoi(c.c_str());
		if(a1>=1&&a1<=31){
			if(b1>=1&&b1<=12){
				return 0;
			}
			else{
				cout<<"Invalid Month."<<endl;
			getch();
			}
		}
		else{
				cout<<"Invalid Date."<<endl;
			getch();
			}
	}
	else {
		cout<<"Invalid Format."<<endl;
					getch();

	}
}



class Admin{
	int id;
	char name[30];
	char owner[30];
	char type[30];
	int price;
	char date[20];
	float avg=0;
	float pre=0;
	public:
		void input(int i){
			id=i;
			cout<<"Enter Bond Name :- ";
			fflush(stdin);
			cin.getline(name,30);
			cout<<"Enter Owner's Name :- ";
			fflush(stdin);
			cin.getline(owner,30);
			cout<<"Enter type of Bond :- ";
			fflush(stdin);
			cin.getline(type,30);
		    cout<<"Pricing :- ";
			cin>>price;
			cout<<"Average return % -:";
			cin>>avg;
			cout<<"Current profit Prediction % :-";
			cin>>pre;
				do{
			cout<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));

		}
			void update(){
			cout<<"Enter Bond Name :- ";
			fflush(stdin);
			cin.getline(name,30);
			cout<<"Enter Owner's Name :- ";
			fflush(stdin);
			cin.getline(owner,30);
			cout<<"Enter type of Bond :- ";
			fflush(stdin);
			cin.getline(type,30);
			cout<<"Pricing :- ";
			cin>>price;
			cout<<"Average return % -:";
			cin>>avg;
			cout<<"\nCurrent profit Prediction % :-";
			cin>>pre;
				do{
			cout<<endl<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));

		}
		
		void output(){
			cout<<"Event ID :- "<<id<<endl<<"Name of Event :- "<<name<<endl<<"Owner Name :- "<<owner<<endl<<"Enter Bond Discription :- "<<type<<endl<<"Price of Bond :- "<<price<<endl<<" Average return :-"<<avg<<endl<<"Current profit Prediction % :-"<<pre<<endl<<"date     :-"<<date<<endl<<endl;
		}
		int search(int l,int i,int n){
			if(id==l){
				return 1;
			}
			i++;
			if(i==n){
			cout<<"Bond ID not found.";
						getch();
							system("cls");

			}
			return 0;
		}
		void del(Admin s){
			id=s.id;
			strcpy(name,s.name);
			strcpy(owner,s.owner);
			strcpy(type,s.type);
			price=s.price;
		}
		int checkid(int l){
			if(id==l){
				return 1;
			}			
			return 0;
		}
};

void addbond(){
	system("cls");
	char y;
	Admin d ;
	int id,i,a,len,n;
	ifstream in("bond.bin",ios::binary);
	in.seekg(0,ios::end);
	len=in.tellg();
	n=len/sizeof(d);
	in.seekg(0,ios::beg);
	Admin s[n];
	if(in){
		while(in.read((char *)&s[i],sizeof(s[i]))){
			i++;
		}
	}
	in.close();
	do{
		cout<<"Enter Bond ID :- ";
		cin>>id;
		for(i=0;i<n;i++){
			a=s[i].checkid(id);
			if(a==1){
				cout<<"Entered ID already exist."<<endl<<"Press any key to continue...";
				getch();
				addbond();  
			}
		}
		d.input(id);
		ofstream out("bond.bin",ios::app|ios::binary);
		out.write((char *)&d,sizeof(d));
		out.close();
		cout<<endl<<"Add more Bond ? (y/n) :- \n\n";
		fflush(stdin);
		y=getch();
	}
	while(i=='y'||i=='Y');
	admindetail();
}

void updatebond(){
	ifstream in("bond.bin",ios::binary);
	int id,i,a;
	Admin d;
	in.seekg(0,ios::end);
	int len=in.tellg();
	int n=len/sizeof(d);
	in.seekg(0,ios::beg);
	Admin s[n];
	if(in){
		while(in.read((char *)&s[i],sizeof(s[i]))){
			i++;
		}
		in.close();
		}
	cout<<endl<<"Enter Bond ID to update :- ";
	cin>>id;
	for(i=0;i<n;i++){
		a=s[i].search(id,i,n);
		if(a==1){
		s[i].update();
		break;
		}
	}
	ofstream out("bond.bin",ios::binary);
	for(i=0;i<n;i++){
		out.write((char *)&s[i],sizeof(s[i]));
	}
	out.close();
	admindetail();
}

void deletebond(){
	ifstream in("bond.bin",ios::binary);
	int id,a,i;
	Admin d;
	in.seekg(0,ios::end);
	int len=in.tellg();
	int n=len/sizeof(d);
	in.seekg(0,ios::beg);
	Admin s[n];
	if(in){
		while(in.read((char *)&s[i],sizeof(s[i]))){
			i++;
		}
		in.close();
		}
	cout<<endl<<"Enter Bond ID to delete :- ";
	cin>>id;
	for(i=0;i<n;i++){
			a=s[i].search(id,i,n);
			if(a==1){
			for(int j=i;j<n;j++){
				s[j].del(s[j+1]);
			}
			ofstream out("bond.bin",ios::binary);
			for(i=0;i<n-1;i++){
				out.write((char *)&s[i],sizeof(s[i]));
			}
			out.close();	
			break;
		}
	}

	admindetail();
}




void admindetail(){
	
	char i;	
	ifstream in("bond.bin",ios::binary);

	if(in){
		Admin d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);      
		in.seekg(0,ios::beg);
		Admin e[n];             // array of object 
		while(in.read((char *)&e[i],sizeof(e[i]))){
			e[i].output();
			i++;
		}
		in.close();
	

			
		cout<<endl<<"1. Add    2. Update    3. Delete    4. Back"<<endl;
		fflush(stdin);
		int k=getch();
		switch(k){
			case '1': addbond();
					break;
			case '2': updatebond();
					break;
			case '3': deletebond();
					break;
			case '4': mainmenu();
					break;
			default : admin();
		}
	}
	
	
	

	else {
		cout<<"Nothing to show... Database doesn't exist."<<endl<<"Creating Database...."<<endl<<"Press any key to continue.";
		ofstream out("bond.bin",ios::binary);
		out.close();
		getch();
		admin();
	}
}

void admin(){
	
	loaddata();
	loginscreen();
	int i;
	system("cls");
	
	ifstream in("bond.bin",ios::binary);
	Admin d;
	in.seekg(0,ios::end);
	int len=in.tellg();
	int n=len/sizeof(d);
	in.close();
	cout<<"Total no. of Bond :- 50"<<endl;
	cout<<"Bond Hold :- "<<n<<endl;
	cout<<"Bond vacant :- "<<50-n<<endl<<endl;

	admindetail();  

	}
	


/////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                             /////SELLER
////////////////////////	






class Seller{
	int id;
	char name[30];
	char Owner[30];
	char description[20];
	int price;
	char sell[30];
	char date[20];
	public:
		void input(int i){
				id=i;
				cout<<"Enter name of Bond :- ";
				fflush(stdin);
				cin.getline(name,30);
				cout<<"Enter name of Owner :-";
				fflush(stdin);
				cin.getline(Owner,30);
				cout<<"Enter Bond Discription :- ";
				fflush(stdin);
				cin.getline(description,50);
					cout<<"Enter whom to sell :- ";
				fflush(stdin);
				cin.getline(sell,50);
				cout<<"Enter Price for bond :- ";
				cin>>price;
					do{
			cout<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));
		}
		
		void output(){
			cout<<"Event ID :- "<<id<<endl<<"Name of Event :- "<<name<<endl<<"Owner Name :- "<<Owner<<endl<<"Enter Bond Discription :- "<<description<<endl<<"whom to sell "<<sell<<endl<<"Price of Bond :- "<<price<<endl<<"date"<<date<<endl<<endl<<endl;
		}
		
		int checkid(int l){
			if(id==l){
				return 1;
			}			
			return 0;
		}
	int search(int l,int i,int n){
			if(id==l){
				return 1;
			}
			i++;
			if(i==n){
			cout<<"Shop ID not found.";
			getch();
			}
			return 0;
		}
		void update(){
			    cout<<"Enter updated name of Bond :- ";
				fflush(stdin);
				cin.getline(name,30);
				cout<<"Enter updated name of Owner :-";
				fflush(stdin);
				cin.getline(Owner,30);
				cout<<"Enter updated Bond Discription :- ";
				fflush(stdin);
				cin.getline(description,50);
				cout<<"Enter whom to sell :- ";
				fflush(stdin);
				cin.getline(sell,50);
				cout<<"Enter Price for bond :- ";
				cin>>price;
					do{
			cout<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));
		}

};




void selledbond(){
		system("cls");
	char i;	
	ifstream in("seller.bin",ios::binary);

	if(in){
		Seller d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);      
		in.seekg(0,ios::beg);
		Seller e[n];             // array of object 
		while(in.read((char *)&e[i],sizeof(e[i]))){
			e[i].output();
			i++;
		}
		in.close();
}
cout<<" Wating 5 sec.....";
	sleep(5);
 bonddetails();
}















void sellBond(){
	int i,id,a;
	char y;
	system("cls");
	system("color 0a");

	ifstream in("seller.bin",ios::binary);
	if(in){
		Seller d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);
		in.seekg(0,ios::beg);
		Seller e[n];
		while(in.read((char *)&e[i],sizeof(e[i]))){
			i++;
		}
		in.close();
		do{
			cout<<"Enter Bond ID :- ";
			cin>>id;
			for(i=0;i<n;i++){
				a=e[i].checkid(id);
				if(a==1){
					cout<<"Entered ID already exist."<<endl<<"Press any key to continue...";
					getch();
					sellBond();
				}
	}
		d.input(id);
		ofstream out("seller.bin",ios::app|ios::binary);
		out.write((char *)&d,sizeof(d));
		out.close();
	//	Dsellbond();   ////////////////////////////////////////////////////////////////////////
		cout<<endl<<"Sell more Bond ? (y/n) :- ";
		cin>>y;
	}
	while(y=='y'||y=='Y');
	seller();
	}
	else {
		ofstream out("seller.bin",ios::binary);
		out.close();
		cout<<"Database Doesn't Exist."<<endl<<"Creating Database..."<<endl<<"Press any key to continue.";
		getch();
		sellBond();
	}
}

void updateBond(){
	ifstream in("seller.bin",ios::binary);
	int id,i,a;
	Seller d;
	in.seekg(0,ios::end);
	int len=in.tellg();
	int n=len/sizeof(d);
	in.seekg(0,ios::beg);
	Seller s[n];
	if(in){
		while(in.read((char *)&s[i],sizeof(s[i]))){
			i++;
		}
		in.close();
		}
	cout<<endl<<"Enter Bond ID to update :- ";
	cin>>id;
	for(i=0;i<n;i++){
		a=s[i].search(id,i,n);
		if(a==1){
		s[i].update();
		break;
		}
	}
	
	ofstream out("seller.bin",ios::binary);
	for(i=0;i<n;i++){
		out.write((char *)&s[i],sizeof(s[i]));
	}
	out.close();
	bonddetails();
}



void bonddetails(){
	
		system("cls");

		char i;	
	ifstream in("bond.bin",ios::binary);
	cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"                                                              File                                          "<<endl<<endl<<endl;
    cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;

	if(in){
		Admin d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);      
		in.seekg(0,ios::beg);
		Admin e[n];             // array of object 
		while(in.read((char *)&e[i],sizeof(e[i]))){
			e[i].output();
			i++;
		}
		in.close();
	}


	cout<<endl<<"1. Update       2. Selled Detail         3. Back"<<endl;
	    fflush(stdin);
	char	n=getch();
		switch(n){
			case '1': updateBond();
						break;
		 case '2': selledbond();
						break;
			case '3': seller();
					break;
			default : bonddetails();
		}
}










void seller(){
	system("cls");
	char n;
	cout<<"1. Sell Bond ";
	cout<<endl<<"2. Show Details";
	cout<<endl<<"3. Back"<<endl;
	fflush(stdin);
	n=getch();
	switch(n){
		case '1': sellBond();    //addmov
				break;
		case '2': bonddetails();    //pvrdetails
				break;
		case '3': mainmenu();
				break;
		default: seller();     //pvrmenu
	}
}



/////////////////////////////////////////// Custome                   ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////




class Customer{
	int id;
	char name[30];
	char Owner[30];
	char description[20];
	int price;
	int year;
	char sell[20];
	char agt[20];
	char date[20];
	public:
		void input(int i){
				id=i;
				cout<<"Enter name of Bond :- ";
				fflush(stdin);
				cin.getline(name,30);
				cout<<"Enter name of Owner :-";
				fflush(stdin);
				cin.getline(Owner,30);
				cout<<"Enter Bond Discription :- ";
				fflush(stdin);
				cin.getline(description,50);
					cout<<"Enter whom to sell :- ";
				fflush(stdin);
				cin.getline(sell,50);
				cout<<"Enter Price for bond :- ";
				cin>>price;
					do{
			cout<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));
		}
		
		
		
		void inputbuy(int i){
				id=i;
				cout<<"Enter name of Bond :- ";
				fflush(stdin);
				cin.getline(name,30);
				cout<<"Enter name of Owner :-";
				fflush(stdin);
				cin.getline(Owner,30);
				cout<<"Enter Bond Discription :- ";
				fflush(stdin);
				cin.getline(description,50);
				cout<<"Enter Agent Name :- ";
				fflush(stdin);
				cin.getline(agt,50);
				cout<<"Enter Price for bond :- ";
				cin>>price;
				cout<<"For How many Year  :-";
				cin>>year;
					do{
			cout<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));
		}
		
		void output(){
			cout<<"Event ID :- "<<id<<endl<<"Name of Event :- "<<name<<endl<<"Owner Name :- "<<Owner<<endl<<"Enter Bond Discription :- "<<description<<endl<<"whom to sell "<<sell<<endl<<"Price of Bond :- "<<price<<endl<<"date"<<date<<endl<<endl<<endl;
		}
		void outputbuy(){
			cout<<"Event ID :- "<<id<<endl<<"Name of Event :- "<<name<<endl<<"Owner Name :- "<<Owner<<endl<<"Enter Bond Discription :- "<<description<<endl<<"Agent Name    :- "<<agt<<endl<<"Price of Bond :- "<<price<<endl<<"For How many Year  :-"<<year<<endl<<"date       :-"<<date<<endl<<endl<<endl;
		}
		int checkid(int l){
			if(id==l){
				return 1;
			}			
			return 0;
		}
	int search(int l,int i,int n){
			if(id==l){
				return 1;
			}
			i++;
			if(i==n){
			cout<<"Shop ID not found.";
			getch();
			}
			return 0;
		}
		void update(){
			    cout<<"Enter updated name of Bond :- ";
				fflush(stdin);
				cin.getline(name,30);
				cout<<"Enter updated name of Owner :-";
				fflush(stdin);
				cin.getline(Owner,30);
				cout<<"Enter updated Bond Discription :- ";
				fflush(stdin);
				cin.getline(description,50);
					cout<<"Enter whom to sell :- ";
				fflush(stdin);
				cin.getline(sell,50);
				cout<<"Enter Price for bond :- ";
				cin>>price;
					do{
			cout<<"Enter date  in (dd/mm/yy) :- ";
			fflush(stdin);
			cin.getline(date,20);
			}while(datetest(date));
		}
		
		
		

};




void cus_selledbond(){
		system("cls");
	char i;	
	ifstream in("cus_seller.bin",ios::binary);

	if(in){
		Customer d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);      
		in.seekg(0,ios::beg);
		Customer e[n];             // array of object 
		while(in.read((char *)&e[i],sizeof(e[i]))){
			e[i].output();
			i++;
		}
		in.close();
}
cout<<" Wating 5 sec ....";
	sleep(5);
 cus_bonddetails();
}


////////////////////////////////////////////////

void buydetail(){
		system("cls");
	char i;	
	ifstream in("cus.bin",ios::binary);

	if(in){
		Customer d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);      
		in.seekg(0,ios::beg);
		Customer e[n];             // array of object 
		while(in.read((char *)&e[i],sizeof(e[i]))){
			e[i].outputbuy();
			i++;
		}
		in.close();
}

cout<< " Wating 5 sec .......";
	sleep(5);
 cus_bonddetails();
}

///////////////////////////////////////////////




void cus_sellBond(){
	int i,id,a;
	char y;
	system("cls");
	system("color 0a");

	ifstream in("cus_seller.bin",ios::binary);
	if(in){
		Seller d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);
		in.seekg(0,ios::beg);
		Seller e[n];
		while(in.read((char *)&e[i],sizeof(e[i]))){
			i++;
		}
		in.close();
		do{
			cout<<"Enter Bond ID :- ";
			cin>>id;
			for(i=0;i<n;i++){
				a=e[i].checkid(id);
				if(a==1){
					cout<<"Entered ID already exist."<<endl<<"Press any key to continue...";
					getch();
					sellBond();
				}
	}
		d.input(id);
		ofstream out("cus_seller.bin",ios::app|ios::binary);
		out.write((char *)&d,sizeof(d));
		out.close();
		cout<<endl<<"Sell more Bond ? (y/n) :- ";
		cin>>y;
	}
	while(y=='y'||y=='Y');
	customer();
	}
	else {
		ofstream out("cus_seller.bin",ios::binary);
		out.close();
		cout<<"Database Doesn't Exist."<<endl<<"Creating Database..."<<endl<<"Press any key to continue.";
		getch();
		cus_sellBond();
	}
}

void cus_updateBond(){
	ifstream in("cus_seller.bin",ios::binary);
	int id,i,a;
	Customer d;
	in.seekg(0,ios::end);
	int len=in.tellg();
	int n=len/sizeof(d);
	in.seekg(0,ios::beg);
	Customer s[n];
	if(in){
		while(in.read((char *)&s[i],sizeof(s[i]))){
			i++;
		}
		in.close();
		}
	cout<<endl<<"Enter Bond ID to update :- ";
	cin>>id;
	for(i=0;i<n;i++){
		a=s[i].search(id,i,n);
		if(a==1){
		s[i].update();
		break;
		}
	}
	
	ofstream out("cus_seller.bin",ios::binary);
	for(i=0;i<n;i++){
		out.write((char *)&s[i],sizeof(s[i]));
	}
	out.close();
	cus_bonddetails();
}






void cus_buyBond(){
	system("cls");
	char y;
	Customer d ;
	int id,i,a,len,n;
	static int ii=1;
	if(ii==1){
	
		cout<<"Nothing to show... Database doesn't exist."<<endl<<"Creating Database...."<<endl<<"Press any key to continue." ;
		ofstream out("cus.bin",ios::binary);
		out.close();
		getch();
	
	ii=0;
}
		system("cls");

	
	ifstream in("cus.bin",ios::binary);
	in.seekg(0,ios::end);
	len=in.tellg();
	n=len/sizeof(d);
	in.seekg(0,ios::beg);
	Customer s[n];
	if(in){
		while(in.read((char *)&s[i],sizeof(s[i]))){
			i++;
		}
	
	in.close();
	do{
		cout<<"Enter Bond ID :- ";
		cin>>id;
		for(i=0;i<n;i++){
			a=s[i].checkid(id);
			if(a==1){
				cout<<"Entered ID already exist."<<endl<<"Press any key to continue...";
				getch();
				cus_buyBond();  
			}
		}
		d.inputbuy(id);  //inputbuy
		ofstream out("cus.bin",ios::app|ios::binary);
		out.write((char *)&d,sizeof(d));
		out.close();
		cout<<endl<<"Buy more Bond ? (y/n) :- \n\n";
		fflush(stdin);
		y=getch();
	}while(y=='y'||y=='Y');
		cus_bonddetails();
	}

}










void cus_bonddetails(){
	
		system("cls");

		char i;	
	ifstream in("bond.bin",ios::binary);
	cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"                                                         File                                                "<<endl<<endl<<endl;
    cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;

	if(in){
		Admin d;
		in.seekg(0,ios::end);
		int len=in.tellg();
		int n=len/sizeof(d);      
		in.seekg(0,ios::beg);
		Admin e[n];             // array of object 
		while(in.read((char *)&e[i],sizeof(e[i]))){
			e[i].output();
			i++;
		}
		in.close();
	}


	cout<<endl<<"1. Update Selled Detail      2. Selled  Detail       3. Buy Details        4. Back"<<endl;
	    fflush(stdin);
	char	n=getch();
		switch(n){
			case '1': cus_updateBond();
						break;
		 case '2': cus_selledbond();
						break;
		case '3': buydetail();
						break;
			case '4': customer();
					break;
			default : cus_bonddetails();
		}
}










void customer(){
	system("cls");
	char n;
	cout<<endl<<"1. Selll Bond ";
	cout<<endl<<"2. Buy bond";
	cout<<endl<<"3. Show Details";
	cout<<endl<<"4. Back"<<endl;
	fflush(stdin);
	n=getch();
	switch(n){
		case '1': cus_sellBond();    //sellBond
				break;
		case '2': cus_buyBond();    //sellBond
				break;
		case '3': cus_bonddetails();    //pvrdetails
				break;
		case '4': mainmenu();
				break;
		default: customer();     //pvrmenu
	}
}
















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void delrecord(){
	char c;
	cout<<endl<<"Are you sure you want to delete all records :- (y/n) :- ";
	cin>>c;
	if(c=='y'||c=='Y'){
		ofstream out("cussell.bin",ios::binary);
		ofstream out1("seller.bin",ios::binary);
		ofstream out2("bond.bin",ios::binary);
		out2.close();
		out1.close();
		out.close();
		cout<<"All records Deleted Succesfully."<<endl<<"Press any key to continue...";
		getch();
	}
	else setting();
	
	mainmenu();
}



void setting(){
 loaddata();

 loginscreen();
	system("cls");
	char a;
	cout<<"1. Change Pin"<<endl<<"2. Delete All Records"<<endl<<"3. Back"<<endl;
	a=getch();
	switch(a){
		case '1':{
			changepin();
			break;
		}
		case '2':{
			delrecord();
			break;
		}
	
		case '3':{
			mainmenu();
			break;
		}
		default:{
			setting();
			break;
		}
	}
}












class set{
	public:
	int pass;
	int show[3];
		set(){
			pass=1234;
			show[0]=1;
			show[1]=1;
			show[2]=1;
		}
		void passinput(){
			int i=0;
			string value;
			char key;
			do{
				key = getch();
		 		switch (key){
					case '\b':{
						if(value.length() > 0)
					  	{
							value.erase(value.length() - 1, 1);
							cout << '\b' << " " << '\b';
					 	}
						break;
					}
					default:
					if(key > 31 && key < 127)
					{
						value.push_back(key);
						cout << "*";
					}
		 		}
			} while(value.length()!=4);
			pass=atoi(value.c_str());
		}
 		int check(int password){
  			if(password==pass)
  			{
  				return 1;	
			}
		  else return 0;
	    }
	    
		
}s;


void changepin(){
	int pass;
	system("cls");
	cout<<"Enter old 4-Digit Pin :- ";
	cin>>pass;
	if(s.check(pass)){
		cout<<"Enter New 4-Digit Pin :- ";
		s.passinput();
		cout<<endl<<"Changed Succesfully.";
		ofstream out("setting.bin",ios::binary);
		out.write((char *)&s,sizeof(s));
		out.close();
		getch();
		setting();
	}
	else{
		cout<<"Incorrect Pin..."<<endl<<"Press any key & re-enter :- ";
		getch();
		changepin();
	}
}



void mainmenu(){
	system("color 1b");
	system("cls");
	int i=0,j=0;

 	gotoxy(97,28);
	gotoxy(44-i,13-j);
	cout<<"||========================||";
	gotoxy(44-i,14-j);
	cout<<"||                        ||";
	gotoxy(44-i,15-j);
	cout<<"||  1 Administrator       ||";
	gotoxy(44-i,16-j);
	cout<<"||                        ||";
	gotoxy(44-i,17-j);
	cout<<"||  2  Sell Person        ||";
	gotoxy(44-i,18-j);
	cout<<"||                        ||";
	gotoxy(44-i,19-j);
	cout<<"||  3  Customer           ||";
	gotoxy(44-i,20-j);
	cout<<"||                        ||";
	gotoxy(44-i,21-j);
	cout<<"||  4. Settings           ||";
	gotoxy(44-i,22-j);
	cout<<"||                        ||";
		gotoxy(44-i,23-j);
	cout<<"||  5.  Exit              ||";
	
	gotoxy(44-i,24-j);
	cout<<"||========================||"<<endl;
	fflush(stdin);
	opt=getch();
	switch(opt){
		case '1': admin();
				break;
		case '2': seller();
				break;
		case '3': customer();
				break;
		case '4': setting();
				break;
		case '5': exit(0);
		default: mainmenu();
	}
}

void loaddata(){
	ifstream in("setting.bin",ios::binary);
	if(in){
		in.read((char *)&s,sizeof(s));
	}
	else {
		in.close();
		ofstream out("setting.bin",ios::binary);
		out.close();
		
	}
}

void loginscreen(){
	system("cls");
	int check,pass;
	cout<<endl<<endl<<"======================================================================================================================== |                                               Administrator Login                                                  |"<<endl;
	cout<<"========================================================================================================================";
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"                                         |===================================|";
	cout<<endl<<"                                         |         Enter 4-Digit Pin         |"<<endl;
	cout<<"                                         |===================================|"<<endl;
	int i=0;
	string value;
	char key;
	for(int j=0;j<4;j++){
		gotoxy(57+j,15);
		cout<<"_";
	}
	gotoxy(57,15);
	do{
		key = getch();
		switch (key){
			case '\b':{
				if(value.length() > 0)
			 	{
					value.erase(value.length() - 1, 1);
					std::cout << '\b' << "_" << '\b';
				}
				break;
			}
			default:
				if(key > 31 && key < 127)
				{
					value.push_back(key);
					std::cout << "*";
				}
			}
	} while(value.length()!=4);
	pass=atoi(value.c_str());
	check=s.check(pass);
	if(check==1)
	{
		cout<<endl<<endl<<endl<<endl<<endl<<"                                                 Login Succesfull...";
		sleep(1);		cout<<endl<<"                                               Press any key to continue.";
	getch();
	//	mainmenu();
	}
	else 
	{
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                                                 Login Unsuccesfull..."<<endl;
		cout<<"                                               Please check your credentials."<<endl;
		cout<<"                                               Press any key to try again.";
		cin.get();
		loginscreen();
	}
}


int main(){
	system("color 0b");
	cout<<endl<<endl<<endl<<endl<<endl<<"                                       Welcome to Bond Portfolio Management "<<endl<<endl<<"                                                     Loading....";
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                           By :- Vikash Vishwakarma                ";
	cout<<endl<<"                                   \t\t                                                            \t\t                            To  :- MoveInSync                       ";

	sleep(4);
//	loaddata();
//	loginscreen();
	mainmenu();
	getch();
}
