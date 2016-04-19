/*
 * side_panel.c
 * Author: Gyeonghwan Hong
 */
#include "side_panel.h"

/* Menu Configuration START */
#define MENU_NUM 2
const char gMenuNames[MENU_NUM][50] = { "Total Process List", "Process Tree" };

Evas_Smart_Cb gMenuCallbacks[MENU_NUM] = { total_process_list_cb,
		process_tree_cb };
/* Menu Configuration END */

/* Panel scroll callback */
static void panel_scroll_cb(void *data, Evas_Object *obj, void *event_info) {
	Elm_Panel_Scroll_Info *ev = event_info;
	Evas_Object *bg = data;
	int col = 127 * ev->rel_x;
	evas_object_color_set(bg, 0, 0, 0, col);
}

/* Create side panel */
Evas_Object* create_side_panel(Evas_Object *parent_eobj) {
	Evas_Object *panel, *bg;

	panel = elm_panel_add(parent_eobj);
	elm_panel_scrollable_set(panel, EINA_TRUE);
	elm_panel_hidden_set(panel, EINA_TRUE);
	elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);

	bg = evas_object_rectangle_add(evas_object_evas_get(parent_eobj));
	evas_object_color_set(bg, 0, 0, 0, 0);
	elm_object_part_content_set(parent_eobj, "elm.swallow.bg", bg);
	evas_object_show(bg);

	evas_object_smart_callback_add(panel, "scroll", panel_scroll_cb, bg);
	evas_object_show(panel);

	return panel;
}

/* Create side panel list */
Evas_Object* create_side_panel_list(Evas_Object *parent_eobj) {
	Evas_Object *list;

	list = elm_list_add(parent_eobj);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	for (int i = 0; i < MENU_NUM; i++) {
		elm_list_item_append(list, gMenuNames[i], NULL, NULL, gMenuCallbacks[i],
		NULL);
	}

	evas_object_show(list);

	return list;
}
