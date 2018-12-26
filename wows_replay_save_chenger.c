#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main(){
	int line=0,i;
	char version[128],newfilepath[1024],arr[1024][1024],inputreplaycount[4],newreplaycount[256];
	FILE *originalfile,*newfile;
	//前置き
	printf("WoWSリプレイ保存数変更機 v1.1\n");
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
	sprintf(newfilepath, "res_mods\\%s\\engine_config.xml", version);

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
	sprintf(newreplaycount, "        <maxReplaysToSave>%s</maxReplaysToSave>\n", inputreplaycount);

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

