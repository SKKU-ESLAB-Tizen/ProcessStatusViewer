/*
 * side_panel.h
 * Author: Gyeonghwan Hong
 */

#ifndef SIDE_PANEL_H_
#define SIDE_PANEL_H_

#include <Elementary.h>
#include <efl_extension.h>

/* Menu callbacks START */
void total_process_list_cb(void *data, Evas_Object *obj, void *event_info);
void process_tree_cb(void *data, Evas_Object *obj, void *event_info);
/* Menu callbacks END */

/* Create side panel */
Evas_Object* create_side_panel(Evas_Object *parent_eobj);

/* Create side panel list */
Evas_Object* create_side_panel_list(Evas_Object *parent_eobj);

#endif /* SIDE_PANEL_H_ */
