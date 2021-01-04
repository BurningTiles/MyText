/**
 * Author  : BurningTiles
 * Created : 2020-08-05 23:36:24
**/ 
 
#include <iostream>
#include <fstream>
using namespace std;

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
void clear() {system("cls");}
#elif defined(UNIX) || defined(LINUX) || defined(__unix__) || defined(__linux__)
void clear() {system("clear");}
#else
void clear() {std::cout << std::string(100,'\n');}
#endif

int N=0;
bool flag = false;

class font{
public:
	string *x;
}ch[95], out;

void init(string fontfile){
	fontfile += ".myfont";
	ifstream in(fontfile.c_str());
	if(in.fail()){
		cerr << endl << "Error in opening Font file.\nTry again." << endl;
		return;
	}
	int n, chtemp, sum;
	if(!(in >> n >> sum)){
		cerr << "Fail to read font file." << endl;
		return;
	}
	if(n<1){
		cerr << "Font file is corrupted.";
	}

	string temp;
	for(int i=0; i<95; ++i){
		if(ch[i].x != NULL){
			delete []ch[i].x;
		}
		ch[i].x = new string[n];
		for(int j=0; j<n; ++j){
			temp="";
			while((in >> chtemp) && chtemp != 20+n){
				chtemp -= n;
				temp.push_back(char(chtemp/2));
				sum -= chtemp + chtemp%11 + ((chtemp/2)%2) + ((chtemp/2)%3) + ((chtemp/2)%5);
			}
			ch[i].x[j]=temp;
		}
	}
	if(sum == 0){
		N = n;
		flag = true;
	}
	else{
		cerr << "Font file is corrupted." << endl;
		flag = false;
	}
}

void addch(int n){
	if(n<0 || n>94)
		return;
	for(int i=0; i<N; ++i)
		out.x[i] += ch[n].x[i];
}

void printer(char text[]){
	if(!flag){
		cerr << "No font selected." << endl;
		return;
	}
	int i;
	if(out.x != NULL){
		delete []out.x;
	}
	out.x = new string[N];
	for(i=0; i<N; ++i)
		out.x[i] = "";
	i=0;
	while(text[i]!='\0'){
		addch(int(text[i])-32);
		++i;
	}
	for(i=0; i<N; ++i)
		cout << out.x[i] << endl;
}

int main(){
	cout << endl << endl;
	cout << "MyText 2.0" << endl;
	cout << "------ ---" << endl;
	cout << "Developed by BurningTiles aka Manish..." << endl;
	cout << "--------- -- ------------ --- ---------" << endl << endl;
	int choice;
	char intext[1000];
	string fontfile="default";
	init(fontfile);
	while(true){
		cout << endl << "   1.Printer      2.Font         3.Exit\n\n-> ";
		cin >> choice;
		while(cin.fail()){
			cout << "Invalid input.\nTry again : ";
			cin.clear();
			cin.ignore(99999,'\n');
			cin >> choice;
		}
		clear();
		switch(choice){
			case 1:
				if(flag){
					cout << "Insert text : ";
					cin.ignore(999, '\n');
					cin.getline(intext,999);
					cout << endl;
					printer(intext);
				}
				else{
					cerr << "No font selected." << endl;
				}
				break;
			case 2:
				cout << "For default write default.\nFont name without extension : ";
				cin >> fontfile;
				init(fontfile);
				break;
			case 3:
				return 0;
				break;
			default:
				cout << "Invalid choice." << endl;
		}
	}
	return 0;
}

/**

**/
