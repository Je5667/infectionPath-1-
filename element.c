//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ifct_element.h"

#define file_name "patientInfo_sample.txt"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};

//ȯ�� ����ü
typedef struct patient 
{
    int index; //��ȣ
    int age; //����
    int detected_time; //Ȯ�ν���
    int history_place[N_HISTORY];
    //���� Ȯ�����ڴ� ȯ���� �ߺ��� Ȯ�ε� ���� , â�� �� N ��°�� ������ ǥ��
    
} PATIENT;

PATIENT* AllocPerson() 
{ 
    PATIENT* pSomeone = malloc( sizeof( PATIENT ) ); 
    // ����ü ä�� 
    return pSomeone; 
} 
/*
int main() 
{ 
PATIENT * pTom = AllocPerson(); 
// ... 
free( pTom ); // �Ҵ��� �޸� ���� ���� ���ô�! 
return 0; 
} 
*/

//main �Լ����� txt ������ �о ���� �����͸� ���� PATIENT �׸��� ����
//������ ������ ��ġ�� void* ���·� ����. 
// ����
// PATIENT (*patient) = ifctele_genElement(~~) �� ���
void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]){
    //printf("%d, %d ,%d ", history_place[0], history_place[1], history_place[2]);
    PATIENT * patient = AllocPerson(); 
    *patient = (PATIENT) { .index = index, .age = age, .detected_time = detected_time,
                            .history_place[0] = history_place[0], .history_place[1] = history_place[1], .history_place[2] = history_place[2],
                            .history_place[3] = history_place[3], .history_place[4] = history_place[4]};
    //patient = {index, age, detected_time, history_place};
    return patient;
}

// ��ġ�� index -> ���ڿ��� ��ȯ. ������ ���·� ����
char* ifctele_getPlaceName(int placeIndex){
    char * a = strdup(countryName[placeIndex]);
    return a;
}
// PATIENT�� history_place�� index ������ ��ġ(Int)�� ��ȯ
int ifctele_getHistPlaceIndex(void* obj, int index){
    PATIENT (*patient) = obj;
    return patient->history_place[index];
}
//PATIENT�� ������ ��¥�� ���ϱ� 
unsigned int ifctele_getinfestedTime(void* obj){
    PATIENT (*patient) = obj;
    int date = patient->detected_time;
    return date-3;
}

//PATIENT �� ���̸� ��ȯ
int ifctele_getAge(void* obj){
    PATIENT (*patient) = obj;
    return patient->age;
}

//Professor Boldü 
//ȯ���� ��� ������ ��ȯ
void ifctele_printElement(void* obj){
    PATIENT (*patient) = obj;
    printf("Ȯ����ȣ : %d, ����: %2d, Ȯ������: %2d, ���: %-12s -> %-12s -> %-12s -> %-12s ->%-12s \n",
        patient->index, patient->age, patient->detected_time, countryName[patient->history_place[0]],
		countryName[patient->history_place[1]], countryName[patient->history_place[2]],
        countryName[patient->history_place[3]], countryName[patient->history_place[4]]);
}
/*

PATIENT* patient_info();
void find_patient_by(int menu);
void printPatientInfo(PATIENT patient);

PATIENT* patient_info() {
    
    static PATIENT patients[10];
    FILE* fp = fopen(file_name, "r");// ���� �б���� ����
    if (fp == NULL) {
        printf("fail to read file");
    }
    int idx;
	printf("��ȣ \t����\t Ȯ������ 4���� ��� \t 3���� ���\t 2���� ��� \t 1���� ��� \t �������\n");
	printf("====\t=====\t======== ============\t===========\t============\t============\t=========\n");
    for (idx = 0;idx<=4;idx++ ){
         fscanf(fp, "%d %d %d %d %d %d %d %d",
    		&patients[idx].ID, &patients[idx].Age, &patients[idx].CheckDate, &patients[idx].exPlaces[0], &patients[idx].exPlaces[1], 
    		&patients[idx].exPlaces[2],&patients[idx].exPlaces[3],&patients[idx].exPlaces[4]);
    	printPatientInfo(patients[idx]);
    }
    fclose(fp); // ���� �ݱ�
    return patients;
    
}


void printPatientInfo(PATIENT patient){
    //printf("��ȣ \t����\t Ȯ������ 4���� ��� \t 3���� ���\t 2���� ��� \t 1���� ��� \t �������\n");
    //printf("====\t=====\t======== ============\t===========\t============\t============\t=========\n");
    printf("%d\t  %2d \t %2d \t %-12s \t %-12s \t %-12s \t %-12s \t %-12s\n",
        patient.ID, patient.Age, patient.CheckDate, countryName[patient.exPlaces[0]],
		countryName[patient.exPlaces[1]], countryName[patient.exPlaces[2]],
        countryName[patient.exPlaces[3]], countryName[patient.exPlaces[4]]);
}

void find_patient_by( int menu) {
    PATIENT* patients = patient_info();
    switch(menu)
        {
            case 1: // ȯ���� ID�� ã�� ���
                printf("ã���� �ϴ� ȯ���� ��ȣ�� �Է��ϼ���: ");
                int findNumber;
                scanf("%d", &findNumber );
                for(int i = 0; i < 6 ; i++){
                    if (patients[i].ID == findNumber) {
                        printf("��ȣ \t����\t Ȯ������ 4���� ��� \t 3���� ���\t 2���� ��� \t 1���� ��� \t �������\n");
	                    printf("====\t=====\t======== ============\t===========\t============\t============\t=========\n");
                        printPatientInfo(patients[i]);
                    }
                }
        }
    
    return;
}
*/


