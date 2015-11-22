/*
 * comm.h
 *
 *  Created on: Nov 19, 2015
 *      Author: GaomingPan
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#define  SESSION_CONF_FILE  "/etc/.ui_info.properties"
#define  PAGES_HOME         "/pages"

#define  SESSION_TIME_OUT        180
#define  MAX_ARRAY_LENTH         2048
#define  HTTP_HEADER_LENTH       1024
#define  MAX_FORM_DATA_LENTH     1024
#define  MAX_PROPERTY_DARA_SIZE  512


#define  PAGE_INDEX     "/index.html"
#define  PAGE_LOGIN     "/pages/login.html"
#define  PAGE_STATUS    "/pages/status.html"

#define  HIDDEN_FORM_ID "page_id"



typedef enum{
	rLogin,
	rStatus,
	rSystem,
	rBadRequest,
	rInvalid,
}RequestCode;


#define  DEBUG(func, msg, code) do{ \
		FILE * fp; \
		char log[1024] = {0}; \
		sprintf(log, "\n\n[<< DEBUG >>] --> f name: %s\n msg: %s\n code: %d\n", func, msg, code); \
        fp = fopen("/dev/console", "w"); \
        if(!fp) \
        	goto err; \
        fwrite(log, 1, strlen(log), fp); \
        fclose(fp); \
        err: ;\
        }while(0)

#endif /* SRC_COMMON_H_ */
