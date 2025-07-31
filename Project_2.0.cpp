#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<stdio.h>
using namespace std;
fstream file,file1;
class product{
    int pno;
    string name;
    float price,qty,tax,dis;
    public:
        void create();
        void show();
        void write();
        void display();
        void admin();
        void search(int n);
        void modify(int n);
        void del(int n);
        void order();
        void menu();
};

void product::create(){
    cout<<"\n\nPlease Enter the Product ID:";
    cin>>pno;
    cout<<"\n\nPlease Enter the Name of Product:";
    cin>>name;
    cout<<"\n\nPlease Enter the Price of Product:";
    cin>>price;
    cout<<"\n\nPlease Enter the Discount on Product(%):";
    cin>>dis;
}

void product::show(){
    cout<<"\nThe ID of Product: "<<pno<<endl;
    cout<<"The name of Product: "<<name<<endl;
    cout<<"The Price of Product: "<<price;
    cout<<"\nDiscount: "<<dis<<"%";
}

void product::write(){
    file.open("shop.txt",ios::out|ios::app);
    create();
    file<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" "<<endl;
    file.close();
    cout<<"\n\nThe Product has been created ";
    getch();
}

void product::display(){
    system("cls");
    cout<<"\n\n\tDisplay All Records !!!\n\n";
    file.open("shop.txt",ios::in);
    if(!file){
        cout<<"\n\nFile not found!";
        getch();
        return;
    }
    file>>pno>>name>>price>>dis;
    while(!file.eof()){
        show();
        cout<<"\n\n----------------------------------------------------------";
        file>>pno>>name>>price>>dis;
    }
    file.close();
    getch();
}

void product::search(int n){
    int isfound=0;
    file.open("shop.txt",ios::in);
    if(!file){
        cout<<"\n\nFile not found!";
        getch();
        return;
    }
    file>>pno>>name>>price>>dis;
    while(!file.eof()){
        if(pno==n){
            system("cls");
            show();
            isfound=1;
            break;
        }
        file>>pno>>name>>price>>dis;
    }
    file.close();
    if(isfound==0)
        cout<<"\n\nNo Record Found!";
    getch();
}

void product::modify(int n){
    int isfound=0;
    system("cls");
    cout<<"\n\nModify Products ";
    file.open("shop.txt",ios::in);
    if(!file){
        cout<<"\n\nFile not found!";
        getch();
        return;
    }
    file1.open("shop1.txt",ios::out);
    file>>pno>>name>>price>>dis;
    while(!file.eof()){
        if(pno==n){
            show();
            cout<<"\n\nPlease Enter the New Details\n";
            create();
            file1<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" "<<endl;
            cout<<"\n\n\tRecord Updated Successfully!";
            isfound=1;    
        }
        else
            file1<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" "<<endl;
        file>>pno>>name>>price>>dis;    
    }
    file.close();
    file1.close();
    remove("shop.txt");
    rename("shop1.txt","shop.txt");
    if(isfound==0)
        cout<<"\n\nNo Record Found!";
    getch();
}

void product::del(int n){
    int isfound=0;
    file.open("shop.txt",ios::in);
    if(!file){
        cout<<"\n\nFile not found!";
        getch();
        return;
    }
    file1.open("shop1.txt",ios::out);
    file>>pno>>name>>price>>dis;
    while(!file.eof()){
        if(pno==n){
            cout<<"\n\n\tRecord Deleted!";
            isfound=1;    
        }
        else
            file1<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" "<<endl;
        file>>pno>>name>>price>>dis;
    }
    file.close();
    file1.close();
    remove("shop.txt");
    rename("shop1.txt","shop.txt");
    if(isfound==0)
        cout<<"\n\n\tNo Record Found!";
    getch();
}

void product::menu(){
    system("cls");
    file.open("shop.txt",ios::in);
    if(!file){
        cout<<"\n\nFile not found!";
        getch();
        return;
    }
    cout<<"\n\n-----Product Menu-----\n\n";
    cout<<"----------------------------------------------------------\n";
    cout<<"ID\t\tName\t\tPrice\n";
    cout<<"----------------------------------------------------------\n";
    file>>pno>>name>>price>>dis;
    while(!file.eof()){
        cout<<pno<<"\t\t"<<name<<"\t\t"<<price<<"\n";
        file>>pno>>name>>price>>dis;
    }
    file.close();
}

void product::order(){
    int order_arr[50],quan[50],c=0;
    float amt=0,damt=0,total=0;
    char ch;
    file.open("shop.txt", ios::in);
    if(file){
        file.close();
        menu();
        cout<<"\n------------------------------";
        cout<<"\n\tPlace your Order\n";
        cout<<"------------------------------";
        do{
            cout<<"\n\nEnter the Product ID:";
            cin>>order_arr[c];
            cout<<"\nQuantity of this product:";
            cin>>quan[c];
            c++;
            cout<<"\nAdd another Product(y/n)?";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
        cout<<"\n\n-----Thank You For Placing Your Order-----";
        getch();
        system("cls");
        cout<<"\n-----------------Invoice---------------------";
        cout<<"\nProduct Details:\n\n";
        cout<<"ID"<<setw(10)<<"Name"<<setw(15)<<"Quantity"<<setw(15)<<"Price"<<setw(15)<<"Amount"<<setw(15)<<fixed<<"Amount after Discount\n";
        for(int i=0;i<c;i++){
            file.open("shop.txt",ios::in);
            file>>pno>>name>>price>>dis;
            while(!file.eof()){
                if(pno==order_arr[i]){
                    amt=price*quan[i];
                    damt=amt-(amt/100*dis);
                    cout<<endl<<order_arr[i]<<setw(8)<<name<<setw(15)<<quan[i]<<setw(15)<<price<<setw(15)<<amt<<setw(15)<<damt<<endl;
                    total+=damt;
                }
                file>>pno>>name>>price>>dis;
            }
            file.close();
        }
        cout<<"\n\nTotal Amount: "<<total<<endl;
        getch();
    }
    else{
        cout<<"\n\nNo products available!";
        getch();
    }
}

void product::admin(){
    system("cls");
    int choice;
    cout<<"\n\n\tADMIN MENU\n\n\t01. Create Product\n\n\t02. Display All Products\n\n\t03. Search Product\n\n\t04. Modify Product\n\n\t05. Delete Product\n\n\t06. View Product Menu\n\n\t07. Back to Main Menu\n\n\tPlease Enter your choice(1-7) ";
    cin>>choice;
    switch(choice){
        case 1:
            system("cls");
            write();
            break;
        case 2:
            display();
            break;
        case 3:
            int num;
            system("cls");
            cout<<"\n\n\tPlease Enter the Product ID:";
            cin>>num;
            search(num);
            break;
        case 4:
            system("cls");
            cout<<"\n\n\tPlease Enter the Product ID to modify:";
            cin>>num;
            modify(num);
            break;
        case 5:
            system("cls");
            cout<<"\n\n\tPlease Enter the Product ID to delete:";
            cin>>num;
            del(num);
            break;
        case 6:
            menu();
            getch();
            break;
        case 7:
            return;
        default:
            cout<<"\a";
            getch();
    }
    admin();
}

int main(){
    product p;
    h:
    int choice;
    system("cls");
    cout<<"-------------Welcome to Bulbulay Billing system-------------\n\n\tMain Menu\n\n\t01. CUSTOMER\n\n\t02. ADMIN\n\n\t03. Exit\n\n\tPlease select an option(1-3)";
    cin>>choice;
    switch(choice){
        case 1:
            system("cls");
            p.order();
            break;
        case 2:
            p.admin();
            break;
        case 3:
            exit(0);
        default:
            cout<<"\a";
            getch();
    }
    goto h;
}
