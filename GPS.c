/*************************************************************************************************************************************/
/***************** Author : Diea Abdeltwab *******************************************************************************************/
/***************** File : GPS ********************************************************************************************************/
/***************** Date : 24/8/2022  *************************************************************************************************/
/***************** Version : 1.0  ****************************************************************************************************/
/***************** Description : Simple GPS Without Graph (Application Of Linked List And Stack) By C Programming Language ***********/
/*************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/************************************************************** Structs *********************************************************************************/
typedef struct Step {
    int data;
    struct Step *next;
}Step;
typedef struct OtherRoad {
	int raw;
	int column;
	Step *otherRoad;
	struct OtherRoad *next;
}OtherRoad;
typedef struct RefreshRoad {
	int raw;
	int column;
	struct RefreshRoad *next;
}RefreshRoad;
/*************************************************************** Global ********************************************************************************/
Step *Other_road=NULL;
OtherRoad *Crossroad=NULL;
RefreshRoad *Refresh_road=NULL;
int Raw,Column;
int END_Raw,END_Column;
double All_Roads[20];
/************************************************************ Help Functions ***************************************************************************/
Step* CopyStack( Step** head)
{
    struct Step* current = *head;
    struct Step* newList = NULL;
    struct Step* tail = NULL;

    while (current != NULL)
    {
        if (newList == NULL)
        {
            newList = (struct Step*)malloc(sizeof(struct Step));
            newList->data = current->data;
            newList->next = NULL;
            tail = newList;
        }
        else {
            tail->next = (struct Step*)malloc(sizeof(struct Step));
            tail = tail->next;
            tail->data = current->data;
            tail->next = NULL;
        }
        current = current->next;
    }

    return newList;
}
void DeleteList( Step** head_ref)
{
   struct Step* current = *head_ref;
   struct Step* next;
   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   *head_ref = NULL;
}
/****************************************************** Push And POP ***************************************************/
void PushStep(Step **top,int value)
{
    Step * newNode = (Step*)malloc(sizeof( Step));
    newNode->data = value;
    if (*top == NULL)
	{
        newNode->next = NULL;
    }
	else
	{
        newNode->next = *top;
    }
    *top = newNode;
}
int PopStep(Step **top)
{
    if (*top == NULL)
    {
        printf("\nStack Underflow\n");
    } else {
        struct Step *temp = *top;
        int temp_data = (*top)->data;
        (*top) =(*top)->next;
        free(temp);
        return temp_data;
    }
}
void PushOtherRoad (int Raw,int Column,Step *other_road)
{
    if (Crossroad==NULL)
    {
        (Crossroad) =(OtherRoad*)malloc(sizeof(OtherRoad));
        (Crossroad)->raw = Raw;
        (Crossroad)->column = Column;
	    (Crossroad)->otherRoad=other_road;
        (Crossroad)->next=NULL;
    }
    else
    {
        OtherRoad *cur = Crossroad;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = (OtherRoad*)malloc(sizeof(OtherRoad));
        cur->next->raw = Raw;
        cur->next->column = Column;
	    cur->next->otherRoad=other_road;
        cur->next->next = NULL;
    }
}
int PopOtherRoad()
{
    if (Crossroad == NULL)
    {
        printf("\nPOP(OtherRoad)-->Stack Underflow\n");
        return 0;
    }
	else
	{
        OtherRoad *temp = Crossroad;
        Raw = (Crossroad)->raw;
        Column = (Crossroad)->column;
        Other_road = (Crossroad)->otherRoad;
        (Crossroad) =(Crossroad)->next;
        free(temp);
        return 1;
    }
}
void PushRefreshRoad(int Raw,int Column)
{
    RefreshRoad * newNode = (RefreshRoad*)malloc(sizeof( RefreshRoad));
    newNode->raw = Raw;
    newNode->column = Column;
    if (Refresh_road == NULL)
	{
        newNode->next = NULL;
    }
	else
	{
        newNode->next = (Refresh_road);
    }
    (Refresh_road) = newNode;
}
int PopRefreshRoad()
{
    if (Refresh_road == NULL)
    {
        printf("\nStack Underflow (RefreshRoad)\n");
        return 0;
    }
	else
	{
        RefreshRoad *temp = Refresh_road;
        Raw = (Refresh_road)->raw;
        Column = (Refresh_road)->column;
        (Refresh_road) =(Refresh_road)->next;
        free(temp);
        return 1;
    }
}
void PushStep_South(int Map[10][10],Step **Main_road)
{
 	PushStep(Main_road,1);
	Map[Raw][Column]=1;
	Raw=Raw+1;
}
void PushStep_East(int Map[10][10],Step **Main_road)
{
 	PushStep(Main_road,2);
	Map[Raw][Column]=1;
	Column=Column+1;
}
void PushStep_North(int Map[10][10],Step **Main_road)
{
	PushStep(Main_road,3);
    Raw=Raw-1;
	Map[Raw][Column]=1;
}
void PushStep_West(int Map[10][10],Step **Main_road)
{
	PushStep(Main_road,4);
	Map[Raw][Column]=1;
	Column=Column-1;
}
void PushOtherRoad_South(Step **Main_road)
{
    Step *other_road=NULL;
 	other_road=CopyStack(Main_road);
	PushStep(&other_road,1);
	PushOtherRoad(Raw+1,Column,other_road);
	printf("(Push-->%d , %d)",Raw+1,Column);
}
void PushOtherRoad_East(Step **Main_road)
{
    Step *other_road=NULL;
	other_road=CopyStack(Main_road);
	PushStep(&other_road,2);
	PushOtherRoad(Raw,Column+1,other_road);
	printf("(Push-->%d , %d)",Raw,Column+1);
}

void PushOtherRoad_North(Step **Main_road)
{
    Step *other_road=NULL;
	other_road=CopyStack(Main_road);
	PushStep(&other_road,3);
	PushOtherRoad(Raw-1,Column,other_road);
	printf("(Push-->%d , %d)",Raw-1,Column);
}
void PushOtherRoad_West(Step **Main_road)
{
    Step *other_road=NULL;
	other_road=CopyStack(Main_road);
	PushStep(&other_road,4);
	PushOtherRoad(Raw,Column-1,other_road);
	printf("(Push-->%d , %d)",Raw,Column-1);
}
/***************************************************************** Check And Take A Step ***********************************************************/
int CheckAndStep_OneWayRoad(int Map[10][10],Step **Main_road)
{
  if((Raw != END_Raw) || (Column != END_Column))
  {
	//South
	if( Map[Raw+1][Column] ==0 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==1 )
	{
	    printf("South--->");
	    PushRefreshRoad(Raw,Column);
        PushStep_South(Map,Main_road);
        return 1;
	}
    //East
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==1 )
	{
	    printf("East--->");
	    PushRefreshRoad(Raw,Column);
        PushStep_East(Map,Main_road);
		return 1;
	}
	//North
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==1 )
	{
	    printf("North--->");
	    PushRefreshRoad(Raw,Column);
        PushStep_North(Map,Main_road);
		return 1;
	}
	//West
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==0 )
	{
	    printf("West--->");
	    PushRefreshRoad(Raw,Column);
        PushStep_West(Map,Main_road);
		return 1;
	}
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==1 )
	{
	   printf(" Impasse \n");
	   DeleteList(Main_road);
	   return -1;
	}
  }
}
int CheckAndStep_Crossroad(int Map[10][10],Step **Main_road)
{
    Step *other_road=NULL;
	//Crossroad
	//South and East
	if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==1 )
	{
	    if(Raw<END_Raw || Column>=END_Column )
	    {
	        printf("South Crossroad--->");
	        if((Raw != END_Raw) || (Column != END_Column))
	        {
                PushOtherRoad_East(Main_road);
	        }
	       else
	         PushRefreshRoad(Raw,Column);
	       PushStep_South(Map,Main_road);
		   return 2;
	    }
	    else if(Column<END_Column || Raw>=END_Raw )
	    {
	        printf("East Crossroad--->");
	        if((Raw != END_Raw) || (Column != END_Column))
	        {
		      PushOtherRoad_South(Main_road);
	        }
	        else
	         PushRefreshRoad(Raw,Column);
	       PushStep_East(Map,Main_road);
	       return 2;
	    }
	}
    //East and North
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==1 )
	{
	    if(Column<END_Column || Raw<=END_Raw )
	    {
	        printf("East Crossroad--->");
	        if((Raw != END_Raw) && (Column != END_Column))
	        {
		       PushOtherRoad_North(Main_road);
	         }
	        else
	           PushRefreshRoad(Raw,Column);
	       PushStep_East(Map,Main_road);
	       return 2;
	    }
	    else if(Raw>END_Raw || Column>=END_Column)
	    {
	        printf("North Crossroad--->");
	        if((Raw != END_Raw) && (Column != END_Column))
	        {
		       PushOtherRoad_East(Main_road);
	         }
	       else
	           PushRefreshRoad(Raw,Column);
	       PushStep_North(Map,Main_road);
	       return 2;

	    }
	}
	//North and West
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==0 )
	{
	    if(Raw>END_Raw || Column<=END_Column)
	    {
	       printf("North Crossroad--->");
	       if((Raw != END_Raw) && (Column != END_Column))
	       {
		       PushOtherRoad_West(Main_road);
	       }
	       else
	          PushRefreshRoad(Raw,Column);
	      PushStep_North(Map,Main_road);
		  return 2;
	    }
	    else if(Column>END_Column || Raw<=END_Raw )
	    {
	        printf("West Crossroad--->");
	       if((Raw != END_Raw) && (Column != END_Column))
	       {
		       PushOtherRoad_North(Main_road);
	       }
	       else
	          PushRefreshRoad(Raw,Column);
	      PushStep_West(Map,Main_road);
		  return 2;
	    }
	}
	//West and South
	else if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==0 )
	{
	    if(Column>END_Column || Raw>=END_Raw)
	    {
	        printf("West Crossroad--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
	           PushOtherRoad_South(Main_road);
	        }
	       else
	           PushRefreshRoad(Raw,Column);
	       PushStep_West(Map,Main_road);
		   return 2;
	    }
	    else if(Raw<END_Raw || Column<=END_Column)
	    {
	        printf("South Crossroad--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
	           PushOtherRoad_West(Main_road);
	        }
	       else
	           PushRefreshRoad(Raw,Column);
	      PushStep_South(Map,Main_road);
		  return 2;
	    }
	}
	// East and West
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==0 )
	{
	    if(Column<=END_Column || Raw<END_Raw)
	    {
	   	    printf("East-Crossroad--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_West(Main_road);
	        }
	        else
	           PushRefreshRoad(Raw,Column);
	        PushStep_East(Map,Main_road);
		    return 2;
	    }
	    else if (Column>END_Column ||Raw>=END_Raw)
	    {
            printf("West-Crossroad--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_East(Main_road);
	        }
	        else
	           PushRefreshRoad(Raw,Column);
	        PushStep_West(Map,Main_road);
		    return 2;
	    }
	}
    //South and North
	else if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==1 )
	{
	    if(Column<END_Column || Raw<=END_Raw)
	    {
	        printf("South-Crossroad--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
			   PushOtherRoad_North(Main_road);
	         }
	       else
	          PushRefreshRoad(Raw,Column);
	       PushStep_South(Map,Main_road);
		   return 2;
	    }
	    else if(Column>=END_Column || Raw>END_Raw )
	    {
	        printf("North-Crossroad--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
			   PushOtherRoad_South(Main_road);
	         }
	       else
	          PushRefreshRoad(Raw,Column);
	       PushStep_North(Map,Main_road);
		   return 2;
	    }
	 }
}

int CheckAndStep_Intersection(int Map[10][10],Step **Main_road)
{
    //Intersection
	//South and East and West
	if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==1 && Map[Raw][Column-1]==0 )
	{
	    if(Raw<END_Raw || Column==END_Column )
	    {
	        printf("South Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_East(Main_road);
		        PushOtherRoad_West(Main_road);
	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_South(Map,Main_road);
		    return 3;
	    }
	    else if(Column<END_Column && Raw>=END_Raw )
	    {
	        printf("East Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_South(Main_road);
		        PushOtherRoad_West(Main_road);
	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_East(Map,Main_road);
		    return 3;
	    }
	    else if(Column>END_Column && Raw>=END_Raw)
	    {
	        printf("West Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_East(Main_road);
		        PushOtherRoad_South(Main_road);
	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_West(Map,Main_road);
		    return 3;
	    }
	}
    //East and North and South
	else if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==1 )
	{
	    if (Column<END_Column || Raw==END_Raw)
	    {
	       printf("East Intersection--->");
		   if((Raw != END_Raw) && (Column != END_Column))
	       {
		      PushOtherRoad_South(Main_road);
              PushOtherRoad_North(Main_road);
	        }
	      else
	          PushRefreshRoad(Raw,Column);
          PushStep_East(Map,Main_road);
		  return 3;
	    }
	    else if (Raw>END_Raw && Column>=END_Column)
	    {
	       printf("North Intersection--->");
		   if((Raw != END_Raw) && (Column != END_Column))
	       {
		      PushOtherRoad_South(Main_road);
		      PushOtherRoad_East(Main_road);
	        }
	      else
	          PushRefreshRoad(Raw,Column);
         PushStep_North(Map,Main_road);
		  return 3;
	    }
	    else if ( Raw<END_Raw && Column>=END_Column )
	    {
	       printf("South Intersection--->");
		   if((Raw != END_Raw) && (Column != END_Column))
	       {
		      PushOtherRoad_East(Main_road);
              PushOtherRoad_North(Main_road);
	        }
	      else
	          PushRefreshRoad(Raw,Column);
          PushStep_South(Map,Main_road);
		  return 3;
	    }

	}
	//North and West and East
	else if( Map[Raw+1][Column]==1 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==0 )
	{
	    if(Raw>END_Raw || Column==END_Column )
	    {
	         printf("North Intersection--->");
		     if((Raw != END_Raw) && (Column != END_Column))
	         {
		         PushOtherRoad_East(Main_road);
		         PushOtherRoad_West(Main_road);
	        }
	        else
	            PushRefreshRoad(Raw,Column);
           PushStep_North(Map,Main_road);
           return 3;
	    }
	    else if( Column>END_Column && Raw<=END_Raw )
	    {
	         printf("West Intersection--->");
		     if((Raw != END_Raw) && (Column != END_Column))
	         {
		         PushOtherRoad_East(Main_road);
		         PushOtherRoad_North(Main_road);
	        }
	        else
	            PushRefreshRoad(Raw,Column);
            PushStep_West(Map,Main_road);
            return 3;
	    }
	    else if( Column<END_Column && Raw<=END_Raw )
	    {
	         printf("East Intersection--->");
		     if((Raw != END_Raw) && (Column != END_Column))
	         {
		         PushOtherRoad_North(Main_road);
		         PushOtherRoad_West(Main_road);
	        }
	        else
	            PushRefreshRoad(Raw,Column);
           PushStep_East(Map,Main_road);
           return 3;
	    }
	}
	//West and South and North
	else if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==1 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==0 )
	{
	    if (Column > END_Column || Raw==END_Raw )
	    {
	        printf("West Intersection--->");
	    	if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_South(Main_road);
		        PushOtherRoad_North(Main_road);
	        }
	        else
	            PushRefreshRoad(Raw,Column);
	       PushStep_West(Map,Main_road);
		   return 3;
	    }
	    else if (Raw<END_Raw && Column <= END_Column)
	    {
	        printf("South Intersection--->");
	    	if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_North(Main_road);
		        PushOtherRoad_West(Main_road);
	        }
	        else
	            PushRefreshRoad(Raw,Column);
	       PushStep_South(Map,Main_road);
		   return 3;
	    }
	    else if (Raw>END_Raw && Column <= END_Column)
	    {
	        printf("North Intersection--->");
	    	if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_South(Main_road);
		        PushOtherRoad_West(Main_road);
	        }
	        else
	            PushRefreshRoad(Raw,Column);
	       PushStep_North(Map,Main_road);
		   return 3;
	    }
	}
	//South and East and North and West
	else if( Map[Raw+1][Column]==0 && Map[Raw][Column+1]==0 && Map[Raw-1][Column]==0 && Map[Raw][Column-1]==0 )
	{
	    if(Raw<END_Raw || Column==END_Column)
	    {
	        printf("South Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_East(Main_road);
		        PushOtherRoad_North(Main_road);
		        PushOtherRoad_West(Main_road);

	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_South(Map,Main_road);
		    return 3;
	    }
	    else if(Column<END_Column || Raw==END_Raw )
	    {
	        printf("East Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_South(Main_road);
		        PushOtherRoad_North(Main_road);
		        PushOtherRoad_West(Main_road);

	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_East(Map,Main_road);
		    return 3;
	    }
	    else if(Raw>END_Raw)
	    {
	        printf("North Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_South(Main_road);
		        PushOtherRoad_East(Main_road);
                PushOtherRoad_West(Main_road);
	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_North(Map,Main_road);
		    return 3;
	    }
	    else if(Column>END_Column)
	    {
	        printf("West Intersection--->");
		    if((Raw != END_Raw) && (Column != END_Column))
	        {
		        PushOtherRoad_South(Main_road);
                PushOtherRoad_East(Main_road);
                PushOtherRoad_North(Main_road);
	         }
	        else
	           PushRefreshRoad(Raw,Column);
            PushStep_West(Map,Main_road);
		    return 3;
	    }

	}
}
/******************************************************************* Display ******************************************************/
void Display(Step *top)
{
    // Display the elements of the stack
    if (top == NULL) {
        printf("\nStack Underflow (Display)\n");
    }
    else
    {
        printf("\n\nThe Road is \n");
        Step *temp =top;
        printf("END <---");
        while (temp->next != NULL)
        {
            printf("%d <---", temp->data);
            temp = temp->next;
        }
        printf("%d <---Start\n\n", temp->data);
    }
}
double DisplayAndPOP(Step *top)
{
    int step;
    double road;
    // Display the elements of the stack
    if (top == NULL)
    {
        printf("\nStack Underflow(DisplayAndPOP)\n");
    }
    else
    {
       while (top != NULL)
        {
          step=PopStep(&top) ;
          road+=step;
          road=road*10;
        }
        road=road/10;
        printf("--> %.0lf <---\n",road);
        return road;
    }
}
void Refresh_Road(int Map[10][10])
{
    int check_Empty;
    while (check_Empty!=0)
     {
	      check_Empty=PopRefreshRoad();
	      Map[Raw][Column]=0;
     }
}
void PrintMap(int Map[10][10])
{
    printf("\nMap After mark : \n");
    for (int i = 0; i < 10; i++)
	{
	  for (int j = 0; j < 10; j++)
        printf("%d ",*(*(Map+i)+j));
	  printf("\n");
	}
}
void BubbleSort (double *arr , int size)
{
    double temp ;
	int sorted;
    do
    {
        sorted=1;
        for (int i=0 ; i<size-1 ; i++)
            if (arr[i]>arr[i+1])
               {
                   temp = arr[i];
                   arr[i] = arr[i+1] ;
                   arr[i+1] = temp ;
                   sorted= 0;
               }
    } while ( sorted==0 );
}
void GeneralDisplay (int Map[10][10])
{
    /**************************************************************** Main Road *******************************************************/
    Step *Main_road=NULL ;
     int Impasse=0,i=1,counter,check_Empty;
     Other_road=NULL;
     while( (Raw != END_Raw) || (Column != END_Column) )
     {
        CheckAndStep_Crossroad(Map,&Main_road);
        CheckAndStep_Intersection( Map,&Main_road);
        Impasse=CheckAndStep_OneWayRoad(Map,&Main_road);
        if (Impasse==-1)
               break;
     }
     Display(Main_road);
     All_Roads[0]=DisplayAndPOP(Main_road);
     Refresh_Road(Map);
    /***************************************************************** Other Roads *****************************************************/
    Impasse=0;
    while(1)
    {
       printf("--------------------------------------------------------------------------\n\n");
	   check_Empty=PopOtherRoad();
       if (check_Empty==0)
           break;
	   printf("POP--> %d  \t%d\n",Raw,Column);
          while( (Raw != END_Raw) || (Column != END_Column))
         {
            CheckAndStep_Crossroad(Map,&Other_road);
            CheckAndStep_Intersection( Map,&Other_road);
            Impasse=CheckAndStep_OneWayRoad(Map,&Other_road);
            if (Impasse==-1)
                 break;
          }
         Display(Other_road);
         All_Roads[i]=DisplayAndPOP(Other_road);
         Refresh_Road(Map);
         i++;
    }
    BubbleSort (All_Roads,i);

    for(counter=0;All_Roads[counter]==0;counter++);
    printf("\n\n---------------------Best Road is: --> %.0lf  <---------------\n",All_Roads[counter]);
}
/***************************************************************************************************************************/
int main()
{
	int Map[10][10]=
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,1,1,0,1,1},
		{1,0,0,0,0,0,1,0,1,1},
		{1,0,1,0,1,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,1,1,1,1,1,1,1,1,1},
    };
	printf("Enter your Start point : ");
	scanf("%d%d",&Raw,&Column);
	printf("Enter your END point : ");
	scanf("%d%d",&END_Raw,&END_Column);
    GeneralDisplay (Map);

    return 0;
}
