//
// Created by vaioco on 08/03/16.
//
#include "parser.h"
static struct config_t* configuration = NULL;


configT_ptr getConfig(){
    return configuration;
}

int get_os_version(){
    if(configuration == NULL) return -1;
    return configuration->osversion;
}
static int parsing_hook_objects(json_value* value, int depth){
    int length,x,i,l;
    json_value* root = NULL;
    json_value* tmp = NULL;
    //meth_hooks_p target;

    length = value->u.array.length;
    for(x = 0; x < length; x++){
        /*
        target = (meth_hooks_p )malloc(sizeof(methods_to_hook_t));
        if( target == NULL){
            LOGG("%s ERROR malloc \n", __PRETTY_FUNCTION__);
            return 1;
        }
        */
        tmp = value->u.array.values[x];
        l = tmp->u.object.length;
        for ( i = 0; i < l ;i++){
            //arthooklog("name: %s  = %s \n", tmp->u.object.values[i].name,tmp->u.object.values[i].value->u.string.ptr );
            ;
        }
        //createInfoTarget(target, tmp, l);
        //addTargetToList(target);
    }
    //targetMethodsListIterator(NULL);
    return 0;
}

static void start_parsing(json_value* value, config_t* c){
    json_value* root = NULL;

    if (value == NULL)
        return;
    if( strcmp(value->u.object.values[0].name, "config") != 0){
        return;
    }
    root = value->u.object.values[0].value; //debug object
    int debug = root->u.object.values[0].value->u.integer;
    c->debug = debug;

    //arthooklog("dexfile vale: %s\n", root->u.object.values[1].name);
    char* dexfile = root->u.object.values[1].value->u.string.ptr;
    //arthooklog("dex target: %s\n", dexfile);
    c->dexfile = (char* )malloc(sizeof(char) * strlen(dexfile) + 1);
    strncpy(c->dexfile, dexfile, strlen(dexfile));
    c->dexfile[strlen(dexfile)] = 0x0;

    //arthooklog("hooks vale: %s\n", root->u.object.values[2].name);
    root = root->u.object.values[2].value;
    parsing_hook_objects(root, 2);
}


int parse_simply(struct config_t* c){
    struct stat file_status;
    int file_size;
    FILE* fp = NULL;
    char* file_contents;
    json_char* json;
    json_value* node;

    if( stat(c->fname, &file_status) != 0 ){
        //LOGG("ERROR stat on %s\n", c->fname);
        return 1;
    }

    file_size = file_status.st_size;
    file_contents = (char*) malloc(file_size);
    if( file_contents == NULL){
        //LOGG("ERROR malloc \n");
        return 1;
    }
    fp = fopen(c->fname, "rt");
    if(!fp){
        //LOGG("ERROR fopen %s \n", c->fname);
        free(file_contents);
        return 1;
    }
    if ( fread(file_contents, file_size,1,fp) != 1){
        //LOGG("ERROR fread\n");
        free(file_contents);
        fclose(fp);
        return 1;
    }
    fclose(fp);
    json = (json_char*) file_contents;
    node = json_parse(json,file_size);
    if(node == NULL){
        //LOGG("ERROR while parsing %s \n", c->fname);
        free(file_contents);
        fclose(fp);
        return 1;
    }
    //process_value(node,0);
    start_parsing(node,c);
    json_value_free(node);
    free(file_contents);
    return 0;

}
static int  program_version(){
    return atoi(VERSION);
}

void* config_init(char* fname){
    char* work_dir;
    //bool zygote = processIsZygote();
    //Logger::printLog("%s called with : %s len %d \n", __PRETTY_FUNCTION__, fname, strlen(fname) );
    /*

    configuration->parser = parse_simply;
    if( configuration->parser(configuration) != 0){
        ;
        //LOGG("ERROR in json parser!!\n");
        //free(c);
        //return NULL;
    }

    configuration->version = program_version();
    int api = (int) getAPIVersion();
    if( api == 1){
        //LOGG("ERROR GETTING API VERSION\n");
        free(configuration);
        return NULL;
    }
    configuration->osversion = api;
    if( _check_runtime() == 0 ){
        //LOGG("ERROR you must set the ART as default runtime!! \n");
        free(configuration);
        return NULL;
    }
    if( !zygote ) {
        configuration->zygote = 0;
        work_dir = ""; //_config_create_env();
        if (work_dir == 0) {
            //LOGG("ERROR CREATE ENV\n");
            free(configuration);
            return NULL;
        }
        //arthooklog("working dir: %s , len = %d \n ", work_dir, strlen(work_dir));
        configuration->optdir = (char*) calloc(strlen(work_dir) + 1, sizeof(char));
        strncpy(configuration->optdir,work_dir,strlen(work_dir));
        configuration->optdir[strlen(work_dir)] = 0x0;
    }else{
        configuration->zygote = 1;
    }

    return configuration;
     */
    return 0;
}