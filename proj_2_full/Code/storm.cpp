// Author: Xiao 'Leo' Liu
// by only using stdio.

#include <iostream>
#include <string.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include "defn.h"

using namespace std;
bool flag = false;
bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;

    return true;
}

int nextPrime(int N)
{

    // Base case
    if (N <= 1)
        return 2;

    int prime = N;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}

int string_2_int(const string& s){
    stringstream s_2_i(s);
    int x = 0;
    s_2_i >> x;
    return  x;
}

int string_2_money(const string& s){
//    char u = s.back();
    char u = s[s.length()-1];
    float result;
    int x;
    if (u == '0'){
        result = 0;
    }
    else{
        string s_sub = s.substr(0,s.length()-1);
        result = strtof(s_sub.c_str(),NULL);
        if (u == 'K'){
            result = result*1000;
        }
        else if (u == 'M'){
            result = result*1000000;
        }
    }
    x = int(result);
    return  x;
}

int compare_month(char* s1, char* s2){
    int result = strcmp(s1, s2);
    if (result==0){
        return result;
    }
    else{
        int idx=0;
        while(int(s1[idx])==int (s2[idx])){
            idx++;
        }
        if (int(s1[idx])<int (s2[idx])){
            result=0;
            return result;
        }
        else if (int(s1[idx])>int (s2[idx])){
            result=1;
            return result;
        }
    }
}

int compare_state(char* s1, char* s2){
    int idx=0;
    int result;
    if (int(s1[idx])<=int (s2[idx])){
        result = 0;
        return result;
    }
    else if (int(s1[idx])>int (s2[idx])){
        result = 1;
        return result;
    }
}

void build_fatalities_structure(fstream& file_F_1, struct fatality_event *fatality_event_save ,int file_size_F){
    string line;
    getline ( file_F_1, line); // read a string
//    fatality_event fatality_event_save[file_size_F]; // save fatality information
    for (int i=0; i<file_size_F; i++){
        getline ( file_F_1, line, ',');
        fatality_event_save[i].fatality_id = string_2_int(line);
        getline ( file_F_1, line, ',');
        fatality_event_save[i].event_id = string_2_int(line);
        getline ( file_F_1, line, ',');
        fatality_event_save[i].fatality_type = line[0];
        getline(file_F_1, line, ',');
        strcpy(fatality_event_save[i].fatality_date, line.c_str());
        if (char(file_F_1.peek())==','){
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_age = 0;
        }
        else{
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_age = string_2_int(line);
        }
        if (char(file_F_1.peek())==','){
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_sex = '?';
        }
        else{
            getline(file_F_1, line, ',');
            fatality_event_save[i].fatality_sex = line[0];
        }
        getline(file_F_1, line, '\n');
        if (line.length()>1) {
            strcpy(fatality_event_save[i].fatality_location, line.c_str());
        }
        else {
            string tem = "N/A";
            strcpy(fatality_event_save[i].fatality_location, tem.c_str());
        }
        fatality_event_save[i].next = NULL;
    }
//    for (int i=0; i<file_size_F; i++){
//        cout << fatality_event_save[i].fatality_id << " " << fatality_event_save[i].event_id<< endl;
//    }
}


void build_event_structure(fstream& file_1, struct storm_event *storm_event_save ,int file_size,
        struct fatality_event *fatality_event_save, int file_size_F){
    string value;
    getline ( file_1, value); // read a string
    for (int i=0; i<file_size; i++){ // save storm event into an array struct
        getline ( file_1, value,',');
        storm_event_save[i].event_id = string_2_int(value);
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].state, value.c_str());
        getline ( file_1, value,',');
        storm_event_save[i].year = string_2_int(value);
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].month_name, value.c_str());
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].event_type, value.c_str());
        getline ( file_1, value,',');
        storm_event_save[i].cz_type= value[0];
        getline ( file_1, value,',');
        strcpy(storm_event_save[i].cz_name, value.c_str());
        getline ( file_1, value,',');
        storm_event_save[i].injuries_direct = string_2_int(value);
        getline ( file_1, value,',');
        storm_event_save[i].injuries_indirect = string_2_int(value);
        getline ( file_1, value,',');
        storm_event_save[i].deaths_direct = string_2_int(value);
        getline ( file_1, value,',');
        storm_event_save[i].deaths_indirect = string_2_int(value);
        if (char(file_1.peek())==','){
            // empty cell
            getline(file_1, value, ',');
            storm_event_save[i].damage_property = 0;
        }
        else{
            getline ( file_1, value,',');
            storm_event_save[i].damage_property = string_2_money(value);
        }
        if (char(file_1.peek())==','){
            // empty cell
            getline(file_1, value, ',');
            storm_event_save[i].damage_crops = 0;
        }
        else{
            getline ( file_1, value,',');
            storm_event_save[i].damage_crops = string_2_money(value);
        }
        getline ( file_1, value,'\n');
        if (value.length()>1){
            strcpy(storm_event_save[i].tor_f_scale, value.c_str());
        }
        else{
            string next_value = "N/A";
            strcpy(storm_event_save[i].tor_f_scale, next_value.c_str());
        }
        storm_event_save[i].f =NULL;

        for (int j=0; j<file_size_F; j++){
            if (fatality_event_save[j].event_id == storm_event_save[i].event_id){
                struct fatality_event * temp = storm_event_save[i].f;
                struct fatality_event * head = storm_event_save[i].f;
                if (temp == NULL){
                    temp = new fatality_event;
                    temp->fatality_id = fatality_event_save[j].fatality_id;
                    temp->event_id = fatality_event_save[j].event_id;
                    temp->fatality_type = fatality_event_save[j].fatality_type;
                    strcpy(temp->fatality_date, fatality_event_save[j].fatality_date);
                    temp->fatality_age = fatality_event_save[j].fatality_age;
                    temp->fatality_sex = fatality_event_save[j].fatality_sex;
                    strcpy(temp->fatality_location, fatality_event_save[j].fatality_location);
                    temp->next = NULL;
                    storm_event_save[i].f = temp;

                }
                else{
                    temp = new fatality_event;
                    temp->fatality_id = fatality_event_save[j].fatality_id;
                    temp->event_id = fatality_event_save[j].event_id;
                    temp->fatality_type = fatality_event_save[j].fatality_type;
                    strcpy(temp->fatality_date, fatality_event_save[j].fatality_date);
                    temp->fatality_age = fatality_event_save[j].fatality_age;
                    temp->fatality_sex = fatality_event_save[j].fatality_sex;
                    strcpy(temp->fatality_location, fatality_event_save[j].fatality_location);
                    temp-> next = head;
                    storm_event_save[i].f = temp;

                }
            }
        }
    }
//    for (int i=0; i<file_size;i++){
//        cout<< "Hi " << storm_event_save[i].event_id <<endl;
//    }
//    cout<< "Hi" << endl;
}


int hash_fun(int hash_size, int key){
    return key%hash_size;
}


void  build_hash_table(struct hash_table_entry **t, int hash_size, int file_size, struct storm_event *storm_event_save){
    int key;
    for (int i = 0; i<file_size; i++){
        key = hash_fun(hash_size,storm_event_save[i].event_id);
//        cout << "Key "<< key << endl;

        struct hash_table_entry* en = t[key];
        struct hash_table_entry* temp = t[key];
//        cout << en<< endl;
        if (en == NULL){
            en = new hash_table_entry;
            en->event_id = storm_event_save[i].event_id;
            en->year = storm_event_save[i].year;
            en->event_index = i;
            en->next = NULL;
            t[key] = en;
        }
        else{
            en = new hash_table_entry;
            en->event_id = storm_event_save[i].event_id;
            en->year = storm_event_save[i].year;
            en->event_index = i;
            en->next = temp;
            t[key] = en;
//            cout << "here "<< t[key]<< endl;
        }
    }
}



void max_heapify_property(struct storm_event *all_event_save, int i, int file_size){
    int l;
    int r;
    int largest=i;
    l = 2*i+1;
    r = 2*i+2;
    if (l<file_size && all_event_save[l].damage_property>all_event_save[i].damage_property){
        largest = l;
    }
    if (r<file_size && all_event_save[r].damage_property>all_event_save[i].damage_property){
        largest = r;
    }
    if (largest!=i){
        struct storm_event * temp = new storm_event;
        temp->event_id = all_event_save[i].event_id;
        strcpy(temp->state, all_event_save[i].state);
        temp->year = all_event_save[i].year;
        strcpy (temp->month_name, all_event_save[i].month_name);
        strcpy(temp->event_type, all_event_save[i].event_type);
        temp->cz_type = all_event_save[i].cz_type;
        strcpy(temp->cz_name, all_event_save[i].cz_name);
        temp->injuries_direct = all_event_save[i].injuries_direct;
        temp->injuries_indirect = all_event_save[i].injuries_indirect;
        temp->deaths_direct = all_event_save[i].deaths_direct;
        temp->deaths_indirect = all_event_save[i].deaths_indirect;
        temp->damage_property = all_event_save[i].damage_property;
        temp->damage_crops = all_event_save[i].damage_crops;
        strcpy(temp->tor_f_scale, all_event_save[i].tor_f_scale);
        temp->f = all_event_save[i].f;

        all_event_save[i].event_id = all_event_save[largest].event_id;
        strcpy(all_event_save[i].state, all_event_save[largest].state);
        all_event_save[i].year = all_event_save[largest].year;
        strcpy (all_event_save[i].month_name, all_event_save[largest].month_name);
        strcpy(all_event_save[i].event_type, all_event_save[largest].event_type);
        all_event_save[i].cz_type = all_event_save[largest].cz_type;
        strcpy(all_event_save[i].cz_name, all_event_save[largest].cz_name);
        all_event_save[i].injuries_direct = all_event_save[largest].injuries_direct;
        all_event_save[i].injuries_indirect = all_event_save[largest].injuries_indirect;
        all_event_save[i].deaths_direct = all_event_save[largest].deaths_direct;
        all_event_save[i].deaths_indirect = all_event_save[largest].deaths_indirect;
        all_event_save[i].damage_property = all_event_save[largest].damage_property;
        all_event_save[i].damage_crops = all_event_save[largest].damage_crops;
        strcpy(all_event_save[i].tor_f_scale, all_event_save[largest].tor_f_scale);
        all_event_save[i].f = all_event_save[largest].f;

        all_event_save[largest].event_id = temp->event_id;
        strcpy( all_event_save[largest].state, temp->state);
        all_event_save[largest].year = temp->year;
        strcpy ( all_event_save[largest].month_name, temp->month_name);
        strcpy( all_event_save[largest].event_type, temp->event_type);
        all_event_save[largest].cz_type = temp->cz_type;
        strcpy( all_event_save[largest].cz_name, temp->cz_name);
        all_event_save[largest].injuries_direct = temp->injuries_direct;
        all_event_save[largest].injuries_indirect = temp->injuries_indirect;
        all_event_save[largest].deaths_direct = temp->deaths_direct;
        all_event_save[largest].deaths_indirect = temp->deaths_indirect;
        all_event_save[largest].damage_property = temp->damage_property;
        all_event_save[largest].damage_crops = temp->damage_crops;
        strcpy(all_event_save[largest].tor_f_scale , temp->tor_f_scale);
        all_event_save[largest].f = temp->f;
//        swap(all_event_save[i],all_event_save[largest]);
        max_heapify_property(all_event_save, largest, file_size);
    }
}

void max_heapify_crops(struct storm_event *all_event_save, int i, int file_size){
    int l;
    int r;
    int largest = i;
    l = 2*i+1;
    r = 2*i+2;
    if (l<file_size && all_event_save[l].damage_crops>all_event_save[i].damage_crops){
        largest = l;
    }
    if (r<file_size && all_event_save[r].damage_crops>all_event_save[i].damage_crops){
        largest = r;
    }
    if (largest!=i){
        swap(all_event_save[i],all_event_save[largest]);
        max_heapify_crops(all_event_save, largest, file_size);
    }
}

void build_max_heap_property(struct storm_event *all_event_save, int file_size){
    int start = floor(file_size/2);
    for (int i=start; i>=0;i--){
        max_heapify_property(all_event_save, i, file_size);
    }
}

void build_max_heap_crops(struct storm_event *all_event_save, int file_size){
    int start = floor(file_size/2);
    for (int i=start; i>=0;i--){
        max_heapify_crops(all_event_save, i, file_size);
    }
}

void max_heapify_fatality(struct max_fatality * max_fatality_save, int i, int file_size){
    int l;
    int r;
    int largest = i;
    l = 2*i+1;
    r = 2*i+2;
    if (l<file_size && max_fatality_save[l].num_fatality>max_fatality_save[i].num_fatality){
        largest = l;
    }
    if (r<file_size && max_fatality_save[r].num_fatality>max_fatality_save[i].num_fatality){
        largest = r;
    }
    if (largest!=i){
        swap( max_fatality_save[i], max_fatality_save[largest]);
        max_heapify_fatality( max_fatality_save, largest, file_size);
    }
}

void build_max_heap_fatality(struct max_fatality * max_fatality_save, int file_size){
    int start = floor(file_size/2);
    for (int i=start; i>=0;i--){
        max_heapify_fatality(max_fatality_save, i, file_size);
    }
}

struct storm_event* delete_max_heap_property(struct storm_event *all_event_save, int file_size){
    file_size = file_size-1;
    storm_event * new_all_event_save = new storm_event[file_size];
    for (int i=0; i<file_size;i++){
        new_all_event_save[i] = all_event_save[i+1];
    }
    return new_all_event_save;
}

struct storm_event* delete_max_heap_crops(struct storm_event *all_event_save, int file_size){
    file_size = file_size-1;
    storm_event * new_all_event_save = new storm_event[file_size];
    for (int i=0; i<file_size;i++){
        new_all_event_save[i] = all_event_save[i+1];
    }
    return new_all_event_save;
}

struct max_fatality* delete_max_heap_fatality(struct max_fatality *all_fatality_save, int file_size){
    file_size = file_size-1;
    max_fatality * new_all_fatality_save = new max_fatality[file_size];
    for (int i=0; i<file_size;i++){
        new_all_fatality_save[i] = all_fatality_save[i+1];
    }
    return new_all_fatality_save;
}

void find_event(struct hash_table_entry **t,int event_id, int hash_size, int num_file,
        const int year_index[], struct annual_storms * annual_storms_save){
    int key;
    key = hash_fun(hash_size,event_id);
    hash_table_entry * en = t[key];
    if (en!= NULL){
        while(en!= NULL){
            if (en->event_id == event_id){
                //
                int yyyy = en->year;
                int index=0;
                for (int i=0;i<num_file;i++){
                    if (yyyy == year_index[i])
                        index = i;
                }
                cout<< "event_id "<< en->event_id<< endl;
                cout<< "state "<< annual_storms_save[index].events[en->event_index].state<< endl;
                cout<< "year "<< annual_storms_save[index].events[en->event_index].year<< endl;
                cout<< "month_name "<< annual_storms_save[index].events[en->event_index].month_name<< endl;
                cout<< "event_type "<< annual_storms_save[index].events[en->event_index].event_type<< endl;
                cout<< "cz_type "<< annual_storms_save[index].events[en->event_index].cz_type<< endl;
                cout<< "cz_name "<< annual_storms_save[index].events[en->event_index].cz_name<< endl;
                cout<< "injuries_direct "<< annual_storms_save[index].events[en->event_index].injuries_direct<< endl;
                cout<< "injuries_indirect "<< annual_storms_save[index].events[en->event_index].injuries_indirect<< endl;
                cout<< "deaths_direct "<< annual_storms_save[index].events[en->event_index].deaths_direct<< endl;
                cout<< "deaths_indirect "<< annual_storms_save[index].events[en->event_index].deaths_indirect<< endl;
                cout<< "damage_property "<< annual_storms_save[index].events[en->event_index].damage_property<< endl;
                cout<< "damage_crops "<< annual_storms_save[index].events[en->event_index].damage_crops<< endl;
                cout<< "tor_f_scale "<< annual_storms_save[index].events[en->event_index].tor_f_scale<< endl;

                if (annual_storms_save[index].events[en->event_index].f== NULL){
                    cout <<endl;
                    cout << "No fatalities " << endl;
                }
                else{
                    while (annual_storms_save[index].events[en->event_index].f != NULL){
                        cout<< endl;
                        cout<< "fatality_id "<<annual_storms_save[index].events[en->event_index].f->fatality_id<<endl;
                        cout<< "event_id "<<annual_storms_save[index].events[en->event_index].f->event_id<<endl;
                        cout<< "fatality_type "<<annual_storms_save[index].events[en->event_index].f->fatality_type<<endl;
                        cout<< "fatality_date "<<annual_storms_save[index].events[en->event_index].f->fatality_date<<endl;
                        cout<< "fatality_age "<<annual_storms_save[index].events[en->event_index].f->fatality_age<<endl;
                        cout<< "fatality_sex "<<annual_storms_save[index].events[en->event_index].f->fatality_sex<<endl;
                        cout<< "fatality_location "<<annual_storms_save[index].events[en->event_index].f->fatality_location<<endl;
                        annual_storms_save[index].events[en->event_index].f = annual_storms_save[index].events[en->event_index].f->next;
                        cout << endl;
                    }
                    break;
                }
            }
            en = en->next;
        }
    }
    else{
        cout<< "There is no such event." << endl;
    }
}

void find_fatality(struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                const int year_index[], struct annual_storms * annual_storms_save){
    int key;
    key = hash_fun(hash_size,event_id);
    hash_table_entry * en = t[key];
    if (en!= NULL){
        while(en!= NULL){
            if (en->event_id == event_id){
                //
                cout << endl;
                cout<< "The most fatal storm id: "<< event_id<<endl;
                int yyyy = en->year;
                int index=0;
                for (int i=0;i<num_file;i++){
                    if (yyyy == year_index[i])
                        index = i;
                }
                if (annual_storms_save[index].events[en->event_index].f== NULL){
                    cout <<endl;
                    cout << "No fatalities " << endl;
                }
                else{
                    while (annual_storms_save[index].events[en->event_index].f != NULL){
                        cout<< "fatality_id "<<annual_storms_save[index].events[en->event_index].f->fatality_id<<endl;
                        cout<< "event_id "<<annual_storms_save[index].events[en->event_index].f->event_id<<endl;
                        cout<< "fatality_type "<<annual_storms_save[index].events[en->event_index].f->fatality_type<<endl;
                        cout<< "fatality_date "<<annual_storms_save[index].events[en->event_index].f->fatality_date<<endl;
                        cout<< "fatality_age "<<annual_storms_save[index].events[en->event_index].f->fatality_age<<endl;
                        cout<< "fatality_sex "<<annual_storms_save[index].events[en->event_index].f->fatality_sex<<endl;
                        cout<< "fatality_location "<<annual_storms_save[index].events[en->event_index].f->fatality_location<<endl;
                        cout << endl;
                        annual_storms_save[index].events[en->event_index].f =
                                annual_storms_save[index].events[en->event_index].f->next;
                    }
                    break;
                }
            }
            en = en->next;
        }
    }
    else{
        cout<< "There is no such event." << endl;
    }
}

void find_range_event(struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                const int year_index[], struct annual_storms * annual_storms_save){
    int key;
    key = hash_fun(hash_size,event_id);
    hash_table_entry * en = t[key];
    if (en!= NULL){
        while(en!= NULL){
            if (en->event_id == event_id){
                //
                int yyyy = en->year;
                int index=0;
                for (int i=0;i<num_file;i++){
                    if (yyyy == year_index[i])
                        index = i;
                }
                cout<< " event_id: "<< en->event_id<< " ";
                cout<< "year: "<< annual_storms_save[index].events[en->event_index].year<< " ";
                cout<< "event_type: "<< annual_storms_save[index].events[en->event_index].event_type<< " ";
                cout<< "cz_type: "<< annual_storms_save[index].events[en->event_index].cz_type<< " ";
                cout<< "cz_name: "<< annual_storms_save[index].events[en->event_index].cz_name<< endl;
                break;
            }
            en = en->next;
        }
    }
    else{
        cout<< "There is no such event." << endl;
    }
}

void find_max_all_damage_property(storm_event * all_event_save, int n, int file_size){
    for (int i=0; i<n; i++){
        build_max_heap_property(all_event_save, file_size);
        build_max_heap_property(all_event_save, file_size);
        build_max_heap_property(all_event_save, file_size);
        cout << "event_id: "<< all_event_save[0].event_id <<" event_type: "
             <<all_event_save[0].event_type <<" amount: "<< all_event_save[0].damage_property<<endl;
        all_event_save = delete_max_heap_property(all_event_save,file_size);
        file_size = file_size-1;
    }
    file_size=file_size+1;
    int height  = floor(log2(file_size));
    int l_height;
    int r_height;
    int num_leaf = file_size- (int(pow(2.0, double(height)))-1);
    int temp = int(pow(2.0, double(height-1)));
    if (num_leaf>temp){
        l_height = height-1;
        r_height = height-1;
    }
    else{
        l_height = height-1;
        r_height = height-2;
    }
    cout <<endl;
    cout << "Num of node of the heap: "<< file_size<< endl;
    cout << "Height of the binary tree: "<< height<< endl;
    cout << "Height of the left binary tree: "<< l_height<< endl;
    cout << "Height of the right binary tree: "<< r_height<< endl;
}

void find_max_all_damage_crops(storm_event * all_event_save, int n, int file_size){
    for (int i=0; i<n; i++){
        build_max_heap_crops(all_event_save, file_size);
        build_max_heap_crops(all_event_save, file_size);
        build_max_heap_crops(all_event_save, file_size);
        cout << "event_id: "<< all_event_save[0].event_id <<" event_type: "
        <<all_event_save[0].event_type <<" amount: "<< all_event_save[0].damage_crops<<endl;
        all_event_save = delete_max_heap_crops(all_event_save,file_size);
        file_size = file_size-1;
    }
    file_size=file_size+1;
    int height  = floor(log2(file_size));
    int l_height;
    int r_height;
    int num_leaf = file_size- (int(pow(2.0, double(height)))-1);
    int temp = int(pow(2.0, double(height-1)));
    if (num_leaf>temp){
        l_height = height-1;
        r_height = height-1;
    }
    else{
        l_height = height-1;
        r_height = height-2;
    }
    cout <<endl;
    cout << "Num of node of the heap: "<< file_size<< endl;
    cout << "Height of the binary tree: "<< height<< endl;
    cout << "Height of the left binary tree: "<< l_height<< endl;
    cout << "Height of the right binary tree: "<< r_height<< endl;
}

void find_max_fatality(max_fatality * all_fatality_save, int n, struct hash_table_entry **t,
        int file_size, int hash_size, int num_file,
        const int year_index[], struct annual_storms * annual_storms_save){
    for (int i=0; i<n; i++){
        build_max_heap_fatality(all_fatality_save,file_size);
        build_max_heap_fatality(all_fatality_save,file_size);
//        cout << " "<< all_fatality_save[0].num_fatality<<endl;
        find_fatality(t,all_fatality_save[0].event_id,hash_size,num_file,year_index,annual_storms_save);
        all_fatality_save = delete_max_heap_fatality(all_fatality_save,file_size);
        file_size = file_size-1;
    }

    int height  = floor(log2(file_size));
    int l_height;
    int r_height;
    int num_leaf = file_size- (int(pow(2.0, double(height)))-1);
    int temp = int(pow(2.0, double(height-1)));
    if (num_leaf>temp){
        l_height = height-1;
        r_height = height-1;
    }
    else{
        l_height = height-1;
        r_height = height-2;
    }
    cout <<endl;
    cout << "Num of node of the heap: "<< file_size<< endl;
    cout << "Height of the binary tree: "<< height<< endl;
    cout << "Height of the left binary tree: "<< l_height<< endl;
    cout << "Height of the right binary tree: "<< r_height<< endl;
}



struct bst* new_bst(int event_id, char* s){// create a new bst node
    struct bst*temp = new bst;
    temp->s = s;
    temp->event_id = event_id;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct bst* insert(struct bst* bst_node, int event_id, char*s){
    if (bst_node==NULL){
        bst_node = new_bst(event_id,s);
        return bst_node;
    }
    int result;
    result = compare_month(s, bst_node->s);
    if (result==0){
        bst_node->left = insert(bst_node->left,event_id,s);
    }
    else if (result==1){
        bst_node->right = insert(bst_node->right,event_id,s);
    }
    return bst_node;
}

void inorder_traversal_month(struct bst* bst_node, char* low, char* high,
                             struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                             const int year_index[], struct annual_storms * annual_storms_save){
    if (bst_node !=NULL){
        inorder_traversal_month(bst_node->left, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        int n1 = compare_month(low,bst_node->s);
        int n2 = compare_month(bst_node->s,high);
        if ( n1==0 && n2==0){
            flag = true;
            cout <<"month_name: "<< bst_node->s;
            find_range_event(t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        }
        inorder_traversal_month(bst_node->right, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
    }
}

void inorder_traversal_state(struct bst* bst_node, char* low, char* high,
                             struct hash_table_entry **t,int event_id, int hash_size, int num_file,
                             const int year_index[], struct annual_storms * annual_storms_save){
    if (bst_node !=NULL){
        inorder_traversal_state(bst_node->left, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        int n1 = compare_state(low,bst_node->s);
        int n2 = compare_state(bst_node->s,high);
        if ( n1==0 && n2==0){
            flag=true;
            cout <<"state: "<< bst_node->s;
            find_range_event(t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
        }
        inorder_traversal_state(bst_node->right, low, high,t,bst_node->event_id,hash_size,num_file,year_index,annual_storms_save);
    }
}

void traversal(struct bst* bst_node){
    if (bst_node !=NULL){
        traversal(bst_node->left);
        cout << bst_node->event_id<< " "<< bst_node->s << endl;
        traversal(bst_node->right);
    }
}

int find_height(struct bst* bst_node){
    if (bst_node == NULL){
        return -1;
    }
    int left_height = find_height(bst_node->left);
    int right_height = find_height(bst_node->right);
    if (left_height>right_height){
        return left_height+1;
    }
    else{
        return right_height+1;
    }
}


int main(int argc, const char* argv[] ) {
    string num(argv[1]);
    int num_file = string_2_int(num);
    new annual_storms;
    annual_storms* annual_storms_save = new annual_storms[num_file];
    annual_fatality * annual_fatality_save = new annual_fatality[num_file];
    int file_f_size[num_file] ;
    int file_d_size[num_file];
    int year_index[num_file];
    for (int i=0; i<num_file; i++){
        string year (argv[i+2]);
        string name;
        name = "fatalities-"+year+".csv";
        year_index[i]=string_2_int(year);
        fstream file_F(name.c_str() );
        string line;
        if(!file_F.is_open()) std::cout << "ERROR: File Open" << '\n';
        int file_size_F = 0;
        while(file_F.good()){
            getline ( file_F, line); // read a string
            if (!line.empty()) {
                file_size_F++;
            }
        }
        file_F.close();
        file_size_F = file_size_F-1;
        file_f_size[i]=file_size_F;


        string name_1;
        name_1 = "details-"+year+".csv";

        fstream file(name_1.c_str() );
        string value;
        if(!file.is_open()) std::cout << "ERROR: File Open" << '\n';
        int file_size = 0;
        while(file.good()){
            getline ( file, value); // read a string
            if (!value.empty()) {
                file_size++;
            }
        }
        file.close();
        file_size = file_size-1;
        file_d_size[i] = file_size;

        fatality_event* fatality_event_save = new fatality_event[file_size_F];
        storm_event * storm_event_save = new storm_event[file_size];
        fstream file_F_1(name.c_str() );
        build_fatalities_structure(file_F_1, fatality_event_save, file_size_F);
        fstream file_1(name_1.c_str() );
        build_event_structure(file_1,storm_event_save,file_size,fatality_event_save,file_size_F);
        int count =1;
        for (int j=0; j<file_size_F; j++){
            if (j+1<file_size_F){
                if (fatality_event_save[j].event_id != fatality_event_save[j+1].event_id){
                    count++;
                }
            }
        }
        max_fatality * max_fatality_save = new max_fatality[count];
        int m=0;
        int arr[file_size_F];
        for (int gg = 0;gg<file_size_F;gg++){
            arr[gg] = 0;
        }
        for (int j=0;j<file_size_F;j++){
            int temp_count =1;
            if (arr[j]==1){
                continue;
            }
            if (j+1<file_size_F){
                for (int k = j+1; k<file_size_F; k++){
                    if (fatality_event_save[j].event_id == fatality_event_save[k].event_id){
                        arr[k] = 1;
                        temp_count++;
                    }
                }
                max_fatality_save[m].event_id = fatality_event_save[j].event_id;
                max_fatality_save[m].num_fatality = temp_count;
                max_fatality_save[m].year = year_index[i];
                m++;
            }
            else{
                max_fatality_save[m].event_id = fatality_event_save[j].event_id;
                max_fatality_save[m].num_fatality = temp_count;
                max_fatality_save[m].year = year_index[i];
            }
        }
        annual_fatality_save[i].year = year_index[i];
        annual_fatality_save[i].num_all_fatality = count;
        annual_fatality_save[i].fatality = max_fatality_save;

        annual_storms_save[i].year = string_2_int(year);
        annual_storms_save[i].events = storm_event_save;
    }

    int total_file_size = 0;
    for (int i=0;i<num_file;i++){
        total_file_size = total_file_size+file_d_size[i];
    }
    int hash_size = nextPrime(2*total_file_size);
    // cout<< hash_size << endl;

    struct hash_table_entry **t;
    t = static_cast<hash_table_entry **>(malloc(sizeof(*t) * hash_size));
//    t = new hash_table_entry*[hash_size]();


    for (int i=0;i<num_file;i++){
        build_hash_table(t,hash_size, file_d_size[i], annual_storms_save[i].events);
    }
    int load=0;
    for (int i=0;i<hash_size;i++){
        if (t[i]!=NULL){
            load++;
        }
    }
    float load_factor = float(load)/float(hash_size);
    int n;

    string line;
    string value;
    cout << "Number of query: "<<endl;
    getline(std::cin, line);
    n = string_2_int(line);
//    cout << "here is the num: "<< n<<endl;

    for(int k=0;k<n;k++) {
        cout << "Enter the NO. "<< k+1 << " query:"<<endl;
        getline(std::cin, line);
        std::stringstream is(line);
        string value;
        int num_words=0;
        while (is>>value){
            num_words++;
        }
        std::stringstream iss(line);
        string value_save[num_words];
        int i=0;
        while (iss>>value){
            value_save[i]= value;
            i++;
        }
        if (num_words == 3){
            int key = string_2_int(value_save[2]);
            find_event(t,key,hash_size,num_file,year_index,annual_storms_save);
            cout << endl;
            cout << "Load Factor: "<< load_factor<< endl;
        }
        if (value_save[0]=="range"){
            if (value_save[1]=="all"){
                // for all years
                int year = 0;
                storm_event * all_event_save = new storm_event[total_file_size];
                for (int i=0; i<num_file; i++){
                    for (int j=0; j<file_d_size[i];j++){
                        all_event_save[year]=annual_storms_save[i].events[j];
                        year++;
                    }
                }
                if (value_save[2]=="state"){
                    char low[STATE_LEN];
                    char high[STATE_LEN];
                    strcpy(low,value_save[3].c_str());
                    strcpy(high,value_save[4].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, all_event_save[0].event_id,all_event_save[0].state);
                    for (int i=1;i<total_file_size;i++){
                        insert(bst_node, all_event_save[i].event_id,all_event_save[i].state);
                    }
                    inorder_traversal_state(bst_node, low, high,t,bst_node->event_id,hash_size,
                            num_file,year_index,annual_storms_save);
                    if (!flag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;

                }
                else if (value_save[2]=="month_name"){
                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    strcpy(low,value_save[3].c_str());
                    strcpy(high,value_save[4].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, all_event_save[0].event_id,all_event_save[0].month_name);
                    for (int i=1;i<total_file_size;i++){
                        insert(bst_node, all_event_save[i].event_id,all_event_save[i].month_name);
                    }
                    inorder_traversal_month(bst_node, low, high,t,bst_node->event_id,hash_size,
                            num_file,year_index,annual_storms_save);
                    if (!flag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;
                }
            }
            else{
                // for a sepcific year
                int year = string_2_int(value_save[1]);
                int index=0;
                for (int i=0;i<num_file;i++){
                    if (year == year_index[i])
                        index = i;
                }
                if (value_save[2]=="state"){
                    char low[STATE_LEN];
                    char high[STATE_LEN];
                    strcpy(low,value_save[3].c_str());
                    strcpy(high,value_save[4].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, annual_storms_save[index].events[0].event_id,
                            annual_storms_save[index].events[0].state);
                    for (int i=1;i<file_d_size[index];i++){
                        insert(bst_node, annual_storms_save[index].events[i].event_id,
                                annual_storms_save[index].events[i].state);
                    }
                    inorder_traversal_state(bst_node, low, high,t,bst_node->event_id,hash_size,
                            num_file,year_index,annual_storms_save);
                    if (!flag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;
                }
                else if (value_save[2]=="month_name"){
                    char low[MONTH_LEN];
                    char high[MONTH_LEN];
                    strcpy(low,value_save[3].c_str());
                    strcpy(high,value_save[4].c_str());
                    struct bst* bst_node = NULL;
                    bst_node = insert(bst_node, annual_storms_save[index].events[0].event_id,
                                      annual_storms_save[index].events[0].month_name);
                    for (int i=1;i<file_d_size[index];i++){
                        insert(bst_node, annual_storms_save[index].events[i].event_id,
                               annual_storms_save[index].events[i].month_name);
                    }
                    inorder_traversal_month(bst_node, low, high,t,bst_node->event_id,hash_size,
                            num_file,year_index,annual_storms_save);
                    if (!flag){
                        cout << "No storm events found for given range"<< endl;
                    }
                    int height = find_height(bst_node);
                    int l_height = find_height(bst_node->left);
                    int r_height = find_height(bst_node->right);
                    cout<< endl;
                    cout<< "Height of bst: "<< height<<endl;
                    cout<< "Height of left bst: "<< l_height<<endl;
                    cout<< "Height of right bst: "<< r_height<<endl;
                }
            }
        }
        else{
            if (value_save[1]=="max"){
                if (value_save[2] == "fatality"){
                    int num = string_2_int(value_save[3]);
                    // do find fatality
                    if (value_save[4]=="all"){
                        // find all years
                        int fatality_size = 0;
                        for (int i=0; i<num_file; i++){
                            fatality_size = fatality_size+ annual_fatality_save[i].num_all_fatality;
                        }
                        max_fatality * all_fatality_save = new max_fatality[fatality_size];
                        int year=0;
                        for (int i=0; i<num_file; i++){
                            for (int j=0; j<annual_fatality_save[i].num_all_fatality;j++){
                                all_fatality_save[year]=annual_fatality_save[i].fatality[j];
                                year++;
                            }
                        }
                        find_max_fatality(all_fatality_save,num, t,fatality_size,
                                hash_size,num_file,year_index,annual_storms_save);
                        cout << endl;
                        cout << "Load Factor: "<< load_factor<< endl;
                    }
                    else{
                        // a specific year
                        int year = string_2_int(value_save[4]);
                        int index=0;
                        for (int i=0;i<num_file;i++){
                            if (year == year_index[i])
                                index = i;
                        }
                        find_max_fatality(annual_fatality_save[index].fatality,num,
                                t,annual_fatality_save[index].num_all_fatality,
                                hash_size,num_file,year_index,annual_storms_save);
                        cout << endl;
                        cout << "Load Factor: "<< load_factor<< endl;
                    }
                }
                else{
                    int num = string_2_int(value_save[2]);
                    if (value_save[3]=="all"){
                        int year = 0;
                        // find from all years
                        // for all years, use this
                        storm_event * all_event_save = new storm_event[total_file_size];
                        for (int i=0; i<num_file; i++){
                            for (int j=0; j<file_d_size[i];j++){
                                all_event_save[year]=annual_storms_save[i].events[j];
                                year++;
                            }
                        }
                        if (value_save[4] == "damage_property"){
                            find_max_all_damage_property(all_event_save,num,total_file_size);
                            cout << endl;
                            cout << "Load Factor: "<< load_factor<< endl;
                        }
                        else{
                            find_max_all_damage_crops(all_event_save,num,total_file_size);
                            cout << endl;
                            cout << "Load Factor: "<< load_factor<< endl;
                        }
                    }
                    else{
                        int year = string_2_int(value_save[3]);
                        // find from a specific year
                        int index=0;
                        for (int i=0;i<num_file;i++){
                            if (year == year_index[i])
                                index = i;
                        }
                        if (value_save[4]== "damage_property"){
                            find_max_all_damage_property(annual_storms_save[index].events,num,file_d_size[index]);
                            cout << endl;
                            cout << "Load Factor: "<< load_factor<< endl;
                        }
                        else{
                            find_max_all_damage_crops(annual_storms_save[index].events,num,file_d_size[index]);
                            cout << endl;
                            cout << "Load Factor: "<< load_factor<< endl;
                        }
                    }
                }
            }
        }
    }

    free(t);
    return 0;
}
