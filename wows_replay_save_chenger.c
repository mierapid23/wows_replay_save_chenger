#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

int main(){
	int line=0,i;
	char version[128],newfilepath[1024],arr[1024][1024],inputreplaycount[4],newreplaycount[256];
	FILE *originalfile,*newfile;
	//前置き
	printf("WoWSリプレイ保存数変更機 v1.0\n");
	printf("作成:境闇 Twitter@Mierapid23\n\n");

	//copy original file
	if((originalfile = fopen("res\\engine_config.xml", "r")) == NULL){
		perror("res\\engine_config.xml");
		system("pause");
		return 1;
	}
	fclose(originalfile);
	
	printf("現在のバージョンを入力してください...\n");
	scanf("%s",&version);
	strcpy(newfilepath,"res_mods\\");
	strcat(newfilepath,version);
	strcat(newfilepath,"\\engine_config.xml");

	if(!(CopyFile("res\\engine_config.xml",newfilepath,FALSE))){
		fprintf(stderr,"ERROR: copy failed.\n");
		system("pause");
		return 1;
	}

	printf("\n");

	//edit new file
	if((newfile = fopen(newfilepath, "r")) == NULL){
		perror(newfilepath);
		system("pause");
		return 1;
	}
	for(i = 0; i< sizeof(arr)/sizeof(arr[0]) && fgets(arr[i],sizeof(arr[i]),newfile);i++){
		line++;
	}
	fclose(newfile);

	printf("新しいリプレイの保存数を入力してください(デフォルト:30)...\n");
	scanf("%s", &inputreplaycount);
	strcpy(newreplaycount, "        <maxReplaysToSave>");
	strcat(newreplaycount, inputreplaycount);
	strcat(newreplaycount,"</maxReplaysToSave>\n");

	for(i = 0;i < line; i++){
		if(strstr(arr[i], "maxReplaysToSave") != NULL){
			strcpy(arr[i], newreplaycount);
			break;
		}
	}

	if((newfile = fopen(newfilepath, "w")) == NULL){
		perror(newfilepath);
		system("pause");
		return 1;
	}
	for(i = 0;i < line;i++){
		fputs(arr[i], newfile);
	}
	fclose(newfile);

	printf("\n");

	//exit
	system("pause");
	return 0;
}


