/* 
 * Mamagiannos Dimitrios - April 2014 
 * 
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

class graphSequence{
    
    int *sequence, *adjacencyMatrix, n;
    
public:
    graphSequence();
    
    bool isGraphic_Havel_Hakimi(int *sequence,int n);
    bool isGraphic_Erdos_Galai();
    
    void mergesort(int *a, int*b, int start, int endd);
    void merge(int *a, int *b, int start, int halfpoint, int endd);
    int findMAx(int* sequence, int n);
    
    void findAdjacencyMatrix();
    void print();
    
    ~graphSequence();
    
};


graphSequence::graphSequence(){
    
    cout<<"Insert n\n";
    cin>>n;
    
    sequence = new int[n];
    
    cout<<"Insert the nodes' verteces\n";
    for(int i=0;i<n;i++){
        cin>>sequence[i];
    }
    
    adjacencyMatrix = new int[n*n];
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adjacencyMatrix[i + j*n] = 0;
        }
    }
}

graphSequence::~graphSequence(){
    free(sequence);
    free(adjacencyMatrix);
    
}

bool graphSequence::isGraphic_Erdos_Galai(){
    
    bool isGraphic = true;
    
    int sumOfDegrees = 0;
    
    for(int i=0;i<n;i++){
        sumOfDegrees += sequence[i];
    }
    
    if(sumOfDegrees%2){
        isGraphic = false;
    }
    else{
        int r = n-1;
        for(int i=0;i<r;i++){
            int sumOfDegreesTo_r=0;
            // 
            for(int j=0;j<r;j++){
                sumOfDegreesTo_r += sequence[j];
            }
            //
            if(sumOfDegreesTo_r <= r*(r-1)){ 
                continue;
            }
            //
            
            int sumOfMin_r_degree = 0;
            
            for(int j=r;j<n;j++){
                int min=sequence[j];
                if(r<min) min = r;
                sumOfMin_r_degree += min;
            }
            
            if(sumOfDegreesTo_r <= r*(r-1) + sumOfMin_r_degree){
                continue;
            }
            else{
                isGraphic = false;
                break;
            }
        }
    }
    return isGraphic;
}

bool graphSequence::isGraphic_Havel_Hakimi(int* sequence, int n){
    
    bool isGraphic,nonZeroDegree=true;
    
    if(findMAx(sequence,n)>n-1){
        isGraphic = false;
        return isGraphic;
    }
    
    for(int i=0;i<n;i++){
        if(sequence[i]>0){
            nonZeroDegree = true;
            break;
        }
        else if(sequence[i]==0){
            nonZeroDegree = false;
        }
        else{
            isGraphic = false;
            return isGraphic;
        }
    }
    if(!nonZeroDegree){
        isGraphic = true;
    }
    else{
        int* tempSequence = new int[n];
        mergesort(sequence,tempSequence,0,n-1);
        int *newCheckSequence;
        newCheckSequence = new int[n-1];
        for(int i=0;i<sequence[0];i++){
            newCheckSequence[i] = sequence[i+1]-1;
        }
        for(int i=sequence[0];i<n-1;i++){
            newCheckSequence[i] = sequence[i+1];
        }
        isGraphic = isGraphic_Havel_Hakimi(newCheckSequence,n-1);
        delete[] tempSequence;
        delete[] newCheckSequence;
    }
    return isGraphic;
}

int graphSequence::findMAx(int* sequence, int n){
    
    int max=sequence[0];
    
    for(int i=1;i<n;i++){
        if(sequence[i]>max){
            max = sequence[i];
        }
    }
    return max;
}


void graphSequence::findAdjacencyMatrix(){
    
    int sumOfAlreadyConnectedNodes=0,*connectedNodes; 	//connected = how many nodes are already connected.
    
    connectedNodes = new int[n];
    
    for(int i=0;i<n;i++){
        connectedNodes[i] = 0;
    }
    
    for(int i=0;i<n;i++){
        sumOfAlreadyConnectedNodes=sequence[i];
        
        for(int j=0;j<n;j++){
            if(i==j){
                adjacencyMatrix[i+j*n] = 0;
            }
            else if(adjacencyMatrix[j+i*n]==1){
                //If adjacencyMatrix[i+j*n] == 1 , there is already a connection. The sumOfAlreadyConnectedNodes is reduced 1 
                adjacencyMatrix[i+j*n] = 1;
                sumOfAlreadyConnectedNodes--;
            }
            else if(sumOfAlreadyConnectedNodes!=0 && connectedNodes[j]<sequence[j] && connectedNodes[i]<sequence[i]){
                adjacencyMatrix[i+j*n] = 1;
                
                sumOfAlreadyConnectedNodes-=1;
                
                connectedNodes[j]++;
                connectedNodes[i]++;
            }
            if(sumOfAlreadyConnectedNodes==0){
                break;
            }
        }
    }
    
}
void graphSequence::print(){
    cout<<"The adjacency matrix is:\n\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<adjacencyMatrix[i+j*n]<<"  ";
        }
        cout<<"\n";
    }
}
void graphSequence::mergesort(int *a, int*b, int start, int endd){
    int halfpoint;
    if (start < endd) {
        halfpoint = (start + endd) / 2;
        mergesort(a, b, start, halfpoint);
        mergesort(a, b, halfpoint + 1, endd);
        merge(a, b, start, halfpoint, endd);
    }
}

void graphSequence:: merge(int *a, int *b, int start, int halfpoint, int endd) {
    int h, i, j, k;
    h = start;
    i = start;
    j = halfpoint + 1;
    
    while ((h <= halfpoint) && (j <= endd)) {
        if (a[h] >= a[j]) {
            b[i] = a[h];
            h++;
        } else {
            b[i] = a[j];
            j++;
        }
        i++;
    }
    if (h > halfpoint) {
        for (k = j; k <= endd; k++) {
            b[i] = a[k];
            i++;
        }
    } else {
        for (k = h; k <= halfpoint; k++) {
            b[i] = a[k];
            i++;
        }
    }
    
    for (k = start; k <= endd; k++) {
        a[k] = b[k];
    }
}

int main(int argc, char* argv[]){
    
    graphSequence graphseq;
    if( graphseq.isGraphic_Erdos_Galai() ){
        graphseq.findAdjacencyMatrix();
	graphseq.print();
    }
    else{
        cout<<"No graph sequence\n";
    }
    
    
    return 0;
}
