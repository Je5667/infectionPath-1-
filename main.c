//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2
#define file_name "patientInfo_sample.txt"

int trackInfester(int patient_no, int *detected_time, int *place);

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    /* if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    } */
    /*
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    
    fclose(fp);
    */
    
    
    //1-2. loading each patient informations
    fp = fopen(file_name, "r");// ���� �б���� ����
    if (fp == NULL) {
        printf("fail to read file");
    }
    int idx;
    
	printf("��ȣ \t����\t Ȯ������ 4���� ��� \t 3���� ���\t 2���� ��� \t 1���� ��� \t �������\n");
	printf("====\t=====\t======== ============\t===========\t============\t============\t=========\n");
    for (idx = 0;idx<=4;idx++ ){
        int Index;
        int Age;
        unsigned int Date; 
        int history[5] = {};
        fscanf(fp, "%d %d %d %d %d %d %d %d",&Index, &Age, &Date, &history[0], &history[1], &history[2], &history[3], &history[4]);
    	ifct_element = ifctele_genElement(Index, Age, Date, history);
    	ifctdb_addTail(ifct_element);
    	ifctele_printElement(ifct_element);
    }

    //1-3. FILE pointer close
    fclose(fp); 
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
                // ������ ȯ��(��ȣ �Է�)�� ���� ���� ���
                // ��ȣ , ����, ����Ȯ������, �ֱ� 5�� �̵���Ҹ� ���
                printf("ã���� �ϴ� ȯ���� ��ȣ�� �Է��ϼ���: ");
                int findNumber;
                scanf("%d", &findNumber );
                ifctele_printElement(ifctdb_getData(findNumber));
                //find_patient_by(MENU_PATIENT);
                break;
                
            case MENU_PLACE:
                // ������ ��� (���ڿ� ����) ���� �ߺ�Ȯ���� �� ȯ�� ����� ���� ���
                printf("ã���� �ϴ� ȯ���� ��ȣ�� �Է��ϼ���: ");
                char city[MAX_PLACENAME];
                scanf("%s", &city );
                
                break;
                
            case MENU_AGE:
                // �ּҿ� �ִ� ���� �Է� �޾�, ���� �� ���� ȯ���� ����� ���� ���
                break;
                
            case MENU_TRACK:
                // ������ ȯ�ڸ� �������� �����ڿ� �������� ���� �� �̵���Ҹ�
                //���������� ����ϰ� ���� �����ڸ� ���� ����ϰ�
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}

