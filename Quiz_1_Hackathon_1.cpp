
#include<bits/stdc++.h>

using namespace std;

class Hospital {
    public:

        string Hname;
        vector<pair<string, string>> donors_type;
        bool bloodBank;
        bool bloodDon;        

        void addHospital() {
            int temp;
            fflush(stdin);
            cout<<"Enter the name of the hospital : ";
            getline(cin, Hname);
            fflush(stdin);
            cout<<"It has a blood bank. (1/0) : ";
            cin>>temp;
            if(temp == 1){ bloodBank = true ;}
            else{ bloodBank = false; }
            fflush(stdin);
            cout<<"It has a blood donation camp. (1/0) : ";
            cin>>temp;
            if(temp == 1){ bloodDon = true ;}
            else{ bloodDon = false; }
        }

        void addDonor(string name, string bloodType) {
            donors_type.push_back(make_pair(name, bloodType));
        }

        void displayList() {
            for(int i = 0; i < donors_type.size(); i++) {
                cout<<donors_type[i].first<<" "<<donors_type[i].second<<endl;
            }
        }

        int reqResponse(string name, string bloodType) {
            for(int i = 0; i < donors_type.size(); i++) {
                if(bloodType == donors_type[i].second) {
                    cout<<"Mr. "<<donors_type[i].first<<" Do you wish to donate blood for "<<"Mr. "<<name<<"'s request. (Yes/No) : ";
                    string res;
                    cin>>res;
                    if(res == "Yes"){
                        cout<<"Blood request successfully responded.\n";
                        return 1;
                    }
                }
            }
            return 0;
        }

        void rareBloodList() {
            cout<<"Rare Blood Groups in "<<Hname<<" Blood Bank : "<<endl;
            for(int i = 0; i < donors_type.size(); i++) {
                if("AB+" == donors_type[i].second || "AB-" == donors_type[i].second || "B-" == donors_type[i].second) {
                    cout<<"Name : "<<donors_type[i].first<<endl<<"Blood Group : "<<donors_type[i].second<<endl;
                }
            }
        }
};

class User {
    public:
        
        string Uname;
        string bloodType;
        string bloodTReq;

        User() {
            fflush(stdin);
            cout<<"Enter your name : ";
            getline(cin, Uname);
            fflush(stdin);
            cout<<"Enter your blood type : ";
            getline(cin, bloodType);
        }

        void generateRequest() {
            cout<<"Enter blood type request (A+ or B- or AB+ likewise) : ";
            cin>>bloodTReq;
        }
    
};

class Admin {
    protected:
        vector<Hospital> Hlist;
        vector<User> Ulist;

    public:

        void addHospital() {
            Hospital temp;
            temp.addHospital();
            Hlist.push_back(temp);
        }

        void viewDonorList(int index) {
            cout<<"The Donor List of "<<Hlist[index].Hname<<" : "<<endl;
            Hlist[index].displayList();
        }

        void addDonor(int index, string name, string bloodType) {
            Hlist[index].addDonor(name, bloodType);
        }

        void displayHlist() {
            cout<<"The Hospitals under Admin's DataBase are : "<<endl;
            for(int i = 0; i < Hlist.size(); i++) {
                cout<<i+1<<". "<<Hlist[i].Hname<<endl;
            }
        }

        void generateReq() {
            User temp;
            temp.generateRequest();
            Ulist.push_back(temp);
        }

        void reqResponse() {
            cout<<"Enter the request id to response : ";
            displayUlist();
            int temp;
            cin>>temp;
            int res;
            for(int i = 0; i < Hlist.size(); i++) {
                res = Hlist[i].reqResponse(Ulist[temp-1].Uname, Ulist[temp-1].bloodTReq);
                if(res == 1){
                    vector<User>::iterator it = Ulist.begin(); 
                    for(int i = 0; i < temp-1; i++) {
                        it++;
                    }
                    Ulist.erase(it);
                    break;
                }
            }
            if(res == 0) {
                cout<<"Blood request has been not fulfilled, Please wait for some more time.\n";
            }
        }

        void displayUlist() {
            for(int i = 0; i < Hlist.size(); i++) {
                cout<<endl<<i+1<<" "<<Ulist[i].Uname<<" "<<Ulist[i].bloodTReq<<endl;
            }
        }

        void rareBloodList() {
            for(int i = 0; i < Hlist.size(); i++) {
                Hlist[i].rareBloodList();
                cout<<endl;
            }
        }
};

int main() {
    Admin admin;
    int choice1, choice2, flag = 0, ID;
    string Dname;
    string DBtype;
    do{
        cout<<"1. Get Access of Admin"<<endl<<"2. Get Access of User"<<endl<<"0. Exit Program"<<endl;
        cin>>choice1;
        switch(choice1){
            case 0:
                return 0;
        
            case 1:
                do{
                    cout<<"Enter the operation ID to perform : "<<endl;
                    cout<<"1. Add Hospital"<<endl
                        <<"2. Add Donor"<<endl
                        <<"3. View Hospital List"<<endl
                        <<"4. View Donor List"<<endl
                        <<"5. Response to Blood Group Request"<<endl
                        <<"6. View Rare Blood Group List"<<endl
                        <<"7. Go Back to initial Menu"<<endl
                        <<"0. Exit Program"<<endl;
                    cin>>choice2;
                    switch(choice2){
                        case 0:
                            return 0;

                        case 1:
                            admin.addHospital();
                            cout<<endl;
                            break;
                        
                        case 2:
                            admin.displayHlist();
                            fflush(stdin);
                            cout<<"Enter the Hospital to add Donor : ";
                            cin>>ID;
                            fflush(stdin);
                            cout<<endl<<"Enter Donor Name : ";
                            getline(cin, Dname);
                            fflush(stdin);
                            cout<<endl<<"Enter Donor Blood Type : ";
                            getline(cin, DBtype);
                            admin.addDonor(ID - 1, Dname, DBtype);
                            cout<<endl;
                            break;

                        case 3:
                            admin.displayHlist();
                            cout<<endl;
                            break;

                        case 4:
                            admin.displayHlist();
                            cout<<"Enter the Hospital ID to view Donors : ";
                            fflush(stdin);
                            cin>>ID;
                            admin.viewDonorList(ID-1);
                            cout<<endl;
                            break;

                        case 5:
                            admin.reqResponse();
                            cout<<endl;
                            break;

                        case 6:
                            admin.rareBloodList();
                            cout<<endl;
                            break;
                        
                        case 7:
                            flag = 1;
                            break;

                        default:
                            cout<<"Enter Valid ID number"<<endl;
                            break;
                    }

                    if (flag == 1) {
                        flag = 0;
                        break;
                    }
                }while(choice2 != 0);
                break;

            case 2:
                cout<<"Requesting Blood Group : "<<endl;
                admin.generateReq();
                break;

            default:
                cout<<"Enter a valid ID\n";
                break;
        }
    }while(choice1 != 0);
}
