#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
using namespace std;

const int MarkSize = 5;

const int NameSize = 20;

char Names[NameSize][NameSize] ={"Petr","Lev","Ivan","Vova","Sergiy",
		"Alex","Artem","Taras","Andriy","Oleg",
		"Avgust","Igor","Nazar","Mars","Maks",
		"Stas","Jul","Gogi","Victor", "Harry"};  
char Sirnames[NameSize][NameSize] = {"Ivanov","Petrov","Sidorov","Gavrilov","Artemov",
		"Markus","Nemirov","Klaus","Bah","Folk",
		"Petrik","Kuv","Zaets","Tek","Open",
		"Len","Hok","Kletz","Haug", "Potter"};

struct Student
{
	char Name[NameSize];
	char Sirname[NameSize];
	int Marks[MarkSize];
	double Average;
};

void Init(Student* pStud, int Size)
{
	for(int i = 0; i < Size; ++i)
	{ 
		int randomIndex = rand() % NameSize;
		strcpy(pStud[i].Name, Names[randomIndex]);
		randomIndex = rand() % NameSize;
		strcpy(pStud[i].Sirname, Sirnames[randomIndex]);
		pStud[i].Average = 0;
		//cout << "Enter marks for " << pStud[i].Name << " " << pStud[i].Sirname << endl;
		for (int j = 0; j < MarkSize; ++j)
		{
			//cout << "Enter mark " << j << ": ";
			//cin >> pStud[i].Marks[j];
			pStud[i].Marks[j]=rand()%5 + 1;
			pStud[i].Average += pStud[i].Marks[j];
		}
		pStud[i].Average = pStud[i].Average /5.0;
	}
}

void ShowStudent(const Student& stud) 
{
		cout << stud.Name;
		cout << setw(15) << stud.Sirname;
		cout << setw(20);
		for (int j = 0; j < MarkSize; ++j)
			cout << stud.Marks[j] << ' ';
		cout << setw(25)<< stud.Average << endl;
}

void Show(Student* pStud, int Size)
{
	cout<<"Name"<<setw(15)<<"Sirname"<<setw(25)<<"Marks"<<setw(30)<<"Average"<< endl;
	for(int i = 0; i < Size; ++i)
	{
		ShowStudent(pStud[i]);
	}
}


#define SORT_FUNCTION(__BY_WHAT, __TYPE) \
void SortBy##__BY_WHAT(Student* pStud, int Size) \
{ \
	for(int pass = 0; pass < Size - 1; pass++) \
	{ \
		__TYPE min = pStud[pass].__BY_WHAT; \
		int minIdx = pass; \
		for(int j = pass + 1; j < Size; ++j) \
			if(min > pStud[j].__BY_WHAT) \
			{ \
				min = pStud[j].__BY_WHAT; \
				minIdx = j; \
			} \
		if (minIdx != pass) \
		{ \
			Student hold = pStud[pass]; \
			pStud[pass] = pStud[minIdx]; \
			pStud[minIdx] = hold; \
		} \
	} \
}

SORT_FUNCTION(Name, string)
SORT_FUNCTION(Sirname, string)
SORT_FUNCTION(Average, double)

Student MaxByAverage(Student* pStud, int Size)
{
	double max = pStud[0].Average;
	int index = 0;
	for(int i = 1; i < Size; i++)
	{
		if(pStud[i].Average > max)
		{
			max = pStud[i].Average;
			index = i;
		}
	}
	return pStud[index];
}

Student MinByAverage(Student* pStud, int Size)
{
	double min = pStud[0].Average;
	int index = 0;
	for(int i = 1; i < Size; i++)
	{
		if(pStud[i].Average < min)
		{
			min = pStud[i].Average;
			index = i;
		}
	}
	return pStud[index];
}

int main()
{
	srand(time(NULL));
	cout<< "Enter number of Students"<< endl;
	int Size;
	cin>> Size;
	Student* pStud = new Student[Size];
	Init(pStud, Size);
	cout<<"\nUnsorted\n";
	Show(pStud, Size);
	cout<< "Sort by Average - enter 1\nSort by Name - enter 2\nSort by Sirname - enter 3\n";
	int choice;
	cin>> choice;
	string byWhat = "";
	bool sorted = true;
	switch(choice)
	{
		case 1:
			SortByAverage(pStud, Size);
			byWhat = "average"; 
			break;
		case 2:
			SortByName(pStud, Size);
			byWhat = "name"; 
			break;
		case 3:
			SortBySirname(pStud, Size);
			byWhat = "sirname"; 
			break;
		default:
			sorted = false;
			break;
	}
	if (sorted) 
	{
		cout<<"\nSorted by " << byWhat << endl;
		Show(pStud, Size);
	} 
	else 
	{
		cout<< "Wrong choice\n";
	}
	cout<< "Student with maximum mark:\n";
	ShowStudent(MaxByAverage(pStud, Size));
	cout<< "Student with minimum mark:\n";
	ShowStudent(MinByAverage(pStud, Size));


	FILE*f = fopen("MyFile1","wb");
	for(int i = 0; i < Size; i++)
	fwrite(pStud + i, sizeof(Student), 1,f);
	fclose(f);
	
	f = fopen("MyFile1","rb");
		fseek(f,0,SEEK_END);
	int size = ftell(f)/sizeof(Student);
	fseek(f,0,SEEK_SET);

	Student*pSt = new Student[Size];
	for(int i = 0; i < Size; i++)
		fread(pSt + i, sizeof(Student), 1, f);
	fclose(f);
	Show(pSt, Size); 
	/*f = fopen("MyFile","rb");
	fread(pStud, sizeof(Student),Size,f);
	fclose(f);
	cout<< pStud<<endl;*/
	delete[] pStud;
	delete[] pSt;
	return 0;
}


/*const int SizeName = 20;

struct Comp
{
	char ProcName[SizeName];
	double ProcFreq;
	int Memory;
	string CompName;
};
int main()
{
	Comp cp = {"Amd",2.5,500,"Hack"};
	Comp* pCmp = new Comp;
	Comp* pComp = new Comp[10];

	pComp[0].Memory = 100;
	pCmp-> Memory = 1000;
	strcpy(pCmp->ProcName,"AMD");
	Comp cpHacker;
	cpHacker.Memory = 500;
	cpHacker.ProcFreq = 2.5;
	Comp cpArr[10];

	strcpy(cpHacker.ProcName, "Intel");
	cpHacker.CompName = "Hacker";

	cpArr[0].CompName = "Apple";
	cpArr[1].CompName = "AMD";

	cout<< cpHacker.Memory<< endl;
	cout<< cpHacker.ProcFreq<< endl;
	cout<< cpHacker.ProcName<< endl;
	cout<< cpHacker.CompName<< endl;

	cout<< cpArr[0].CompName<< endl;
	cout<< cpArr[1].CompName<< endl;
	cout<< cp.Memory<< endl;
	cout<< pCmp->Memory<< endl;
	cout<< pCmp->ProcName<< endl;
	cout<< pComp[0].Memory<< endl;
	return 0;
}
/*void Func(int*pAr, int Count)
{
	int Arr[1000];
	cout<< Count<< endl;
	Func(Arr,Count + 1);
}
int main()
{
	int Count = 0;
	int Arr[1000];
	cout<< Count<< endl;
	Func(Arr,Count + 1);
	return 0;
}*/