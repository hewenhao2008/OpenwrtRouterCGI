/*
 * do_process.c
 *
 *  Created on: Nov 24, 2015
 *      Author: GaomingPan
 */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "util.h"
#include "contents.h"

#include "do_process.h"


void do_logout()
{
    clean_session();
    fprintf(stdout, "%s", "[\"code\":0]");
}

void do_network_settings(RequestCode reCode)
{
	FILE *fp;
	char  ret[10];

	char argv[MAX_ARRAY_LENTH];

    char wan_proto[MAX_PROPERTY_DARA_SIZE] = {0},
	     wan_ip[MAX_PROPERTY_DARA_SIZE] = {0},
		 wan_netmask[MAX_PROPERTY_DARA_SIZE] = {0},
		 wan_gateway[MAX_PROPERTY_DARA_SIZE] = {0},
		 wan_dns[MAX_PROPERTY_DARA_SIZE] = {0},
		 wan_pppoe_username[MAX_PROPERTY_DARA_SIZE] = {0},
		 wan_pppoe_password[MAX_PROPERTY_DARA_SIZE] = {0};

    char lan_proto[MAX_PROPERTY_DARA_SIZE] = {0},
	     lan_ip[MAX_PROPERTY_DARA_SIZE] = {0},
		 lan_netmask[MAX_PROPERTY_DARA_SIZE] = {0};

    if ( get_post_data_property("wan_proto") )
    	memcpy(wan_proto, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_proto,"%s","dhcp");

    if ( get_post_data_property("wan_ip") )
    	memcpy(wan_ip, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_ip,"%s","192.168.10.100");

    if ( get_post_data_property("wan_netmask") )
    	memcpy(wan_netmask, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_netmask,"%s","255.255.255.0");

    if ( get_post_data_property("wan_dns") )
    	memcpy(wan_dns, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_dns,"%s","114.114.114.114");

    if ( get_post_data_property("wan_gateway") )
    	memcpy(wan_gateway, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_gateway,"%s", "192.168.10.1");

    if ( get_post_data_property("wan_pppoe_username") )
    	memcpy(wan_pppoe_username, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_pppoe_username, "%s", "000000");

    if ( get_post_data_property("wan_pppoe_password") )
    	memcpy(wan_pppoe_password, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wan_pppoe_password, "%s", "12345678");

    if ( get_post_data_property("lan_proto") )
    	memcpy(lan_proto, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(lan_proto, "%s", "static");

    if ( get_post_data_property("lan_ip") )
    	memcpy(lan_ip, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(lan_ip, "%s", "192.168.79.1");

    if ( get_post_data_property("lan_netmask") )
    	memcpy(lan_netmask, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(lan_netmask, "%s", "255.255.255.0");

    switch(reCode){
    case rsWan:
    	sprintf(argv, "%s %s %s %s %s %s %s %s %s",
    			  NETWORK_SETTINGS_SCRIPT,
				  "wan", wan_proto, wan_ip, wan_netmask,
				   wan_gateway, wan_dns, wan_pppoe_username,
				   wan_pppoe_password
    	       );
    	fp = popen(argv, "r");
    	if(!fp){
    		fprintf(stdout, "%s", "{\"result\":1}");
    		return;
    	}
    	fread(ret, 1, 10, fp);
    	pclose(fp);
    	fprintf(stdout, "%s%d%s", "{\"result\":", atol(ret), "}");
    	DEBUG("do_network_settings", argv, atol(ret));
    	return;
    	break;
    case rsLan:
    	sprintf(argv, "%s %s %s %s %s",
    			  NETWORK_SETTINGS_SCRIPT,
				  "lan", lan_proto, lan_ip, wan_netmask
    	       );
    	fp = popen(argv, "r");
    	if(!fp){
    		fprintf(stdout, "%s", "{\"result\":1}");
    		return;
    	}
    	fread(ret, 1, 10, fp);
    	pclose(fp);
    	fprintf(stdout, "%s%d%s", "{\"result\":", atol(ret), "}");
    	return;
    	break;
    default:
    	break;
    }

}


void do_wireless_settings()
{
	FILE *fp;
	char  ret[10];

	char argv[MAX_ARRAY_LENTH];

	char wifi_disabled[MAX_PROPERTY_DARA_SIZE],
	     wifi_ssid[MAX_PROPERTY_DARA_SIZE],
		 wifi_encryption[MAX_PROPERTY_DARA_SIZE],
		 wifi_key[MAX_PROPERTY_DARA_SIZE],
		 wifi_ssid_hidden[MAX_PROPERTY_DARA_SIZE];

    if ( get_post_data_property("disabled") )
    	memcpy(wifi_disabled, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wifi_disabled,"%s","0");

    if ( get_post_data_property("ssid") )
    	memcpy(wifi_ssid, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wifi_ssid,"%s","wifi_pty");

    if ( get_post_data_property("encryption") )
    	memcpy(wifi_encryption, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wifi_encryption,"%s","none");

    if ( get_post_data_property("key") )
    	memcpy(wifi_key, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wifi_key,"%s","12345678");

    if ( get_post_data_property("hidden") )
    	memcpy(wifi_ssid_hidden, property_data, MAX_PROPERTY_DARA_SIZE);
    else
    	sprintf(wifi_ssid_hidden,"%s", "0");

	sprintf(argv, "%s %s %s %s %s %s",
			WIRELESS_SETTINGS_SCRIPT,
			  wifi_disabled, wifi_ssid, wifi_encryption, wifi_key,
			  wifi_ssid_hidden
	       );

	fp = popen(argv, "r");
	if(!fp){
		fprintf(stdout, "%s", "{\"result\":1}");
		return;
	}
	fread(ret, 1, 10, fp);
	pclose(fp);
	fprintf(stdout, "%s%d%s", "{\"result\":", atol(ret), "}");
	DEBUG("do_wireless_settings", argv, atol(ret));
	return;
}


