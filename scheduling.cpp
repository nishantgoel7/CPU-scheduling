#include "iostream"


using namespace std;

int process[100][7]; //ID,bt,at,wt,tat,executed?(1 for yes),finish time

//int pno,att;//process-number, attribute
int n,t=0;//number of processes(remains cosntant)
int tw=0;


void disp(){
cout<<"\tpID\tBT\tAT\n";
for(int i=0;i<n;i++)
cout<<"\t"<<process[i][0]<<"\t"<<process[i][1]<<"\t"<<process[i][2]<<"\n";;
}//end disp

void disp_all(){
cout<<"\tpID\tBT\tAT\tWT\tTAT\texec?\n";
for(int i=0;i<n;i++)
{
  cout<<"\t"<<process[i][0]<<"\t"<<process[i][1]<<"\t"<<process[i][2]
      <<"\t"<<process[i][3]<<"\t"<<process[i][4]<<"\t"<<process[i][5]<<"\n";
}

cout<<"\n\nTime elapsed ::"<<t<<"\n Time wasted in waiting ::\t"<<tw<<endl;
}//end disp


void inp()
{
start:
cout<<"\n\n\n";
cout<<"Enter number of processes :\t";
cin>>n;
if(n<1){
cout<<"please enter number greater than 0";
goto start;
}
if(n>99){
cout<<"please enter number less than 90";
goto start;
}
int pno=0;

while(pno<n){ 					 //input loop
process[pno][0]=pno+1;
cout<<"\n Enter process burst time:\t";
cin>>process[pno][1];
cout<<"\n Enter process arrival time:\t";
cin>>process[pno][2];
process[pno][5]=0;
pno++;
}//end input loop

cout<<"\n You entered the values ::\n";
disp();

}//end input function

void swap(int p){
t=process[p][0];
process[p][0]=process[p+1][0];
process[p+1][0]=t;
t=process[p][1];
process[p][1]=process[p+1][1];
process[p+1][1]=t;
t=process[p][2];
process[p][2]=process[p+1][2];
process[p+1][2]=t;

t=process[p][3];
process[p][3]=process[p+1][3];
process[p+1][3]=t;
t=process[p][4];
process[p][4]=process[p+1][4];
process[p+1][4]=t;
t=process[p][5];
process[p][5]=process[p+1][5];
process[p+1][5]=t;
t=process[p][6];
process[p][6]=process[p+1][6];
process[p+1][6]=t;

}//end swap fn

void bbs(int srt){
int i,j;
for(i=0;i<n;i++){

for(j=0;j<n-i-1;j++){
if(process[j][srt]>process[j+1][srt]) //1 for burst time sorting,  2 for orrival time sorting
swap(j);
} //end innter for
}//end outer for
}//end bbs :: bt based bubble sort function

void sjf(){
int ctr=0,i=0;

bbs(1);
while (ctr<n) {
if (process[ctr][5]==1) {
  ctr++;

} else if (process[ctr][2]<=t) {
  process[ctr][3]=t-process[ctr][2];
  t+=process[ctr][1];
  process[ctr][4]=t-process[ctr][2];
  process[ctr][5]=1;
  process[ctr][6]=t;
  ctr++;

} else {
  int i=ctr+1;
  int cc=0;
  while (cc==0 && i<n) {
    if (process[i][2]<=t) {
      process[i][3]=t-process[i][2];
      t+=process[i][1];
      process[i][4]=t-process[i][2];
      process[i][5]=1;
      process[i][6]=t;
      cc=1;
    } else {
      i++;
    }
  }//while loop searching for next available process based on AT
  if(cc==0){
    t++;
    tw++;
  }

}//if next in queue process's AT is greater than elapsed time
}//competing loop for all processes
bbs(6);
}//end sjf

void fcfs(){
int ctr=0;

bbs(2);
while (ctr<n) {
if (process[ctr][2]<=t) {
  process[ctr][3]=t-process[ctr][2];
  t+=process[ctr][1];
  process[ctr][4]=t-process[ctr][2];
  process[ctr][5]=1;
  ctr++;

} else {
  t++;
  tw++;
  }/*/if current process's AT is greater than elapsed time*/
}
}/*/end fcfs*/


int main(){
int c;
inp();

start:

cout<<"\n Which scheduling method to use? \n 1. FCFS\n 2. SJF non-preemptive\n";
cin>>c;
switch (c){
  case 1: fcfs();
          break;
  case 2: sjf();
          break;
  default:  cout<<"\n Please enter \'1\' or \'2\' \n\n";
            goto start;
}

cout << "Order of execution :" << '\n';
disp_all();
return 0;
}//end main
