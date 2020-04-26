#include"myshell.h"

int redirection(Args args,config *cfg){
    int in_pos=-2,out_pos=-2;
    int in_pos_co=-2,out_pos_co=-2; 
    int range=args.size();
    ofstream out_file;
    ifstream in_file;
    string filename;
    //save IO streambuffer
    streambuf *re_in=cin.rdbuf(),*re_out=cout.rdbuf();
    for(int i=0;i<range;i++){
       if(args[i]=="<"){
            //a redirection symbol is next to another
           if(i-in_pos==1||i-out_pos==1){
                printf("bash: unexpected syntax Error near redirection symbol\n");
                return CMD_CAN_NOT_EXCUTE;
           }
           in_pos=i;
        }
       else if(args[i]==">"||args[i]==">>"){
            if(i-in_pos==1||i-out_pos==1){
                printf("bash: unexpected syntax Error near redirection symbol\n");
                return CMD_CAN_NOT_EXCUTE;
           }
           out_pos=i;
        }
        if(args[i][0]=='<'&&args[i].size()>1){
            if(i-in_pos==1||i-out_pos==1){
                printf("bash: unexpected syntax Error near redirection symbol\n");
                return CMD_CAN_NOT_EXCUTE;
           }
            in_pos_co=i;
        }
        else if(args[i][0]=='>'&&args[i].size()>1){
            if(i-in_pos==1||i-out_pos==1){
                printf("bash: unexpected syntax Error near redirection symbol\n");
                return CMD_CAN_NOT_EXCUTE;
           }
            if(args[i].size()==2&&args[i][1]=='>');
            else out_pos_co=i;
        }
   }
 
    //Behind the redirection symbol is empty
   if(in_pos+1==range||out_pos+1==range){
        printf("bash: unexpected syntax Error near symbol 'newline'\n");
        return CMD_CAN_NOT_EXCUTE;
    }
    //cout<<in_pos_co<<" "<<in_pos<<endl;
    //cout<<out_pos_co<<" "<<out_pos<<endl;

    //I redirection 
    if(in_pos!=-2||in_pos_co!=-2){
        
        if(in_pos>in_pos_co){
            
            in_file.open(args[in_pos+1].c_str());
            if(in_file.fail()){
                printf("Canot open file\n");
                return CMD_CAN_NOT_EXCUTE;
            }
        }
        //redirection symbol with filename
        else if(in_pos<in_pos_co)
        {
            filename= args[in_pos_co].substr(1,args[in_pos_co].size()-1);
            in_file.open(filename.c_str());
            if(in_file.fail()){
                printf("Canot open file\n");
                return CMD_CAN_NOT_EXCUTE;
            }
            
            
        }
        cin.rdbuf(in_file.rdbuf());
    }

    //O redirection 
    if(out_pos!=-2||out_pos_co!=-2){
        
        if(out_pos>out_pos_co){
            if(args[out_pos]==">")
                out_file.open(args[out_pos+1].c_str());
            else if(args[out_pos]==">>")
                out_file.open(args[out_pos+1].c_str(),ios::app);
        }
        //redirection symbol with filename
        else if(out_pos<out_pos_co){
            if(args[out_pos_co].find(">>")==-1){
                filename= args[out_pos_co].substr(1,args[out_pos_co].size()-1);
                
                out_file.open(filename.c_str());
            }
            else {
                filename= args[out_pos_co].substr(2,args[out_pos_co].size()-2);
             
                out_file.open(filename.c_str(),ios::app);
            }
        }
    

        cout.rdbuf(out_file.rdbuf());
    }
    
    //delete redirection symbols and filenames
    bool is_delete=false;
    for(vector<string>::iterator it =args.begin();it!=args.end();){
       if(*it=="<"){
           args.erase(it);
           args.erase(it);
           is_delete=true;
        }
       if(*it==">"||*it==">>"){
           args.erase(it);
           args.erase(it);
           is_delete=true;
        }
        if((*it)[0]=='<'&&(*it).size()>1){
            args.erase(it);
            is_delete=true;
        }
        if((*it)[0]=='>'&&(*it).size()>1){
            args.erase(it);
            is_delete=true;
        }
        if(!is_delete)
            it++;   
        is_delete=false;
   }

    
    int stat=cmd_execute(args,cfg) ;

    //reset IO streambuffer
    cin.rdbuf(re_in);
    cout.rdbuf(re_out);
    in_file.close();
    out_file.close();

    return stat;
}