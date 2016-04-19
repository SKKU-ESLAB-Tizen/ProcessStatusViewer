/*
 * base_gui.h
 * Author: Gyeonghwan Hong
 */

#ifndef BASE_GUI_H_
#define BASE_GUI_H_

#include <app.h>
#include <system_settings.h>
#include <Elementary.h>
#include <efl_extension.h>
#include <dlog.h>
#include "psviewer.h"

#define ICON_DIR "/opt/usr/apps/skku.ospractice.psviewer/res/images"

/* Process Info View Objects */
typedef struct process_info_evas_objs {
	Evas_Object *content;

	app_eobjs_s *mAppEobjs;
} proc_info_eobjs_s;

/* Total Process List Item Data */
typedef struct list_item_evas_objs {
	/* Process list item information */
	int pid;
	char process_name[100];

	/*********************************/

	Elm_Object_Item *mItem;

	app_eobjs_s *mAppEobjs;
} list_item_eobjs_s;

/* Create base GUI */
void create_base_gui(app_eobjs_s *app_eobjs);

/* Create main view */
Evas_Object* create_main_view(app_eobjs_s *app_eobjs);

/* Create base layout */
Evas_Object* create_base_layout(Evas_Object *parent_eobj);

#endif /* BASE_GUI_H_ */
