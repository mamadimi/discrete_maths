#include "iostream"
#include "stdlib.h"
#include "cstring"

using namespace std;

class graph{
    
    int **nodeNodeArray,**nodeVertexArray;
    
    bool *activeNode,*activeVertex,*activeSameVertex;
    
    int **contractedVertex,**deletedVertex,*sameVertex;
    
    int conCounter,vertCounter,sameVertCounter;
    
    int nodes,verteces; //total nodes and verteces
    
    int sumVertex;
    
    int nods[2];
    
public:
    
    graph();
    ~graph();
    graph(int **nodeNodeArray,int **nodeVertexArray,int nodes,int verteces);
    void graph_K_5();
    void graph_K_3_3();
    
    void findNodesOfVertex(int vertex, int *currentNodes);
    void contractionVertex(int node1,int node2);
    void deleteVertex(int node1,int node2);
    void print();
    
    friend bool isMinor(graph *A, graph *B);
    friend bool isPlanar(graph *A);
    friend void deleteVertecesProcess(graph *A, graph *B, bool *isMinor);
    
    
};
graph::graph(){
    
}
graph::~graph(){
    
    for(int i=0;i<nodes;i++){
        free(nodeNodeArray[i]);
    }
    free(nodeNodeArray);
    
    for(int i=0;i<verteces;i++){
        free(nodeVertexArray[i]);
    }
    free(nodeVertexArray);   
}
graph::graph(int **nodeNodeArray,int **nodeVertexArray,int nodes,int verteces){
    this->nodeNodeArray = nodeNodeArray;
    this->nodeVertexArray = nodeVertexArray;
    this->nodes = nodes;
    this->verteces = verteces;
    
    //Initialization of active nodes and verteces
    
    activeNode= new bool[nodes];
    for(int i=0;i<nodes;i++){
        activeNode[i]=true;
    }
    
    activeVertex = new bool[verteces];
    for(int i=0;i<verteces;i++){
        activeVertex[i]=true;
    }
    
    activeSameVertex = new bool[verteces];
    for(int i=0;i<verteces;i++){
        activeSameVertex[i]=true;
    }
    
    contractedVertex=(int**)malloc(verteces*sizeof(int*));
    for(int i=0;i<verteces;i++){
        contractedVertex[i] = (int*)malloc(2*sizeof(int));
    }
    
    deletedVertex=(int**)malloc(verteces*sizeof(int*));
    for(int i=0;i<verteces;i++){
        deletedVertex[i] = (int*)malloc(2*sizeof(int));
    }
    
    sameVertex=(int*)malloc(verteces*sizeof(int));
    
    conCounter=0;
    vertCounter=0;
    sameVertCounter=0;
    sumVertex=0;
}

void graph::graph_K_5(){
    
    nodes = 5;
    verteces = 9;
    
    //Initialization nodeNodeArray and nodeVertexArray for K_5 graph
    
    nodeNodeArray = (int**)malloc(nodes*sizeof(int*));
    for(int i=0;i<nodes;i++){
        nodeNodeArray[i] = (int*)malloc(nodes*sizeof(int));
    }
    
    for(int i=0;i<nodes;i++){
        for(int j=i;j<nodes;j++){
            if(i==j){
                nodeNodeArray[i][j] = 0;
            }
            else{
                nodeNodeArray[i][j] = 1;
                nodeNodeArray[j][i] = 1;
            }
        }
    }
    
    nodeVertexArray = (int**)malloc(verteces*sizeof(int*));
    for(int i=0;i<verteces;i++){
        nodeVertexArray[i] = (int*)malloc(nodes*sizeof(int));
    }
    
    for(int i=0;i<verteces;i++){
        for(int j=0;j<nodes;j++){
            nodeVertexArray[i][j]=0;
        }
    }
    
    nodeVertexArray[0][0]=1;nodeVertexArray[0][1]=1;nodeVertexArray[1][1]=1;
    nodeVertexArray[1][2]=1;nodeVertexArray[2][2]=1;nodeVertexArray[2][3]=1;
    nodeVertexArray[3][3]=1;nodeVertexArray[3][4]=1;nodeVertexArray[4][0]=1;
    nodeVertexArray[4][4]=1;nodeVertexArray[5][0]=1;nodeVertexArray[5][2]=1;
    nodeVertexArray[6][0]=1;nodeVertexArray[6][3]=1;nodeVertexArray[7][1]=1;
    nodeVertexArray[7][4]=1;nodeVertexArray[8][1]=1;nodeVertexArray[8][3]=1;
}

void graph::graph_K_3_3(){
    
    nodes = 6;
    verteces = 9;
    
    //Initialization nodeNodeArray and nodeVertexArray for K_5 graph
    
    nodeNodeArray = (int**)malloc(nodes*sizeof(int*));
    for(int i=0;i<nodes;i++){
        nodeNodeArray[i] = (int*)malloc(nodes*sizeof(int));
    }
    
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            nodeNodeArray[i][j] = 1;
            if(i==j) nodeNodeArray[i][j] = 0;
        }
    }
    
    
    nodeVertexArray = (int**)malloc(verteces*sizeof(int*));
    for(int i=0;i<verteces;i++){
        nodeVertexArray[i] = (int*)malloc(nodes*sizeof(int));
    }
    
    for(int i=0;i<verteces;i++){
        for(int j=0;j<nodes;j++){
            nodeVertexArray[i][j]=0;
        }
    }
    
    nodeVertexArray[0][0]=1;nodeVertexArray[1][0]=1;nodeVertexArray[2][0]=1;
    nodeVertexArray[3][1]=1;nodeVertexArray[4][1]=1;nodeVertexArray[5][1]=1;
    nodeVertexArray[6][2]=1;nodeVertexArray[7][2]=1;nodeVertexArray[8][2]=1;
    nodeVertexArray[0][3]=1;nodeVertexArray[1][4]=1;nodeVertexArray[2][5]=1;
    nodeVertexArray[3][3]=1;nodeVertexArray[4][4]=1;nodeVertexArray[5][5]=1;
    nodeVertexArray[6][3]=1;nodeVertexArray[7][4]=1;nodeVertexArray[8][5]=1;
}

void graph::findNodesOfVertex(int vertex, int *currentNodes){
    
    int numberOfConnectedNodes=0;
    
    for(int i=0;i<nodes;i++){
        if(activeNode[i]==true && nodeVertexArray[vertex][i]==1){
            currentNodes[numberOfConnectedNodes]=i;
            numberOfConnectedNodes+=1;
        }
        if(numberOfConnectedNodes==2) break;
    }
}

void graph::contractionVertex(int node1,int node2){
    // Update nodeNodeArray
    for(int i=0;i<nodes;i++){
        if(i!=node1 && i!=node2 && nodeNodeArray[node2][i]==1){
            nodeNodeArray[node1][i] = nodeNodeArray[node2][i];
        }
    }
    activeNode[node2] = false;
    
    //Delete verteces because of contraction
    
    int vertexID=0;
    
    for(int i=0;i<verteces;i++){
        if(activeVertex[i] == true){
            if(nodeVertexArray[i][node1] == 1 && nodeVertexArray[i][node2] == 1){
                vertexID = i;
                activeVertex[vertexID]=false;
            }
        }
    }
    
    // nodeVertexArray
    
    for(int i=0;i<verteces;i++){
        if(nodeVertexArray[i][node1]==1 || nodeVertexArray[i][node2]==1){
            nodeVertexArray[i][node1] = nodeVertexArray[i][node2] = 1;
        }
    }
}

void graph::deleteVertex(int node1,int node2){
    for(int i=0;i<verteces;i++){
        if(nodeVertexArray[i][node1]==1 && nodeVertexArray[i][node2]==1){
            activeVertex[i]=false;
        }
    }
}
void deleteVertecesProcess(graph *A, graph *B, bool *isMinor){
    *isMinor = true;
    
    for(int i=0;i<B->nodes;i++){
        for(int j=i;j<B->nodes;j++){
            if(B->nodeNodeArray[i][j] == A->nodeNodeArray[i][j]){
                continue;
            }
            else{
                if(B->nodeNodeArray[i][j]==0){
                    A->deleteVertex(i,j);
                    A->deletedVertex[A->vertCounter][0]=i;
                    A->deletedVertex[A->vertCounter][1]=j;
                    A->vertCounter++;
                }
                else{
                    *isMinor=false;
                    break;
                }
            }
        }
        
        if(*isMinor==false){
            break;
        }
    }
    
    if(*isMinor){
        //Same nodes' ids speculation
        bool activeSameVertexFlag=true;
        
        for(int i=0;i<B->verteces;i++){
            for(int k=0;k<A->verteces;k++){
                if(A->activeSameVertex[k]==true){
                    activeSameVertexFlag = true;
                    
                    for(int j=0;j<B->nodes;j++){
                        if((A->nodeVertexArray[k][j])!= (B->nodeVertexArray[i][j])){
                            activeSameVertexFlag = false;
                            break;
                        }
                    }
                    if(activeSameVertexFlag){
                        A->activeSameVertex[k]=false;
                        A->sumVertex++;
                        A->sameVertex[A->sameVertCounter]=k;
                        A->sameVertCounter++;
                        break;
                    }
                }
            }
        }
        if( !(A->sumVertex == B->verteces) ) *isMinor = false;
    }
}

bool isMinor(graph *A, graph *B){
    if(A->nodes < B->nodes) return false;
    
    int numberOfContactedNodes=0,vertexCounter=0;
    int startNode = A->nodes-1;
    
    //Nodes contraction
    
    for(int i=0;i< ( A->nodes - B->nodes );i++){
        bool contractionFlag = true;
        vertexCounter=0;
        do{
            if(A->activeVertex[vertexCounter]==true && vertexCounter < A->verteces){
                
                int currentNodes[2];
                
                A->findNodesOfVertex(vertexCounter,currentNodes);
                
                if(currentNodes[0]== startNode || currentNodes[1] == startNode){
                    
                    numberOfContactedNodes++;
                    startNode--;
                    
                    A->contractionVertex(currentNodes[0],currentNodes[1]);
                    A->contractedVertex[A->conCounter][0] = currentNodes[0];
                    A->contractedVertex[A->conCounter][1] = currentNodes[1];
                    A->conCounter++;
                    
                    contractionFlag = false;
                }
            }
            vertexCounter++;
            
        }while(contractionFlag);
        
        if(numberOfContactedNodes == A->nodes - B->nodes){ //If the 2 grpahs have the same nodes, start delete just other verteces
            bool isMinorFlag = true;
            deleteVertecesProcess(A, B, &isMinorFlag);
            
            return isMinorFlag;
        }
        else{
            return false;
        }
    }
    
    return false;
}

bool isPlanar(graph *A){
    
    //Copy grpah A
    int **nodeNodeArray_temp, **nodeVertexArray_Temp;
    
    nodeNodeArray_temp = (int**)malloc(A->nodes*sizeof(int*));
    for(int i=0;i<A->nodes;i++){
        nodeNodeArray_temp[i] = (int*)malloc(A->nodes*sizeof(int));
    }
    
    for(int i=0;i<A->nodes;i++){
        for(int j=0;j<A->nodes;j++){
            nodeNodeArray_temp[i][j] = A->nodeNodeArray[i][j];
        }
    }
    
    nodeVertexArray_Temp = (int**)malloc(A->verteces*sizeof(int*));
    for(int i=0;i<A->verteces;i++){
        nodeVertexArray_Temp[i] = (int*)malloc(A->nodes*sizeof(int));
    }
    
    for(int i=0;i<A->verteces;i++){
        for(int j=0;j<A->nodes;j++){
            nodeVertexArray_Temp[i][j] = A->nodeVertexArray[i][j];
        }
    }
    
    graph Atemp(nodeNodeArray_temp, nodeVertexArray_Temp, A->nodes, A->verteces);
    
    graph K_5;
    K_5.graph_K_5();
    
    if(isMinor(&Atemp,&K_5)){
        return false;
    }
    else{
        graph K_3_3;
        K_3_3.graph_K_3_3();
        
        if(isMinor(A,&K_3_3)){
            return false;
        }
        else{
            return true;
        }
    }
}
void graph::print(){
    cout<<"Node Node array\n";
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            cout<<nodeNodeArray[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    cout<<"Node verteces array\n";
    for(int i=0;i<verteces;i++){
        for(int j=0;j<nodes;j++){
            cout<<nodeVertexArray[i][j]<<" ";
        }
        cout<<"\n";
    }
    
}

void demoIsMinor(){
    cout<<"Demo is Minor\n";
    int nodes = 4;
    int verteces = 5;
    int **nodeNodeArray, **nodeVertexArray;
    
    nodeNodeArray = (int**)malloc(nodes*sizeof(int*));
    for(int i=0;i<nodes;i++){
        nodeNodeArray[i] = (int*)malloc(nodes*sizeof(int));
        //Zero Initialization 
        for(int j=0;j<nodes;j++){
            nodeNodeArray[i][j] = 0;
        }
    }
    
    nodeNodeArray[0][1] = 1;nodeNodeArray[0][2] = 1;nodeNodeArray[0][3] = 1;
    nodeNodeArray[1][0] = 1;nodeNodeArray[1][2] = 1;
    nodeNodeArray[2][0] = 1;nodeNodeArray[2][1] = 1;nodeNodeArray[2][3] = 1;
    nodeNodeArray[3][0] = 1;nodeNodeArray[3][2] = 1;
    
    nodeVertexArray = (int**)malloc(verteces*sizeof(int*));
    for(int i=0;i<verteces;i++){
        nodeVertexArray[i] = (int*)malloc(nodes*sizeof(int));
        //Zero Initialization 
        for(int j=0;j<nodes;j++){
            nodeVertexArray[i][j] = 0;
        }
    }
    
    nodeVertexArray[0][0] = 1;nodeVertexArray[0][1] = 1;
    nodeVertexArray[1][1] = 1;nodeVertexArray[1][2] = 1;
    nodeVertexArray[2][0] = 1;nodeVertexArray[2][2] = 1;
    nodeVertexArray[3][0] = 1;nodeVertexArray[3][3] = 1;
    nodeVertexArray[4][2] = 1;nodeVertexArray[4][3] = 1;
    
    graph A(nodeNodeArray, nodeVertexArray, nodes, verteces);
    
    //-----------------------------------------------------------------
    
    int **nodNode_B, **nodeVertex_B;
    int node_B = 3;
    int verteces_B = 3;
    
    nodNode_B = (int**)malloc(node_B*sizeof(int*));
    for(int i=0;i<node_B;i++){
        nodNode_B[i] = (int*)malloc(node_B*sizeof(int));
        //Zero Initialization 
        for(int j=0;j<node_B;j++){
            nodNode_B[i][j] = 0;
        }
    }
    
    nodNode_B[0][2] = 1;
    nodNode_B[1][2] = 1;
    nodNode_B[0][3] = 1;
    nodNode_B[2][0] = 1;nodNode_B[2][1] = 1;
    
    nodeVertex_B = (int**)malloc(verteces_B*sizeof(int*));
    for(int i=0;i<verteces_B;i++){
        nodeVertex_B[i] = (int*)malloc(node_B*sizeof(int));
        //Zero Initialization 
        for(int j=0;j<node_B;j++){
            nodeVertex_B[i][j] = 0;
        }
    }
    
    nodeVertex_B[0][0] = 1;nodeVertex_B[0][2] = 1;
    nodeVertex_B[1][0] = 1;nodeVertex_B[1][2] = 1;
    nodeVertex_B[2][1] = 1;nodeVertex_B[2][2] = 1;
    
    graph B(nodNode_B, nodeVertex_B, node_B, verteces_B);
    
    cout<<"Graph is minor : "<<isMinor(&A,&B)<<"\n\n";
}

void demoIsPlanar(){
    cout<<"Demo is Planar\n";
    
    int nodes = 5;
    int verteces = 9;
    int **nodeNodeArray, **nodeVertexArray;
    
    nodeNodeArray = (int**)malloc(nodes*sizeof(int*));
    for(int i=0;i<nodes;i++){
        nodeNodeArray[i] = (int*)malloc(nodes*sizeof(int));
        //Zero Initialization 
        for(int j=0;j<nodes;j++){
            nodeNodeArray[i][j] = 0;
        }
    }
    
    nodeNodeArray[0][0] = 0;nodeNodeArray[0][1] = 1;nodeNodeArray[0][2] = 1;nodeNodeArray[0][3] = 1;nodeNodeArray[0][4] = 1;
    nodeNodeArray[1][0] = 1;nodeNodeArray[1][1] = 0;nodeNodeArray[1][2] = 1;nodeNodeArray[1][3] = 1;nodeNodeArray[1][4] = 1;
    nodeNodeArray[2][0] = 1;nodeNodeArray[2][1] = 1;nodeNodeArray[2][2] = 0;nodeNodeArray[2][3] = 1;nodeNodeArray[2][4] = 1;
    nodeNodeArray[3][0] = 1;nodeNodeArray[3][1] = 1;nodeNodeArray[3][2] = 1;nodeNodeArray[3][3] = 0;nodeNodeArray[3][4] = 1;
    nodeNodeArray[4][0] = 1;nodeNodeArray[4][1] = 1;nodeNodeArray[4][2] = 1;nodeNodeArray[4][3] = 1;nodeNodeArray[4][4] = 0;
    
    nodeVertexArray = (int**)malloc(verteces*sizeof(int*));
    for(int i=0;i<verteces;i++){
        nodeVertexArray[i] = (int*)malloc(nodes*sizeof(int));
        //Zero Initialization 
        for(int j=0;j<nodes;j++){
            nodeVertexArray[i][j] = 0;
        }
    }
    
    nodeVertexArray[0][0] = 1;nodeVertexArray[0][1] = 1;
    nodeVertexArray[1][1] = 1;nodeVertexArray[1][2] = 1;
    nodeVertexArray[2][2] = 1;nodeVertexArray[2][3] = 1;
    nodeVertexArray[3][3] = 1;nodeVertexArray[3][4] = 1;
    
    nodeVertexArray[4][0] = 1;nodeVertexArray[4][4] = 1;
    nodeVertexArray[5][0] = 1;nodeVertexArray[5][2] = 1;
    
    nodeVertexArray[6][0] = 1;nodeVertexArray[6][3] = 1;
    nodeVertexArray[7][1] = 1;nodeVertexArray[7][4] = 1;
    nodeVertexArray[8][1] = 1;nodeVertexArray[8][3] = 1;
    
    graph A(nodeNodeArray, nodeVertexArray, nodes, verteces);
    
    cout<<"Graph is planar : "<<isPlanar(&A)<<"\n";
    
}

int main(){
    
    demoIsMinor();
    
    demoIsPlanar();
    
    return 0;
}
