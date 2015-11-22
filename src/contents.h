/*
 * contents.h
 *
 *  Created on: Nov 20, 2015
 *      Author: GaomingPan
 */

#ifndef SRC_CONTENTS_H_
#define SRC_CONTENTS_H_

#include "common.h"

static  char user_name[30];
static  char password[33];

static  long last_session_time = 0;

static char  http_response_header[HTTP_HEADER_LENTH];

static char  http_post_data[MAX_FORM_DATA_LENTH];

static char  http_get_data[MAX_FORM_DATA_LENTH];

static char  property_data[MAX_PROPERTY_DARA_SIZE];


#define  REDIRECT_PAGES "<?xml version=\"1.0\" encoding=\"utf-8\"?> \
	<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\"> \
	<html xmlns=\"http://www.w3.org/1999/xhtml\"> \
	<head> \
	<meta http-equiv=\"refresh\" content=\"0; url=%s\" /> \
	</head>  \
	<body style=\"background-color: black\">  \
	</body> \
	</html>"

#endif /* SRC_CONTENTS_H_ */
