#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//struct definitions here
struct Date{
	int day;
	int month;
	int year;
};
struct Player{
	char name[20];
	int age;
	struct Date *date; // date is another struct that holds dates.
	
};
struct Team{
	char teamName[20];
	int nOfPlayers;
	struct Player playerList[22];//simple list that stores the players in the Team.
};
//function definitions here
void AddPlayer(struct Team *,struct Player *);
struct Team CreateEmptyTeam(char *);
struct Player CreateFootballPlayer(char *,int,int,int,int);
void StoreTeam(struct Team *);
void ReadTeam();
int main(){
	char playerName[20],teamName[20];
	struct Player *Player;
	struct Team *team;
	int age,dateday,datemonth,dateyear,selection,i=0;
	printf("1:Create Football Player");  //I created a menu for using application efficiently
	printf("\n2:Create Empty Team");
	printf("\n3:Add Player");
	printf("\n4:Store Team");
	printf("\n5:Read Team");
	printf("\n6:Exit");
	printf("\nSelection:");
	scanf("%d",&selection);
	fflush(stdin);

	while(selection != 6){
		switch(selection){
		case(1): // case for creating football player
			Player=(struct Player *)malloc(sizeof(struct Player));
			if(Player == NULL){
				printf("Dynamic Memory Allocation Error!\n");
			}
			printf("Enter the name of footballer: ");
			fflush(stdin);
			scanf("%s",&playerName);
			fflush(stdin);
			printf("Enter the age of footballer: ");
			scanf("%d",&age);
			fflush(stdin);
			printf("Enter the birth date of footballer(dd/mm/yyyy): ");
			scanf("%d/%d/%d",&dateday,&datemonth,&dateyear);
			fflush(stdin);
			*Player=CreateFootballPlayer(playerName,age,dateday,datemonth,dateyear);
			break;
		case(2):// case for creating empty team
			team=(struct Team *)malloc(sizeof(struct Team));
			if(team==NULL){
				printf("Dynamic Memory Allocation Error!\n");
			}
			printf("Enter the team name: ");
			scanf("%s",&teamName);
			fflush(stdin);
			*team=CreateEmptyTeam(teamName);
			break;
		case(3): // case for adding one player to team 
			AddPlayer(team,Player);
			break;
		case(4)://case for storing team into a file
			StoreTeam(team);
			break;
		case(5)://case for reading from file
			ReadTeam();
			break;
		case(6)://case for escaping application
			exit(0);
			break;
		default:// default for the wrong choices
			printf("Wrong choose!\n");
			break;
	}
		printf("\n1:Create Football Player");
		printf("\n2:Create Empty Team");
		printf("\n3:Add Player");
		printf("\n4:Store Team");
		printf("\n5:Read Team");
		printf("\n6:Exit");
		printf("\nSelection:");
		scanf("%d",&selection);
		fflush(stdin);
	}
	return 0;
}
//following fuction takes information from main and adds to struct, then returns it.
struct Player CreateFootballPlayer(char name[20],int age,int dateday,int datemonth,int dateyear){
	struct Player *newPlayer;
	int i=0;
	newPlayer = (struct Player *)malloc(sizeof(struct Player));
	if(newPlayer==NULL){
		printf("Dynamic Memory Allocation Error!\n");
	}
	newPlayer->date = (struct Date *)malloc(sizeof(struct Date));
	if(newPlayer->date == NULL){
		printf("Dynamic Memory Allocation Error!\n");
	}
	while(i<20){
		newPlayer->name[i]=name[i];
		i++;
	}
	
	newPlayer->age = age;
	newPlayer->date->day = dateday;
	newPlayer->date->month = datemonth;
	newPlayer->date->year = dateyear;
	printf("%s %d %d/%d/%d",newPlayer->name,newPlayer->age,newPlayer->date->day,newPlayer->date->month,newPlayer->date->year);
	return *newPlayer;
	
}
//following fuction takes the name of team then creates and team then returns it.
struct Team CreateEmptyTeam(char *name){
	struct Team *newTeam;
	int i;
	newTeam=(struct Team*)malloc(sizeof(struct Team));
	if(newTeam==NULL){
		printf("Dynamic Memory Allocation Error!\n");
	}
	strcpy(newTeam->teamName,name);//team name is the name that the app takes it on main.
	newTeam->nOfPlayers=0; // number of player of the new team is 0 because the team is empty now.

	return *newTeam;
}
//following  function takes team and one player and adds player into the list in the team struct.
void AddPlayer(struct Team *team,struct Player *player){
	team->playerList[team->nOfPlayers++]=*player; // adds player into the last element of the list then increments the number of players
	int a;
	for(a=0;a<team->nOfPlayers;a++){
		printf("%s",team->playerList[a].name);
		printf(" %d",team->playerList[a].age);
		printf(" %d/%d/%d",team->playerList[a].date->day,team->playerList[a].date->month,team->playerList[a].date->year);
		printf("\n");
	}	
}
//following function stores the team in an txt file names "teaminfo.txt"
void StoreTeam(struct Team *team){
	int i;
	FILE *fstore;
	fstore = fopen("teaminfo.txt","w");
	if(fstore == NULL){
		printf("File operation error!\n");
	}
	fprintf(fstore,"%s\n",team->teamName); // the first line is the team name, following lines player informations.
	for(i=0;i<team->nOfPlayers;i++){
		fprintf(fstore,"%s;%d;%d/%d/%d,",team->playerList[i].name,team->playerList[i].age,team->playerList[i].date->day,team->playerList[i].date->month,team->playerList[i].date->year);
	}
	fclose(fstore);
}
//following function reads the player informations from the text file
void ReadTeam(){
	struct Team *newTeam;
	int i=0;
	newTeam =(struct Team *)malloc(sizeof(struct Team));
	newTeam->nOfPlayers=0;
	FILE *fread;
	fread = fopen("teaminfo.txt","r");
	if(fread == NULL){
		printf("File operation Error!\n");
	}
	else{
		fscanf(fread,"%s\n",newTeam->teamName);
		while(!feof(fread)){
			fscanf(fread,"%s;",newTeam->playerList[i].name);
			fscanf(fread,"%[^;]",newTeam->playerList[i].name);
			fscanf(fread,";");    
			fscanf(fread,"%[^;]",&newTeam->playerList[i].age);
			fscanf(fread,";");
			fscanf(fread,"%[^/]",&newTeam->playerList[i].date->day);
			fscanf(fread,"/");
			fscanf(fread,"%[^/]",&newTeam->playerList[i].date->month);
			fscanf(fread,"/");
			fscanf(fread,"%[^,]",&newTeam->playerList[i].date->year);
			fscanf(fread,",");
			newTeam->nOfPlayers++;
			
			printf("%s\n",newTeam->playerList[0].name);
			i++;
			
		}
	}

//	for(i=0;i<newTeam->nOfPlayers;i++){
//		printf("%s;%d;%d/%d/%d,",newTeam->playerList[i].name,newTeam->playerList[i].age,newTeam->playerList[i].date->day,newTeam->playerList[i].date->month,newTeam->playerList[i].date->year);
//	}
//	
	fclose(fread);
}
