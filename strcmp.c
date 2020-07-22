
int strcmp(char* s1, char* s2){
    int length = strlen(s1);
    
    for (int i=0; i < length; i++){
        if (s1[i]<s2[i]){
            return "<0";
        } 
        if (s1[i]>s2[i]){
            return ">0"
        }
    }
    return "0"
    

}