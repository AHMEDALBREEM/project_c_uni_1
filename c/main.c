#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <Windows.h>
#include<time.h>
FILE *user,*newdatauser,*a;
FILE *ticket,*new_ticket;
FILE *last_operation,*new_last_operation;
FILE *tmp;
#define dont_care sleep(2);system("cls");
typedef struct _syst
{
    int wYear;
    int wMonth;
    int wDay;
    int wDayOfWeek;
} syst;
typedef struct _syst2
{
    WORD wYear;
    WORD wMonth;
    WORD wDay;
    WORD wDayOfWeek;
} syst2;

typedef struct ticket_info_onedirect
{
    int id;
    char from[50];
    char where[50];
    char date[50];
    int price;
    int t_visa_req;
    int t_cov_req;
} ticket_info_onedir;

typedef struct ticket_info_twodirect
{
    int id;
    char from[50];
    char where[50];
    char date_go[50];
    char date_ret[50];
    int price;
    int t_visa_req;
    int t_cov_req;
} ticket_info_twodir;

int main()
{
    start();
    remove("tmp.txt");
    return 0;
}

void start()
{
    int x;
    char username[50];
    char password[50];
    printf("welcome to our system for airlines tickets ");
    printf("\n 1-Login \n 2-Sgin up \n 3-Exit\n");
    printf("Enter the number : ");
    scanf("%d",&x);
    int y;
    if(x==1)
    {
        system("cls");
        printf("Enter the username : ");
        scanf("%s",username);
        printf("Enter the password : ");
        scanf("%s",password);
        y = login(username,password);
        if(y==1)
        {
            printf("You signed in sussuccfly");
            dont_care;
            user_dashboard(username);
        }
        if(y==2)
        {
            printf("You signed in sussuccfly");
            dont_care;
            admin_dashboard();

        }
        if(y==-1)
        {
            printf("sorry , your account blocked in our system");
            dont_care;
            start();
        }
        if(y==0)
        {
            printf("sorry , you don't have any account in our system ");
            dont_care;
            start();
        }
    }
    if(x==2)
    {
        sginup();
    }
    if(x==3)
    {
        exit(1);
    }
    else
    {
        dont_care
        printf("check the input \n");
        start();
    }
}

int login(char *username_req,char *password_req)
{
    char buffer[1024],username[50],password[50];
    int access,admin_access,co_cert,visa_cert;
    int balance;
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
    }
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if(!(strcmp(username,username_req))&&(!(strcmp(password_req,password)))&&(access ==1))
        {
            if(admin_access ==1)
            {
                return 2;
            }
            if(admin_access ==0)
            {
                return 1;
            }
        }
        if(!(strcmp(username,username_req))&&(!(strcmp(password_req,password)))&&(access ==0))
        {
            return -1;
        }
    }
    fclose(user);
    return 0;
}

void sginup()
{
    int x;
    char username[50],password[50],last_operation[500];
    int access=1,admin_access=0,co_cert=0,visa_cert=0;
    int balance=1000000;
    printf("Enter the username : ");
    scanf("%s",username);
    if((check_username(username)))
    {
        printf("Enter the password (it's must Contain Capital and Small letter and Numbers) : ");
        scanf("%s",password);
        if(check_strngth(password))
        {
            user = fopen("user.txt","a");
            if(user==NULL)
            {
                user = fopen("user.txt","w");
            }
            fprintf(user," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username,password,access,admin_access,balance,co_cert,visa_cert);
            fclose(user);
            printf("Signed up succssefily \n");
        }
        else
        {
            printf("Check the strength of the password !! (it's must Contain Capital and Small letter and Numbers the password must be also more the 8 )");
        }
    }
    else
    {
        printf("Try Another Username !!\n");
    }
    printf("\n 1- go back \n 2- exit \n Enter the spacifc number : ");
    scanf("%d",&x);
    if(x==1)
    {
        dont_care
        start();
    }
    else
    {
        dont_care
        exit(1);
    }

}

int check_strngth(char* password)
{
    int temp=0,i,enable1=1,enable2=1;
    for(i=0; i<strlen(password); i++)
    {
        if((((password[i]<=90)&&(password[i]>=(65)))&&(enable1))||((password[i]<=122)&&(password[i]>=(97))&&(enable2)))
        {
            temp++;
            enable1=0;
            enable2=0;
        }
    }
    if((temp)&&(strlen(password)>8))
    {
        return 1;
    }
    return 0;
}
void user_dashboard(char *username)
{
    sort_ticket();
    printf("Welcome to user panel \n\n");
    avaliavility(username);
    printf("1 - Buy ticket \n");
    printf("2 - Return ticket \n");
    printf("3 - View account \n");
    printf("4- Logout \n");
    printf("Enter the number : ");
    int y;
    scanf("%d",&y);
    if(y==1)
    {
        dont_care
        buy_ticket(username);
    }
    else if(y==2)
    {
        dont_care
        return_ticket(username);
    }
    else if(y==3)
    {
        dont_care
        user_inf(username);
    }
    else if(y==4)
    {
        dont_care
        start();
    }
    else
    {
        dont_care
        printf("Check the input \n");
        user_dashboard(username);
    }
}

void user_inf(char *username)
{
    int x,c;
    char username1[100];
    view_info_user(username);
    printf("\n 1- Delete your account \n 2- go back \n 3- exit \n Enter the spacifc number : ");
    scanf("%d",&x);
    if(x==1)
    {
        printf("Do you want to transfer your balance ? \n 1- Yes \n 2- No \n");
        scanf("%d",&c);
        if(c==1)
        {
            printf("Enter the username you want to trasfer to him : ");
            scanf("%s",username1);
            if(!(strcmp(username,username1)))
            {
                printf(" You can't transfer to yourself !! \n");
                dont_care user_inf(username);
            }
            transfer_balance(username,save_balance(username),username1);
            dont_care
            delete_account(username);
            start();
        }
        if(c==2)
        {
            dont_care
            delete_account(username);
            start();
        }
    }
    else if(x==2)
    {
        dont_care
        user_dashboard(username);
    }
    else if(x==3)
    {
        dont_care
        exit(1);
    }
}
int save_balance(char *username)
{
    char password[100],username_tmp[100];
    int access,admin_access,x,co_cert,visa_cert;
    int balance;
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024];
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username_tmp,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if(!(strcmp(username,username_tmp)))
        {
            return balance;
        }
    }
    fclose(user);
}
void transfer_balance(char *username,int balance_moved,char *username1)
{
    user = fopen("user.txt","r");
    if(user == NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024],user_tmp[100],password[100];
    int access,admin_access,co_cert,visa_cert;
    int balance,founded;
    tmp = fopen("tmp.txt","w");
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",user_tmp,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if((!(strcmp(username1,user_tmp))))
        {
            founded=1;
            sprintf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",user_tmp,password,access,admin_access,(balance+balance_moved),co_cert,visa_cert);
            fputs(buffer,tmp);
        }
        else
        {
            fputs(buffer,tmp);
        }

    }
    fclose(tmp);
    fclose(user);
    tmp = fopen("tmp.txt","r");
    user = fopen("user.txt","w");
    while(fgets(buffer,1024,tmp)!=NULL)
    {
        fputs(buffer,user);
    }
    fclose(tmp);
    fclose(user);
    if(founded!=1)
    {
        printf("check the username !!");
        dont_care user_inf(username);
    }
    remove("tmp.txt");
}
void delete_account(char *username1)
{
    int x;
    printf("Please , Can you support us ? \n if you want to support us ENTER 1 otherwise ENTER 2 \n");
    scanf("%d",&x);
    if(x==1)
    {
        system("start https://forms.gle/LyZPqeZxzVf6mcCG7");
    }
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024],user_tmp[100],password[100];
    int access,admin_access,co_cert,visa_cert;
    int balance;
    tmp = fopen("tmp.txt","w");
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",user_tmp,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if(((strcmp(username1,user_tmp))))
        {
            fputs(buffer,tmp);
        }
    }
    fclose(tmp);
    fclose(user);
    tmp = fopen("tmp.txt","r");
    user = fopen("user.txt","w");
    while(fgets(buffer,1024,tmp)!=NULL)
    {
        fputs(buffer,user);
    }
    fclose(tmp);
    fclose(user);
    remove("tmp.txt");
    delete_operation(username1);
    printf("your account is deleted !! ");
    dont_care
}
void return_ticket(char *username)
{
    int z=0,c;
    char username1[100],date[100],buffer[1024];
    int price,id,req_ref,ref;
    printf("Enter the referance of that ticket : ");
    scanf("%d",&req_ref);
    last_operation = fopen("last_operation.txt","r");
    if(last_operation==NULL)
    {
        last_operation = fopen("last_operation.txt","w");
    }
    while(fgets(buffer,1024,last_operation)!= NULL)
    {
        sscanf(buffer,"*REF %d : username %s bought ticket %d in %s with price %d *\n",&ref,username1,&id,date,&price);
        if((ref==req_ref)&&(!(strcmp(username,username1))))
        {
            z=1;
        }
        sscanf(buffer,"REF %d : username %s bought ticket %d in %s with price %d \n",&ref,username1,&id,date,&price);
        if((ref==req_ref)&&(!(strcmp(username,username1)))&&(z!=1))
        {
            c = add_balance(req_ref,username,id,date,price);
            if(c)
            {
                printf("returned done to your account !!");
                dont_care
                user_dashboard(username);
            }
            else if (!c)
            {
                printf("sorry , you actions is blocked from our system !!");
                dont_care
                user_dashboard(username);
            }
        }
    }
    printf("please check your id of the flight and try again . \n");
    dont_care user_dashboard(username);
    fclose(last_operation);
}
void buy_ticket(char *username)
{
    int id,x=0,z=0,c,k,fixed_price;
    char date[1024];
    int o;
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    printf("Enter the ID of the flight : \n");
    scanf("%d",&id);
    ticket = fopen("ticket.txt","r");
    if(ticket==NULL)
    {
        ticket = fopen("ticket.txt","w");
    }
    char buffer[1024];
    printf("\n");
    float ysum=0,msum=0,dsum=0;
    struct _syst2 today;
    struct _syst2 sp_date;
    GetSystemTime(&today);
    sprintf(date,"%hu/%hu/%hu",today.wDayOfWeek,today.wMonth,today.wYear);
    while(fgets(buffer,1024,ticket)!= NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if(tk_on.id==id)
        {
            z=1;
            sscanf(tk_on.date,"%hu/%hu/%hu",&sp_date.wDayOfWeek,&sp_date.wMonth,&sp_date.wYear);
            k = compare_dates(sp_date,today);
            if(sp_date.wYear>today.wYear)
            {
                ysum=sp_date.wYear-today.wYear;
            }
            if(sp_date.wMonth>today.wMonth)
            {
                msum=sp_date.wMonth-today.wMonth;
            }
            if(sp_date.wDayOfWeek>today.wDayOfWeek)
            {
                dsum=sp_date.wDayOfWeek-today.wDayOfWeek;
            }
            o=((dsum)+(msum*30)+(ysum*365));
            printf(" the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",tk_on.id,tk_on.from,tk_on.where,tk_on.date,tk_on.price*o,tk_on.t_cov_req,tk_on.t_visa_req);
            printf("Do you want to confirm the order ? \n1-YES \n2-NO \n Enter the spacifc number ? \n");
            scanf("%d",&x);
            if(x==1)
            {
                if(k==1)
                {

                    c = edit_balance(username,(tk_on.price*o));
                    if(c==1)
                    {
                        printf("You bought the ticket successfully \n");
                        dont_care
                        save_bought_operation(username,id,date,(tk_on.price*o));
                        user_dashboard(username);
                    }
                    else if(c==-1)
                    {
                        printf("sorry , you balance not enough !!");
                        dont_care
                        user_dashboard(username);
                    }
                }
            }
            else if(x==2)

            {
                dont_care
                user_dashboard(username);
            }
        }
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
        if((tk_tw.id==id)&&(z!=1))
        {
            sscanf(tk_tw.date_go,"%hu/%hu/%hu",&sp_date.wDayOfWeek,&sp_date.wMonth,&sp_date.wYear);
            k = compare_dates(sp_date,today);
            if(sp_date.wYear>today.wYear)
            {
                ysum=sp_date.wYear-today.wYear;
            }
            if(sp_date.wMonth>today.wMonth)
            {
                msum=sp_date.wMonth-today.wMonth;
            }
            if(sp_date.wDayOfWeek>today.wDayOfWeek)
            {
                dsum=sp_date.wDayOfWeek-today.wDayOfWeek;
            }
            o=((dsum)+(msum*30)+(ysum*365));
            printf(" the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",tk_on.id,tk_on.from,tk_on.where,tk_on.date,tk_tw.price*o,tk_on.t_cov_req,tk_on.t_visa_req);
            printf("Do you want to confirm the order ? \n1-YES \n2-NO \n Enter the spacifc number ? \n");
            scanf("%d",&x);
            if(x==1)
            {
                if(k==1)
                {
                    c = edit_balance(username,(tk_tw.price * o));
                    if(c==1)
                    {

                        printf("You bought the ticket successfully \n");
                        dont_care
                        save_bought_operation(username,id,date,(tk_tw.price * o));
                        user_dashboard(username);
                    }
                    else if(c==-1)
                    {
                        printf("sorry , you balance not enough !!");

                        dont_care
                        user_dashboard(username);
                    }
                    else if(c==-2)
                    {
                        printf("sorry , you actions is blocked from our system !!");
                        dont_care
                        user_dashboard(username);
                    }
                }
                else if(x==2)
                {
                    dont_care
                    user_dashboard(username);
                }
            }
        }
    }
    if(k==0)
    {
        printf("today is %d/%d/%d you can't check that flight ",today.wDayOfWeek,today.wMonth,today.wMonth);
        sleep(3);
        system("cls");
        user_dashboard(username);
    }
    if(z!=1)
    {
        printf("the flight not founded ");
        dont_care
        user_dashboard(username);
    }
    fclose(ticket);
}

void admin_dashboard()
{
    int y;
    printf("Welcome to admin pannel\n");
    printf("1 - add ticket \n");
    printf("2 - edit ticket \n");
    printf("3 - delete ticket \n");
    printf("4 - spacifc ticket info \n");
    printf("5 - block user \n");
    printf("6 - Track Operation spacifc user \n");
    printf("7 - spacifc user info \n");
    printf("8 - Logout \n");
    printf("Enter the number : ");
    scanf("%d",&y);
    if(y==1)
    {
        dont_care
        add_ticket();
    }
    else if(y==2)
    {
        dont_care
        edit_ticket();
    }
    else if(y==3)
    {
        dont_care
        delete_ticket();
    }
    else if(y==4)
    {
        dont_care
        spacfic_ticket_info();
    }
    else if(y==5)
    {
        dont_care
        block_user();
    }
    else if(y==6)
    {
        dont_care
        track_op_user();
    }
    else if(y==7)
    {
        dont_care
        spacifc_user_info();
    }
    else if(y==8)
    {
        dont_care
        start();
    }
    else
    {
        dont_care
        printf("Check the input !! \n");
        admin_dashboard();
    }
}

void delete_ticket()
{
    int founded;
    int id,x,z;
    char buffer[1024];
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    printf("Enter the ID of the flight : \n");
    scanf("%d",&id);
    ticket = fopen("ticket.txt","r");
    if(ticket==NULL)
    {
        ticket = fopen("ticket.txt","w");
    }
    new_ticket = fopen("tmp.txt","w");
    while(fgets(buffer,1024,ticket)!=NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if(!(tk_on.id==id))
        {
            z=1;
            fputs(buffer,new_ticket);
        }
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
        if((!(tk_tw.id==id))&&(z!=1))
        {
            fputs(buffer,new_ticket);
        }
    }
    fclose(new_ticket);
    fclose(ticket);
    ticket = fopen("ticket.txt","w");
    new_ticket = fopen("tmp.txt","r");
    while(fgets(buffer,1024,new_ticket)!=NULL)
    {
        fputs(buffer,ticket);
    }
    fclose(ticket);
    fclose(new_ticket);
    remove("tmp.txt");
    if(z != 1)
    {
        printf("flight not founed !!");
    }
    if(z == 1)
    {
        printf("%d deleted \n ",id);
    }
    ask_admin();
}
void ask_admin()
{
    int x;
    printf("\n 1- go back \n 2- exit \n Enter the spacifc number : ");
    scanf("%d",&x);
    if(x==1)
    {
        dont_care
        admin_dashboard();
    }
    else
    {
        dont_care
        exit(1);
    }
}
void track_op_user()
{
    char date_tmp[100],username_tmp[100],charc[100];
    int id_tmp,ref_tmp,x;
    int price_tmp;
    char buffer[1024],username[100];
    last_operation = fopen("last_operation.txt","r");
    if(last_operation == NULL)
    {
        last_operation = fopen("last_operation.txt","w");
    }
    printf(" Enter spacfic username : \n");
    scanf("%s",username);
    while((fgets(buffer,1024,last_operation)))
    {
        x=0;
        sscanf(buffer,"REF %d : username %s %s ticket %d in %s with price %d \n",&ref_tmp,username_tmp,charc,&id_tmp,date_tmp,&price_tmp);
        if(!(strcmp(username,username_tmp))&&(!(strcmp("bought",charc))))
        {
            puts(buffer);
            x=1;
        }
        if(x==0)
        {
            sscanf(buffer,"*REF %d : username %s bought ticket %d in %s with price %d *\n",&ref_tmp,username_tmp,&id_tmp,date_tmp,&price_tmp);
            if(!(strcmp(username,username_tmp)))
            {
                sprintf(buffer,"REF %d : username %s returned ticket %d in %s with price %d \n ",ref_tmp,username_tmp,id_tmp,date_tmp,price_tmp);
                puts(buffer);
                x=1;
            }
        }
    }

    if(x!=1)
    {
        printf("there no exsist any operation for this username !!\n");
    }

    ask_admin();

}


void spacfic_ticket_info()
{
    int id,x,z;
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    printf("Enter the ID of the flight : \n");
    scanf("%d",&id);
    ticket = fopen("ticket.txt","r");
    if(ticket==NULL)
    {
        ticket = fopen("ticket.txt","w");
    }
    char buffer[1024];
    printf("\n");
    while(fgets(buffer,1024,ticket)!=NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if(tk_on.id==id)
        {
            puts(buffer);
            z=1;
        }
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
        if(tk_tw.id==id&&(z!=1))
        {
            puts(buffer);
        }
    }
    if(z!=1)
    {
        printf("the flight not founded ");
    }
    fclose(ticket);
    ask_admin();
}

void edit_ticket()
{
    int founed=0;
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    int id;
    char buffer[1024];
    int x;
    printf("Enter the Id of the flight ? \n");
    scanf("%d",&id);
    ticket = fopen("ticket.txt","r");
    if(ticket==NULL)
    {
        ticket = fopen("ticket.txt","w");
    }
    new_ticket = fopen("tmp.txt","w");
    while(fgets(buffer,1024,ticket)!=NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if((tk_on.id==id)&&(id%2==0))
        {
            founed =1;
            printf("What you want to edit ? \n 1-price \n 2-from \n 3-where \n 4-date \n 5-visa requirment \n 6-corona certificate requirment \nEnter the Number : \n");
            scanf("%d",&x);
            if(x==1)
            {
                printf("the updated price ? ");
                scanf("%d",&tk_on.price);
            }
            else if(x==2)
            {
                printf("the updated from ? ");
                scanf("%s",tk_on.from);
            }
            else if(x==3)
            {
                printf("the updated where ? ");
                scanf("%s",tk_on.where);
            }
            else if(x==4)
            {
                printf("the updated date ? ");
                scanf("%s",tk_on.date);
            }
            else if(x==5)
            {
                printf("the updated for visa requirment must->1 mustn't -> 0 ? ");
                scanf("%d",&tk_on.t_visa_req);
            }
            else if(x==6)
            {
                printf("the updated for corona certificat requirment must->1 mustn't -> 0 ? ");
                scanf("%d",&tk_on.t_cov_req);
            }
            sprintf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",tk_on.id,tk_on.from,tk_on.where,tk_on.date,tk_on.price,tk_on.t_cov_req,tk_on.t_visa_req);
            fputs(buffer,new_ticket);
        }
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
        if((tk_tw.id==id)&&(founed!=1)&&((id%2==1)))
        {
            founed =1;
            printf("What you want to edit ? \n 1-price \n 2-from \n 3-where \n 4-date to go \n 5-date to retrun \n 6-visa requirment \n 7-corona certificate requirment \nEnter the number : ");
            scanf("%d",&x);
            if(x==1)
            {
                printf("the updated price ? ");
                scanf("%d",&tk_tw.price);
            }
            else if(x==2)
            {
                printf("the updated from ? ");
                scanf("%s",tk_tw.from);
            }
            else if(x==3)
            {
                printf("the updated where ? ");
                scanf("%s",tk_tw.where);
            }
            else if(x==4)
            {
                printf("the updated date to go ? ");
                scanf("%s",tk_tw.date_go);
            }
            else if(x==6)
            {
                printf("the updated for visa requirment must->1 mustn't -> 0 ? ");
                scanf("%d",&tk_tw.t_visa_req);
            }
            else if(x==7)
            {
                printf("the updated for corona certificat requirment date to go must->1 mustn't -> 0  ? ");
                scanf("%d",&tk_tw.t_cov_req);
            }
            else if(x==5)
            {
                printf("the updated date to return ? ");
                scanf("%s",tk_tw.date_ret);
            }
            sprintf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,tk_tw.price,tk_tw.t_cov_req,tk_tw.t_visa_req);
            fputs(buffer,new_ticket);
        }
        else if ((tk_tw.id!=id)&&(tk_on.id!=id))
        {
            fputs(buffer,new_ticket);
        }
    }
    fclose(ticket);
    fclose(new_ticket);
    if((founed)!=1)
    {
        printf("flight not founded");
    }
    ticket = fopen("ticket.txt","w");
    new_ticket = fopen("tmp.txt","r");
    while(fgets(buffer,1024,new_ticket)!=NULL)
    {
        fputs(buffer,ticket);
    }
    fclose(ticket);
    fclose(new_ticket);
    remove("tmp.txt");
    ask_admin();


}
void add_ticket()
{
    char buffer[1024];
    struct _syst2 today;
    struct _syst2 sp_date,sp_date2;
    GetSystemTime(&today);
    int type_trip,x;
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    a = fopen("ticket.txt","a");
    if(a==NULL)
    {
        a = fopen("ticket.txt","w");
    }
    printf("Enter the type of trip : \n 1- One direction \n 2- Two direction \n");
    scanf("%d",&type_trip);
    if(type_trip == 1)
    {
        printf("Enter the Id of the flight ? \n");
        scanf("%d",&tk_on.id);
        if((tk_on.id%2==0)&&(check_id(tk_on.id)))
        {
            printf("Enter the Place you will move to ? \n");
            scanf("%s",tk_on.from);
            printf("Enter the Place will the flight will to go ? \n");
            scanf("%s",tk_on.where);
            printf("Enter the Date of the flight  ? \n");
            scanf("%s",tk_on.date);
            sscanf(tk_on.date,"%hu/%hu/%hu",&sp_date.wDayOfWeek,&sp_date.wMonth,&sp_date.wYear);
            if(compare_dates(sp_date,today))
            {
                printf("Enter the Price of the ticket ? (100 for every mounth )\n");
                scanf("%d",&tk_on.price);
                printf("Enter must contain visa before traveling for that country 1- must 0- musn't ? \n");
                scanf("%d",&tk_on.t_visa_req);
                printf("Enter have a covied ceratificate before 1- must 0- musn't ? \n");
                scanf("%d",&tk_on.t_cov_req);
                sprintf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",tk_on.id,tk_on.from,tk_on.where,tk_on.date,tk_on.price,tk_on.t_cov_req,tk_on.t_visa_req);
                fputs(buffer,a);
            }
        }
        if ((compare_dates(sp_date,today))!=1)
        {
            printf("check your entered date \n");
            dont_care admin_dashboard();
        }
        if((tk_on.id%2!=0)||(!(check_id(tk_on.id))))
        {
            printf("Check the condtion to create the id \n");
        }
    }
    else if (type_trip==2)
    {
        printf("Enter the Id of the flight ? \n");
        scanf("%d",&tk_tw.id);
        if((tk_tw.id%2==1)&&(check_id(tk_on.id)))
        {
            printf("Enter the Place you will move to ? \n");
            scanf("%s",tk_tw.from);
            printf("Enter the Place will the flight will to go ? \n");
            scanf("%s",tk_tw.where);
            printf("Enter the Date of the flight will go ? \n");
            scanf("%s",tk_tw.date_go);
            sscanf(tk_tw.date_go,"%hu/%hu/%hu",&sp_date.wDayOfWeek,&sp_date.wMonth,&sp_date.wYear);
            if(compare_dates(sp_date,today))
            {
                printf("Enter the Date of the flight will return  ? \n");
                scanf("%s",tk_tw.date_ret);
                sscanf(tk_tw.date_ret,"%hu/%hu/%hu",&sp_date2.wDayOfWeek,&sp_date2.wMonth,&sp_date2.wYear);
                if(compare_dates(sp_date2,sp_date))
                {
                    printf("Enter the Price of the ticket (200 for every mounth )? \n");
                    scanf("%d",&tk_tw.price);
                    printf("Enter must contain visa before traveling for that country 1- must 0- musn't ? \n");
                    scanf("%d",&tk_tw.t_visa_req);
                    printf("Enter have a covied ceratificate before 1- must 0- musn't ? \n");
                    scanf("%d",&tk_tw.t_cov_req);
                    sprintf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,tk_tw.price,tk_tw.t_cov_req,tk_tw.t_visa_req);
                    fputs(buffer,a);
                }
            }
        }
        else if((tk_tw.id%2!=1)||(!(check_id(tk_on.id))))
        {
            printf("Check the condtion to create the id \n");
        }
        if (((compare_dates(sp_date,today))!=1)||((compare_dates(sp_date2,today))!=1))
        {
            printf("check your entered date \n");
        }
    }
    fclose(a);
    ask_admin();

}

void block_user()
{
    int founed;
    user = fopen("user.txt","r");
    char buffer[1024],buffer1[1024],sp_user[100],username[100],password[100];
    int access,admin_access,visa_cert,co_cert;
    int balance;
    printf("Enter the username : ");

    scanf("%s",sp_user);
    newdatauser = fopen("tmp.txt","w");
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if((!(strcmp(sp_user,username))))
        {
            founed=1;
            if(access == 1)
            {
                access = 0;
                printf("blocked !!");
                sprintf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username,password,access,admin_access,balance,co_cert,visa_cert);
                fputs(buffer,newdatauser);
            }
            else
            {
                printf("blocked before");
                fputs(buffer,newdatauser);

            }
        }
        else if((((strcmp(sp_user,username)))))
        {
            fputs(buffer,newdatauser);
        }
    }
    if(founed!=1)
    {
        printf("User not founded  !!");
    }
    fclose(newdatauser);
    fclose(user);

    newdatauser = fopen("tmp.txt","r");
    user = fopen("user.txt","w");
    while(fgets(buffer1,1024,newdatauser)!=NULL)
    {
        fputs(buffer1,user);
    }
    fclose(newdatauser);
    fclose(user);
    ask_admin();


    if(user == NULL )
    {
        printf("there is no user to block them !! \n");
        ask_admin();
    }
}
void spacifc_user_info()
{
    int x;
    char username_req[50];
    printf("Enter the username : ");
    scanf("%s",username_req);
    view_info_user(username_req);
    ask_admin();

}
void view_info_user(char *username1)
{
    int x;
    x = view_account(username1);
    if((x)==1)
    {
        printf("The Username Not founed \n");
    }
}
int view_account(char *username1)
{
    char username[50],password[100];
    int access,admin_access,x,co_cert,visa_cert;
    int balance;
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024];
    int z;
    char visa_cert_yn[100],co_cert_yn[100];
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if(!(strcmp(username,username1)))
        {
            if((visa_cert != 0) && (co_cert  != 0) )
            {
                strcpy(co_cert_yn,"yes");
                strcpy(visa_cert_yn,"yes");
            }
            else if((visa_cert != 0) && (co_cert  == 0 ))
            {
                strcpy(co_cert_yn,"no");
                strcpy(visa_cert_yn,"yes");
            }
            else if((visa_cert == 0) && (co_cert  != 0))
            {
                strcpy(co_cert_yn,"yes");
                strcpy(visa_cert_yn,"no");
            }
            else if((visa_cert == 0) && (co_cert  == 0 ))
            {
                strcpy(co_cert_yn,"no");
                strcpy(visa_cert_yn,"no");
            }
            printf("\n username : %s \n password : %s \n access : %d \n balance : %d \n having a visa %s and having corona certificate %s \n",username1,password,access,balance,co_cert_yn,visa_cert_yn);
            z=1;
        }
    }
    if(z!=1)
    {
        return 1;
    }
    fclose(user);
}

int edit_balance(char *username,int price)
{
    int founed;
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024],buffer1[1024],sp_user[100],password[100];
    int access,admin_access,co_cert,visa_cert;
    int balance;
    newdatauser = fopen("tmp.txt","w");
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",sp_user,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if((!(strcmp(sp_user,username)))&&(balance<price))
        {
            return -1;
        }
        else if((!(strcmp(sp_user,username)))&&(balance>=price))
        {
            founed=1;
            balance = balance - price;
            sprintf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",sp_user,password,access,admin_access,balance,co_cert,visa_cert);
            fputs(buffer,newdatauser);
        }
    }

    if((((strcmp(sp_user,username)))))
    {
        fputs(buffer,newdatauser);
    }
    if(founed!=1)
    {
        printf("User not founded  !!");
        return 0;
    }
    fclose(newdatauser);
    fclose(user);
    newdatauser = fopen("tmp.txt","r");
    user = fopen("user.txt","w");
    while(fgets(buffer1,1024,newdatauser)!=NULL)
    {
        fputs(buffer1,user);
    }
    fclose(newdatauser);
    fclose(user);
    remove("tmp.txt");
    return 1;
}

void save_bought_operation(char *username,int id,char *date,int price)
{
    srand(time(NULL));
    last_operation = fopen("last_operation.txt","a");
    if(last_operation == NULL)
    {
        last_operation = fopen("last_operation.txt","w");
    }
    int ref=rand()%1000;
    printf("save your reference number to do any operation : %d",ref);
    sleep(4);
    system("cls");
    fprintf(last_operation,"REF %d : username %s bought ticket %d in %s with price %d \n",ref,username,id,date,price);
    fclose(last_operation);
}

void save_returned_operation(int ref,char *username,int id,char *date,int price)
{
    char date_tmp[100],username_tmp[100];
    int id_tmp,ref_tmp;
    int price_tmp;
    char buffer[1024];
    last_operation = fopen("last_operation.txt","r");
    if(last_operation == NULL)
    {
        last_operation = fopen("last_operation.txt","w");
    }
    tmp = fopen("tmp.txt","w");
    while((fgets(buffer,1024,last_operation)))
    {
        sscanf(buffer,"REF %d : username %s bought ticket %d in %s with price %d \n",&ref_tmp,username_tmp,&id_tmp,date_tmp,&price_tmp);
        if((!(strcmp(username,username_tmp)))&&(id == id_tmp)&&(ref==ref_tmp))
        {
            fprintf(tmp,"*REF %d : username %s bought ticket %d in %s with price %d *\n",ref,username,id,date,price);
        }
        else
        {
            fputs(buffer,tmp);
        }
    }
    fclose(last_operation);
    fclose(tmp);
    last_operation = fopen("last_operation.txt","w");
    tmp = fopen("tmp.txt","r");
    while(fgets(buffer,1024,tmp)!=NULL)
    {
        fputs(buffer,last_operation);
    }
    fclose(last_operation);
    fclose(tmp);
    remove("tmp.txt");
}

int add_balance(int ref,char *username,int id,char *date,int price)
{
    int founed;
    user = fopen("user.txt","r");
    if(user == NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024],buffer1[1024],sp_user[100],password[100];
    int access,admin_access,co_cert,visa_cert;
    int balance;
    newdatauser = fopen("tmp.txt","w");
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",sp_user,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if((!(strcmp(sp_user,username))))
        {
                balance = balance + price;
                save_returned_operation(ref,username,id,date,price);
                sprintf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",sp_user,password,access,admin_access,balance,co_cert,visa_cert);
                fputs(buffer,newdatauser);}
        else if((((strcmp(sp_user,username)))))
            {
                fputs(buffer,newdatauser);
            }
        }

    fclose(newdatauser);
    fclose(user);
    newdatauser = fopen("tmp.txt","r");
    user = fopen("user.txt","w");
    while(fgets(buffer1,1024,newdatauser)!=NULL)
    {
        fputs(buffer1,user);
    }
    fclose(newdatauser);
    fclose(user);
    remove("tmp.txt");
    return 1;
}

int compare_dates(struct _syst2 date1, struct _syst2 date2)
{
    if (date1.wYear < date2.wYear)
        return 0;

    else if (date1.wYear > date2.wYear)
        return 1;

    if (date1.wYear == date2.wYear)
    {
        if (date1.wMonth<date2.wMonth)
            return 0;
        else if (date1.wMonth>date2.wMonth)
            return 1;
        else if (date1.wDayOfWeek<date2.wDayOfWeek)
            return 0;
        else if(date2.wDayOfWeek>date2.wDayOfWeek)
            return 1;
        else
            return 0;
    }
}
int subtract_dates(struct _syst date1, struct _syst2 date2)
{
    int ysum=0,msum=0,dsum=0,sum=0;
    if(date1.wYear>date2.wYear)
    {
        ysum=date1.wYear-date2.wYear;//0
    }
    if(date1.wMonth>date2.wMonth)
    {
        msum=date1.wMonth-date2.wMonth;//2
    }
    if(date1.wDayOfWeek>date2.wDayOfWeek)
    {
        dsum=date1.wDayOfWeek-date2.wDayOfWeek;//2
    }
    sum=((dsum)+(msum*30)+(ysum*365));
    return sum;
}

int check_username(char *username)
{
    int x;
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
        fclose(user);
        return 1;
    }
    char buffer[1024],user_tmp[100],password[100];
    int access,admin_access,co_cert,visa_cert;
    int balance;
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",user_tmp,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if((!(strcmp(username,user_tmp))))
        {
            fclose(user);
            return 0;
        }
    }
    fclose(user);
    return 1;
}
void delete_operation(char *username)
{

    char date_tmp[100],username_tmp[100];
    int id_tmp,ref_tmp;
    int price_tmp;
    char buffer[1024];
    last_operation = fopen("last_operation.txt","r");
    if(last_operation == NULL)
    {
        last_operation = fopen("last_operation.txt","w");
    }
    tmp = fopen("tmp.txt","w");
    while((fgets(buffer,1024,last_operation)))
    {
        sscanf(buffer,"REF %d : username %s bought ticket %d in %s with price %d \n",&ref_tmp,username_tmp,&id_tmp,date_tmp,&price_tmp);
        if(((strcmp(username,username_tmp))))
        {
            fputs(buffer,tmp);
        }
        if(!((strcmp(username,username_tmp))))
        {
            sprintf(buffer,"REF %d : username %s bought ticket %d in %s with price %d [deleted] \n",ref_tmp,username_tmp,id_tmp,date_tmp,price_tmp);
            fputs(buffer,tmp);
        }
    }
    fclose(last_operation);
    fclose(tmp);
    last_operation = fopen("last_operation.txt","w");
    tmp = fopen("tmp.txt","r");
    while(fgets(buffer,1024,tmp)!=NULL)
    {
        fputs(buffer,last_operation);
    }
    fclose(last_operation);
    fclose(tmp);
    remove("tmp.txt");
}
void avaliavility(char *username1)
{
    int a[2];
    char username[50],password[100];
    int access,admin_access,co_cert,visa_cert;
    int balance;
    user = fopen("user.txt","r");
    if(user==NULL)
    {
        user = fopen("user.txt","w");
    }
    char buffer[1024];
    while(fgets(buffer,1024,user)!=NULL)
    {
        sscanf(buffer," username : %s password : %s access : %d admin access : %d balance : %d having a visa %d and having corona certificate %d \n",username,password,&access,&admin_access,&balance,&co_cert,&visa_cert);
        if(!(strcmp(username,username1)))
        {
            a[0]=co_cert;
            a[1]=visa_cert;
            fclose(user);
            break;
        }
    }
    char date_tmp[100],username_tmp[100];
    int id_tmp,ref_tmp;
    int zz[2],z,xy=0;
    int price_tmp;
    last_operation = fopen("last_operation.txt","r");
    if(last_operation == NULL)
    {
        last_operation = fopen("last_operation.txt","w");
    }
    while((fgets(buffer,1024,last_operation)))
    {
        sscanf(buffer,"REF %d : username %s bought ticket %d in %s with price %d \n",&ref_tmp,username_tmp,&id_tmp,date_tmp,&price_tmp);
        if(!((strcmp(username1,username_tmp))))
        {
            xy=1;
            break;
        }
    }
    if(xy!=1)
    {
        return  ;
    }
    fclose(last_operation);
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    ticket = fopen("ticket.txt","r");
    if(ticket==NULL)
    {
        ticket = fopen("ticket.txt","w");
    }
    printf("\n");
    while(fgets(buffer,1024,ticket)!=NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if(tk_on.id==id_tmp)
        {
            zz[0]=tk_on.t_cov_req;
            zz[1]=tk_on.t_visa_req;
            z=1;
            break;
        }
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
        if((tk_tw.id==id_tmp)&&(z!=1))
        {
            zz[0]=tk_tw.t_cov_req;
            zz[1]=tk_tw.t_visa_req;
            break;
        }
    }
    fclose(ticket);
    if((a[0]!=zz[0])||(a[1]!=zz[1]))
    {
        printf(" Warning Notification : Check your required files before traveling !! \n\n");
    }
}
void sort_ticket()
{
    int i=0,y=0;
    char buffer[1024];
    ticket_info_onedir tk_on;
    ticket = fopen("ticket.txt","r");
    if(ticket==NULL)
    {
        ticket = fopen("ticket.txt","w");
    }
    while(fgets(buffer,1024,ticket)!=NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if(tk_on.id%2==0)
        {
            i++;
        }
        else
        {
            y++;
        }
    }
    if(((y == 0) && (i == 0 )))
    {
        printf("notficaion : there is no tickets avaliable !! \n");
        return;
    }
    if((i == 1 )&&(y == 0))
    {
        return;
    }
    if((i == 0 )&&(y == 1))
    {
        return;
    }

    if(((i > 1 )&&(y == 0))||(((i > 1 )&&(y > 1)))||(((i == 0 )&&(y > 1))))
    {

        ticket_info_twodir tk_tw;
        struct _syst date;
        float pc;
        struct _syst2 today;
        GetSystemTime(&today);
        int a=0, b=0;
        int id_one[i],price_one[i],t_visa_req_one[i],t_cov_req_one[i];
        int id_one_tmp,price_one_tmp,t_visa_req_one_tmp,t_cov_req_one_tmp;
        char from_one[i][50],where_one[i][50],date_one[i][50];
        int id_two_tmp,price_two_tmp,t_visa_req_two_tmp,t_cov_req_two_tmp;
        int id_two[y],price_two[y],t_visa_req_two[y],t_cov_req_two[y];
        char from_one_tmp[50],where_one_tmp[50],date_one_tmp[50];
        char from_two_tmp[50],where_two_tmp[50],date_go_two_tmp[50],date_ret_two_tmp[50];
        char from_two[y][50],where_two[y][50],date_go_two[y][50],date_ret_two[y][50];

        fclose(ticket);
        ticket = fopen("ticket.txt","r");
        if(ticket==NULL)
        {
            ticket = fopen("ticket.txt","w");
        }
        while(fgets(buffer,1024,ticket)!=NULL)
        {
            sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
            if(tk_on.id%2==0)
            {
                id_one[a]=tk_on.id;
                strcpy(from_one[a],tk_on.from);
                strcpy(where_one[a],tk_on.where);
                strcpy(date_one[a],tk_on.date);
                price_one[a]=(tk_on.price);
                t_cov_req_one[a]=tk_on.t_cov_req;
                t_visa_req_one[a]=tk_on.t_visa_req;
                ++a;
            }
            else
            {
                sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
                id_two[b]=tk_tw.id;
                strcpy(from_two[b],tk_tw.from);
                strcpy(where_two[b],tk_tw.where);
                strcpy(date_go_two[b],tk_tw.date_go);
                strcpy(date_ret_two[b],tk_tw.date_ret);
                price_two[b]=tk_tw.price;
                t_cov_req_two[b]=tk_tw.t_cov_req;
                t_visa_req_two[b]=tk_tw.t_visa_req;
                ++b;
            }
        }
        fclose(ticket);
        for(a=0; a<i-1; ++a)
        {
            for(b=0; b<i-1; ++b)
            {
                if(price_one[b+1]<price_one[b])
                {
                    //
                    id_one_tmp=id_one[b+1];
                    id_one[b+1]=id_one[b];
                    id_one[b]=id_one_tmp;
                    //
                    strcpy(from_one_tmp,from_one[b+1]);
                    strcpy(from_one[b+1],from_one[b]);
                    strcpy(from_one[b],from_one_tmp);
                    //
                    strcpy(where_one_tmp,where_one[b+1]);
                    strcpy(where_one[b+1],where_one[b]);
                    strcpy(where_one[b],where_one_tmp);
                    //
                    strcpy(date_one_tmp,date_one[b+1]);
                    strcpy(date_one[b+1],date_one[b]);
                    strcpy(date_one[b],date_one_tmp);
                    //
                    price_one_tmp=price_one[b+1];
                    price_one[b+1]=price_one[b];
                    price_one[b]=price_one_tmp;
                    //
                    t_cov_req_one_tmp=t_cov_req_one[b+1];
                    t_cov_req_one[b+1]=t_cov_req_one[b];
                    t_cov_req_one[b]=t_cov_req_one_tmp;
                    //
                    t_visa_req_one_tmp=t_visa_req_one[b+1];
                    t_visa_req_one[b+1]=t_visa_req_one[b];
                    t_visa_req_one[b]=t_visa_req_one_tmp;
                }
            }
        }
        for(a=0; a<y-1; ++a)
        {
            for(b=0; b<y-1; ++b)
            {
                if(price_two[b+1]<price_two[b])
                {
                    //
                    id_two_tmp=id_two[b+1];
                    id_two[b+1]=id_two[b];
                    id_two[b]=id_two_tmp;
                    //
                    strcpy(from_two_tmp,from_two[b+1]);
                    strcpy(from_two[b+1],from_two[b]);
                    strcpy(from_two[b],from_two_tmp);
                    //
                    strcpy(where_two_tmp,where_two[b+1]);
                    strcpy(where_two[b+1],where_two[b]);
                    strcpy(where_two[b],where_two_tmp);
                    //
                    strcpy(date_go_two_tmp,date_go_two[b+1]);
                    strcpy(date_go_two[b+1],date_go_two[b]);
                    strcpy(date_go_two[b],date_go_two_tmp);
                    //
                    strcpy(date_ret_two_tmp,date_ret_two[b+1]);
                    strcpy(date_ret_two[b+1],date_ret_two[b]);
                    strcpy(date_ret_two[b],date_ret_two_tmp);
                    //
                    price_two_tmp=price_two[b+1];
                    price_two[b+1]=price_two[b];
                    price_two[b]=price_two_tmp;
                    //
                    t_cov_req_two_tmp=t_cov_req_two[b+1];
                    t_cov_req_two[b+1]=t_cov_req_two[b];
                    t_cov_req_two[b]=t_cov_req_two_tmp;
                    //
                    t_visa_req_two_tmp=t_visa_req_two[b+1];
                    t_visa_req_two[b+1]=t_visa_req_two[b];
                    t_visa_req_two[b]=t_visa_req_two_tmp;
                }
            }
        }
        ticket = fopen("ticket.txt","w");
        for(a=0; a<i; ++a)
        {
            fprintf(ticket," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",id_one[a],from_one[a],where_one[a],date_one[a],price_one[a],t_cov_req_one[a],t_visa_req_one[a]);
        }
        for(a=0; a<y; ++a)
        {
            fprintf(ticket," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",id_two[a],from_two[a],where_two[a],date_go_two[a],date_ret_two[a],price_two[a],t_cov_req_two[a],t_visa_req_two[a]);
        }
        fclose(ticket);

        ticket = fopen("ticket.txt","r");
        while(fgets(buffer,1024,ticket)!=NULL)
        {
            sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
            if((tk_on.id%2==0))
            {
                sscanf(tk_on.date,"%d/%d/%d",&date.wDayOfWeek,&date.wMonth,&date.wYear);
                pc = subtract_dates(date,today);
                tk_on.price = (tk_on.price*pc);
                printf(" id ticket \t from \t to \t date to go \t price \n");
                printf(" %d \t\t %s \t %s \t %s \t %d \n",tk_on.id,tk_on.from,tk_on.where,tk_on.date,tk_on.price,tk_on.t_cov_req,tk_on.t_visa_req);
            }
            else if ((tk_on.id%2==1))
            {
                sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
                sscanf(tk_tw.date_go,"%d/%d/%d",&date.wDayOfWeek,&date.wMonth,&date.wYear);
                pc = subtract_dates(date,today);
                tk_tw.price = (tk_tw.price*pc);
                printf(" id ticket \t from \t to \t date to go \t date to return \t price \n");
                printf(" %d \t\t %s \t %s \t %s \t %s \t\t %d \n",tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,tk_tw.price);
            }
        }
        fclose(ticket);
        printf("\n");
    }
}
int check_id(int x)
{
    char buffer[1024];
    ticket_info_onedir tk_on;
    ticket_info_twodir tk_tw;
    ticket = fopen("ticket.txt","r");
    while(fgets(buffer,1024,ticket)!=NULL)
    {
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_on.id,tk_on.from,tk_on.where,tk_on.date,&tk_on.price,&tk_on.t_cov_req,&tk_on.t_visa_req);
        if(tk_on.id==x)
        {
            return 0;
        }
        sscanf(buffer," the flight id : %d the flight from : %s where : %s the date of the ticket from : %s to : %s the price of the ticket : %d have a covied ceratificate : %d and must contain visa before traveling : %d \n",&tk_tw.id,tk_tw.from,tk_tw.where,tk_tw.date_go,tk_tw.date_ret,&tk_tw.price,&tk_tw.t_cov_req,&tk_tw.t_visa_req);
        if(tk_tw.id==x)
        {
            return 0;
        }
    }
    fclose(ticket);
    return 1;
}
