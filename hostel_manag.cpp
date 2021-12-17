#include<fstream>
#include<iostream>
#include<string.h>
#include<iomanip>
#include<vector>
using namespace std;
struct official
{
	char name[20],login[40],password[20];
};
class student
{
    public:
    char name[40],unique_id[80],roll_no[20],password[20];
    int room,absent,diet;
    char *ptr,*ptr1;
    student()
    {
        absent=0;
        diet=0;
    }
    void set_abs(int alpha)
    {
        absent=absent+(50*alpha);
    }
    void set_die(int beta)
    {
        diet=diet+(75*beta);
    }
    void die_pay(int amount1)
    {
        diet=diet-amount1;
    }
    void abs_pay(int amount2)
    {
        absent=absent-amount2;
    }
    void write(ofstream &os)
    {
        os.write(name,strlen(name));
        os<<ends;
        os.write(roll_no,strlen(roll_no));
        os<<ends;
        strcat(roll_no,name);
        strcpy(unique_id,roll_no);
        os.write(unique_id,strlen(unique_id));
        os<<ends;
        os.write(password,strlen(password));
        os<<ends;
        os.write((char*)&room,sizeof(room));
        os.write((char*)&absent,sizeof(absent));
        os.write((char*)&diet,sizeof(diet));
    }
    int read(ifstream &is)
    {
        is.get(name,40,0);
        name[is.gcount()]=0;
        is.ignore(1);
        is.get(roll_no,20,0);
        roll_no[is.gcount()]=0;
        is.ignore(1);
        is.get(unique_id,40,0);
        unique_id[is.gcount()]=0;
        is.ignore(1);
        is.get(password,20,0);
        password[is.gcount()]=0;
        is.ignore(1);
        is.read((char*)&room,sizeof(room));
        is.read((char*)&absent,sizeof(absent));
        is.read((char*)&diet,sizeof(diet));
        return is.good();
    }
    friend ostream & operator << (ostream &os,student &b);
    friend istream & operator >> (istream &is,student &b);
    friend ofstream &operator << (ofstream &fos,student &b)
    {
        int i=0;
        b.write(fos);
        i++;
        return fos;
    }
    friend ifstream &operator >> (ifstream &fos,student &b)
    {
        int j=0;
        b.read(fos);
        j++;
        return fos;
    }
    friend class Rooms;
};
istream &operator >> (istream &is,student &b)
{
    cout << "Name : ";
    is>>ws;
    is.get(b.name,40);
    cout << "roll number :";
    is>>ws;
    is.get(b.roll_no,20);
    cout << "room no.:";
    is>>ws>>b.room;
    cout << "Generate a strong password." << endl;
    is>>ws;
    is.get(b.password,20);
    return is;
}
ostream &operator << (ostream &os,student &b)
{
    os << b.name << endl;
    os << b.unique_id << endl;
    os << b.roll_no << endl;
    os << b.room << endl;
    os << b.password << endl;
    os << b.absent << endl;
    os << b.diet << endl;
    return os;
}
class Rooms
{
    int empty;
    public:
    Rooms()
    {
        empty=5;
    }
    
    void setdata()
    {
        empty=empty-1;
    }
    int give()
    {
        return empty;
    }
    void display()
    {
        cout << empty << endl;
    }
} r[5];
void info()
{
    cout << "Dietry charge is Rs. 75.00 per meal." << endl;
    cout << "If any student fails to appear in attendance then Rs. 50.00 fine per absent, will be imposed on the student. " << endl;
}
int read_fine(char *x,char *y)
{
    student st[25];
    int i=0,j,k;
    ifstream i_read("students_data.txt",ios::binary);
    while(1)
    {
        i_read>>st[i];
        if(i_read.fail())
        break;
        i++;
    }
    for(int j=0;j<i;j++)
    {
        if(strcmp(st[j].unique_id,x)==0&&strcmp(st[j].password,y)==0)
        {
            cout << "You have taken meal for " << (st[j].diet)/75 << " days" << endl;
            cout << "Your total mess charges are Rs. " << st[j].diet << endl;
            cout << "You have absent for " << (st[j].absent)/50 << " days" << endl;
            cout << "You have to pay Rs. " << st[j].absent << " fine" << endl; 
            k=1;
            break;
        }
        
    }
    if(k==1)
    return 0;
    else
    {
        cout << "Please enter correct details!" << endl;
        return 1;
    }
    
}
int pay_fine(char *pay1,char *pay2)
{
    student st[25];
    int i=0,j,k,pay_choice,die_am,abs_am,dis1,dis2;
    ifstream i_pay("students_data.txt",ios::binary);
    while(1)
    {
        i_pay>>st[i];
        if(i_pay.fail())
        break;
        i++;
    }
    i_pay.close();
    for(int j=0;j<i;j++)
    {
        if(strcmp(st[j].unique_id,pay1)==0&&strcmp(st[j].password,pay2)==0)
        {
            cout << "You have taken meal for " << (st[j].diet)/75 << " days" << endl;
            cout << "Your total mess charges are Rs. " << st[j].diet << endl;
            cout << "You have absent for " << (st[j].absent)/50 << " days" << endl;
            cout << "You have to pay Rs. " << st[j].absent << " fine" << endl; 
            cout << "Enter 1 for paying dietry charges and 2 for paying fine for absents : ";
            cin >> pay_choice;
            if(pay_choice==1)
            {
                cout << "Enter amount you would like to pay : ";
                cin >> die_am;
                dis1=st[j].diet;
                st[j].die_pay(die_am);
                cout << "You have successfully paid Rs " << die_am << endl;
                cout << "Your new dietry charges are Rs " << dis1-die_am << endl;
            }
            else if(pay_choice==2)
            {
                cout << "Enter amount you would like to pay : ";
                cin >> abs_am;
                dis2=st[j].absent;
                st[j].abs_pay(abs_am);
                cout << "You have successfully paid Rs " << abs_am << endl;
                cout << "Your pending fine amount is Rs " << dis2-abs_am << endl;
            }
            k=1;
            break;
        }
        
    }
    
    if(k==1)
    {
        ofstream o_pay("students_data.txt",ios::trunc|ios::binary);
        for(int x=0;x<i;x++)
        {
            o_pay<<st[x];
        }
        o_pay.close();
        return 0;
    }
    
    else
    {
        cout << "Please enter correct details!" << endl;
        return 1;
    }
}
int edit_att(char *a,char *b)
{
    int i=0,k=0,j=0,days;
    student st[25],s1;
    ifstream i_off("students_data.txt",ios::binary);
    while(1)
    {
        i_off>>st[i];
        if(i_off.fail())
        break;
        i++;
    }
    i_off.close();
    for(int j=0;j<i;j++)
    {
        if(strcmp(a,st[j].unique_id)==0&&strcmp(b,st[j].roll_no)==0)
        {
            cout << "Enter number of absents of roll number " << st[j].roll_no << " : ";
            cin >> days;
            st[j].set_abs(days);
            k=1;
            break;
        }
    }
    ofstream o_off("students_data.txt",ios::trunc|ios::binary);
    if(k==1)
    {
        for(int a=0;a<i;a++)
        {
            o_off<<st[a];
        }
        o_off.close();
        return 1;
    }
    else
    {
        cout << "You entered wrong uniqueid or roll number!" << endl;
        cout << "Please try again." << endl;
        return 0;
    }
}
int edit_die(char *e,char *f)
{
    int i=0,k=0,j=0,days;
    student st[25],s1;
    ifstream i_off("students_data.txt",ios::binary);
    while(1)
    {
        i_off>>st[i];
        if(i_off.fail())
        break;
        i++;
    }
    i_off.close();
    for(int j=0;j<i;j++)
    {
        if(strcmp(e,st[j].unique_id)==0&&strcmp(f,st[j].roll_no)==0)
        {
            cout << "Enter number of days on which student has taken meal. " << st[j].roll_no << " : ";
            cin >> days;
            st[j].set_die(days);
            k=1;
            break;
        }
    }
    ofstream o_off("students_data.txt",ios::trunc|ios::binary);
    if(k==1)
    {
        for(int a=0;a<i;a++)
        {
            o_off<<st[a];
        }
        o_off.close();
        return 1;
    }
    else
    {
        cout << "You entered wrong uniqueid or roll number!" << endl;
        cout << "Please try again." << endl;
        return 0;
    }
}
void read_room()
{
    student st[25];
    int i=0,j=0;
    ifstream i_file("students_data.txt",ios::binary);
    cout << "Maximum five vacancies are allowed in a room." << endl;
    while(1)
    {
        i_file >> st[i];
        if(i_file.fail())
        break;
        i++;
    }
    for(int k=0;k<i;k++)
    r[st[k].room-1].setdata();
    for(int x=0;x<=4;x++)
    {
        cout << " Vacancies in Room number " << x+1 << "are : ";
        r[x].display();
    }

    
}
void write_data()
{
    student st[25];
    char pass_test[20];
    int i=0,j=0,pass=0;
    int flag=0;
    ofstream ofile("students_data.txt",ios::app|ios::binary);
    char ch;
    do
    {
        
        cin >> st[i];
        r[st[i].room-1].setdata();
        if(r[st[i].room-1].give()<0)
        {
            cout << "Please enter valid room number!" << endl;
            flag=1;
        }
        else
        {
            do
            {
                cout << "Verify your password : ";
                cin >> pass_test;
                if(strcmp(pass_test,st[i].password)==0)
                {
                    cout << "Password verified." << endl;
                    pass=1;
                }
                else
                cout << "You entered wrong password!" << endl;
            } while (pass==0);
        }
        if(flag==0)
        {
            ofile << st[i];
        }
        
        i++;
        flag=0;

    } while (flag==1);
    ofile.close();
    cout << "Your uniqueid is : " << st[i-1].unique_id << endl;
    cout << "Memorise your uniqueid ans password for further use." << endl;
    

}
int read_off(char *off1,char *off2)
{
	official mem[5];
	
}
int main()
{
    int start_choice;
    cout << "WELCOME to NIT KURUKSHETRA" << endl;
    cout << "Enter 1 if you are a new student." << endl;
    cout << "Enter 2 if you want to know about dietry charges and fine imposed on students per absent" << endl;
    cout << "Enter 3 if you want to know your dietry charges or fine to be paid." << endl;
    cout << "Enter 4 if you want to pay your dietry charges or attendance fine." << endl;
    cout << "Enter 5 if you are an official." << endl;
    cin >> start_choice;
    if(start_choice==1)
    {
        read_room();
        cout << "Enter your details : " << endl;
        write_data();
    }
    else if(start_choice==2)
    {
        info();
    }
    else if(start_choice==3)
    {
        char start_uniq[80],start_pass[20];
        int ret;
        char edit;
        do
        {
            do
            {
                cout << "Enter your uniqueid : ";
                cin >> start_uniq;
                cout << "Enter your password : ";
                cin >> start_pass;
                cout << "Want to edit your details? (y/n) ";
                cin >> edit;
            } while (toupper(edit)=='Y');
            ret=read_fine(start_uniq,start_pass);
        } while (ret!=0);
        
    }
    else if(start_choice==4)
    {
        char pay_id[80],pay_pass[20],pay_edit;
        int pay_ret;
        do
        {
            do
            {
                cout << "Enter your uniqueid : ";
                cin >> pay_id;
                cout << "Enter your password : ";
                cin >> pay_pass;
                cout << "Want to edit your details? (y/n) ";
                cin >> pay_edit;
            } while (toupper(pay_edit)=='Y');
            pay_ret=pay_fine(pay_id,pay_pass);
        } while (pay_ret!=0);
        
    }
    else if(start_choice==5)
    {
        int off_choice;
        int flag1,flag2;
        student s_off;
        char edit_roll[20],edit_id[40],con_choice,con_choice2,logiid[40],log_pass[20];
        cout << "Enter your login id : " ;
        cin >> loginid;
        cout << "Enter your password : ";
        cin >> log_pass;
        cout << "Enter 1 for editing attendance of students." << endl;
        cout << "Enter 2 for editing mess charges of students." << endl;
        cin >> off_choice;
        if(off_choice==1)
        {
            do
            {
                do
                {
                    cout << "Enter roll number of student who was absent in roll call : ";
                    cin >> edit_roll;
                    cout << "Enter uniqueid of student : ";
                    cin >> edit_id;
                    flag1=edit_att(edit_id,edit_roll);
                } while (flag1!=1);
                cout << "Want to continue? (y/n)";
                cin >> con_choice;
            } while (toupper(con_choice)=='Y');
            
            
        }
        else
        {
            do
            {
                do
                {
                    cout << "Enter roll number of student whose mess charges are to be updated : ";
                    cin >> edit_roll;
                    cout << "Enter uniqueid of student : ";
                    cin >> edit_id;
                    flag2=edit_die(edit_id,edit_roll);
                } while (flag2!=1);
                cout << "Want to continue? (y/n)";
                cin >> con_choice2;
            } while (toupper(con_choice2)=='Y');
        }
    }
    return 0;
}
