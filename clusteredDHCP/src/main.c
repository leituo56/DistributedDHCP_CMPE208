
//CMPE 208 course project -- clustered DHCP servers     wei zhong 009433424

#include "config.h"
#include "getopt.h"

dhcp_config  dhcpconf;
dhcp_data    dhcpdata;

struct option longopts[] = {
    {"logfile",       REQ_ARGU, NULL, 'l'},
    {"dbpath",        REQ_ARGU, NULL, 'p'},
	{"server",	      REQ_ARGU, NULL, 's'},
	{"loglevel",      REQ_ARGU, NULL, 'd'},
	{"display",		  NO_ARGU , NULL, 't'},
	{"daemon",        NO_ARGU,  NULL, 'D'}, 
};

DHCP_UINT32 start_task(void *ctrl, void * func)
{
    int             err = 0;
    pthread_attr_t  attr;

    err = pthread_attr_init(&attr);
    if (err != 0)
        return(err);
			
    if((err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) != 0)
		return err;
	
    err = pthread_create(NULL, &attr, func, ctrl);
    pthread_attr_destroy(&attr);

    return(err);
}


void handle_sig(int sig_num)
{
    sig_num = sig_num;
    exit_log();
}

void chk_para(dhcp_config *conf)
{
	if(!strlen(conf->db_path))
		strcpy(conf->db_path, DEFAULT_DBPATH);
	
    if(!strlen(conf->log_filename))
		strcpy(conf->log_filename, DEFAULT_DHCP_LOG);

    if(!conf->serverip) {
	    printf("must provide server ip address for this node!\n");
		exit(-1);
	}

	if(!validate_localip(conf->serverip)){
	    printf("server ip not found in this node!\n");
		exit(-1);
	}
}

void load_para(int argc, char **argv)
{
    int  option;
    int  longindex;

	while ((option = getopt_long(argc, argv, "l:p:s:d:tD", longopts, &longindex)) != -1)
    {
        switch (option) {
			case 'l':
				strncpy(dhcpconf.log_filename, optarg, 256);
				break;
			case 'p':
				strncpy(dhcpconf.db_path, optarg, 256);
				break;
			case 's':
				dhcpconf.serverip = inet_addr(optarg);			
				break;
			case 'D':
				dhcpconf.daemon = 1;
				break;
			case 'd':
				dhcpconf.loglevel = atoi(optarg);
				break;
			case 't':
				dhcpconf.display = 1;
				break;				
			default:
				printf("not support\n");			
				exit(-1);
		}
	}
    
}

void register_sig()
{
    signal(SIGINT,  handle_sig);
    signal(SIGABRT, handle_sig);
    signal(SIGTERM, handle_sig);
    signal(SIGQUIT, handle_sig);
    signal(SIGTSTP, handle_sig);
    signal(SIGHUP,  handle_sig);
}

void load_cfg_change()
{
	//TBD
}

int main(int argc, char **argv)
{
	fd_set readfds;

	load_para(argc, argv);
    chk_para(dhcpconf);
	init_log(dhcpconf);
    init_db(dhcpconf);
    init_dhcp_stack(dhcpconf);
    register_sig();

    while(1) {
		poll_sock(dhcpdata, &readfds);
		load_cfg_change();
		dhcpserver(readfds);
	}

	LOG_ERR("should never be here!\n");
}
