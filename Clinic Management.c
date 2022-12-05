/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Clinic Management *********************************************************************************/
/***************** Date : 25/8/2022  ****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Simple Clinic Management (Application Of Linked List) By C Programming Language ************/
/****************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/************************************************************* Structs **************************************************************************************/
typedef struct patient{
    char name[10];
    int age;
    char gender[10];
    double iD;
    char pathological_case[100];
    float reserve_time;
    struct patient *next;
}New_Patient;
/***************************************************************** Global ***********************************************************************************/
New_Patient *Patients = NULL;
float Empty_timetable[5]={2,2.5,3,4,4.5};
/************************************************************* Help Functions *******************************************************************************/
void insert_Patient (char Name[10],int Age,char Gender[10],double ID)
{
    if (Patients==NULL)
    {
        Patients =(New_Patient*)malloc(sizeof(New_Patient));
        strcpy(Patients->name, Name);
        Patients->age=Age;
        strcpy(Patients->gender, Gender);
        Patients->iD=ID;
        strcpy(Patients->pathological_case, "First Time");
        Patients->reserve_time=0;
        Patients->next=NULL;
    }
    else
    {
        New_Patient *cur = Patients;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = (New_Patient*)malloc(sizeof(New_Patient));
        strcpy(cur->next->name, Name);
        cur->next->age=Age;
        strcpy(cur->next->gender, Gender);
        cur->next->iD=ID;
        strcpy(cur->next->pathological_case, "First Time");
        cur->next->reserve_time=0;
        cur->next->next = NULL;
    }
}
void insert_Reserve (float reserve_time,double ID)
{
    New_Patient *ptr = Patients;
    while(ptr!= NULL)
    {
        if (ID==ptr->iD)
		{
			ptr->reserve_time=reserve_time;
			break;
		}
        ptr = ptr->next;
    }
}
int Serch_ID (double ID)
{
    int Counter;
	New_Patient *ptr = Patients;

    while (ptr!= NULL)
    {
        if (ID==ptr->iD)
		{
			return 1 ;
			break;
		}
        ptr = ptr->next;
    }
	if (ptr==NULL)
     	return 0 ;
}
/**************************************************************************** Admin Mode ********************************************************************************/
void Add_New_Patient()
{
    char Name[10],Gender[10],flag=0,Counter;
    int Age;
    double ID;
    printf("Enter Patient Name : ");
    scanf("%s",Name);
    printf("Enter Patient Age : ");
    scanf("%d",&Age);
    printf("Enter Patient Gender : ");
    scanf("%s",Gender);
    do{
       printf("Enter Patient ID : ");
       scanf("%lf",&ID);
       flag=Serch_ID(ID);
       if (flag==1)
       {
          printf("Error..>Incorrect ID (Already Exists)\n");
          Counter++;
       }
     }while (flag==1);
     if(Counter==3)
         return 0;
    insert_Patient(Name,Age,Gender,ID);
}
int Edit_patient_record ()
{

    char Name[10],Gender[10],Pathological_case[100],Counter;
    int Age,Edit_switch,flag;
    double ID,New_ID;
    float Reserve_time;
    New_Patient *ptr = Patients;
    do{
       printf("Enter Patient ID : ");
       scanf("%lf",&ID);
       flag=Serch_ID(ID);
       if (flag==0){
            printf("Error..>Incorrect ID (NOT Found)\n");
            Counter++;
       }

     }while (flag==0 && Counter!=3);
     if(Counter==3)
         return 0;
    do{
        printf("\nEnter \n 1 For Edit Name \n 2 For Edit Age \n 3 For Edit Gender \n 4 For Edit ID \n 5 For Edit Reserve time  \n 6 For Edit Pathological case \n ");
        scanf("%d",&Edit_switch);
     }while( Edit_switch > 6 && Edit_switch < 1 );
     if(Edit_switch==1)
     {
        printf("Enter Patient NEW Name : ");
        scanf("%s",Name);
        while (ptr!= NULL)
        {
            if (ID==ptr->iD)
            {
                strcpy(ptr->name, Name);
                break;
            }
            ptr = ptr->next;
        }
     }
    else if(Edit_switch==2)
    {
        printf("Enter Patient NEW Age : ");
        scanf("%d",&Age);
        while (ptr!= NULL)
        {
            if (ID==ptr->iD)
            {
                ptr->age=Age;
                break;
            }
            ptr = ptr->next;
        }
    }
    else if(Edit_switch==3)
    {
        printf("Enter Patient NEW Gender : ");
        scanf("%s",Gender);
        while (ptr!= NULL)
        {
            if (ID==ptr->iD)
            {
                strcpy(ptr->gender, Gender);
                break;
            }
            ptr = ptr->next;
        }
    }
    else if(Edit_switch==4)
    {
        printf("Enter Patient NEW ID : ");
        scanf("%lf",&New_ID);
        while (ptr!= NULL)
        {
            if (ID==ptr->iD)
            {
                ptr->iD=New_ID;
                break;
            }
            ptr = ptr->next;
        }
    }
    else if(Edit_switch==5)
    {
        while (ptr!= NULL)
        {
            if (ID==ptr->iD)
            {
                Cancel_reservation();
                Appointment_Reserve();
                break;
            }
            ptr = ptr->next;
        }
    }
    else if(Edit_switch==6)
    {
        printf("Enter Patient NEW Pathological case : ");
        scanf("%s",Pathological_case);
        while (ptr!= NULL)
        {
            if (ID==ptr->iD)
            {
                strcpy( ptr->pathological_case, Pathological_case);
                break;
            }
            ptr = ptr->next;
        }
    }
}
int Appointment_Reserve()
{
     char flag,Counter;
     float reserve_time;
     double ID;
    do{
       printf("Enter Patient ID : ");
       scanf("%lf",&ID);
       flag=Serch_ID(ID);
       if (flag==0){
            printf("Error..>Incorrect ID (NOT Found)\n");
            Counter++;
       }
     }while (flag==0 && Counter!=3);
     if(Counter==3)
          return 0;
     printf("Enter Patient Reserve time : ");
     scanf("%f",&reserve_time);
    if (reserve_time==2 && Empty_timetable[0]==2)
    {
        Empty_timetable[0]=0;
        insert_Reserve(reserve_time,ID);
    }
    else if (reserve_time==2.5 && Empty_timetable[1]==2.5)
    {
        Empty_timetable[1]=0;
        insert_Reserve(reserve_time,ID);
    }
    else if (reserve_time==3 && Empty_timetable[2]==3)
    {
        Empty_timetable[2]=0;
        insert_Reserve(reserve_time,ID);
    }
    else if (reserve_time==4 && Empty_timetable[3]==4)
     {
        Empty_timetable[3]=0;
        insert_Reserve(reserve_time,ID);
     }
    else  if (reserve_time==4.5 && Empty_timetable[4]==4.5)
     {
        Empty_timetable[4]=0;
        insert_Reserve(reserve_time,ID);
     }
    else
        printf("..This Time Is Not Available For Reserve\n");
}
void Cancel_reservation()
{
     char flag,Counter;
     float reserve_time;
     double ID;
    do{
       printf("Enter Patient ID : ");
       scanf("%lf",&ID);
       flag=Serch_ID(ID);
       if (flag==0){
            printf("Error..>Incorrect ID (NOT Found)\n");
            Counter++;
       }
     }while (flag==0 && Counter!=3);
     if(Counter==3)
          return 0;
     printf("Enter Patient Cancel Reserve time : ");
     scanf("%f",&reserve_time);
    if (reserve_time==2 && Empty_timetable[0]==0)
    {
        Empty_timetable[0]=2;
        insert_Reserve(0,ID);
    }
    else if (reserve_time==2.5 && Empty_timetable[1]==0)
    {
        Empty_timetable[1]=2.5;
        insert_Reserve(0,ID);
    }
    else if (reserve_time==3 && Empty_timetable[2]==0)
    {
        Empty_timetable[2]=3;
        insert_Reserve(0,ID);
    }
    else if (reserve_time==4 && Empty_timetable[3]==0)
     {
        Empty_timetable[3]=4;
        insert_Reserve(0,ID);
     }
    else  if (reserve_time==4.5 && Empty_timetable[4]==0)
     {
        Empty_timetable[4]=4.5;
        insert_Reserve(0,ID);
     }
     else
        printf("..This Time Is Not Available For Cancel !!\n");
}
void Print_Reserve ()
{
    printf("Empty appointments\n");
    for(int i=0;i<5;i++)
       if(Empty_timetable[i] > 0)
          printf("%.1f\n",Empty_timetable[i]);
    New_Patient *ptr = Patients;
    printf("Appointments are Busy\n");
    while (ptr != NULL)
    {
        if (ptr->reserve_time != 0.000)
		{
            printf("\nName Patient IS : %s\n",ptr->name);
            printf("Age Patient IS : %d\n",ptr->age);
            printf("Gender Patient IS : %s\n",ptr->gender);
            printf("ID Patient IS : %lf\n",ptr->iD);
            printf("Pathological Case Patient IS : %s\n",ptr->pathological_case);
            printf("Reserve Time Patient IS : %f\n\n",ptr->reserve_time);
		}
		else if (ptr->next==NULL )
            printf("\n..There Are No Busy Dates..\n");
        ptr = ptr->next;
    }
}
void Admin_Mode()
{
    double password;
    int Admin_switch=0,count=0;
    while (count != 3)
    {
      printf("Enter Password : ");
      scanf("%lf",&password);
      while (password==1234 )
      {
        printf("............................ Welcome Doctor ............................... \n");
        printf("Enter \n 1 For Add New Patient \n 2 For Edit Patient Record \n 3 For Appointment Reserve \n 4 For Cancel reservation \n 5 For Print Reserve case \n 6 For Close Program \nYour Choice....> ");
        scanf("%d",&Admin_switch);
        if(Admin_switch==1)
           Add_New_Patient();
        else if(Admin_switch==2)
           Edit_patient_record();
        else if(Admin_switch==3)
           Appointment_Reserve();
        else if(Admin_switch==4)
            Cancel_reservation();
        else if(Admin_switch==5)
           Print_Reserve ();
        else if(Admin_switch==6)
            break ;
        else
            printf("\n Wrong Input. \n");
      }
      if(Admin_switch==6)
            break ;
      if (password!=1234)
       {
           printf("Password is Wrong \n");
           count++;
       }
    }
   if(count ==3)
        printf("Who Are You !! >> This Mode  for The Doctor only ");
}
/**************************************************************************** User Mode ************************************************************************************/
void View_patient_record()
{
    double ID;
    printf("Enter Your ID : ");
    scanf("%lf",&ID);
	New_Patient *ptr = Patients;
    while (ptr != NULL)
    {
        if (ID==ptr->iD)
		{
            printf("\nYour Name IS : %s\n",ptr->name);
            printf("Your Age IS : %d\n",ptr->age);
            printf("Your Gender IS : %s\n",ptr->gender);
            printf("Your ID IS : %lf\n",ptr->iD);
            printf("Your Pathological Case IS : %s\n",ptr->pathological_case);
            printf("Your Reserve Time IS : %f\n\n",ptr->reserve_time);
			break;
		}
        ptr = ptr->next;
    }
	if (ptr==NULL)
		printf("\nYou Are NoT Found\n");
}
void  View_today_reservations(float timetable[5])
{
    printf("Appointments\n");
    for(int i=0;i<5;i++)
          printf("%.1f\n",timetable[i]);
    printf("Empty appointments\n");
    for(int i=0;i<5;i++)
       if(Empty_timetable[i] > 0)
          printf("%.1f\n",Empty_timetable[i]);
}
void  User_Mode()
{
    float timetable[5]={2,2.5,3,4,4.5};
    int User_switch=0,count=0;
    while (1)
    {
        printf("............................ Welcome Patient :) ............................... \n");
        printf("Enter \n 1 For View Your Information \n 2 For View Today Reservations \n 3 For Close Program \n.Your Choice....> ");
        scanf("%d",&User_switch);
        if(User_switch==1)
           View_patient_record();
        else if(User_switch==2)
           View_today_reservations(timetable);
        else if(User_switch==3)
            break;
        else
            printf("\n Wrong Input. \n");
    }
}
/****************************************************************** Main ************************************************************/
void main()
{
    int Switch=0;
    while(1)
    {
        printf("\n............................ Welcome ............................... \n");
        printf("Enter \n 1 Admin mode \n 2 User mode\n.Your Choice....> ");
        scanf("%d",&Switch);
        if(Switch==1)
           Admin_Mode();
        else if(Switch==2)
            User_Mode();
        else
            printf("\n Wrong Input. \n");
    }
}
