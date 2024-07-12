//  Name       : Mohamad Azan bin Amit
//	Student ID : 2021963241
//	Group	   : M3CS2302A
//	Project	   : GPA calculator


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

const int numCourse = 7; //number of subjects
const int numStud = 10; //number of students

struct courseDetails{
	string courseName;
	string courseCode;
	int creditHour;
};

struct studDetails{
	string studName;
	int studID;
	float mark[numCourse];
	float gpa;
};

void calcGPA(studDetails[], courseDetails[]); //to calculate GPA
int countAD(studDetails[]); //to count the number of students who get Dean's list
void writeOutput(studDetails[]); //to write output into a file

int main(){
	ifstream read1;
	read1.open("course.txt");
	ifstream read2;
	read2.open("marks.txt");
	
	courseDetails subject[numCourse];
	studDetails student[numStud];
	int numAD;
	
	int j=0;
	while(!read1.eof()){
		getline(read1,subject[j].courseName,';');
		getline(read1,subject[j].courseCode,';');
		read1>>subject[j].creditHour;
		read1.ignore();
		j++;
	}
	
	int i=0;
	while(!read2.eof()){
		getline(read2,student[i].studName,';');
		read2>>student[i].studID;
		read2.ignore(1,';');
			for(int a=0; a<numCourse; a++){
				read2>>student[i].mark[a];
				read2.ignore(1,';');
			}
		i++;
	}
	
	calcGPA(student, subject);
	numAD = countAD(student);
	cout<<endl<<"Number of students who get Dean's List: "<<numAD;
	writeOutput(student);
	
	read1.close();
	read2.close();
	return 0;
}

void calcGPA(studDetails arr1[], courseDetails arr2[]){
	float pointer[numStud][numCourse], totalcredithour, y;
	
	for(int x=0;x<numCourse;x++){
		totalcredithour+=arr2[x].creditHour;
	}
	
	for(int i=0; i<numStud; i++){
		for(int j=0; j<numCourse; j++){
			if(arr1[i].mark[j]>=80)
				pointer[i][j]=4.00;
			else if(arr1[i].mark[j]>=75)
				pointer[i][j]=3.67;
			else if(arr1[i].mark[j]>=70)
				pointer[i][j]=3.33;
			else if(arr1[i].mark[j]>=65)
				pointer[i][j]=3.00;
			else if(arr1[i].mark[j]>=60)
				pointer[i][j]=2.67;
			else if(arr1[i].mark[j]>=55)
				pointer[i][j]=2.33;
			else if(arr1[i].mark[j]>=50)
				pointer[i][j]=2.00;
			else if(arr1[i].mark[j]>=47)
				pointer[i][j]=1.67;
			else if(arr1[i].mark[j]>=44)
				pointer[i][j]=1.33;
			else if(arr1[i].mark[j]>=40)
				pointer[i][j]=1.00;
			else if(arr1[i].mark[j]>=30)
				pointer[i][j]=0.67;
			else
				pointer[i][j]=0.00;
		}
	}
	cout<<left<<setw(19)<<"    Name"<<"  GPA"<<endl;
	for(int a=0;a<numStud;a++){
		y=0;
		for(int b=0;b<numCourse;b++){
			y=y+(pointer[a][b]*arr2[b].creditHour);
		}
		arr1[a].gpa=y/totalcredithour;
		cout<<fixed<<showpoint;
		cout<<right<<setw(2)<<a+1<<". ";
		cout<<left<<setw(15)<<arr1[a].studName<<": ";
		cout<<setprecision(2)<<arr1[a].gpa<<endl;
	}
}

int countAD(studDetails arr[]){
	int count=0;
	for(int i=0;i<numStud;i++){
		if(arr[i].gpa>=3.5)
			count+=1;
	}
	return count;
}

void writeOutput(studDetails arr[]){
	ofstream write1;
	write1.open("result list.txt");
	
	write1<<"--------------------------------------------------------\nNo.";
	write1<<left<<setw(21)<<" Student Name";
	write1<<left<<setw(10)<<"Student ID";
	write1<<left<<setw(9)<<"   GPA";
	write1<<"Dean's list?";
	write1<<"\n--------------------------------------------------------\n";
	
	for(int i=0; i<numStud; i++){
		write1<<right<<setw(2)<<i+1<<". ";
		write1<<left<<setw(20)<<arr[i].studName;
		write1<<left<<setw(13)<<arr[i].studID;
		write1<<fixed<<showpoint;
		write1<<left<<setw(9)<<setprecision(2)<<arr[i].gpa;
		if(arr[i].gpa>=3.5)
			write1<<"Yes\n";
		else
			write1<<"No"<<endl;
	}
	write1.close();
}

