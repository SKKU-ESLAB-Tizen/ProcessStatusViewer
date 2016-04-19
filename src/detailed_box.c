/*
 * detailed_box.c
 */

#include "detailed_box.h"
#include "common_ui.h"

/* Back button clicked callback */
void back_button_clicked_cb(void *data, Evas_Object * obj, void *event_info) {
	proc_info_eobjs_s *procInfoEobjs = data;
	app_eobjs_s *appEobjs = procInfoEobjs->mAppEobjs;
	elm_naviframe_item_pop(appEobjs->mNaviFrame);
}

void create_detailed_box(list_item_eobjs_s* listItemEobjs) {
	Evas_Object *detailed_box, *backBtn, *scroller, *contentsLabel;
	Elm_Object_Item *detailedNaviFrameItem;
	app_eobjs_s *appEobjs = listItemEobjs->mAppEobjs;

	/* TODO: Retrieve process information from list item */
	int pid = listItemEobjs->pid;
	char* process_name = listItemEobjs->process_name;

	/***********************************************/

	proc_info_eobjs_s *procInfoEobjs = calloc(1, sizeof(proc_info_eobjs_s));
	procInfoEobjs->mAppEobjs = appEobjs;

	scroller = create_scroller(appEobjs->mNaviFrame);

	/* append box */
	detailed_box = create_box(scroller);
	evas_object_size_hint_weight_set(detailed_box, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(detailed_box, EVAS_HINT_FILL,
	EVAS_HINT_FILL);
	elm_box_padding_set(detailed_box, 0, 30);
	elm_object_content_set(scroller, detailed_box);

	/* content */
	/* TODO: Update contents of detailed box */
	char str_buf[1000];
	sprintf(str_buf, "Specific information of process %s (pid %d)\n......",
			process_name, pid);
	contentsLabel = create_label(detailed_box, str_buf);
	/*****************************************/

	evas_object_size_hint_weight_set(contentsLabel, EVAS_HINT_EXPAND,
	EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(contentsLabel, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(detailed_box, contentsLabel);
	procInfoEobjs->content = contentsLabel;

	/* TODO: Update title of detailed box */
	char str_buf2[1000];
	sprintf(str_buf2, "%s (%d)", process_name, pid);
	detailedNaviFrameItem = elm_naviframe_item_push(appEobjs->mNaviFrame,
			str_buf2, NULL, NULL, scroller, NULL);
	/**************************************/

	/* back button */
	backBtn = create_button(appEobjs->mNaviFrame, "naviframe/title_done", NULL);
	evas_object_smart_callback_add(backBtn, "clicked", back_button_clicked_cb,
			procInfoEobjs);
	elm_object_item_part_content_set(detailedNaviFrameItem, "title_left_btn",
			backBtn);
}

