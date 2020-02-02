// Author: Xiao 'Leo' Liu
// by only using stdio.

#include <iostream>
#include <string.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<int> component;
using namespace std;
#define INF 99999

struct vertex
{
    int vertex_no;
    int data;
    int dt;
    int ft;
    string color;
    struct vertex * next = NULL;
};

//float calculate_correlation(vector< vector<float> > data_save, int v1, int v2){
//    float r = 0;
//    int num_v1 =0;
//    int num_v2 =0;
//    for (int i=0;i<832;i++){
//        if (data_save[v1].at(i) == 168 || data_save[v2].at(i)== 168){
//            r = 0;
//            return r;
//        }
//        else if (data_save[v1].at(i) != 157){
//            num_v1++;
//        }
//    }
//    float sum_v1 = 0;
//    for (int i=0;i<832;i++){
//        if (data_save[v1].at(i) != 157){
//            sum_v1 = sum_v1+data_save[v1].at(i);
//        }
//    }
//    float mean_v1 = sum_v1/float(num_v1);
//    float s_v1 = 0.0;
//    for (int i = 0;i<832;i++){
//        if (data_save[v1].at(i) != 157){
//            s_v1 = s_v1+ pow((data_save[v1].at(i) - mean_v1), 2.0);
//        }
//    }
//
//
//    for (int i=0;i<832;i++){
//        if (data_save[v1].at(i) == 168 || data_save[v2].at(i) == 168){
//            r = 0;
//            return r;
//        }
//        else if (data_save[v2].at(i) != 157){
//            num_v2++;
//        }
//    }
//
//    float sum_v2 = 0;
//    for (int i=0;i<832;i++){
//        if (data_save[v2].at(i) != 157){
//            sum_v2 = sum_v2+data_save[v2].at(i);
//        }
//    }
//    float mean_v2 = sum_v2/float(num_v2);
//    float s_v2 = 0;
//    for (int i = 0;i<832;i++){
//        if (data_save[v2].at(i) != 157){
//            s_v2 = s_v2+ pow((data_save[v2].at(i) - mean_v2), 2.0);
//        }
//    }
//
//
//    float s_v12 = 0;
//    for (int i=0;i<832;i++){
//        if( data_save[v1].at(i) != 157 && data_save[v2].at(i) != 157){
//            s_v12 = s_v12 + (data_save[v1].at(i) - mean_v1)*(data_save[v2].at(i) - mean_v2);
//        }
//    }
//
//
//    r = s_v12/pow((s_v1*s_v2),0.5);
//    r = abs(r);
//
//    return r;
//}

float get_r(vector< vector<float> > Sxy_save, vector<float> Sxx_save, int v1, int v2){
    float r = 0;
    r = (Sxy_save[v1].at(v2)) /sqrt(Sxx_save.at(v1) * Sxx_save.at(v2));
    r = abs(r);
    return r;
}

void add_edge(struct vertex **G, struct vertex * vertex_list, int v1, int v2){
    struct vertex *temp1 = G[v1];
    struct vertex *temp2 = G[v2];
    struct vertex *head1 = G[v1];
    struct vertex *head2 = G[v2];
    // advancing temp1 and temp2, check if the edge will be added;
    while(temp1->next!=NULL){
        if (temp1->vertex_no == v2){
            return;
        }
        temp1 = temp1->next;
    }
    while(temp2->next!=NULL){
        if (temp2->vertex_no == v1){
            return;
        }
        temp2 = temp2->next;
    }
    // after checking, now add the edge between v1 and v2;
    struct vertex * entry = new vertex;
    entry->vertex_no = vertex_list[v2].vertex_no;
    entry->data = vertex_list[v2].data;
    temp1->next = entry;
//    entry->next = head1;
//    G[v1] = entry;

    struct vertex * entry1 = new vertex;
    entry1->vertex_no = vertex_list[v1].vertex_no;
    entry1->data = vertex_list[v1].data;
    temp2->next = entry1;
//    entry1->next = head2;
//    G[v2] = entry1;
}

bool is_edge(vertex **G, int v1, int v2) {
    bool flag = false;
    if (v1 == v2){
        flag = false;
        return flag;
    }
    struct vertex *temp1 = G[v1];
    // advancing temp1 and temp2, check if the edge will be added;
    while(temp1!=NULL){
        if (temp1->vertex_no == v2){
            flag = true;
            return flag;
        }
        temp1 = temp1->next;
    }
    return flag;
}

int DFS_VISIT(vertex **G, struct vertex * vertex_list,int u, int time,int num_node){
    time = time+1;
    num_node = num_node+1;
    vertex_list[u].dt = time;
    vertex_list[u].color = "GRAY";
    for (int i=0;i<3969;i++){
        if(is_edge(G,u,i)){
            if (vertex_list[i].color == "WHITE"){
                num_node = DFS_VISIT(G,vertex_list,i,time,num_node);
            }
        }
    }
    vertex_list[u].color = "BLACK";
    time = time+1;
    vertex_list[u].ft = time;
    return num_node;
}

int DFS(vertex **G, struct vertex * vertex_list){
    int num_connected = 0;
    int time = 0;
    int num_node=0;
    for (int i=0;i<3969;i++){
        if(vertex_list[i].color=="WHITE"){
            num_node = DFS_VISIT(G,vertex_list,i,time,num_node);
            component.push_back(num_node);
            num_node=0;
            num_connected++;
        }
    }
    return num_connected;
}

float get_cluster_coefficient(vertex **G, vector< vector<float> > data_save){
    vector <float> cluster;
    for (int i=0; i<3969; i++){
        int k =0;
        vector <int> e;
        struct vertex *temp;
        temp = G[i];
        if (data_save[i].at(0)!=168 && temp->next!=NULL){
            while (temp->next!=NULL){
                k++;
                temp = temp->next;
                e.push_back(temp->vertex_no);
            }
            int ee = 0;
            if (k>=2){
                for (int j=0; j<e.size();j++){
                    for (int jj=j+1; jj<e.size();jj++){
                        if (is_edge(G,e.at(j),e.at(jj))){
                            ee++;
                        }
                    }
                }
            }
            float cluster_coefficient;
            if (ee == 0){
                cluster_coefficient = 0;
            }
            else{
                cluster_coefficient = float(2*ee)/float(k*(k-1));
            }
            cluster.push_back(cluster_coefficient);
//            cout<< cluster_coefficient << endl;
            e.clear();
        }
    }
    float sum_cluster = 0.0;
    for (int i=0;i<cluster.size();i++){
        sum_cluster = sum_cluster + cluster.at(i);
    }

    float avg_cluster = sum_cluster/float(cluster.size());
    cluster.clear();
    return avg_cluster;
}

float Floyd_Warshall(int **adj_G){
    int count = 0;
    int sum = 0;
    for (int k=0;k<3969;k++){
        for (int i=0; i<3969; i++){
            for (int j = i+1; j<3969; j++){
                if (adj_G[i][k] + adj_G[k][j] < adj_G[i][j]){
                    adj_G[i][j] = adj_G[i][k] + adj_G[k][j];
                    adj_G[j][i] = adj_G[i][k] + adj_G[k][j];
                }
            }
        }
    }

    for (int i=0; i<3969; i++){
        for (int j=i+1; j<3969; j++){
            if (adj_G[i][j]!= INF){
                count++;
                sum = sum+adj_G[i][j];
            }
        }
    }
    float l_G = float(sum)/float(count);
    return l_G;
}

int main(){
    cout<<"--------------- loading the data -----------------"<<endl;
    string year;
    string week;
    string name;
    vector< vector<float> > data_save (3969, vector<float> (832));
    for (int yyyy = 1990;yyyy<2006;yyyy++){
        year = static_cast<ostringstream*>( &(ostringstream() << yyyy) )->str();
        cout<<"loading data from year: "<< year<<endl;
        for (int ww = 1;ww<53;ww++){
            if (ww<10){
                week = "0"+static_cast<ostringstream*>( &(ostringstream() << ww) )->str();
            }
            else if (ww>=10){
                week = static_cast<ostringstream*>( &(ostringstream() << ww) )->str();
            }
            name = "./"+ year +"/Beaufort_Sea_diffw"+week+"y"+year+"+landmask";
            ifstream inputFile(name.c_str(), ios::in |ios::binary);
            float dataIn = 0;
            for (int i=0;i<3969;i++){
                inputFile.read((char*)&dataIn,4);
                data_save[i].at(((yyyy-1989)-1)*52 + ww-1) = dataIn;
            }
            inputFile.close();
        }
    }
    cout<<"--------------- finished loading the data -----------------"<<endl;


    // save all the data for building the graph;
    cout<<"--------------- preparing the data -----------------"<<endl;
    vector<float> Sxx_save (3969);
    vector<float> mean_save(3969);
    for (int i=0;i<3969;i++){
        int num_v =0;
        float sum = 0;
        for (int j=0;j<832;j++){
            if(data_save[i].at(j)!=157){
                num_v++;
                sum=sum+data_save[i].at(j);
            }
        }
        float mean = sum/float(num_v);
        mean_save.at(i) = mean;
        float Sxx = 0;
        for (int j=0;j<832;j++){
            if(data_save[i].at(j)!=157){
                Sxx = Sxx + (data_save[i].at(j) - mean)*(data_save[i].at(j) - mean);
            }
        }
        Sxx_save.at(i) = Sxx;
    }
    vector< vector<float> > Sxy_save(3969, vector<float> (3969));
    for (int i=0;i<3969;i++){
        for (int j=i+1;j<3969;j++){
            float Sxy = 0;
            for (int k=0;k<832;k++){
                Sxy = Sxy + (data_save[i].at(k) - mean_save.at(i))*(data_save[j].at(k) - mean_save.at(j));
            }
            Sxy_save[i].at(j)=Sxy;
        }
    }


    cout<<"--------------- start building graph -----------------"<<endl;
    float thresh[3] = {0.95, 0.925, 0.9};
    for (int kk=0;kk<3;kk++){
        cout<< "building graph on "<< thresh[kk]<<" threshold"<<endl;
        int** adj_G = new int*[3969];
        for(int i = 0; i < 3969; ++i)
            adj_G[i] = new int[3969];
        for (int i=0; i<3969; i++){
            for (int j=i; j<3969; j++){
                if (i==j){
                    adj_G[i][j] = 0;
                }
                else{
                    adj_G[i][j] = INF;
                    adj_G[j][i] = INF;
                }
            }
        }

        vertex * vertex_list = new vertex[3969];
        for (int i=0;i<3969;i++){
            vertex_list[i].data = i;
            vertex_list[i].vertex_no = i;
            vertex_list[i].dt=0;
            vertex_list[i].ft=0;
            vertex_list[i].color = "WHITE";
        }
        struct vertex **G;
        G = static_cast<vertex**>(malloc(sizeof(*G) *3969));
        for (int i=0;i<3969;i++){
            G[i] = &vertex_list[i];
        }


        float rr=0;

        for (int i=0;i<3969; i++){
//        cout<< "----"<<i<<"----"<<endl;
            for (int j=i+1;j<3969;j++){
                if (data_save[i].at(0)!=168 && data_save[j].at(0)!=168){
                    rr = (Sxy_save[i].at(j)) /sqrt(Sxx_save.at(i) * Sxx_save.at(j));
                    rr = abs(rr);
                    if(rr>thresh[kk]){
                        add_edge(G,vertex_list,i,j);
                        adj_G[i][j] = 1;
                        adj_G[j][i] = 1;
                    }
                }
            }
        }
        float r_G;
        r_G = get_cluster_coefficient(G,data_save);
        cout<< "clustering coefficient of G: "<< r_G <<endl;
        float l_G;
        l_G = Floyd_Warshall(adj_G);
        cout<< "characteristic path length: "<< l_G<<endl;



//        cout<<"--------------- start DFS on graph -----------------"<<endl;
//        int connected = DFS(G,vertex_list);
//        cout << "connected components: "<<connected<< endl;
//        for (int i=0;i<component.size();i++){
//            if (component.at(i)!=1){
//                cout<<component.at(i)<<endl;
//            }
//        }
//        component.clear();
//


        // initialize an array for saving the degree of distribution;
        int arr[3969];
        for (int i=0;i<3969;i++){
            arr[i]=0;
        }
        // calculate the degree of distribution as an array;
        for (int i = 0; i<3969;i++){
            int count = -1;
            while (G[i]!=NULL){
                count++;
                G[i] = G[i]->next;
            }
            arr[count]++;
        }

        //computing the characteristic of random graphs;
        int sum_degree = 0;
        int sum_count = 0;
        float mean_k;
        float r_random;
        float l_random;

        //print the result of distribution array
        for (int i=0;i<3969;i++){
            if (arr[i]!=0){
//                cout<<"degree of "<< i << ": "<< arr[i]<<endl;
                sum_degree = sum_degree + i*arr[i];

//                cout<<arr[i]<<endl;
            }
        }
        for (int i =0; i<3969; i++){
            if (data_save[i].at(0)!=168){
                sum_count++;
            }
        }
        mean_k = float(sum_degree)/float(sum_count);
        r_random = mean_k/float(sum_count);
        l_random = float(log(sum_count))/ float(log(mean_k));
        cout<< "clustering coefficient of G_random: "<< r_random<<endl;
        cout << "characteristic path length of G_random: "<< l_random<<endl;

        delete[](vertex_list);
        delete[] (adj_G);
        free(G);
        cout<<endl;
    }
    return 0;
}
